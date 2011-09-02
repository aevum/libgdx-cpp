
/*
    Copyright 2011 Aevum Software aevum @ aevumlab.com

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.

    @author Victor Vicente de Carvalho victor.carvalho@aevumlab.com
    @author Ozires Bortolon de Faria ozires@aevumlab.com
*/

#include "Texture.hpp"

#include "gdx-cpp/Gdx.hpp"
#include "gdx-cpp/graphics/Pixmap.hpp"
#include "gdx-cpp/math/MathUtils.hpp"
#include "GL10.hpp"
#include "gdx-cpp/graphics/glutils/MipMapGenerator.hpp"
#include "gdx-cpp/assets/AssetLoaderParameters.hpp"
#include "gdx-cpp/assets/loaders/TextureParameter.hpp"
#include "gdx-cpp/graphics/glutils/PixmapTextureData.hpp"

#include <list>
#include <sstream>
#include "glutils/FileTextureData.hpp"

using namespace gdx_cpp::graphics;
using namespace gdx_cpp;

const Texture::TextureWrap Texture::TextureWrap::ClampToEdge = Texture::TextureWrap(GL10::GL_CLAMP_TO_EDGE);
const Texture::TextureWrap Texture::TextureWrap::Repeat = Texture::TextureWrap(GL10::GL_REPEAT);

const Texture::TextureFilter Texture::TextureFilter::Nearest = Texture::TextureFilter(GL10::GL_NEAREST);
const Texture::TextureFilter Texture::TextureFilter::Linear = Texture::TextureFilter(GL10::GL_LINEAR);
const Texture::TextureFilter Texture::TextureFilter::MipMap = Texture::TextureFilter(GL10::GL_LINEAR_MIPMAP_LINEAR);
const Texture::TextureFilter Texture::TextureFilter::MipMapNearestNearest = Texture::TextureFilter(GL10::GL_NEAREST_MIPMAP_NEAREST);
const Texture::TextureFilter Texture::TextureFilter::MipMapLinearNearest = Texture::TextureFilter(GL10::GL_LINEAR_MIPMAP_NEAREST);
const Texture::TextureFilter Texture::TextureFilter::MipMapNearestLinear = Texture::TextureFilter(GL10::GL_NEAREST_MIPMAP_LINEAR);
const Texture::TextureFilter Texture::TextureFilter::MipMapLinearLinear = Texture::TextureFilter(GL10::GL_LINEAR_MIPMAP_LINEAR);

Texture::managedTextureMap Texture::managedTextures;
int Texture::buffer = 0;
assets::AssetManager* Texture::assetManager = 0;

void Texture::create (TextureData::ptr data) {
    this->glHandle = 0;
    this->enforcePotImages = true;
    this->useHWMipMap = true;
    this->assetManager = 0;
    
    glHandle = createGLHandle();
    load(data);
    if (data->isManaged()) addManagedTexture(gdx_cpp::Gdx::app, shared_from_this());
}

int Texture::createGLHandle () {
    Gdx::gl->glGenTextures(1, &buffer);
    return buffer;
}

void Texture::load (const TextureData::ptr& data) {
    if (this->data != NULL && data->isManaged() != this->data->isManaged()) {
        Gdx::app->error("Texture.cpp") << "New data must have the same managed status as the old data";
    }

    this->data = data;

    if (data->getType() == TextureData::TextureDataType::Pixmap) {
        Pixmap::ptr pixmap = data->getPixmap();
        uploadImageData(pixmap);
        if (data->disposePixmap()) pixmap->dispose();
        setFilter(minFilter, magFilter);
        setWrap(uWrap, vWrap);
    }

    if (data->getType() == TextureData::TextureDataType::Compressed) {
        Gdx::gl->glBindTexture(GL10::GL_TEXTURE_2D, glHandle);
        data->uploadCompressedData();
        setFilter(minFilter, magFilter);
        setWrap(uWrap, vWrap);
    }
}

void Texture::uploadImageData (const gdx_cpp::graphics::Pixmap::ptr pixmap) {
    if (enforcePotImages && Gdx::gl20 == NULL
            && (! gdx_cpp::math::utils::isPowerOfTwo(data->getWidth()) || !gdx_cpp::math::utils::isPowerOfTwo(data->getHeight())))
    {
        Gdx::app->error("Texture.cpp") << "texture width and height must be powers of two";
    }

    bool disposePixmap = false;

    Pixmap::ptr tmp = pixmap;
    
    if (*data->getFormat() != pixmap->getFormat()) {
        tmp = Pixmap::ptr(new Pixmap(pixmap->getWidth(), pixmap->getHeight(), *data->getFormat()));
        Pixmap::Blending blend = Pixmap::getBlending();
        Pixmap::setBlending(Pixmap::None);
        tmp->drawPixmap(*pixmap, 0, 0, 0, 0, pixmap->getWidth(), pixmap->getHeight());
        Pixmap::setBlending(blend);
        disposePixmap = true;
    }

    Gdx::gl->glBindTexture(GL10::GL_TEXTURE_2D, glHandle);
    if (data->useMipMaps()) {
        glutils::MipMapGenerator::generateMipMap(*tmp, tmp->getWidth(), tmp->getHeight(), disposePixmap);
    } else {
        Gdx::gl->glTexImage2D(GL10::GL_TEXTURE_2D, 0, tmp->getGLInternalFormat(), tmp->getWidth(), tmp->getHeight(), 0,
                            tmp->getGLFormat(), tmp->getGLType(), tmp->getPixels());
        if (disposePixmap) tmp->dispose();
    }
}

