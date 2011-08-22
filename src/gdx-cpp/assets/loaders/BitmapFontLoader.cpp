
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

#include "BitmapFontLoader.hpp"

using namespace gdx_cpp::assets::loaders;

gdx_cpp::utils::ArrayAssetDescriptor>& BitmapFontLoader::getDependencies (const std::string& fileName,const BitmapFontParameter& parameter) {
    FileHandle handle = resolve(fileName);
    data = new BitmapFontData(handle, parameter != null ? parameter.flip : false);

    Array<AssetDescriptor> deps = new Array<AssetDescriptor>();
    deps.add(new AssetDescriptor(data.getImageFile(), Texture.class, null));
    return deps;
}

void BitmapFontLoader::loadAsync (const gdx_cpp::assets::AssetManager& manager,const std::string& fileName,const BitmapFontParameter& parameter) {
    this.manager = manager;
    this.fileName = fileName;
}

gdx_cpp::graphics::g2d::BitmapFont& BitmapFontLoader::loadSync () {
    FileHandle handle = resolve(fileName);
    TextureRegion region = new TextureRegion(manager.get(data.getImageFile(), Texture.class));
    return new BitmapFont(data, region, true);
}

