
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

#include "TextureAtlasLoader.hpp"

using namespace gdx_cpp::assets::loaders;

gdx_cpp::graphics::g2d::TextureAtlas& TextureAtlasLoader::load (const gdx_cpp::assets::AssetManager& assetManager,const std::string& fileName,const TextureAtlasParameter& parameter) {
for (Page page : data.getPages()) {
        Texture texture = assetManager.get(page.textureFile.path().replaceAll("\\\\", "/"), Texture.class);
        page.texture = texture;
    }

    return new TextureAtlas(data);
}

gdx_cpp::utils::ArrayAssetDescriptor>& TextureAtlasLoader::getDependencies (const std::string& fileName,const TextureAtlasParameter& parameter) {
    FileHandle atlasFile = resolve(fileName);
    FileHandle imgDir = atlasFile.parent();

    if (parameter != null)
        data = new TextureAtlasData(atlasFile, imgDir, parameter.flip);
    else
        data = new TextureAtlasData(atlasFile, imgDir, false);

    Array<AssetDescriptor> dependencies = new Array<AssetDescriptor>();
for (Page page : data.getPages()) {
        FileHandle handle = resolve(page.textureFile.path());
        TextureParameter params = new TextureParameter();
        params.format = page.format;
        params.genMipMaps = page.useMipMaps;
        dependencies.add(new AssetDescriptor(handle.path().replaceAll("\\\\", "/"), Texture.class, params));
    }
    return dependencies;
}

