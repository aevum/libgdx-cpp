
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
#include "gdx-cpp/files/FileHandle.hpp"
#include "gdx-cpp/assets/AssetDescriptor.hpp"
#include "gdx-cpp/graphics/g2d/TextureRegion.hpp"
#include <assets/AssetManager.hpp>

using namespace gdx_cpp::files;
using namespace gdx_cpp::assets;
using namespace gdx_cpp::assets::loaders;

std::vector<AssetDescriptor> BitmapFontLoader::getDependencies (const std::string& fileName,const Parameter* parameter) {
    FileHandle handle = resolve(fileName);
    data = BitmapFontData::ptr(new BitmapFontData(handle, parameter != NULL ? ((BitmapFontParameter*)parameter)->flip : false));

    std::vector<AssetDescriptor> deps;
    deps.push_back(AssetDescriptor(data->getImageFile(), AssetManager::Texture, NULL));
    
    return deps;
}

void BitmapFontLoader::loadAsync (const gdx_cpp::assets::AssetManager* manager,
                                  const std::string& fileName,
                                  const BitmapFontParameter& parameter) {
    this->manager = manager;
    this->fileName = fileName;
}

gdx_cpp::graphics::g2d::BitmapFont& BitmapFontLoader::loadSync () {
    const FileHandle& handle = resolve(fileName);
    graphics::gd2::TextureRegion region = TextureRegion::ptr(new TextureRegion(manager.get(data->getImageFile(), AssetManager::Texture)));
    return new BitmapFont(data, region, true);
}

