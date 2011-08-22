
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

#include "Image.hpp"

using namespace gdx_cpp::scenes::scene2d::actors;

void Image::draw (const gdx_cpp::graphics::g2d::SpriteBatch& batch,float parentAlpha) {
    if (region.getTexture() != null) {
        batch.setColor(color.r, color.g, color.b, color.a * parentAlpha);
        if (scaleX == 1 && scaleY == 1 && rotation == 0)
            batch.draw(region, x, y, width, height);
        else
            batch.draw(region, x, y, originX, originY, width, height, scaleX, scaleY, rotation);
    }
}

bool Image::touchDown (float x,float y,int pointer) {
    return x > 0 && y > 0 && x < width && y < height;
}

bool Image::touchUp (float x,float y,int pointer) {
    return false;
}

bool Image::touchDragged (float x,float y,int pointer) {
    return false;
}

gdx_cpp::scenes::scene2d::Actor& Image::hit (float x,float y) {
    if (x > 0 && x < width) if (y > 0 && y < height) return this;

    return null;
}

