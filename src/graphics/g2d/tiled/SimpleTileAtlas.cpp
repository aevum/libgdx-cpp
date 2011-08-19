
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

#include "SimpleTileAtlas.hpp"

using namespace gdx_cpp::graphics::g2d::tiled;

gdx_cpp::graphics::g2d::TextureRegion* SimpleTileAtlas::split (const gdx_cpp::graphics::Texture& texture,int totalWidth,int totalHeight,int width,int height,int spacing,int margin) {
    // TODO add padding support
    int xSlices = (totalWidth - margin) / (width + spacing);
    int ySlices = (totalHeight - margin) / (height + spacing);

    TextureRegion[][] res = new TextureRegion[xSlices][ySlices];
    for (int x = 0; x < xSlices; x++) {
        for (int y = 0; y < ySlices; y++) {
            res[x][y] = new TextureRegion(texture, margin + x * (width + spacing), margin + y * (height + spacing), width, height);
        }
    }
    return res;
}

