
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

#include <stdlib.h>

#include "TextureAtlas.hpp"
#include "gdx-cpp/graphics/Texture.hpp"
#include "gdx-cpp/graphics/g2d/Sprite.hpp"
#include "gdx-cpp/graphics/g2d/TextureRegion.hpp"

using namespace gdx;

TextureAtlas::AtlasRegion TextureAtlas::addRegion (const std::string& name, const Texture::ptr& texture, int x, int y, int width, int height) {
    textures.insert(texture);    

    regions.push_back(AtlasRegion(texture, x, y, width, height));
    
    regions.back().name = name;
    regions.back().originalWidth = width;
    regions.back().originalHeight = height;
    regions.back().index = -1;
    
    return regions.back();
}

TextureAtlas::AtlasRegion TextureAtlas::addRegion (const std::string& name, TextureRegion textureRegion) {
    return addRegion(name, textureRegion.getTexture(), textureRegion.getRegionX(), textureRegion.getRegionY(),
                     textureRegion.getRegionWidth(), textureRegion.getRegionHeight());
}

bool TextureAtlas::findRegion (const std::string& name, TextureAtlas::AtlasRegion& placement) {
    for (auto & elem : regions)
        if (elem.name == name) {
            placement = elem;
            return true;
        }
    
    return false;
}

bool TextureAtlas::findRegion (const std::string& name, int index, AtlasRegion& placement) {
    for (auto & elem : regions) {
        AtlasRegion& region = elem;
        if (region.name != name) continue;
        if (region.index != index) continue;
        placement = region;
        return true;
    }
    
    return false;
}

std::vector< TextureAtlas::AtlasRegion > TextureAtlas::findRegions (const std::string& name) {
    std::vector< AtlasRegion > matched;
   
    for (auto & elem : regions) {
        AtlasRegion& region = elem;
        if (region.name == name) matched.push_back(region);
    }
    
    return matched;
}

std::vector< Sprite::ptr > TextureAtlas::createSprites () {
    std::vector< Sprite::ptr > sprites;
    for (auto & elem : regions) {
        sprites.push_back(newSprite(elem));
    }
    
    return sprites;
}

Sprite::ptr TextureAtlas::createSprite (const std::string& name) {
    for (auto & elem : regions)
        if (elem.name == name) return newSprite(elem);
    
    return nullptr;
}

Sprite::ptr TextureAtlas::createSprite (const std::string& name,int index) {
    for (auto & elem : regions) {
        AtlasRegion& region = elem;
        if (region.name != name) continue;
        if (region.index != index) continue;
        return newSprite(elem);
    }
    
    return nullptr;
}

std::vector< Sprite::ptr > TextureAtlas::createSprites (const std::string& name) {
    std::vector< Sprite::ptr > matched;
    
    for (auto & elem : regions) {
        const AtlasRegion& region = elem;
        if (region.name == name) matched.push_back(newSprite(region));
    }
    
    return matched;
}

Sprite::ptr TextureAtlas::newSprite (const TextureAtlas::AtlasRegion& region) {
    if (region.packedWidth == region.originalWidth && region.packedHeight == region.originalHeight) {
        Sprite::ptr sprite = Sprite::ptr(new Sprite(region));
        if (region.rotate) sprite->rotate90(true);
        return sprite;
    }
    return Sprite::ptr(new AtlasSprite(region));
}

void TextureAtlas::dispose () {
    textures.clear();
}

TextureAtlas::AtlasRegion::AtlasRegion(const Texture::ptr& texture, int x, int y, int width, int height) : gdx::TextureRegion(texture, x, y, width, height) {
    packedWidth = width;
    packedHeight = height;
}

