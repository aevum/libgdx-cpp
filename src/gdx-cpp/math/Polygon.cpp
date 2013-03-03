
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

#include <cassert>
#include <iostream>

#include "MathUtils.hpp"
#include "Polygon.hpp"
#include "gdx-cpp/Gdx.hpp"
#include "gdx-cpp/math/Rectangle.hpp"

using namespace gdx;

Polygon::Polygon(const std::vector< float >& vertices)
  : vertices(vertices),
x(0),
y(0),
originX(0),
originY(0),
rotation(0),
scaleX(1),
scaleY(1),
dirty(false)
{
  if (vertices.size() < 6) {
     std::cerr << "polygons must contain at least 3 points." << std::endl;
     assert(false);
  }
}

std::vector<float>& Polygon::getVertices () {
    if (!dirty) return vertices;

    int numFloats = vertices.size();

    float translateX = x + originX;
    float translateY = y + originY;
    float cos = cosDeg(rotation);
    float sin = sinDeg(rotation);
    
    float x, y;
    
    for (int i = 0; i < numFloats; i += 2) {
        x = vertices[i];
        y = vertices[i + 1];

        // move vertices to local coordinates
        x -= translateX;
        y -= translateY;

        // scale if needed
        if (scaleX != 1 || scaleY != 1) {
            x *= scaleX;
            y *= scaleY;
        }

        // rotate if needed
        if (rotation != 0) {
            x = cos * x - sin * y;
            y = sin * x + cos * y;
        }

        // move vertices back to world coordinates
        x += translateX;
        y += translateY;

        vertices[i] = x;
        vertices[i + 1] = y;
    }

    dirty = false;

    return vertices;
}

void Polygon::setOrigin (float originX,float originY) {
    this->originX = originX;
    this->originY = originY;
    dirty = true;
}

void Polygon::setPosition (float x,float y) {
    this->x = x;
    this->y = y;
    dirty = true;
}

void Polygon::translate (float x,float y) {
    this->x += x;
    this->y += y;
    dirty = true;
}

void Polygon::setRotation (float degrees) {
    this->rotation = degrees;
    dirty = true;
}

void Polygon::rotate (float degrees) {
    rotation += degrees;
    dirty = true;
}

void Polygon::setScale (float scaleX,float scaleY) {
    this->scaleX = scaleX;
    this->scaleY = scaleY;
    dirty = true;
}

void Polygon::scale (float amount) {
    this->scaleX += amount;
    this->scaleY += amount;
    dirty = true;
}

float Polygon::area () {
    float area = 0;

    const std::vector<float>& vertices = getVertices();
    int numFloats = vertices.size();

    int x1, y1, x2, y2;
    for (int i = 0; i < numFloats; i += 2) {
        x1 = i;
        y1 = i + 1;
        x2 = (i + 2) % numFloats;
        y2 = (i + 3) % numFloats;

        area += vertices[x1] * vertices[y2];
        area -= vertices[x2] * vertices[y1];
    }
    area *= 0.5f;
    return area;
}

Rectangle& Polygon::getBoundingRectangle () {

    const std::vector<float>& vertices = getVertices();

    float minX = vertices[0];
    float minY = vertices[1];
    float maxX = vertices[0];
    float maxY = vertices[1];

    int numFloats = vertices.size();
    
    for (int i = 2; i < numFloats; i += 2) {
        minX = minX > vertices[i] ? vertices[i] : minX;
        minY = minY > vertices[i + 1] ? vertices[i + 1] : minY;
        maxX = maxX < vertices[i] ? vertices[i] : maxX;
        maxY = maxY < vertices[i + 1] ? vertices[i + 1] : maxY;
    }

    bounds.x = minX;
    bounds.y = minY;
    bounds.width = maxX - minX;
    bounds.height = maxY - minY;

    return bounds;
}

bool Polygon::contains (float x,float y) {
    const std::vector<float>& vertices = getVertices();
    int numFloats = vertices.size();
    int intersects = 0;

    for (int i = 0; i < numFloats; i += 2) {
        float x1 = vertices[i];
        float y1 = vertices[i + 1];
        float x2 = vertices[(i + 2) % numFloats];
        float y2 = vertices[(i + 3) % numFloats];
        gdx_log_debug("Poly Test: ", "Testing Point (%f,%f) against (%f %f) and (%f,%f)", x, y, x1, y1, x2, y2);
        if (((y1 <= y && y < y2) || (y2 <= y && y < y1)) && x < ((x2 - x1) / (y2 - y1) * (y - y1) + x1)) intersects++;
    }
    return (intersects & 1) == 1;
}

float Polygon::getX () {
    return x;
}

float Polygon::getY () {
    return y;
}

float Polygon::getOriginX () {
    return originX;
}

float Polygon::getOriginY () {
    return originY;
}

float Polygon::getRotation () {
    return rotation;
}

float Polygon::getScaleX () {
    return scaleX;
}

float Polygon::getScaleY () {
    return scaleY;
}

