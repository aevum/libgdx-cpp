/*
    Copyright 2011 <copyright holder> <email>

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/


#ifndef GDX_CPP_ASSETS_ASSETTYPE_HPP
#define GDX_CPP_ASSETS_ASSETTYPE_HPP

#include <string>

namespace gdx_cpp {

namespace assets {

class AssetType {
public:
    const static AssetType BitmapFont;
    const static AssetType Music;
    const static AssetType Pixmap;
    const static AssetType Sound;
    const static AssetType TextureAtlas;
    const static AssetType Texture;

    const std::string& getSimpleName() {
        return simpleName;
    }

    bool operator == (const AssetType& other) {
        return this == &other;
    }

    bool operator != (const AssetType& other) {
        return !(*this == other);
    }

private:
    AssetType(const std::string& simpleName) : simpleName(simpleName) {
    }

    std::string simpleName;
};

}

}

#endif // GDX_CPP_ASSETS_ASSETTYPE_HPP
