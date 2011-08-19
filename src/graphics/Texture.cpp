
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

using namespace gdx_cpp::graphics;

bool Texture::isMipMap () {
    return glEnum != GL10.GL_NEAREST && glEnum != GL10.GL_LINEAR;
}

int Texture::getGLEnum () {
    return glEnum;
}

int Texture::getGLEnum () {
    return glEnum;
}

void Texture::create (const TextureData& data) {
    glHandle = createGLHandle();
    load(data);
    if (data.isManaged()) addManagedTexture(Gdx.app, this);
}

int Texture::createGLHandle () {
    buffer.position(0);
    buffer.limit(buffer.capacity());
    Gdx.gl.glGenTextures(1, buffer);
    return buffer.get(0);
}

void Texture::load (const TextureData& data) {
    if (this.data != null && data.isManaged() != this.data.isManaged())
        throw new GdxRuntimeException("New data must have the same managed status as the old data");
    this.data = data;

    if (data.getType() == TextureDataType.Pixmap) {
        Pixmap pixmap = data.getPixmap();
        uploadImageData(pixmap);
        if (data.disposePixmap()) pixmap.dispose();
        setFilter(minFilter, magFilter);
        setWrap(uWrap, vWrap);
    }

    if (data.getType() == TextureDataType.Compressed) {
        Gdx.gl.glBindTexture(GL10.GL_TEXTURE_2D, glHandle);
        data.uploadCompressedData();
        setFilter(minFilter, magFilter);
        setWrap(uWrap, vWrap);
    }
}

void Texture::uploadImageData (const Pixmap& pixmap) {
    if (enforcePotImages && Gdx.gl20 == null
            && (!MathUtils.isPowerOfTwo(data.getWidth()) || !MathUtils.isPowerOfTwo(data.getHeight())))
        throw new GdxRuntimeException("texture width and height must be powers of two");

    boolean disposePixmap = false;
    if (data.getFormat() != pixmap.getFormat()) {
        Pixmap tmp = new Pixmap(pixmap.getWidth(), pixmap.getHeight(), data.getFormat());
        Blending blend = Pixmap.getBlending();
        Pixmap.setBlending(Blending.None);
        tmp.drawPixmap(pixmap, 0, 0, 0, 0, pixmap.getWidth(), pixmap.getHeight());
        Pixmap.setBlending(blend);
        pixmap = tmp;
        disposePixmap = true;
    }

    Gdx.gl.glBindTexture(GL10.GL_TEXTURE_2D, glHandle);
    if (data.useMipMaps()) {
        MipMapGenerator.generateMipMap(pixmap, pixmap.getWidth(), pixmap.getHeight(), disposePixmap);
    } else {
        Gdx.gl.glTexImage2D(GL10.GL_TEXTURE_2D, 0, pixmap.getGLInternalFormat(), pixmap.getWidth(), pixmap.getHeight(), 0,
                            pixmap.getGLFormat(), pixmap.getGLType(), pixmap.getPixels());
        if (disposePixmap) pixmap.dispose();
    }
}

void Texture::reload () {
    if (!data.isManaged()) throw new GdxRuntimeException("Tried to reload unmanaged Texture");
    createGLHandle();
    load(data);
}

void Texture::bind () {
    Gdx.gl.glBindTexture(GL10.GL_TEXTURE_2D, glHandle);
}

void Texture::bind (int unit) {
    Gdx.gl.glActiveTexture(GL10.GL_TEXTURE0 + unit);
    Gdx.gl.glBindTexture(GL10.GL_TEXTURE_2D, glHandle);
}

void Texture::draw (const Pixmap& pixmap,int x,int y) {
    if (data.isManaged()) throw new GdxRuntimeException("can't draw to a managed texture");

    Gdx.gl.glBindTexture(GL10.GL_TEXTURE_2D, glHandle);
    Gdx.gl.glTexSubImage2D(GL10.GL_TEXTURE_2D, 0, x, y, pixmap.getWidth(), pixmap.getHeight(), pixmap.getGLFormat(),
                           pixmap.getGLType(), pixmap.getPixels());
}

