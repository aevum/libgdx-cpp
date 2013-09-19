
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


#include <iostream>
#include <list>
#include <unordered_map>
#include <utility>

#include "gdx-cpp/gl.hpp"

#include "Texture.hpp"
#include "gdx-cpp/Gdx.hpp"
#include "gdx-cpp/Graphics.hpp"
#include "gdx-cpp/Log.hpp"
// #include "gdx-cpp/assets/AssetType.hpp"
#include "gdx-cpp/graphics/GLCommon.hpp"
#include "gdx-cpp/graphics/Pixmap.hpp"
#include "gdx-cpp/graphics/TextureData.hpp"
#include "gdx-cpp/graphics/glutils/MipMapGenerator.hpp"
#include "gdx-cpp/graphics/glutils/PixmapTextureData.hpp"
#include "gdx-cpp/math/MathUtils.hpp"



namespace gdx {
class Application;
class AssetManager;
}  // namespace gdx

using namespace gdx;

const Texture::TextureWrap Texture::TextureWrap::ClampToEdge = Texture::TextureWrap(gdx::GL::CLAMP_TO_EDGE);
const Texture::TextureWrap Texture::TextureWrap::Repeat = Texture::TextureWrap(gdx::GL::REPEAT);

const Texture::TextureFilter Texture::TextureFilter::Nearest = Texture::TextureFilter(gdx::GL::NEAREST);
const Texture::TextureFilter Texture::TextureFilter::Linear = Texture::TextureFilter(gdx::GL::LINEAR);
const Texture::TextureFilter Texture::TextureFilter::MipMap = Texture::TextureFilter(gdx::GL::LINEAR_MIPMAP_LINEAR);
const Texture::TextureFilter Texture::TextureFilter::MipMapNearestNearest = Texture::TextureFilter(gdx::GL::NEAREST_MIPMAP_NEAREST);
const Texture::TextureFilter Texture::TextureFilter::MipMapLinearNearest = Texture::TextureFilter(gdx::GL::LINEAR_MIPMAP_NEAREST);
const Texture::TextureFilter Texture::TextureFilter::MipMapNearestLinear = Texture::TextureFilter(gdx::GL::NEAREST_MIPMAP_LINEAR);
const Texture::TextureFilter Texture::TextureFilter::MipMapLinearLinear = Texture::TextureFilter(gdx::GL::LINEAR_MIPMAP_LINEAR);

Texture::managedTextureMap Texture::managedTextures;
unsigned int Texture::buffer = 0;
AssetManager* Texture::assetManager = nullptr;

Texture::ptr Texture::newFromFile(const FileHandle::ptr& file,
                                  const Pixmap::Format* format,
                                  bool useMipMaps)
{
    ptr newTex = ptr(new Texture);
    newTex->initialize(file, format, useMipMaps);

    return newTex;
}

void Texture::create (const TextureData::ptr& data) {
    this->glHandle = 0;
    this->enforcePotImages = true;
    this->useHWMipMap = true;
    this->assetManager = nullptr;

    glHandle = createGLHandle();
    std::cerr << glHandle;
    load(data);

    if (data->isManaged()) {
        addManagedTexture(app, Texture::ptr(shared_from_this()));
    }
}

int Texture::createGLHandle () {
    gl->glGenTextures(1, &buffer);
    return buffer;
}

void Texture::load (const TextureData::ptr& data) {
    if (this->data && data->isManaged() != this->data->isManaged()) {
        gdx_log_error("Texture.cpp", "New data must have the same managed status as the old data");
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
        gl->glBindTexture(gdx::GL::TEXTURE_2D, glHandle);
        data->uploadCompressedData();
        setFilter(minFilter, magFilter);
        setWrap(uWrap, vWrap);
    }
}

