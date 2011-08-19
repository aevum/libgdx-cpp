
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

#include "TextureRegion.hpp"

using namespace gdx_cpp::graphics::g2d;

void TextureRegion::setRegion (const gdx_cpp::graphics::Texture& texture) {
    this.texture = texture;
    setRegion(0, 0, texture.getWidth(), texture.getHeight());
}

void TextureRegion::setRegion (int x,int y,int width,int height) {
    float invTexWidth = 1f / texture.getWidth();
    float invTexHeight = 1f / texture.getHeight();
    setRegion(x * invTexWidth, y * invTexHeight, (x + width) * invTexWidth, (y + height) * invTexHeight);
}

void TextureRegion::setRegion (float u,float v,float u2,float v2) {
    this.u = u;
    this.v = v;
    this.u2 = u2;
    this.v2 = v2;
}

void TextureRegion::setRegion (const TextureRegion& region) {
    texture = region.texture;
    setRegion(region.u, region.v, region.u2, region.v2);
}

void TextureRegion::setRegion (const TextureRegion& region,int x,int y,int width,int height) {
    texture = region.texture;
    setRegion(region.getRegionX() + x, region.getRegionY() + y, width, height);
}

gdx_cpp::graphics::Texture& TextureRegion::getTexture () {
    return texture;
}

void TextureRegion::setTexture (const gdx_cpp::graphics::Texture& texture) {
    this.texture = texture;
}

float TextureRegion::getU () {
    return u;
}

void TextureRegion::setU (float u) {
    this.u = u;
}

float TextureRegion::getV () {
    return v;
}

void TextureRegion::setV (float v) {
    this.v = v;
}

float TextureRegion::getU2 () {
    return u2;
}

void TextureRegion::setU2 (float u2) {
    this.u2 = u2;
}

float TextureRegion::getV2 () {
    return v2;
}

void TextureRegion::setV2 (float v2) {
    this.v2 = v2;
}

int TextureRegion::getRegionX () {
    return (int)(u * texture.getWidth());
}

void TextureRegion::setRegionX (int x) {
    setU(x / (float)texture.getWidth());
}

int TextureRegion::getRegionY () {
    return (int)(v * texture.getHeight());
}

void TextureRegion::setRegionY (int y) {
    setV(y / (float)texture.getHeight());
}

int TextureRegion::getRegionWidth () {
    return (int)((u2 - u) * texture.getWidth());
}

void TextureRegion::setRegionWidth (int width) {
    setU2(u + width / (float)texture.getWidth());
}

int TextureRegion::getRegionHeight () {
    return (int)((v2 - v) * texture.getHeight());
}

void TextureRegion::setRegionHeight (int height) {
    setV2(v + height / (float)texture.getHeight());
}

void TextureRegion::flip (bool x,bool y) {
    if (x) {
        float temp = u;
        u = u2;
        u2 = temp;
    }
    if (y) {
        float temp = v;
        v = v2;
        v2 = temp;
    }
}

void TextureRegion::scroll (float xAmount,float yAmount) {
    if (xAmount != 0) {
        float width = (u2 - u) * texture.getWidth();
        u = (u + xAmount) % 1;
        u2 = u + width / texture.getWidth();
    }
    if (yAmount != 0) {
        float height = (v2 - v) * texture.getHeight();
        v = (v + yAmount) % 1;
        v2 = v + height / texture.getHeight();
    }
}

TextureRegion* TextureRegion::split (int tileWidth,int tileHeight) {
    int x = getRegionX();
    int y = getRegionY();
    int width = getRegionWidth();
    int height = getRegionHeight();

    if (width < 0) {
        x = x - width;
        width = -width;
    }

    if (height < 0) {
        y = y - height;
        height = -height;
    }

    int rows = height / tileHeight;
    int cols = width / tileWidth;

    int startX = x;
    TextureRegion[][] tiles = new TextureRegion[rows][cols];
    for (int row = 0; row < rows; row++, y += tileHeight) {
        x = startX;
        for (int col = 0; col < cols; col++, x += tileWidth) {
            tiles[row][col] = new TextureRegion(texture, x, y, tileWidth, tileHeight);
        }
    }

    return tiles;
}

TextureRegion* TextureRegion::split (const gdx_cpp::graphics::Texture& texture,int tileWidth,int tileHeight) {
    TextureRegion region = new TextureRegion(texture);
    return region.split(tileWidth, tileHeight);
}

