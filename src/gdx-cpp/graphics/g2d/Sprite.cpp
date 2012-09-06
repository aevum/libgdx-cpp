
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

#include "Sprite.hpp"
#include <cmath>
#include <string.h>

#include "gdx-cpp/utils/NumberUtils.hpp"
#include "gdx-cpp/math/MathUtils.hpp"
#include "gdx-cpp/graphics/g2d/SpriteBatch.hpp"
#include <stdexcept>

using namespace gdx;

Sprite::Sprite()
 : color(1,1,1,1),
x(0),
y(0),
width(0),
height(0),
originX(0),
originY(0),
rotation(0),
scaleX(1),
scaleY(1),
dirty(true)
{
    setColor(1, 1, 1, 1);
}

void Sprite::set (const ptr& sprite) {
    memcpy(&vertices[0], &sprite->vertices[0], SPRITE_SIZE * sizeof(float));
    texture = sprite->texture;
    x = sprite->x;
    y = sprite->y;
    width = sprite->width;
    height = sprite->height;
    originX = sprite->originX;
    originY = sprite->originY;
    rotation = sprite->rotation;
    scaleX = sprite->scaleX;
    scaleY = sprite->scaleY;
    dirty = sprite->dirty;
}

void Sprite::setBounds (float x,float y,float width,float height) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;

    if (dirty) return;

    float x2 = x + width;
    float y2 = y + height;

    vertices[X1] = x;
    vertices[Y1] = y;

    vertices[X2] = x;
    vertices[Y2] = y2;

    vertices[X3] = x2;
    vertices[Y3] = y2;

    vertices[X4] = x2;
    vertices[Y4] = y;

    if (rotation != 0 || scaleX != 1 || scaleY != 1) dirty = true;
}

void Sprite::setSize (float width,float height) {
    this->width = width;
    this->height = height;

    if (dirty) return;

    float x2 = x + width;
    float y2 = y + height;
    
    vertices[X1] = x;
    vertices[Y1] = y;

    vertices[X2] = x;
    vertices[Y2] = y2;

    vertices[X3] = x2;
    vertices[Y3] = y2;

    vertices[X4] = x2;
    vertices[Y4] = y;

    if (rotation != 0 || scaleX != 1 || scaleY != 1) dirty = true;
}

void Sprite::setPosition (float x,float y) {
    translate(x - this->x, y - this->y);
}

void Sprite::translate (float xAmount,float yAmount) {
    x += xAmount;
    y += yAmount;

    if (dirty) return;

    vertices[X1] += xAmount;
    vertices[Y1] += yAmount;

    vertices[X2] += xAmount;
    vertices[Y2] += yAmount;

    vertices[X3] += xAmount;
    vertices[Y3] += yAmount;

    vertices[X4] += xAmount;
    vertices[Y4] += yAmount;
}

void Sprite::setColor (const Color& tint) {
    float color = tint.toFloatBits();
    vertices[C1] = color;
    vertices[C2] = color;
    vertices[C3] = color;
    vertices[C4] = color;
}

void Sprite::setColor (float r,float g,float b,float a) {
    int intBits = ((int)(255 * a) << 24) | ((int)(255 * b) << 16) | ((int)(255 * g) << 8) | ((int)(255 * r));

    float color =  NumberUtils::intBitsToFloat(intBits & 0xfeffffff);

    vertices[C1] = color;
    vertices[C2] = color;
    vertices[C3] = color;
    vertices[C4] = color;
}

void Sprite::setOrigin (float originX,float originY) {
    this->originX = originX;
    this->originY = originY;
    dirty = true;
}

void Sprite::setRotation (float degrees) {
    this->rotation = degrees;
    dirty = true;
}

void Sprite::rotate (float degrees) {
    rotation += degrees;
    dirty = true;
}

void Sprite::rotate90 (bool clockwise) {
    if (clockwise) {
        float temp = vertices[V1];
        vertices[V1] = vertices[V4];
        vertices[V4] = vertices[V3];
        vertices[V3] = vertices[V2];
        vertices[V2] = temp;

        temp = vertices[U1];
        vertices[U1] = vertices[U4];
        vertices[U4] = vertices[U3];
        vertices[U3] = vertices[U2];
        vertices[U2] = temp;
    } else {
        float temp = vertices[V1];
        vertices[V1] = vertices[V2];
        vertices[V2] = vertices[V3];
        vertices[V3] = vertices[V4];
        vertices[V4] = temp;

        temp = vertices[U1];
        vertices[U1] = vertices[U2];
        vertices[U2] = vertices[U3];
        vertices[U3] = vertices[U4];
        vertices[U4] = temp;
    }
}

void Sprite::setScale (float scaleXY) {
    this->scaleX = scaleXY;
    this->scaleY = scaleXY;
    dirty = true;
}

void Sprite::setScale (float scaleX,float scaleY) {
    this->scaleX = scaleX;
    this->scaleY = scaleY;
    dirty = true;
}

