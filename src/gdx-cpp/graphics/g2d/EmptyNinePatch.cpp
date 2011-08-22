
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

#include "EmptyNinePatch.hpp"

using namespace gdx_cpp::graphics::g2d;

EmptyNinePatch& EmptyNinePatch::getInstance () {
    if (instance == null) {
        // This is kind of gross...
        Texture texture = new Texture(2, 2, Format.RGBA8888);
        region = new TextureRegion(texture) {
            public int getRegionWidth () {
                return 0;
            }

            public int getRegionHeight () {
                return 0;
            }
        };
        emptyPatches = new TextureRegion[] { //
            region, region, region, //
            region, region, region, //
            region, region, region //
        };
        instance = new EmptyNinePatch();
    }
    return instance;
}

int EmptyNinePatch::getRegionWidth () {
    return 0;
}

int EmptyNinePatch::getRegionHeight () {
    return 0;
}

TextureRegion& EmptyNinePatch::getRegion () {
    getInstance();
    return region;
}

void EmptyNinePatch::draw (const SpriteBatch& batch,float x,float y,float width,float height) {
}

