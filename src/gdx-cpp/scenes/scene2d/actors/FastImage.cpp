
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

#include "FastImage.hpp"

using namespace gdx_cpp::scenes::scene2d::actors;

void FastImage::draw (const gdx_cpp::graphics::g2d::SpriteBatch& batch,float parentAlpha) {
    updateSprite();

    if (region.getTexture() != null) {
        sprite.draw(batch, parentAlpha);
    }
}

void FastImage::updateSprite () {
    if (sX != x || sY != y) {
        sprite.setPosition(x, y);
        sX = x;
        sY = y;
    }

    if (sOriginX != originX || sOriginY != originY) {
        sprite.setOrigin(originX, originY);
        sOriginX = originX;
        sOriginY = originY;
    }

    if (sRotation != rotation) {
        sprite.setRotation(rotation);
        sRotation = rotation;
    }

    if (sScaleX != scaleX || sScaleY != scaleY) {
        sprite.setScale(scaleX, scaleY);
        sScaleX = scaleX;
        sScaleY = scaleY;
    }

    if (sWidth != width || sHeight != height) {
        sprite.setSize(width, height);
        sWidth = width;
        sHeight = height;
    }

    sprite.setColor(color);
    sprite.setRegion(region);
}

bool FastImage::touchDown (float x,float y,int pointer) {
    return x > 0 && y > 0 && x < width && y < height;
}

bool FastImage::touchUp (float x,float y,int pointer) {
    return false;
}

bool FastImage::touchDragged (float x,float y,int pointer) {
    return false;
}

gdx_cpp::scenes::scene2d::Actor& FastImage::hit (float x,float y) {
    if (x > 0 && x < width) if (y > 0 && y < height) return this;

    return null;
}