void Texture::uploadImageData (const Pixmap::ptr& pixmap) {
    if (enforcePotImages && gl20 == nullptr
            && (! isPowerOfTwo(data->getWidth()) || !isPowerOfTwo(data->getHeight())))
    {
        gdx_log_error("gdx","Texture.cpp: texture width and height must be powers of two");
    }

    bool disposePixmap = false;

    Pixmap::ptr tmp = pixmap;

    if (*data->getFormat() != pixmap->getFormat()) {
        tmp = Pixmap::newFromPixmap(*pixmap);
        tmp->drawPixmap(*pixmap, 0, 0, 0, 0, pixmap->getWidth(), pixmap->getHeight());
        disposePixmap = true;
    }

    gl->glBindTexture(gdx::GL::TEXTURE_2D, glHandle);
    gl->glPixelStorei(gdx::GL::UNPACK_ALIGNMENT, 1);
    if (data->useMipMaps()) {
        MipMapGenerator::generateMipMap(tmp, tmp->getWidth(), tmp->getHeight(), disposePixmap);
    } else {
        gl->glTexImage2D(gdx::GL::TEXTURE_2D, 0, tmp->getGLInternalFormat(), tmp->getWidth(), tmp->getHeight(), 0,
                              tmp->getGLFormat(), tmp->getGLType(), tmp->getPixels());

        if (disposePixmap) tmp->dispose();
    }
}

void Texture::reload () {
    if (!data->isManaged()) {
        gdx_log_error(__FILE__, "Tried to reload unmanaged Texture");
    }

    createGLHandle();
    load(data);
}

void Texture::bind () {
    gl->glBindTexture(gdx::GL::TEXTURE_2D, glHandle);
}

void Texture::bind (int unit) {
    gl->glActiveTexture(gdx::GL::TEXTURE0 + unit);
    gl->glBindTexture(gdx::GL::TEXTURE_2D, glHandle);
}

void Texture::draw (Pixmap& pixmap,int x,int y) {
    if (data->isManaged()) {
        gdx_log_error(__FILE__ , "can't draw to a managed texture");
    }

    gl->glBindTexture(gdx::GL::TEXTURE_2D, glHandle);
    gl->glTexSubImage2D(gdx::GL::TEXTURE_2D, 0, x, y, pixmap.getWidth(), pixmap.getHeight(), pixmap.getGLFormat(),
                             pixmap.getGLType(), (const unsigned char*) pixmap.getPixels());
}

int Texture::getWidth () const {
    return data->getWidth();
}

int Texture::getHeight () const {
    return data->getHeight();
}

const Texture::TextureFilter& Texture::getMinFilter () const {
    return minFilter;
}

const Texture::TextureFilter& Texture::getMagFilter () const {
    return magFilter;
}

const Texture::TextureWrap& Texture::getUWrap () const {
    return uWrap;
}

