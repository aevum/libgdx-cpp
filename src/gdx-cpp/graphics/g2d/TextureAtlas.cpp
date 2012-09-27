
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

#include "TextureAtlas.hpp"
#include <climits>
#include <unordered_map>

using namespace gdx;

void TextureAtlas::load (const TextureAtlasData& data) {
    std::unordered_map< TextureAtlasData::Page::shared_ptr_t, Texture::ptr > pageToTexture;
    for (auto page = data.pages.begin(); page != data.pages.end(); page++) {
        Texture::ptr texture = nullptr;
        if ((*page)->texture == nullptr) {
            texture = Texture::newFromFile((*page)->textureFile, &(*page)->format, (*page)->useMipMaps);
            texture->setFilter((*page)->minFilter, (*page)->magFilter);
            texture->setWrap((*page)->uWrap, (*page)->vWrap);
        } else {
            texture = (*page)->texture;
            texture->setFilter((*page)->minFilter, (*page)->magFilter);
            texture->setWrap((*page)->uWrap, (*page)->vWrap);
        }
        
        textures.insert(texture);
        pageToTexture[*page] = texture;
    }

    for (auto region = data.regions.begin(); region != data.regions.end(); ++region) {
        AtlasRegion::shared_ptr_t atlasRegion = std::make_shared<AtlasRegion>(pageToTexture[(*region)->page], (*region)->left, (*region)->top, (*region)->width,
                (*region)->height);
        atlasRegion->index = (*region)->index;
        atlasRegion->name = (*region)->name;
        atlasRegion->offsetX = (*region)->offsetX;
        atlasRegion->offsetY = (*region)->offsetY;
        atlasRegion->originalHeight = (*region)->originalHeight;
        atlasRegion->originalWidth = (*region)->originalWidth;
        atlasRegion->rotate = (*region)->rotate;
        regions.push_back(atlasRegion);
    }
}

TextureAtlas::AtlasRegion::shared_ptr_t TextureAtlas::addRegion (const std::string& name, const Texture::ptr& texture, int x, int y, int width, int height) {
    textures.insert(texture);
    
    AtlasRegion::shared_ptr_t region = std::make_shared<AtlasRegion>(texture, x, y, width, height);    
    region->name = name;
    region->originalWidth = width;
    region->originalHeight = height;
    region->index = -1;
    regions.push_back(region);
    
    return region;
}

TextureAtlas::AtlasRegion::shared_ptr_t TextureAtlas::addRegion (const std::string& name, TextureRegion textureRegion) {
    return addRegion(name, textureRegion.getTexture(), textureRegion.getRegionX(), textureRegion.getRegionY(),
                     textureRegion.getRegionWidth(), textureRegion.getRegionHeight());
}

TextureAtlas::AtlasRegion::shared_ptr_t TextureAtlas::findRegion (const std::string& name) {
    for (int i = 0, n = regions.size(); i < n; i++)
        if (regions[i]->name == name) {
            return regions[i];
        }
    
    return nullptr;
}

TextureAtlas::AtlasRegion::shared_ptr_t TextureAtlas::findRegion (const std::string& name, int index) {
    for (int i = 0, n = regions.size(); i < n; i++) {
        AtlasRegion::shared_ptr_t& region = regions[i];
        if (region->name != name) continue;
        if (region->index != index) continue;
        return region;
    }
    
    return nullptr;
}

std::vector< TextureAtlas::AtlasRegion::shared_ptr_t > TextureAtlas::findRegions (const std::string& name) {
    std::vector< TextureAtlas::AtlasRegion::shared_ptr_t > matched;
    
    for (int i = 0, n = regions.size(); i < n; i++) {
        AtlasRegion::shared_ptr_t& region = regions[i];
        if (region->name == name) matched.push_back(region);
    }
    
    return matched;
}

std::vector< Sprite::ptr > TextureAtlas::createSprites () {
    std::vector< Sprite::ptr > sprites;
    for (int i = 0, n = regions.size(); i < n; i++) {
        sprites.push_back(newSprite(*regions[i]));
    }
    
    return sprites;
}

Sprite::ptr TextureAtlas::createSprite (const std::string& name) {
    for (int i = 0, n = regions.size(); i < n; i++)
        if (regions[i]->name == name) return newSprite(*regions[i]);
    
    return nullptr;
}

Sprite::ptr TextureAtlas::createSprite (const std::string& name,int index) {
    for (int i = 0, n = regions.size(); i < n; i++) {
        AtlasRegion::shared_ptr_t& region = regions[i];
        if (region->name != name) continue;
        if (region->index != index) continue;
        return newSprite(*regions[i]);
    }
    
    return nullptr;
}

std::vector< Sprite::ptr > TextureAtlas::createSprites (const std::string& name) {
    std::vector< Sprite::ptr > matched;
    
    for (int i = 0, n = regions.size(); i < n; i++) {
        const AtlasRegion::shared_ptr_t& region = regions[i];
        if (region->name == name) matched.push_back(newSprite(*region));
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

int TextureAtlas::compare (const TextureAtlas::TextureAtlasData::Region& region1,const TextureAtlas::TextureAtlasData::Region& region2) {
    int i1 = region1.index;
    if (i1 == -1) i1 = INT_MAX;
    
    int i2 = region2.index;
    if (i2 == -1) i2 = INT_MAX;

    return i1 - i2;
}

std::vector< TextureAtlas::TextureAtlasData::Page::shared_ptr_t  >& TextureAtlas::TextureAtlasData::getPages() {
    return pages;
}
std::vector< TextureAtlas::TextureAtlasData::Region::shared_ptr_t  >& TextureAtlas::TextureAtlasData::getRegions() {
    return regions;
}
TextureAtlas::TextureAtlasData::Page::Page(const FileHandle::ptr& _handle, bool _useMipMaps, Pixmap::Format _format, Texture::TextureFilter _minFilter, Texture::TextureFilter _magFilter, Texture::TextureWrap _uWrap, Texture::TextureWrap _vWrap) :
    textureFile(_handle),
    useMipMaps(_useMipMaps),
    format(_format),
    minFilter(_minFilter),
    magFilter(_magFilter),
    uWrap(_uWrap),
    vWrap(_vWrap)
{
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
float TextureAtlas::AtlasSprite::getX() {
    return Sprite::getX() - region.offsetX;
}
float TextureAtlas::AtlasSprite::getY() {
    return Sprite::getY() - region.offsetY;
}
float TextureAtlas::AtlasSprite::getOriginX() {
    return Sprite::getOriginX() + region.offsetX;
}
float TextureAtlas::AtlasSprite::getOriginY() {
    return Sprite::getOriginY() + region.offsetY;
}
float TextureAtlas::AtlasSprite::getWidth() {
    float packedWidth = region.rotate ? region.packedHeight : region.packedWidth;
    return Sprite::getWidth() / packedWidth * region.originalWidth;
}
float TextureAtlas::AtlasSprite::getHeight() {
    float packedHeight = region.rotate ? region.packedWidth : region.packedHeight;
    return Sprite::getHeight() / packedHeight * region.originalHeight;
}
TextureAtlas::AtlasRegion TextureAtlas::AtlasSprite::getAtlasRegion() {
    return region;
}