void Texture::reload () {
    if (!data->isManaged()) {
        gdx_cpp::Gdx::app->error(__FILE__) << "Tried to reload unmanaged Texture";
    }
    
    createGLHandle();
    load(data);
}

void Texture::bind () {
    Gdx::gl->glBindTexture(GL10::GL_TEXTURE_2D, glHandle);
}

void Texture::bind (int unit) {
    Gdx::gl->glActiveTexture(GL10::GL_TEXTURE0 + unit);
    Gdx::gl->glBindTexture(GL10::GL_TEXTURE_2D, glHandle);
}

void Texture::draw (const Pixmap& pixmap,int x,int y) {
    if (data->isManaged()){
        gdx_cpp::Gdx::app->error(__FILE__) << "can't draw to a managed texture";
    }

    Gdx::gl->glBindTexture(GL10::GL_TEXTURE_2D, glHandle);
    Gdx::gl->glTexSubImage2D(GL10::GL_TEXTURE_2D, 0, x, y, pixmap.getWidth(), pixmap.getHeight(), pixmap.getGLFormat(),
                           pixmap.getGLType(), pixmap.getPixels());
}

int Texture::getWidth () const {
    return data->getWidth();
}

int Texture::getHeight () const {
    return data->getHeight();
}

const gdx_cpp::graphics::Texture::TextureFilter& Texture::getMinFilter () const {
    return minFilter;
}

const gdx_cpp::graphics::Texture::TextureFilter& Texture::getMagFilter () const {
    return magFilter;
}

const gdx_cpp::graphics::Texture::TextureWrap& Texture::getUWrap () const {
    return uWrap;
}

const gdx_cpp::graphics::Texture::TextureWrap& Texture::getVWrap () const {
    return vWrap;
}

TextureData::ptr Texture::getTextureData () {
    return data;
}

bool Texture::isManaged () {
    return data->isManaged();
}

int Texture::getTextureObjectHandle () {
    return glHandle;
}

void Texture::setWrap (const gdx_cpp::graphics::Texture::TextureWrap& u, const gdx_cpp::graphics::Texture::TextureWrap& v) {
    this->uWrap = u;
    this->vWrap = v;
    bind();
    Gdx::gl->glTexParameterf(GL10::GL_TEXTURE_2D, GL10::GL_TEXTURE_WRAP_S, u.getGLEnum());
    Gdx::gl->glTexParameterf(GL10::GL_TEXTURE_2D, GL10::GL_TEXTURE_WRAP_T, v.getGLEnum());
}

void Texture::setFilter (const gdx_cpp::graphics::Texture::TextureFilter& minFilter, const gdx_cpp::graphics::Texture::TextureFilter& magFilter) {
    this->minFilter = minFilter;
    this->magFilter = magFilter;
    bind();
    Gdx::gl->glTexParameterf(GL10::GL_TEXTURE_2D, GL10::GL_TEXTURE_MIN_FILTER, minFilter.getGLEnum());
    Gdx::gl->glTexParameterf(GL10::GL_TEXTURE_2D, GL10::GL_TEXTURE_MAG_FILTER, magFilter.getGLEnum());
}

void Texture::dispose () {
    buffer = glHandle;
    Gdx::gl->glDeleteTextures(1, &buffer);
    
    if (data->isManaged()) {
        if (managedTextures.count(Gdx::app))
            managedTextures[Gdx::app].remove(shared_from_this());
    }
}

void Texture::setEnforcePotImages (bool enforcePotImages) {
    Texture::enforcePotImages = enforcePotImages;
}

void Texture::addManagedTexture (gdx_cpp::Application* app,const Texture::ptr texture) {
    managedTextures[app].push_back(texture);
}

void Texture::clearAllTextures (gdx_cpp::Application* app) {
    managedTextures.erase(app);
}

const assets::AssetType& Texture::getAssetType()
{
    return assets::AssetType::Texture;
}

