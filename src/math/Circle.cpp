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


#include "Circle.hpp"
#include "Vector2.hpp"

using namespace gdx_cpp::math;

Circle::Circle(): x(0.0), y(0.0), radius(0.0)
{

}

Circle::~Circle()
{

}

Circle& Circle::operator=(const Circle& other)
{
    return *this;
}

bool Circle::operator==(const Circle& other) const
{
///TODO: return ...;
}


Circle::Circle(float _x, float _y, float _radius): x(_x), y(_y), radius(_radius)
{

}

Circle::Circle(const Vector2& position, float _radius): x(position.x), y(position.y), radius(_radius)
{
}

bool Circle::contains (float _x, float _y) {
    _x = this->x - _x;
    _y = this->y - _y;
    return _x * _x + _y * _y <= radius * radius;
}

bool Circle::contains (const Vector2& point) {
    float _x = this->x - point.x;
    float _y = this->y - point.y;
    return _x * _x + _y * _y <= radius * radius;
}
