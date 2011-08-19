
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

#include "TextureDict.hpp"

using namespace gdx_cpp::graphics;

TextureRef& TextureDict::loadTexture (const std::string& path) {
    return loadTexture(path, TextureFilter.MipMap, TextureFilter.Linear, TextureWrap.ClampToEdge, TextureWrap.ClampToEdge);
}

TextureRef& TextureDict::loadTexture (const std::string& path,const gdx_cpp::graphics::Texture::TextureFilter& minFilter,const gdx_cpp::graphics::Texture::TextureFilter& magFilter,const gdx_cpp::graphics::Texture::TextureWrap& uwrap,const gdx_cpp::graphics::Texture::TextureWrap& vwrap) {
    if (sDictionary.containsKey(path)) {
        TextureRef ref = sDictionary.get(path);
        ref.addRef();
        return ref;
    }
    // load new texture
    FileHandle texFile = Gdx.app.getFiles().getFileHandle(path, FileType.Internal);
    Texture newTex = new Texture(texFile, minFilter.isMipMap() || magFilter.isMipMap() ? true : false);
    newTex.setFilter(minFilter, magFilter);
    newTex.setWrap(uwrap, vwrap);
    TextureRef ref = new TextureRef(path, newTex);
    sDictionary.put(path, ref);
    return ref;
}

void TextureDict::removeTexture (const std::string& path) {
    sDictionary.remove(path);
}

void TextureDict::unloadAll () {
for (TextureRef tex : sDictionary.values()) {
        tex.dispose();
    }
    sDictionary.clear();
}

