
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

using namespace gdx;

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
    float centerColumnX = x;
    if (patches[BOTTOM_LEFT])
        centerColumnX += patches[BOTTOM_LEFT]->getRegionWidth();
    else if (patches[MIDDLE_LEFT])
        centerColumnX += patches[MIDDLE_LEFT]->getRegionWidth();
    else if (patches[TOP_LEFT]) //
        centerColumnX += patches[TOP_LEFT]->getRegionWidth();

    float rightColumnX = x + width;
    if (patches[BOTTOM_RIGHT])
        rightColumnX -= patches[BOTTOM_RIGHT]->getRegionWidth();
    else if (patches[MIDDLE_RIGHT])
        rightColumnX += patches[MIDDLE_RIGHT]->getRegionWidth();
    else if (patches[TOP_RIGHT]) //
        rightColumnX += patches[TOP_RIGHT]->getRegionWidth();

    float middleRowY = y;
    if (patches[TOP_LEFT])
        middleRowY += patches[TOP_LEFT]->getRegionHeight();
    else if (patches[TOP_CENTER])
        middleRowY += patches[TOP_CENTER]->getRegionHeight();
    else if (patches[TOP_RIGHT]) //
        middleRowY += patches[TOP_RIGHT]->getRegionHeight();

    float topRowY = y + height;
    if (patches[TOP_LEFT])
        topRowY -= patches[TOP_LEFT]->getRegionHeight();
    else if (patches[TOP_CENTER])
        topRowY -= patches[TOP_CENTER]->getRegionHeight();
    else if (patches[TOP_RIGHT]) //
        topRowY -= patches[TOP_RIGHT]->getRegionHeight();

    // Bottom row
    if (patches[BOTTOM_LEFT]) batch.draw(*patches[BOTTOM_LEFT], x, y, centerColumnX - x, middleRowY - y);
    if (patches[BOTTOM_CENTER])
        batch.draw(*patches[BOTTOM_CENTER], centerColumnX, y, rightColumnX - centerColumnX, middleRowY - y);
    if (patches[BOTTOM_RIGHT])
        batch.draw(*patches[BOTTOM_RIGHT], rightColumnX, y, x + width - rightColumnX, middleRowY - y);

    // Middle row
    if (patches[MIDDLE_LEFT]) batch.draw(*patches[MIDDLE_LEFT], x, middleRowY, centerColumnX - x, topRowY - middleRowY);
    if (patches[MIDDLE_CENTER])
        batch.draw(*patches[MIDDLE_CENTER], centerColumnX, middleRowY, rightColumnX - centerColumnX, topRowY - middleRowY);
    if (patches[MIDDLE_RIGHT])
        batch.draw(*patches[MIDDLE_RIGHT], rightColumnX, middleRowY, x + width - rightColumnX, topRowY - middleRowY);

    // Top row
    if (patches[TOP_LEFT]) batch.draw(*patches[TOP_LEFT], x, topRowY, centerColumnX - x, y + height - topRowY);
    if (patches[TOP_CENTER])
        batch.draw(*patches[TOP_CENTER], centerColumnX, topRowY, rightColumnX - centerColumnX, y + height - topRowY);
    if (patches[TOP_RIGHT])
        batch.draw(*patches[TOP_RIGHT], rightColumnX, topRowY, x + width - rightColumnX, y + height - topRowY);
}

float NinePatch::getLeftWidth () {
    return !patches[TOP_LEFT] ? 0 : patches[TOP_LEFT]->getRegionWidth();
}

float NinePatch::getRightWidth () {
    return !patches[TOP_RIGHT] ? 0 : patches[TOP_RIGHT]->getRegionWidth();
}

float NinePatch::getTopHeight () {
    return !patches[TOP_RIGHT] ? 0 : patches[TOP_RIGHT]->getRegionHeight();
}

float NinePatch::getBottomHeight () {
    return !patches[BOTTOM_RIGHT] ? 0 : patches[BOTTOM_RIGHT]->getRegionHeight();
}

float NinePatch::getTotalHeight () {
    float totalHeight = getTopHeight() + getBottomHeight();
    if (patches[MIDDLE_CENTER]) totalHeight += patches[MIDDLE_CENTER]->getRegionHeight();
    
    return totalHeight;
}

float NinePatch::getTotalWidth () {
    float totalWidth = getLeftWidth() + getRightWidth();
    if (patches[MIDDLE_CENTER]) totalWidth += patches[MIDDLE_CENTER]->getRegionWidth();
    
    return totalWidth;
}

std::vector< TextureRegion::ptr > NinePatch::getPatches()
{
    return patches;
}

NinePatch::NinePatch(TextureRegion::ptr region)
{
    patches.push_back(null_shared_ptr());
    patches.push_back(null_shared_ptr());
    patches.push_back(null_shared_ptr());
    patches.push_back(null_shared_ptr());
    patches.push_back(region);
    patches.push_back(null_shared_ptr());
    patches.push_back(null_shared_ptr());
    patches.push_back(null_shared_ptr());
    patches.push_back(null_shared_ptr());
}
