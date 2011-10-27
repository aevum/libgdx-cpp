
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
#include "gdx-cpp/utils/MatrixBase.hpp"
#include <cmath>

using namespace gdx_cpp::graphics::g2d;
using namespace gdx_cpp::graphics;

TextureRegion::ptr TextureRegion::newFromTexture(gdx_cpp::graphics::Texture::ptr texture)
{
    return ptr(new TextureRegion(texture));
}

TextureRegion::ptr TextureRegion::newFromRegion(TextureRegion& region)
{
    return ptr(new TextureRegion(region));
}

/** Constructs a region with no texture and no coordinates defined. */
TextureRegion::TextureRegion ():  u(0.0), v(0.0), u2(0.0), v2(0.0)
{
}

/** Constructs a region the size of the specified texture. */
TextureRegion::TextureRegion (Texture::ptr _texture) : texture(_texture), u(0.0), v(0.0), u2(0.0), v2(0.0)
{
    setRegion(0, 0, _texture->getWidth(), _texture->getHeight());
}

/** @param width The width of the texture region. May be negative to flip the sprite when drawn.
 * @param height The height of the texture region. May be negative to flip the sprite when drawn. */
TextureRegion::TextureRegion (gdx_cpp::graphics::Texture::ptr _texture, int x, int y, int width, int height): texture(_texture), u(0.0), v(0.0), u2(0.0), v2(0.0)
{
    setRegion(x, y, width, height);
}

TextureRegion::TextureRegion (gdx_cpp::graphics::Texture::ptr _texture, float u, float v, float u2, float v2):texture(_texture), u(0.0), v(0.0), u2(0.0), v2(0.0)
{
    setRegion(u, v, u2, v2);
}

/** Constructs a region with the same texture and coordinates of the specified region. */
TextureRegion::TextureRegion (TextureRegion& region):u(0.0), v(0.0), u2(0.0), v2(0.0)
{
    setRegion(region);
}

/** Constructs a region with the same texture as the specified region and sets the coordinates relative to the specified region.
 * @param width The width of the texture region. May be negative to flip the sprite when drawn.
 * @param height The height of the texture region. May be negative to flip the sprite when drawn. */
TextureRegion::TextureRegion (TextureRegion& region, int x, int y, int width, int height):u(0.0), v(0.0), u2(0.0), v2(0.0)
{
    setRegion(region, x, y, width, height);
}



void TextureRegion::setRegion (gdx_cpp::graphics::Texture::ptr _texture) {
    this->texture = _texture;
    setRegion(0, 0, _texture->getWidth(), _texture->getHeight());
}

void TextureRegion::setRegion (int x,int y,int width,int height) {
    float invTexWidth = 1.f / texture->getWidth();
    float invTexHeight = 1.f / texture->getHeight();
    setRegion(x * invTexWidth, y * invTexHeight, (x + width) * invTexWidth, (y + height) * invTexHeight);
}

void TextureRegion::setRegion (float u,float v,float u2,float v2) {
    this->u = u;
    this->v = v;
    this->u2 = u2;
    this->v2 = v2;
}

void TextureRegion::setRegion (const TextureRegion& region) {
    texture = region.texture;
    setRegion(region.u, region.v, region.u2, region.v2);
}

void TextureRegion::setRegion (const gdx_cpp::graphics::g2d::TextureRegion& region, int x, int y, int width, int height) {
    texture = region.texture;
    setRegion(region.getRegionX() + x, region.getRegionY() + y, width, height);
}

gdx_cpp::graphics::Texture::ptr TextureRegion::getTexture () const {
    return texture;
}

void TextureRegion::setTexture (gdx_cpp::graphics::Texture::ptr) {
    this->texture = texture;
}

float TextureRegion::getU () const {
    return u;
}

void TextureRegion::setU (float u) {
    this->u = u;
}

float TextureRegion::getV () const {
    return v;
}

void TextureRegion::setV (float v) {
    this->v = v;
}

float TextureRegion::getU2 () const {
    return u2;
}

void TextureRegion::setU2 (float u2) {
    this->u2 = u2;
}

float TextureRegion::getV2 () const {
    return v2;
}

void TextureRegion::setV2 (float v2) {
    this->v2 = v2;
}

int TextureRegion::getRegionX () const {
    return (int)(u * texture->getWidth());
}

void TextureRegion::setRegionX (int x) {
    setU(x / (float)texture->getWidth());
}

int TextureRegion::getRegionY () const {
    return (int)(v * texture->getHeight());
}

void TextureRegion::setRegionY (int y) {
    setV(y / (float)texture->getHeight());
}

int TextureRegion::getRegionWidth () const {
    return (int)((u2 - u) * texture->getWidth());
}

void TextureRegion::setRegionWidth (int width) {
    setU2(u + width / (float)texture->getWidth());
}

int TextureRegion::getRegionHeight () const {
    return (int)((v2 - v) * texture->getHeight());
}

void TextureRegion::setRegionHeight (int height) {
    setV2(v + height / (float)texture->getHeight());
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
        float width = (u2 - u) * texture->getWidth();
        u = std::fmod((u + xAmount), 1);
        u2 = u + width / texture->getWidth();
    }
    if (yAmount != 0) {
        float height = (v2 - v) * texture->getHeight();
        v = std::fmod((v + yAmount), 1);
        v2 = v + height / texture->getHeight();
    }
}

gdx_cpp::utils::MatrixBase<TextureRegion::ptr> TextureRegion::split (int tileWidth, int tileHeight)
{
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

    const int rows = height / tileHeight;
    const int cols = width / tileWidth;

    int startX = x;
    gdx_cpp::utils::MatrixBase<TextureRegion::ptr> matrix(rows, cols);

    for (int row = 0; row < rows; row++, y += tileHeight) {
        x = startX;
        for (int col = 0; col < cols; col++, x += tileWidth) {
            matrix[row][col] = TextureRegion::ptr(new TextureRegion(texture, x, y, tileWidth, tileHeight));
        }
    }

    return matrix;
}



gdx_cpp::utils::MatrixBase<TextureRegion::ptr> TextureRegion::split (gdx_cpp::graphics::Texture::ptr texture, int tileWidth, int tileHeight) {
    TextureRegion region(texture);
    return region.split(tileWidth, tileHeight);
}

