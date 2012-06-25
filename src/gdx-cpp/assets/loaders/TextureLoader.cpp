
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

#include "TextureLoader.hpp"

using namespace gdx;

void TextureLoader::loadAsync (const AssetManager& manager,const std::string& fileName,const TextureParameter& parameter) {
    FileHandle handle = resolve(fileName);
    Pixmap pixmap = new Pixmap(handle);
    Format format = null;
    boolean genMipMaps = false;
    texture = null;

    if (parameter != null) {
        format = parameter.format;
        genMipMaps = parameter.genMipMaps;
        texture = parameter.texture;
    }

    data = new FileTextureData(handle, pixmap, format, genMipMaps);
}

Texture& TextureLoader::loadSync () {
    if (texture != null) {
        texture.load(data);
        return texture;
    } else {
        return new ReferenceCountedTexture(data);
    }
}

ArrayAssetDescriptor& TextureLoader::getDependencies (const std::string& fileName,const TextureParameter& parameter) {
    return null;
}

void TextureLoader::incRefCount () {
    refCount++;
}

int TextureLoader::getRefCount () {
    return refCount;
}

void TextureLoader::dispose () {
    refCount--;
    if (refCount > 0) return;
    super.dispose();
}