int Texture::getWidth () {
    return data.getWidth();
}

int Texture::getHeight () {
    return data.getHeight();
}

TextureFilter& Texture::getMinFilter () {
    return minFilter;
}

TextureFilter& Texture::getMagFilter () {
    return magFilter;
}

TextureWrap& Texture::getUWrap () {
    return uWrap;
}

TextureWrap& Texture::getVWrap () {
    return vWrap;
}

TextureData& Texture::getTextureData () {
    return data;
}

bool Texture::isManaged () {
    return data.isManaged();
}

int Texture::getTextureObjectHandle () {
    return glHandle;
}

void Texture::setWrap (const TextureWrap& u,const TextureWrap& v) {
    this.uWrap = u;
    this.vWrap = v;
    bind();
    Gdx.gl.glTexParameterf(GL10.GL_TEXTURE_2D, GL10.GL_TEXTURE_WRAP_S, u.getGLEnum());
    Gdx.gl.glTexParameterf(GL10.GL_TEXTURE_2D, GL10.GL_TEXTURE_WRAP_T, v.getGLEnum());
}

void Texture::setFilter (const TextureFilter& minFilter,const TextureFilter& magFilter) {
    this.minFilter = minFilter;
    this.magFilter = magFilter;
    bind();
    Gdx.gl.glTexParameterf(GL10.GL_TEXTURE_2D, GL10.GL_TEXTURE_MIN_FILTER, minFilter.getGLEnum());
    Gdx.gl.glTexParameterf(GL10.GL_TEXTURE_2D, GL10.GL_TEXTURE_MAG_FILTER, magFilter.getGLEnum());
}

void Texture::dispose () {
    buffer.put(0, glHandle);
    Gdx.gl.glDeleteTextures(1, buffer);
    if (data.isManaged()) {
        if (managedTextures.get(Gdx.app) != null) managedTextures.get(Gdx.app).remove(this);
    }
}

void Texture::setEnforcePotImages (bool enforcePotImages) {
    Texture.enforcePotImages = enforcePotImages;
}

void Texture::addManagedTexture (const gdx_cpp::Application& app,const Texture& texture) {
    List<Texture> managedTexureList = managedTextures.get(app);
    if (managedTexureList == null) managedTexureList = new ArrayList<Texture>();
    managedTexureList.add(texture);
    managedTextures.put(app, managedTexureList);
}

void Texture::clearAllTextures (const gdx_cpp::Application& app) {
    managedTextures.remove(app);
}

void Texture::invalidateAllTextures (const gdx_cpp::Application& app) {
    List<Texture> managedTexureList = managedTextures.get(app);
    if (managedTexureList == null) return;

    if (assetManager == null) {
        for (int i = 0; i < managedTexureList.size(); i++) {
            Texture texture = managedTexureList.get(i);
            texture.reload();
        }
    } else {
        List<Texture> textures = new ArrayList<Texture>(managedTexureList);
        managedTexureList.clear();
for (Texture texture : textures) {
            String fileName = assetManager.getAssetFileName(texture);
            if (fileName == null) {
                texture.reload();
            } else {
                TextureParameter params = new TextureParameter();
                params.format = texture.getTextureData().getFormat();
                params.genMipMaps = texture.getTextureData().useMipMaps();
                params.texture = texture;
                texture.glHandle = Texture.createGLHandle();
                assetManager.remove(fileName);
                assetManager.preload(fileName, Texture.class, params);
            }
            managedTexureList.add(texture);
        }
    }
}

void Texture::setAssetManager (const gdx_cpp::assets::AssetManager& manager) {
    Texture.assetManager = manager;
}

std::string& Texture::getManagedStatus () {
    StringBuilder builder = new StringBuilder();
    builder.append("Managed textures/app: { ");
for (Application app : managedTextures.keySet()) {
        builder.append(managedTextures.get(app).size());
        builder.append(" ");
    }
    builder.append("}");
    return builder.toString();
}

