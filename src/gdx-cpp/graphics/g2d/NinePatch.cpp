
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
#include <stdexcept>
#include "gdx-cpp/graphics/Texture.hpp"
#include "gdx-cpp/graphics/g2d/SpriteBatch.hpp"
#include "TextureRegion.hpp"

using namespace gdx_cpp::graphics::g2d;
using namespace gdx_cpp::graphics;

NinePatch::NinePatch (Texture::ptr texture, int left, int right, int top, int bottom) {
    TextureRegion::ptr t(new TextureRegion(texture));
    initialize(t, left, right, top, bottom);
}

NinePatch::NinePatch (TextureRegion::ptr region, int left, int right, int top, int bottom) {
    initialize(region, left, right, top, bottom);
}

void NinePatch::initialize(TextureRegion::ptr region, int left, int right, int top, int bottom)
{
    int middleWidth = region->getRegionWidth() - left - right;
    int middleHeight = region->getRegionHeight() - top - bottom;
    patches.reserve(9);
    patches[0] = TextureRegion::ptr(new TextureRegion(*region, 0, 0, left, top));
    patches[1] = TextureRegion::ptr(new TextureRegion(*region, left, 0, middleWidth, top));
    patches[2] = TextureRegion::ptr(new TextureRegion(*region, left + middleWidth, 0, right, top));
    patches[3] = TextureRegion::ptr(new TextureRegion(*region, 0, top, left, middleHeight));
    patches[4] = TextureRegion::ptr(new TextureRegion(*region, left, top, middleWidth, middleHeight));
    patches[5] = TextureRegion::ptr(new TextureRegion(*region, left + middleWidth, top, right, middleHeight));
    patches[6] = TextureRegion::ptr(new TextureRegion(*region, 0, top + middleHeight, left, bottom));
    patches[7] = TextureRegion::ptr(new TextureRegion(*region, left, top + middleHeight, middleWidth, bottom));
    patches[8] = TextureRegion::ptr(new TextureRegion(*region, left + middleWidth, top + middleHeight, right, bottom));
}

NinePatch::NinePatch (std::vector< TextureRegion::ptr >& _patches): patches(_patches)
{
    if (patches.size() != 9) throw std::runtime_error("NinePatch needs nine TextureRegions");
    this->patches = patches;
    checkValidity();
}

void NinePatch::checkValidity () {
    if (patches[BOTTOM_LEFT]->getRegionWidth() != patches[TOP_LEFT]->getRegionWidth()
            || patches[BOTTOM_LEFT]->getRegionWidth() != patches[MIDDLE_LEFT]->getRegionWidth()) {
        throw std::runtime_error("Left side patches must have the same width");
    }

    if (patches[BOTTOM_RIGHT]->getRegionWidth() != patches[TOP_RIGHT]->getRegionWidth()
            || patches[BOTTOM_RIGHT]->getRegionWidth() != patches[MIDDLE_RIGHT]->getRegionWidth()) {
        throw std::runtime_error("Right side patches must have the same width");
    }

    if (patches[BOTTOM_LEFT]->getRegionHeight() != patches[BOTTOM_CENTER]->getRegionHeight()
            || patches[BOTTOM_LEFT]->getRegionHeight() != patches[BOTTOM_RIGHT]->getRegionHeight()) {
        throw std::runtime_error("Bottom patches must have the same height");
    }

    if (patches[TOP_LEFT]->getRegionHeight() != patches[TOP_CENTER]->getRegionHeight()
            || patches[TOP_LEFT]->getRegionHeight() != patches[TOP_RIGHT]->getRegionHeight()) {
        throw std::runtime_error("Top patches must have the same height");
    }
}

void NinePatch::draw (SpriteBatch& batch,float x,float y,float width,float height) {
    float widthTopBottom = width - (patches[TOP_LEFT]->getRegionWidth() + patches[TOP_RIGHT]->getRegionWidth());
    float heightLeftRight = height - (patches[TOP_LEFT]->getRegionHeight() + patches[BOTTOM_LEFT]->getRegionHeight());
    float widthCenter = widthTopBottom;

    // bottom patches
    batch.draw(*patches[BOTTOM_LEFT], x, y, patches[BOTTOM_LEFT]->getRegionWidth(), patches[BOTTOM_LEFT]->getRegionHeight());
    batch.draw(*patches[BOTTOM_CENTER], x + patches[BOTTOM_LEFT]->getRegionWidth(), y, widthCenter,
               patches[BOTTOM_CENTER]->getRegionHeight());
    batch.draw(*patches[BOTTOM_RIGHT], x + patches[BOTTOM_LEFT]->getRegionWidth() + widthTopBottom, y,
               patches[BOTTOM_RIGHT]->getRegionWidth(), patches[BOTTOM_RIGHT]->getRegionHeight());

    y += patches[BOTTOM_LEFT]->getRegionHeight();
    // center patches
    batch.draw(*patches[MIDDLE_LEFT], x, y, patches[MIDDLE_LEFT]->getRegionWidth(), heightLeftRight);
    batch.draw(*patches[MIDDLE_CENTER], x + patches[MIDDLE_LEFT]->getRegionWidth(), y, widthCenter, heightLeftRight);
    batch.draw(*patches[MIDDLE_RIGHT], x + patches[MIDDLE_LEFT]->getRegionWidth() + widthTopBottom, y,
               patches[MIDDLE_RIGHT]->getRegionWidth(), heightLeftRight);

    // top patches
    y += heightLeftRight;
    batch.draw(*patches[TOP_LEFT], x, y, patches[TOP_LEFT]->getRegionWidth(), patches[TOP_LEFT]->getRegionHeight());
    batch.draw(*patches[TOP_CENTER], x + patches[TOP_LEFT]->getRegionWidth(), y, widthCenter,
               patches[TOP_CENTER]->getRegionHeight());
    batch.draw(*patches[TOP_RIGHT], x + patches[TOP_LEFT]->getRegionWidth() + widthTopBottom, y,
               patches[TOP_RIGHT]->getRegionWidth(), patches[TOP_RIGHT]->getRegionHeight());
}

float NinePatch::getLeftWidth () {
    return patches[TOP_LEFT]->getRegionWidth();
}

float NinePatch::getRightWidth () {
    return patches[TOP_RIGHT]->getRegionWidth();
}

float NinePatch::getTopHeight () {
    return patches[TOP_RIGHT]->getRegionHeight();
}

float NinePatch::getBottomHeight () {
    return patches[BOTTOM_RIGHT]->getRegionHeight();
}

float NinePatch::getTotalHeight () {
    return getTopHeight() + getBottomHeight() + patches[MIDDLE_LEFT]->getRegionHeight();
}

float NinePatch::getTotalWidth () {
    return getLeftWidth() + getRightWidth() + patches[MIDDLE_CENTER]->getRegionWidth();
}

