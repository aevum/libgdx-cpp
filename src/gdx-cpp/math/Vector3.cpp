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

#include "Vector3.hpp"

#include <cmath>
#include <string>
#include <sstream>
#include <assert.h>

#include "Matrix4.hpp"
#include <gdx-cpp/utils/NumberUtils.hpp>

using namespace gdx;

Vector3 Vector3::X(1, 0, 0);
Vector3 Vector3::Y(0, 1, 0);
Vector3 Vector3::Z(0, 0, 1);

Vector3 Vector3::_tmp;
Vector3 Vector3::_tmp2;
Vector3 Vector3::_tmp3;

Vector3::Vector3() : x(0),
y(0),
z(0)
{
}

Vector3::~Vector3()
{
}

Vector3& Vector3::operator=(const Vector3& other)
{
    this->set(other.x, other.y, other.z);
    return *this;
}

bool Vector3::operator==(const Vector3& other) const
{
    if (this == &other) return true;
    //TODO
//   if (NumberUtils.floatToIntBits(x) != NumberUtils.floatToIntBits(other.x)) return false;
//   if (NumberUtils.floatToIntBits(y) != NumberUtils.floatToIntBits(other.y)) return false;
//   if (NumberUtils.floatToIntBits(z) != NumberUtils.floatToIntBits(other.z)) return false;
    return true;
}

Vector3::Vector3 (float x, float y, float z) {
    this->set(x, y, z);
}

Vector3::Vector3(const Vector3& vector) {
    this->set(vector);
}

Vector3::Vector3(float* values) {
    this->set(values[0], values[1], values[2]);
}

Vector3& Vector3::set(float x, float y, float z)  {
    this->x = x;
    this->y = y;
    this->z = z;
    return *this;
}

Vector3& Vector3::set(const Vector3& vector) {
    return this->set(vector.x, vector.y, vector.z);
}

Vector3& Vector3::set(const float* values) {
    return this->set(values[0], values[1], values[2]);
}

Vector3 Vector3::cpy() {
    return Vector3(*this);
}

Vector3& Vector3::tmp() const {
    return _tmp.set(*this);
}

Vector3& Vector3::tmp2() const {
    return _tmp2.set(*this);
}

Vector3& Vector3::tmp3() const {
    return _tmp3.set(*this);
}

Vector3& Vector3::add(const Vector3& vector) {
    return this->add(vector.x, vector.y, vector.z);
}

Vector3& Vector3::add(float x, float y, float z) {
    return this->set(this->x + x, this->y + y, this->z + z);
}

Vector3& Vector3::add(float values) {
    return this->set(this->x + values, this->y + values, this->z + values);
}

Vector3& Vector3::sub(const Vector3& a_vec) {
    return this->sub(a_vec.x, a_vec.y, a_vec.z);
}

Vector3& Vector3::sub(float x, float y, float z) {
    return this->set(this->x - x, this->y - y, this->z - z);
}

Vector3& Vector3::sub(float value) {
    return this->set(this->x - value, this->y - value, this->z - value);
}

Vector3& Vector3::mul(float value) {
    return this->set(this->x * value, this->y * value, this->z * value);
}

Vector3& Vector3::div(float value) {
    float d = 1 / value;
    return this->set(this->x * d, this->y * d, this->z * d);
}

float Vector3::len() const {
    return (float)std::sqrt(x * x + y * y + z * z);
}

float Vector3::len2() {
    return x * x + y * y + z * z;
}

bool Vector3::idt(const Vector3& vector) {
    return x == vector.x && y == vector.y && z == vector.z;
}

float Vector3::dst(const Vector3& vector) {
    float a = vector.x - x;
    float b = vector.y - y;
    float c = vector.z - z;

    a *= a;
    b *= b;
    c *= c;

    return (float)std::sqrt(a + b + c);
}

Vector3& Vector3::nor() {
    if (this->len() == 0) {
        return *this;
    } else {
        return this->div(len());
    }
}

float Vector3::dot(const Vector3& vector) const{
    return x * vector.x + y * vector.y + z * vector.z;
}

Vector3& Vector3::crs(const Vector3& vector) {
    return this->set(y * vector.z - z * vector.y, z * vector.x - x * vector.z, x * vector.y - y * vector.x);
}