void Texture::invalidateAllTextures (gdx_cpp::Application* app) {
    textureList& managedTexureList = managedTextures[app];

    if (assetManager == NULL) {
        textureList::iterator it = managedTexureList.begin();
        textureList::iterator end = managedTexureList.end();
       
        for (; it != end; it++) {
            (*it)->reload();
        }
    } else {
//         textureList t(managedTexureList);
// 
//         managedTexureList.clear();
// 
//         textureList::iterator it = t.begin();
//         textureList::iterator end = t.end();
// 
//         std::string filename;
//         
//         for (; it != end; ++it) {           
//             if (!assetManager->getAssetFileName((Asset&) *it, filename)) {
//                 (*it)->reload();
//             } else {
//                 assets::loaders::TextureParameter::ptr params;
//                 params->format = (*it)->getTextureData()->getFormat();
//                 params->genMipMaps = (*it)->getTextureData()->useMipMaps();
//                 params->texture = *it;
//                 (*it)->glHandle = Texture::createGLHandle();
//                 assetManager->remove(filename);
//                 assetManager->preload(filename, assets::AssetType::Texture, params);
//             }
//             managedTexureList.push_back(*it);
//         }
    }
}

void Texture::setAssetManager (gdx_cpp::assets::AssetManager* manager) {
    Texture::assetManager = manager;
}

std::string Texture::getManagedStatus () {
    std::stringstream builder;
    builder << "Managed textures/app: { ";

    managedTextureMap::iterator it = managedTextures.begin();
    managedTextureMap::iterator end = managedTextures.end();

    for(; it != end; it++) {
        builder << it->second.size() << " ";
    }
    builder << "}";
    
    return builder.str();
}

Texture::Texture(const TextureData::ptr data)
:
minFilter(TextureFilter::Nearest)
,magFilter(TextureFilter::Nearest)
,uWrap(TextureWrap::ClampToEdge)
,vWrap(TextureWrap::ClampToEdge)
{
    create(data);
}

Texture::Texture(int width, int height, const Pixmap::Format& format)
:
minFilter(TextureFilter::Nearest)
,magFilter(TextureFilter::Nearest)
,uWrap(TextureWrap::ClampToEdge)
,vWrap(TextureWrap::ClampToEdge)
{
    Pixmap::ptr pixmap(new Pixmap(width, height, format));
    glutils::PixmapTextureData::ptr ptd(new glutils::PixmapTextureData(pixmap, NULL, false, true));
    create(ptd);
}

Texture::Texture(Pixmap::ptr pixmap, const Pixmap::Format& format, bool useMipMaps)
:
minFilter(TextureFilter::Nearest)
,magFilter(TextureFilter::Nearest)
,uWrap(TextureWrap::ClampToEdge)
,vWrap(TextureWrap::ClampToEdge)
{
    create(glutils::PixmapTextureData::ptr(new glutils::PixmapTextureData(pixmap, &format, useMipMaps, false)));
}

Texture::Texture(const gdx_cpp::files::FileHandle& file, bool useMipMaps)
:
minFilter(TextureFilter::Nearest)
,magFilter(TextureFilter::Nearest)
,uWrap(TextureWrap::ClampToEdge)
,vWrap(TextureWrap::ClampToEdge)
{
    initialize(file, NULL, useMipMaps);
}

Texture::Texture(const gdx_cpp::files::FileHandle& file,const Pixmap::Format& format, bool useMipMaps)
:
minFilter(TextureFilter::Nearest)
,magFilter(TextureFilter::Nearest)
,uWrap(TextureWrap::ClampToEdge)
,vWrap(TextureWrap::ClampToEdge)
{
   initialize(file, &format, useMipMaps);
}

Texture::Texture(const gdx_cpp::files::FileHandle file)
:
minFilter(TextureFilter::Nearest)
,magFilter(TextureFilter::Nearest)
,uWrap(TextureWrap::ClampToEdge)
,vWrap(TextureWrap::ClampToEdge)
{
    initialize(file, NULL, false);
}

Texture::Texture(const Pixmap& pixmap, bool useMipMaps)
:
minFilter(TextureFilter::Nearest)
,magFilter(TextureFilter::Nearest)
,uWrap(TextureWrap::ClampToEdge)
,vWrap(TextureWrap::ClampToEdge)
{
    Gdx::files::internal(internalPath);
}

void Texture::initialize(const gdx_cpp::files::FileHandle& file,const Pixmap::Format* format, bool useMipMaps)
{
    this->glHandle = 0;
    this->enforcePotImages = true;
    this->useHWMipMap = true;
    this->assetManager = 0;

    std::string s = file.name();
    std::string suffix(".etc1");
    int found = s.rfind(suffix);
    if( found != s.npos && (found == (s.length() - suffix.length()) ) ){
         create(new ETC1TextureData(file, useMipMaps));
     } else {
         create(new glutils::FileTextureData(file, NULL, format, useMipMaps));
     }
}