void Sprite::scale (float amount) {
    this->scaleX += amount;
    this->scaleY += amount;
    dirty = true;
}

const Sprite::vertex_array_t& Sprite::getVertices () {
    if (dirty) {
        dirty = false;

        float localX = -originX;
        float localY = -originY;
        float localX2 = localX + width;
        float localY2 = localY + height;
        float worldOriginX = this->x - localX;
        float worldOriginY = this->y - localY;
        if (scaleX != 1 || scaleY != 1) {
            localX *= scaleX;
            localY *= scaleY;
            localX2 *= scaleX;
            localY2 *= scaleY;
        }
        if (rotation != 0) {
            float cos = cosDeg(rotation);
            float sin = sinDeg(rotation);
            
            float localXCos = localX * cos;
            float localXSin = localX * sin;
            float localYCos = localY * cos;
            float localYSin = localY * sin;
            float localX2Cos = localX2 * cos;
            float localX2Sin = localX2 * sin;
            float localY2Cos = localY2 * cos;
            float localY2Sin = localY2 * sin;

            float x1 = localXCos - localYSin + worldOriginX;
            float y1 = localYCos + localXSin + worldOriginY;
            
            vertices[X1] = x1;
            vertices[Y1] = y1;

            float x2 = localXCos - localY2Sin + worldOriginX;
            float y2 = localY2Cos + localXSin + worldOriginY;
            vertices[X2] = x2;
            vertices[Y2] = y2;

            float x3 = localX2Cos - localY2Sin + worldOriginX;
            float y3 = localY2Cos + localX2Sin + worldOriginY;
            vertices[X3] = x3;
            vertices[Y3] = y3;

            vertices[X4] = x1 + (x3 - x2);
            vertices[Y4] = y3 - (y2 - y1);
        } else {
            float x1 = localX + worldOriginX;
            float y1 = localY + worldOriginY;
            float x2 = localX2 + worldOriginX;
            float y2 = localY2 + worldOriginY;

            vertices[X1] = x1;
            vertices[Y1] = y1;

            vertices[X2] = x1;
            vertices[Y2] = y2;

            vertices[X3] = x2;
            vertices[Y3] = y2;

            vertices[X4] = x2;
            vertices[Y4] = y1;
        }
    }
    return vertices;
}

const Rectangle& Sprite::getBoundingRectangle () {
    getVertices();

    float minx = vertices[X1];
    float miny = vertices[Y1];
    float maxx = vertices[X1];
    float maxy = vertices[Y1];

    minx = minx > vertices[X2] ? vertices[X2] : minx;
    minx = minx > vertices[X3] ? vertices[X3] : minx;
    minx = minx > vertices[X4] ? vertices[X4] : minx;

    maxx = maxx < vertices[X2] ? vertices[X2] : maxx;
    maxx = maxx < vertices[X3] ? vertices[X3] : maxx;
    maxx = maxx < vertices[X4] ? vertices[X4] : maxx;

    miny = miny > vertices[Y2] ? vertices[Y2] : miny;
    miny = miny > vertices[Y3] ? vertices[Y3] : miny;
    miny = miny > vertices[Y4] ? vertices[Y4] : miny;

    maxy = maxy < vertices[Y2] ? vertices[Y2] : maxy;
    maxy = maxy < vertices[Y3] ? vertices[Y3] : maxy;
    maxy = maxy < vertices[Y4] ? vertices[Y4] : maxy;

    bounds.x = minx;
    bounds.y = miny;
    bounds.width = maxx - minx;
    bounds.height = maxy - miny;

    return bounds;
}

void Sprite::draw (SpriteBatch& spriteBatch) {
    spriteBatch.draw(*texture, getVertices().data(), 20, 0, SPRITE_SIZE);
}

void Sprite::draw (SpriteBatch& spriteBatch,float alphaModulation) {
    Color color = getColor();
    float oldAlpha = color.a;
    color.a *= alphaModulation;
    setColor(color);
    draw(spriteBatch);
    color.a = oldAlpha;
    setColor(color);
}

float Sprite::getX () {
    return x;
}

float Sprite::getY () {
    return y;
}

float Sprite::getWidth () {
    return width;
}

float Sprite::getHeight () {
    return height;
}

float Sprite::getOriginX () {
    return originX;
}

float Sprite::getOriginY () {
    return originY;
}

float Sprite::getRotation () {
    return rotation;
}

float Sprite::getScaleX () {
    return scaleX;
}

float Sprite::getScaleY () {
    return scaleY;
}

const Color& Sprite::getColor () {
    float floatBits = vertices[C1];
    int intBits = NumberUtils::floatToRawIntBits(vertices[C1]);
    color.r = (intBits & 0xff) / 255.0f;
    color.g = (((unsigned int )intBits >> 8) & 0xff) / 255.0f;
    color.b = (((unsigned int )intBits >> 16) & 0xff) / 255.0f;
    color.a = (((unsigned int)intBits >> 24) & 0xff) / 255.0f;
    return color;
}

