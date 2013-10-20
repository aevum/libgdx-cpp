/*
    Copyright 2011 <copyright holder> <email>

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/


#include <algorithm>
#include <sstream>
#include <string>

#include "Rectangle.hpp"

using namespace gdx;

Rectangle::Rectangle(): x(0.0),
y(0.0),
width(0.0),
height(0.0)
{

}


Rectangle::Rectangle (float _x, float _y, float _width, float _height): x(_x),
y(_y),
width(_width),
height(_height)
{

}

Rectangle::Rectangle(const Rectangle& other)
{
    set(other);
}

Rectangle::~Rectangle()
{

}

Rectangle& Rectangle::operator=(const Rectangle& other)
{
    this->x = other.x;
    this->y = other.y;
    this->width = other.width;
    this->height = other.height; 
    return *this;
}


float Rectangle::getX () const
{
    return x;
}

void Rectangle::setX (float _x)
{
    x = _x;
}

float Rectangle::getY () const
{
    return y;
}
void Rectangle::setY (float _y)
{
    y = _y;
}
float Rectangle::getWidth () const
{
    return width;
}
void Rectangle::setWidth (float _width)
{
    width = _width;
}
float Rectangle::getHeight () const
{
    return height;
}
void Rectangle::setHeight (float _height)
{
    height = _height;
}

bool Rectangle::contains (const Rectangle& rectangle)
{
    float xmin = rectangle.x;
    float xmax = xmin + rectangle.width;

    float ymin = rectangle.y;
    float ymax = ymin + rectangle.height;

    return ((xmin > x && xmin < x + width) && (xmax > x && xmax < x + width))
           && ((ymin > y && ymin < y + height) && (ymax > y && ymax < y + height));
}

bool Rectangle::overlaps (const Rectangle& rectangle)
{
    return !(x > rectangle.x + rectangle.width || x + width < rectangle.x || y > rectangle.y + rectangle.height || y + height < rectangle.y);
}

void Rectangle::set (float x, float y, float width, float height)
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

bool Rectangle::contains (float x, float y)
{
    return this->x < x && this->x + this->width > x && this->y < y && this->y + this->height > y;
}

void Rectangle::set (const Rectangle& rect) {
    this->x = rect.x;
    this->y = rect.y;
    this->width = rect.width;
    this->height = rect.height;
}


void Rectangle::merge(const Rectangle& rect)
{
    float minX = std::min(x, rect.x);
    float maxX = std::max(x + width, rect.x + rect.width);
    x = minX;
    width = maxX - minX;

    float minY = std::min(y, rect.y);
    float maxY = std::max(y + height, rect.y + rect.height);
    y = minY;
    height = maxY - minY;
}

std::string Rectangle::toString ()
{
    std::stringstream ss;
    ss << x << "," << y << "," << width << "," << height;
    return ss.str();
}
