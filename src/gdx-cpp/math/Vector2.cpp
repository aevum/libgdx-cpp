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


#include "Vector2.hpp"

#include <cmath>
#include <string>
#include <sstream>

#include "MathUtils.hpp"
#include "Matrix3.hpp"

using namespace gdx;

Vector2 Vector2::_tmp;

Vector2::Vector2() : x(0.0),
y(0.0)
{
}

Vector2::Vector2(float _x, float _y) : x(_x),
y(_y)
{
}

Vector2::Vector2(const Vector2& other)
{
    set(other);
}

float Vector2::len () {
    return (float)std::sqrt(x * x + y * y);
}

Vector2::~Vector2()
{
}

Vector2& Vector2::operator=(const Vector2& other)
{
    set(other);
    return *this;
}

bool Vector2::operator==(const Vector2& other) const
{
    if (this == &other) {
        return true;
    }

    return this->x == other.x && this->x == other.y;
}

Vector2& Vector2::set (const Vector2& v) {
    this->x = v.x;
    this->y = v.y;
    return *this;
}

Vector2& Vector2::set (float _x, float _y) {
    x = _x;
    y = _y;
    return *this;
}

Vector2& Vector2::sub (const Vector2& v) {
    x -= v.x;
    y -= v.y;
    return *this;
}

Vector2& Vector2::nor () {
    float len = this->len();
    if (len != 0) {
        x /= len;
        y /= len;
    }
    return *this;
}

Vector2& Vector2::add (const Vector2& v) {
    x += v.x;
    y += v.y;
    return *this;
}

Vector2& Vector2::add (float x, float y) {
    this->x += x;
    this->y += y;
    return *this;
}

float Vector2::dot (const Vector2& v) {
    return x * v.x + y * v.y;
}


Vector2& Vector2::mul (float scalar) {
    x *= scalar;
    y *= scalar;
    return *this;
}

float Vector2::dst (const Vector2& v) const {
    float x_d = v.x - x;
    float y_d = v.y - y;
    return (float)std::sqrt(x_d * x_d + y_d * y_d);
}

float Vector2::dst (float x, float y) {
    float x_d = x - this->x;
    float y_d = y - this->y;
    return (float)std::sqrt(x_d * x_d + y_d * y_d);
}

float Vector2::dst2 (const Vector2& v) {
    float x_d = v.x - x;
    float y_d = v.y - y;
    return x_d * x_d + y_d * y_d;
}

std::string Vector2::toString () {
    std::stringstream ss;
    ss <<  x << ":" << y << "]";
    return ss.str();
}

Vector2& Vector2::sub (float x, float y) {
    this->x -= x;
    this->y -= y;
    return *this;
}

Vector2& Vector2::tmp () {
    return _tmp.set(*this);
}

Vector2& Vector2::mul (const Matrix3& mat) {
    float x = this->x * mat.vals[0] + this->y * mat.vals[3] + mat.vals[6];
    float y = this->x * mat.vals[1] + this->y * mat.vals[4] + mat.vals[7];
    this->x = x;
    this->y = y;
    return *this;
}

float Vector2::crs (const Vector2& v) {
    return this->x * v.y - this->y * v.x;
}

float Vector2::crs (float x, float y) {
    return this->x * y - this->y * x;
}

float Vector2::angle () {
    float angle =  (float) std::atan2(y, x) *  detail::radiansToDegrees;
    if (angle < 0) angle += 360;
    return angle;
}

Vector2 Vector2::rotate (float angle) {
    float rad = angle * detail::degreesToRadians;
    float cos = (float)std::cos(rad);
    float sin = (float)std::sin(rad);

    float newX = this->x * cos - this->y * sin;
    float newY = this->x * sin + this->y * cos;

    this->x = newX;
    this->y = newY;

    return *this;
}

Vector2 Vector2::lerp (Vector2& target, float alpha) {
    Vector2 r = this->mul(1.0f - alpha);
    r.add(target.tmp().mul(alpha));
    return r;
}


