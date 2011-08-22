
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

#include "NinePatch.hpp"

using namespace gdx_cpp::graphics::g2d;

void NinePatch::checkValidity () {
    if (patches[BOTTOM_LEFT].getRegionWidth() != patches[TOP_LEFT].getRegionWidth()
            || patches[BOTTOM_LEFT].getRegionWidth() != patches[MIDDLE_LEFT].getRegionWidth()) {
        throw new GdxRuntimeException("Left side patches must have the same width");
    }

    if (patches[BOTTOM_RIGHT].getRegionWidth() != patches[TOP_RIGHT].getRegionWidth()
            || patches[BOTTOM_RIGHT].getRegionWidth() != patches[MIDDLE_RIGHT].getRegionWidth()) {
        throw new GdxRuntimeException("Right side patches must have the same width");
    }

    if (patches[BOTTOM_LEFT].getRegionHeight() != patches[BOTTOM_CENTER].getRegionHeight()
            || patches[BOTTOM_LEFT].getRegionHeight() != patches[BOTTOM_RIGHT].getRegionHeight()) {
        throw new GdxRuntimeException("Bottom patches must have the same height");
    }

    if (patches[TOP_LEFT].getRegionHeight() != patches[TOP_CENTER].getRegionHeight()
            || patches[TOP_LEFT].getRegionHeight() != patches[TOP_RIGHT].getRegionHeight()) {
        throw new GdxRuntimeException("Top patches must have the same height");
    }
}

void NinePatch::draw (const SpriteBatch& batch,float x,float y,float width,float height) {
    float widthTopBottom = width - (patches[TOP_LEFT].getRegionWidth() + patches[TOP_RIGHT].getRegionWidth());
    float heightLeftRight = height - (patches[TOP_LEFT].getRegionHeight() + patches[BOTTOM_LEFT].getRegionHeight());
    float widthCenter = widthTopBottom;

    // bottom patches
    batch.draw(patches[BOTTOM_LEFT], x, y, patches[BOTTOM_LEFT].getRegionWidth(), patches[BOTTOM_LEFT].getRegionHeight());
    batch.draw(patches[BOTTOM_CENTER], x + patches[BOTTOM_LEFT].getRegionWidth(), y, widthCenter,
               patches[BOTTOM_CENTER].getRegionHeight());
    batch.draw(patches[BOTTOM_RIGHT], x + patches[BOTTOM_LEFT].getRegionWidth() + widthTopBottom, y,
               patches[BOTTOM_RIGHT].getRegionWidth(), patches[BOTTOM_RIGHT].getRegionHeight());

    y += patches[BOTTOM_LEFT].getRegionHeight();
    // center patches
    batch.draw(patches[MIDDLE_LEFT], x, y, patches[MIDDLE_LEFT].getRegionWidth(), heightLeftRight);
    batch.draw(patches[MIDDLE_CENTER], x + patches[MIDDLE_LEFT].getRegionWidth(), y, widthCenter, heightLeftRight);
    batch.draw(patches[MIDDLE_RIGHT], x + patches[MIDDLE_LEFT].getRegionWidth() + widthTopBottom, y,
               patches[MIDDLE_RIGHT].getRegionWidth(), heightLeftRight);

    // top patches
    y += heightLeftRight;
    batch.draw(patches[TOP_LEFT], x, y, patches[TOP_LEFT].getRegionWidth(), patches[TOP_LEFT].getRegionHeight());
    batch.draw(patches[TOP_CENTER], x + patches[TOP_LEFT].getRegionWidth(), y, widthCenter,
               patches[TOP_CENTER].getRegionHeight());
    batch.draw(patches[TOP_RIGHT], x + patches[TOP_LEFT].getRegionWidth() + widthTopBottom, y,
               patches[TOP_RIGHT].getRegionWidth(), patches[TOP_RIGHT].getRegionHeight());
}

float NinePatch::getLeftWidth () {
    return patches[TOP_LEFT].getRegionWidth();
}

float NinePatch::getRightWidth () {
    return patches[TOP_RIGHT].getRegionWidth();
}

float NinePatch::getTopHeight () {
    return patches[TOP_RIGHT].getRegionHeight();
}

float NinePatch::getBottomHeight () {
    return patches[BOTTOM_RIGHT].getRegionHeight();
}

float NinePatch::getTotalHeight () {
    return getTopHeight() + getBottomHeight() + patches[MIDDLE_LEFT].getRegionHeight();
}

float NinePatch::getTotalWidth () {
    return getLeftWidth() + getRightWidth() + patches[MIDDLE_CENTER].getRegionWidth();
}

