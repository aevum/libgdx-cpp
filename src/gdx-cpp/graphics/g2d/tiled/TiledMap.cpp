
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

#include "TiledMap.hpp"

using namespace gdx_cpp::graphics::g2d::tiled;

void TiledMap::setTileProperty (int id,const std::string& name,const std::string& value) {
for (TileProperty tp : tileProperties) {
        if (tp.id == id) {
            tp.propertyMap.put(name, value);
            return;
        }
    }

    // no TileProperty found with the correct id, add a new one
    TileProperty tempProperty = new TileProperty();
    tempProperty.id = id;
    tempProperty.propertyMap.put(name, value);
    tileProperties.add(tempProperty);
}

std::string& TiledMap::getTileProperty (int id,const std::string& name) {
for (TileProperty tp : tileProperties) {
        if (tp.id == id) {
            return tp.propertyMap.get(name);
        }
    }

    return null;
}