void Sprite::setRegion (float u,float v,float u2,float v2) {
    this->u = u;
    this->v = v;
    this->u2 = u2;
    this->v2 = v2;

    vertices[U1] = u;
    vertices[V1] = v2;

    vertices[U2] = u;
    vertices[V2] = v;

    vertices[U3] = u2;
    vertices[V3] = v;

    vertices[U4] = u2;
    vertices[V4] = v2;
}

void Sprite::setU (float u) {
    this->u = u;
    vertices[U1] = u;
    vertices[U2] = u;
}

void Sprite::setV (float v) {
    this->v = v;
    vertices[V2] = v;
    vertices[V3] = v;
}

void Sprite::setU2 (float u2) {
    this->u2 = u2;
    vertices[U3] = u2;
    vertices[U4] = u2;
}

void Sprite::setV2 (float v2) {
    this->v2 = v2;
    vertices[V1] = v2;
    vertices[V4] = v2;
}

void Sprite::flip (bool x,bool y) {
    TextureRegion::flip(x, y);
    if (x) {
        float temp = vertices[U1];
        vertices[U1] = vertices[U3];
        vertices[U3] = temp;
        temp = vertices[U2];
        vertices[U2] = vertices[U4];
        vertices[U4] = temp;
    }
    if (y) {
        float temp = vertices[V1];
        vertices[V1] = vertices[V3];
        vertices[V3] = temp;
        temp = vertices[V2];
        vertices[V2] = vertices[V4];
        vertices[V4] = temp;
    }
}

void Sprite::scroll (float xAmount,float yAmount) {
    if (xAmount != 0) {
        float u = std::fmod ((vertices[U1] + xAmount), 1);
        float u2 = u + width / texture->getWidth();
        this->u = u;
        this->u2 = u2;
        vertices[U1] = u;
        vertices[U2] = u;
        vertices[U3] = u2;
        vertices[U4] = u2;
    }
    if (yAmount != 0) {
        float v = std::fmod ((vertices[V2] + yAmount) , 1.0f);
        float v2 = v + height / texture->getHeight();
        this->v = v;
        this->v2 = v2;
        vertices[V1] = v2;
        vertices[V2] = v;
        vertices[V3] = v;
        vertices[V4] = v2;
    }
}

Sprite::Sprite(ptr _sprite) :
 color(1,1,1,1)
{
    this->set(_sprite);
}
Sprite::Sprite(Texture::ptr texture) :
 color(1,1,1,1)
{
    initialize(texture, 0, 0, texture->getWidth(), texture->getHeight());
}

Sprite::Sprite(Texture::ptr texture, int srcWidth, int srcHeight) :
    color(1,1,1,1)
{
    initialize(texture, 0, 0, srcWidth, srcHeight);
}

Sprite::Sprite(Texture::ptr texture, int srcX, int srcY, int srcWidth, int srcHeight) : color(1,1,1,1) {
    initialize(texture, srcX, srcY, srcWidth, srcHeight);
}

void Sprite::initialize(Texture::ptr texture, int srcX, int srcY, int srcWidth, int srcHeight)
{
    if (!texture)
        throw std::runtime_error("texture cannot be null.");

    this->scaleX = 1;
    this->scaleY = 1;
    this->dirty = true;
    this->x = this->y = this->width = this->height = 0;
    
    this->rotation = 0;
    
    this->texture = texture;
    
    TextureRegion::setRegion(srcX, srcY, srcWidth, srcHeight);
    setColor(1, 1, 1, 1);
    setSize(std::abs(srcWidth), std::abs(srcHeight));
    setOrigin(width / 2, height / 2);
}

Sprite::Sprite(const TextureRegion& region) : color(1,1,1,1) {
    this->scaleX = 1;
    this->scaleY = 1;
    this->dirty = true;
    this->x = this->y = this->width = this->height = 0;
    
    this->rotation = 0;
    
    TextureRegion::setRegion(region);
    setColor(1, 1, 1, 1);
    setSize(std::abs(region.getRegionWidth()), std::abs(region.getRegionHeight()));
    setOrigin(width / 2, height / 2);
}

Sprite::Sprite(const TextureRegion& region, int srcX, int srcY, int srcWidth, int srcHeight) : color(1,1,1,1) {
    this->scaleX = 1;
    this->scaleY = 1;
    this->dirty = true;
    this->x = this->y = this->width = this->height = 0;
    
    this->rotation = 0;
    
    TextureRegion::setRegion(region, srcX, srcY, srcWidth, srcHeight);
    setColor(1, 1, 1, 1);
    setSize(std::abs(srcWidth), std::abs(srcHeight));
    setOrigin(width / 2, height / 2);
}

Sprite::~Sprite() {
}