Vector3 Vector3::crs(float x, float y, float z) {
    return this->set(this->y * z - this->z * y, this->z * x - this->x * z, this->x * y - this->y * x);
}

Vector3& Vector3::mul(const Matrix4& matrix) {
    return this->set(x * matrix.val[Matrix4::M00] + y * matrix.val[Matrix4::M01] + z * matrix.val[Matrix4::M02] + matrix.val[Matrix4::M03], x
                     * matrix.val[Matrix4::M10] + y * matrix.val[Matrix4::M11] + z * matrix.val[Matrix4::M12] + matrix.val[Matrix4::M13], x * matrix.val[Matrix4::M20] + y
                     * matrix.val[Matrix4::M21] + z * matrix.val[Matrix4::M22] + matrix.val[Matrix4::M23]);
}

Vector3& Vector3::prj(const Matrix4& matrix) {
    float l_w = x * matrix.val[Matrix4::M30] + y * matrix.val[Matrix4::M31] + z * matrix.val[Matrix4::M32] + matrix.val[Matrix4::M33];
    return this->set((x * matrix.val[Matrix4::M00] + y * matrix.val[Matrix4::M01] + z * matrix.val[Matrix4::M02] + matrix.val[Matrix4::M03]) / l_w,
                     (x * matrix.val[Matrix4::M10] + y * matrix.val[Matrix4::M11] + z * matrix.val[Matrix4::M12] + matrix.val[Matrix4::M13]) / l_w,
                     (x * matrix.val[Matrix4::M20] + y * matrix.val[Matrix4::M21] + z * matrix.val[Matrix4::M22] + matrix.val[Matrix4::M23]) / l_w);
}

Vector3& Vector3::rot(const Matrix4& matrix) {
    return this->set(x * matrix.val[Matrix4::M00] + y * matrix.val[Matrix4::M01] + z * matrix.val[Matrix4::M02], x * matrix.val[Matrix4::M10] + y
                     * matrix.val[Matrix4::M11] + z * matrix.val[Matrix4::M12], x * matrix.val[Matrix4::M20] + y * matrix.val[Matrix4::M21] + z * matrix.val[Matrix4::M22]);
}

bool Vector3::isUnit() const {
    return this->len() == 1;
}

bool Vector3::isZero() {
    return x == 0 && y == 0 && z == 0;
}

Vector3 Vector3::lerp(Vector3& target, float alpha) {
    Vector3 r = this->mul(1.0f - alpha);
    r.add(target.tmp().mul(alpha));
    return r;
}

Vector3& Vector3::slerp(Vector3& target, float alpha) {
    float dot = this->dot(target);
    if (dot > 0.99995f || dot < 0.9995f) {
        this->add(target.tmp().sub(*this).mul(alpha));
        this->nor();
        return *this;
    }

    if (dot > 1) dot = 1;
    if (dot < -1) dot = -1;

    float theta0 = (float)std::acos(dot);
    float theta = theta0 * alpha;
    Vector3 v2 = target.tmp().sub(x * dot, y * dot, z * dot);
    v2.nor();
    return this->mul((float)std::cos(theta)).add(v2.mul((float)std::sin(theta))).nor();
}

std::string Vector3::toString() {
    std::stringstream ss;
    ss << x << "," << y << "," << z;
    return ss.str();
}

float Vector3::dot(float x, float y, float z) {
    return this->x * x + this->y * y + this->z * z;
}

float Vector3::dst2(Vector3 point) {

    float a = point.x - x;
    float b = point.y - y;
    float c = point.z - z;

    a *= a;
    b *= b;
    c *= c;

    return a + b + c;
}

float Vector3::dst2(float x, float y, float z) {
    float a = x - this->x;
    float b = y - this->y;
    float c = z - this->z;

    a *= a;
    b *= b;
    c *= c;

    return a + b + c;
}

float Vector3::dst(float x, float y, float z) {
    return (float)std::sqrt(dst2(x, y, z));
}

int Vector3::hashCode() {
    int prime = 31;
    int result = 1;
    result = prime * result + NumberUtils::floatToIntBits(x);
    result = prime * result + NumberUtils::floatToIntBits(y);
    result = prime * result + NumberUtils::floatToIntBits(z);
    return result;
}

Vector3& Vector3::scale(float scalarX, float scalarY, float scalarZ) {
    x *= scalarX;
    y *= scalarY;
    z *= scalarZ;
    return *this;
}
