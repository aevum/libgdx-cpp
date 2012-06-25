
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

using namespace gdx;

ArrayPage& TextureAtlas::getPages () {
    return pages;
}

ArrayRegion>& TextureAtlas::getRegion () {
    return regions;
}

void TextureAtlas::load (const TextureAtlasData& data) {
    ObjectMap<Page, Texture> pageToTexture = new ObjectMap<Page, Texture>();
for (Page page : data.pages) {
        Texture texture = null;
        if (page.texture == null) {
            texture = new Texture(page.textureFile, page.format, page.useMipMaps);
            texture.setFilter(page.minFilter, page.magFilter);
            texture.setWrap(page.uWrap, page.vWrap);
        } else {
            texture = page.texture;
            texture.setFilter(page.minFilter, page.magFilter);
            texture.setWrap(page.uWrap, page.vWrap);
        }
        textures.add(texture);
        pageToTexture.put(page, texture);
    }

for (Region region : data.regions) {
        AtlasRegion atlasRegion = new AtlasRegion(pageToTexture.get(region.page), region.left, region.top, region.width,
                region.height);
        atlasRegion.index = region.index;
        atlasRegion.name = region.name;
        atlasRegion.offsetX = region.offsetX;
        atlasRegion.offsetY = region.offsetY;
        atlasRegion.originalHeight = region.originalHeight;
        atlasRegion.originalWidth = region.originalWidth;
        atlasRegion.rotate = region.rotate;
        regions.add(atlasRegion);
    }
}

AtlasRegion& TextureAtlas::addRegion (const std::string& name,const Texture& texture,int x,int y,int width,int height) {
    textures.add(texture);
    AtlasRegion region = new AtlasRegion(texture, x, y, width, height);
    region.name = name;
    region.originalWidth = width;
    region.originalHeight = height;
    region.index = -1;
    regions.add(region);
    return region;
}

AtlasRegion& TextureAtlas::addRegion (const std::string& name,const TextureRegion& textureRegion) {
    return addRegion(name, textureRegion.texture, textureRegion.getRegionX(), textureRegion.getRegionY(),
                     textureRegion.getRegionWidth(), textureRegion.getRegionHeight());
}

std::list<AtlasRegion>& TextureAtlas::getRegions () {
    return regions;
}

AtlasRegion& TextureAtlas::findRegion (const std::string& name) {
    for (int i = 0, n = regions.size(); i < n; i++)
        if (regions.get(i).name.equals(name)) return regions.get(i);
    return null;
}

AtlasRegion& TextureAtlas::findRegion (const std::string& name,int index) {
    for (int i = 0, n = regions.size(); i < n; i++) {
        AtlasRegion region = regions.get(i);
        if (!region.name.equals(name)) continue;
        if (region.index != index) continue;
        return region;
    }
    return null;
}

std::list<AtlasRegion>& TextureAtlas::findRegions (const std::string& name) {
    ArrayList<AtlasRegion> matched = new ArrayList();
    for (int i = 0, n = regions.size(); i < n; i++) {
        AtlasRegion region = regions.get(i);
        if (region.name.equals(name)) matched.add(new AtlasRegion(region));
    }
    return matched;
}

std::list<Sprite>& TextureAtlas::createSprites () {
    ArrayList sprites = new ArrayList(regions.size());
    for (int i = 0, n = regions.size(); i < n; i++)
        sprites.add(newSprite(regions.get(i)));
    return sprites;
}

Sprite& TextureAtlas::createSprite (const std::string& name) {
    for (int i = 0, n = regions.size(); i < n; i++)
        if (regions.get(i).name.equals(name)) return newSprite(regions.get(i));
    return null;
}

Sprite& TextureAtlas::createSprite (const std::string& name,int index) {
    for (int i = 0, n = regions.size(); i < n; i++) {
        AtlasRegion region = regions.get(i);
        if (!region.name.equals(name)) continue;
        if (region.index != index) continue;
        return newSprite(regions.get(i));
    }
    return null;
}

std::list<Sprite>& TextureAtlas::createSprites (const std::string& name) {
    ArrayList<Sprite> matched = new ArrayList();
    for (int i = 0, n = regions.size(); i < n; i++) {
        AtlasRegion region = regions.get(i);
        if (region.name.equals(name)) matched.add(newSprite(region));
    }
    return matched;
}

Sprite& TextureAtlas::newSprite (const AtlasRegion& region) {
    if (region.packedWidth == region.originalWidth && region.packedHeight == region.originalHeight) {
        Sprite sprite = new Sprite(region);
        if (region.rotate) sprite.rotate90(true);
        return sprite;
    }
    return new AtlasSprite(region);
}

void TextureAtlas::dispose () {
for (Texture texture : textures)
        texture.dispose();
    textures.clear();
}

int TextureAtlas::compare (const TextureAtlas::TextureAtlasData::Region& region1,const TextureAtlas::TextureAtlasData::Region& region2) {
    int i1 = region1.index;
    if (i1 == -1) i1 = Integer.MAX_VALUE;
    int i2 = region2.index;
    if (i2 == -1) i2 = Integer.MAX_VALUE;
    return i1 - i2;
}

void TextureAtlas::flip (bool x,bool y) {
    super.flip(x, y);
    if (x) offsetX = originalWidth - offsetX - packedWidth;
    if (y) offsetY = originalHeight - offsetY - packedHeight;
}

void TextureAtlas::setPosition (float x,float y) {
    super.setPosition(x + region.offsetX, y + region.offsetY);
}

void TextureAtlas::setBounds (float x,float y,float width,float height) {
    super.setBounds(x + region.offsetX, y + region.offsetY, width, height);
}

void TextureAtlas::setOrigin (float originX,float originY) {
    super.setOrigin(originX + region.offsetX, originY + region.offsetY);
}

void TextureAtlas::flip (bool x,bool y) {
    // Flip texture.
    super.flip(x, y);

    float oldOffsetX = region.offsetX;
    float oldOffsetY = region.offsetY;
    // Update x and y offsets.
    region.flip(x, y);

    // Update position with new offsets.
    translate(region.offsetX - oldOffsetX, region.offsetY - oldOffsetY);
}

float TextureAtlas::getX () {
    return super.getX() - region.offsetX;
}

float TextureAtlas::getY () {
    return super.getY() - region.offsetY;
}

AtlasRegion& TextureAtlas::getAtlasRegion () {
    return region;
}