const Texture::TextureWrap& Texture::getVWrap () const {
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

void Texture::setWrap (const Texture::TextureWrap& u, const Texture::TextureWrap& v) {
    this->uWrap = u;
    this->vWrap = v;
    bind();
    gl->glTexParameterf(gdx::GL::TEXTURE_2D, gdx::GL::TEXTURE_WRAP_S, u.getGLEnum());
    gl->glTexParameterf(gdx::GL::TEXTURE_2D, gdx::GL::TEXTURE_WRAP_T, v.getGLEnum());
}

void Texture::setFilter (const Texture::TextureFilter& minFilter, const Texture::TextureFilter& magFilter) {
    this->minFilter = minFilter;
    this->magFilter = magFilter;
    bind();
    gl->glTexParameterf(gdx::GL::TEXTURE_2D, gdx::GL::TEXTURE_MIN_FILTER, minFilter.getGLEnum());
    gl->glTexParameterf(gdx::GL::TEXTURE_2D, gdx::GL::TEXTURE_MAG_FILTER, magFilter.getGLEnum());
}

void Texture::dispose () {
    if (glHandle != 0) {
        gl->glDeleteTextures(1, &glHandle);

        if (data->isManaged()) {
//                 managedTextures[app].remove();
        }

        glHandle = 0;
    }
}

void Texture::setEnforcePotImages (bool enforcePotImages) {
    Texture::enforcePotImages = enforcePotImages;
}

void Texture::addManagedTexture (Application* app, const Texture::ptr& texture) {
    managedTextures[app].push_back(Texture::weak_ptr(texture));
}

void Texture::clearAllTextures (Application* app) {
    managedTextures.erase(app);
}

void Texture::invalidateAllTextures (Application* app) {
    textureList& managedTexureList = managedTextures[app];

    if (assetManager == nullptr) {
        auto it = managedTexureList.begin();
        auto end = managedTexureList.end();

        for (; it != end; it++) {
            it->lock()->reload();
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
//                 TextureParameter::ptr params;
//                 params->format = (*it)->getTextureData()->getFormat();
//                 params->genMipMaps = (*it)->getTextureData()->useMipMaps();
//                 params->texture = *it;
//                 (*it)->glHandle = Texture::createGLHandle();
//                 assetManager->remove(filename);
//                 assetManager->preload(filename, AssetType::Texture, params);
//             }
//             managedTexureList.push_back(*it);
//         }
    }
}

void Texture::setAssetManager (AssetManager* manager) {
    Texture::assetManager = manager;
}

std::string Texture::getManagedStatus () {
    std::stringstream builder;
    builder << "Managed textures/app: { ";

    auto it = managedTextures.begin();
    auto end = managedTextures.end();

    for(; it != end; it++) {
        builder << it->second.size() << " ";
    }
    builder << "}";

    return builder.str();
}

Texture::Texture(const TextureData::ptr& data)
    :
    minFilter(TextureFilter::Nearest),
magFilter(TextureFilter::Nearest),
uWrap(TextureWrap::ClampToEdge),
vWrap(TextureWrap::ClampToEdge)
{
    create(data);
}

Texture::Texture(int width, int height, const Pixmap::Format& format, Pixmap::PixmapType pixType)
    :
    minFilter(TextureFilter::Nearest),
magFilter(TextureFilter::Nearest),
uWrap(TextureWrap::ClampToEdge),
vWrap(TextureWrap::ClampToEdge)
{
    Pixmap::ptr pixmap = Pixmap::newFromRect(width, height, format, pixType);
    PixmapTextureData::ptr ptd(new PixmapTextureData(pixmap, nullptr, false, true));
    create(ptd);
}

Texture::Texture(Pixmap::ptr pixmap, const Pixmap::Format& format, bool useMipMaps)
    :
    minFilter(TextureFilter::Nearest),
magFilter(TextureFilter::Nearest),
uWrap(TextureWrap::ClampToEdge),
vWrap(TextureWrap::ClampToEdge)
{
    create(PixmapTextureData::ptr(new PixmapTextureData(pixmap, &format, useMipMaps, false)));
}

Texture::Texture()
    :
    minFilter(TextureFilter::Nearest),
magFilter(TextureFilter::Nearest),
uWrap(TextureWrap::ClampToEdge),
vWrap(TextureWrap::ClampToEdge)
{
}

Texture::Texture(const Pixmap::ptr& pixmap, bool useMipMaps)
    :
    minFilter(TextureFilter::Nearest),
magFilter(TextureFilter::Nearest),
uWrap(TextureWrap::ClampToEdge),
vWrap(TextureWrap::ClampToEdge)
{
    create(PixmapTextureData::ptr(new PixmapTextureData(pixmap, nullptr , useMipMaps, false)));
}

void Texture::initialize(const FileHandle::ptr& file, const Pixmap::Format* format, bool useMipMaps)
{
    this->glHandle = 0;
    this->enforcePotImages = true;
    this->useHWMipMap = true;
    this->assetManager = nullptr;

    create(TextureData::ptr(graphics->resolveTextureData(file, nullptr, format, useMipMaps)));
}

Texture::~Texture()
{
    dispose();
}

bool Texture::TextureFilter::isMipMap() {
    return glEnum != gdx::GL::NEAREST && glEnum != gdx::GL::LINEAR;
}