TextureAtlas::AtlasRegion::AtlasRegion(const TextureAtlas::AtlasRegion& region) {
    setRegion(region);
    index = region.index;
    name = region.name;
    offsetX = region.offsetX;
    offsetY = region.offsetY;
    packedWidth = region.packedWidth;
    packedHeight = region.packedHeight;
    originalWidth = region.originalWidth;
    originalHeight = region.originalHeight;
    rotate = region.rotate;
}
void TextureAtlas::AtlasRegion::flip(bool x, bool y) {
    gdx::TextureRegion::flip(x, y);
    if (x) offsetX = originalWidth - offsetX - packedWidth;
    if (y) offsetY = originalHeight - offsetY - packedHeight;
}
TextureAtlas::AtlasSprite::AtlasSprite(TextureAtlas::AtlasRegion _region) :
    region(_region)
{
    originalOffsetX = region.offsetX;
    originalOffsetY = region.offsetY;
    setRegion(region);
    setOrigin(region.originalWidth / 2.f, region.originalHeight / 2.f);
    int width = std::abs(region.getRegionWidth());
    int height = std::abs(region.getRegionHeight());

    if (region.rotate) {
        rotate90(true);
        Sprite::setBounds(region.offsetX, region.offsetY, height, width);
    } else
        Sprite::setBounds(region.offsetX, region.offsetY, width, height);

    setColor(1, 1, 1, 1);
}

void TextureAtlas::AtlasSprite::setPosition(float x, float y) {
    Sprite::setPosition(x + region.offsetX, y + region.offsetY);
}

void TextureAtlas::AtlasSprite::setBounds(float x, float y, float width, float height) {
    float widthRatio = width / region.originalWidth;
    float heightRatio = height / region.originalHeight;
    region.offsetX = originalOffsetX * widthRatio;
    region.offsetY = originalOffsetY * heightRatio;
    int packedWidth = region.rotate ? region.packedHeight : region.packedWidth;
    int packedHeight = region.rotate ? region.packedWidth : region.packedHeight;
    Sprite::setBounds(x + region.offsetX, y + region.offsetY, packedWidth * widthRatio, packedHeight
                      * heightRatio);
}

void TextureAtlas::AtlasSprite::setSize(float width, float height) {
    setBounds(getX(), getY(), width, height);
}

void TextureAtlas::AtlasSprite::setOrigin(float originX, float originY) {
    Sprite::setOrigin(originX - region.offsetX, originY - region.offsetY);
}

void TextureAtlas::AtlasSprite::flip(bool x, bool y) {
    // Flip texture.
    Sprite::flip(x, y);

    float oldOriginX = getOriginX();
    float oldOriginY = getOriginY();
    float oldOffsetX = region.offsetX;
    float oldOffsetY = region.offsetY;

    float widthRatio = getWidth() / region.originalWidth;
    float heightRatio = getHeight() / region.originalHeight;

    region.offsetX /= widthRatio;
    region.offsetY /= heightRatio;
    // Updates x and y offsets.
    region.flip(x, y);
    region.offsetX *= widthRatio;
    region.offsetY *= heightRatio;

    // Update position and origin with new offsets.
    translate(region.offsetX - oldOffsetX, region.offsetY - oldOffsetY);
    setOrigin(oldOriginX, oldOriginY);
}

float TextureAtlas::AtlasSprite::getX() const {
    return Sprite::getX() - region.offsetX;
}
float TextureAtlas::AtlasSprite::getY() const {
    return Sprite::getY() - region.offsetY;
}
float TextureAtlas::AtlasSprite::getOriginX() const {
    return Sprite::getOriginX() + region.offsetX;
}
float TextureAtlas::AtlasSprite::getOriginY() const {
    return Sprite::getOriginY() + region.offsetY;
}
float TextureAtlas::AtlasSprite::getWidth() const {
    float packedWidth = region.rotate ? region.packedHeight : region.packedWidth;
    return Sprite::getWidth() / packedWidth * region.originalWidth;
}
float TextureAtlas::AtlasSprite::getHeight() const {
    float packedHeight = region.rotate ? region.packedWidth : region.packedHeight;
    return Sprite::getHeight() / packedHeight * region.originalHeight;
}

TextureAtlas::AtlasRegion TextureAtlas::AtlasSprite::getAtlasRegion() {
    return region;
}

std::unique_ptr< TextureAtlas > TextureAtlas::newAtlasFromProvider(TextureAtlas::TextureAtlasDataProvider& provider) {
    auto  atlas = new TextureAtlas;    
    atlas->regions = provider.loadAtlasRegions();    
    return std::unique_ptr<TextureAtlas>(atlas);
}

TextureAtlas::AtlasRegion::AtlasRegion()
{
}

