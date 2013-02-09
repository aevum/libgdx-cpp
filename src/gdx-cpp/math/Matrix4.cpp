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
#include <string.h>
#include <cassert>
#include <cmath>
#include <iostream>
#include <string>
#include <sstream>

#include "MathUtils.hpp"
#include "Matrix3.hpp"
#include "Matrix4.hpp"
#include "Quaternion.hpp"
#include "Vector3.hpp"

using namespace gdx;

float _tmp[16];

Matrix4::Matrix4(const Matrix4& other)
{
    this->set(other);
}

Matrix4::~Matrix4()
{
}

Matrix4& Matrix4::operator=(const Matrix4& other)
{
    return this->set(other);
}

Matrix4::Matrix4 () {
    memset(val, 0, sizeof(float) * 16);
    val[M00] = 1;
    val[M11] = 1;
    val[M22] = 1;
    val[M33] = 1;
}

Matrix4::Matrix4 (float* values) {
    this->set(values);
}

Matrix4::Matrix4 (const Quaternion& quaternion) {
    this->set(quaternion);
}

Matrix4& Matrix4::set(const Matrix4& matrix) {
    return this->set(matrix.val);
}

Matrix4& Matrix4::set(const float* values) {
    memcpy(val, values, sizeof(float) * 15);
    return *this;
}

Matrix4& Matrix4::set(const Quaternion& quaternion) {
    // Compute quaternion factors
    float l_xx = quaternion.x * quaternion.x;
    float l_xy = quaternion.x * quaternion.y;
    float l_xz = quaternion.x * quaternion.z;
    float l_xw = quaternion.x * quaternion.w;
    float l_yy = quaternion.y * quaternion.y;
    float l_yz = quaternion.y * quaternion.z;
    float l_yw = quaternion.y * quaternion.w;
    float l_zz = quaternion.z * quaternion.z;
    float l_zw = quaternion.z * quaternion.w;
    // Set matrix from quaternion
    val[M00] = 1 - 2 * (l_yy + l_zz);
    val[M01] = 2 * (l_xy - l_zw);
    val[M02] = 2 * (l_xz + l_yw);
    val[M03] = 0;
    val[M10] = 2 * (l_xy + l_zw);
    val[M11] = 1 - 2 * (l_xx + l_zz);
    val[M12] = 2 * (l_yz - l_xw);
    val[M13] = 0;
    val[M20] = 2 * (l_xz - l_yw);
    val[M21] = 2 * (l_yz + l_xw);
    val[M22] = 1 - 2 * (l_xx + l_yy);
    val[M23] = 0;
    val[M30] = 0;
    val[M31] = 0;
    val[M32] = 0;
    val[M33] = 1;
    return *this;
}

void Matrix4::set(Vector3& xAxis, Vector3& yAxis, Vector3& zAxis, const Vector3& pos) {
    val[M00] = xAxis.x;
    val[M01] = xAxis.y;
    val[M02] = xAxis.z;
    val[M10] = yAxis.x;
    val[M11] = yAxis.y;
    val[M12] = yAxis.z;
    val[M20] = -zAxis.x;
    val[M21] = -zAxis.y;
    val[M22] = -zAxis.z;
    val[M03] = pos.x;
    val[M13] = pos.y;
    val[M23] = pos.z;
    val[M30] = 0;
    val[M31] = 0;
    val[M32] = 0;
    val[M33] = 1;
}

Matrix4::ptr Matrix4::cpy() {
    return Matrix4::ptr(new Matrix4(*this));
}

Matrix4& Matrix4::trn(const Vector3& vector) {
    val[M03] += vector.x;
    val[M13] += vector.y;
    val[M23] += vector.z;
    return *this;
}

Matrix4& Matrix4::trn(float x, float y, float z) {
    val[M03] += x;
    val[M13] += y;
    val[M23] += z;
    return *this;
}

float* Matrix4::getValues() {
    return val;
}

Matrix4& Matrix4::mul(const Matrix4& matrix) {
    _tmp[M00] = val[M00] * matrix.val[M00] + val[M01] * matrix.val[M10] + val[M02] * matrix.val[M20] + val[M03]
                * matrix.val[M30];
    _tmp[M01] = val[M00] * matrix.val[M01] + val[M01] * matrix.val[M11] + val[M02] * matrix.val[M21] + val[M03]
                * matrix.val[M31];
    _tmp[M02] = val[M00] * matrix.val[M02] + val[M01] * matrix.val[M12] + val[M02] * matrix.val[M22] + val[M03]
                * matrix.val[M32];
    _tmp[M03] = val[M00] * matrix.val[M03] + val[M01] * matrix.val[M13] + val[M02] * matrix.val[M23] + val[M03]
                * matrix.val[M33];
    _tmp[M10] = val[M10] * matrix.val[M00] + val[M11] * matrix.val[M10] + val[M12] * matrix.val[M20] + val[M13]
                * matrix.val[M30];
    _tmp[M11] = val[M10] * matrix.val[M01] + val[M11] * matrix.val[M11] + val[M12] * matrix.val[M21] + val[M13]
                * matrix.val[M31];
    _tmp[M12] = val[M10] * matrix.val[M02] + val[M11] * matrix.val[M12] + val[M12] * matrix.val[M22] + val[M13]
                * matrix.val[M32];
    _tmp[M13] = val[M10] * matrix.val[M03] + val[M11] * matrix.val[M13] + val[M12] * matrix.val[M23] + val[M13]
                * matrix.val[M33];
    _tmp[M20] = val[M20] * matrix.val[M00] + val[M21] * matrix.val[M10] + val[M22] * matrix.val[M20] + val[M23]
                * matrix.val[M30];
    _tmp[M21] = val[M20] * matrix.val[M01] + val[M21] * matrix.val[M11] + val[M22] * matrix.val[M21] + val[M23]
                * matrix.val[M31];
    _tmp[M22] = val[M20] * matrix.val[M02] + val[M21] * matrix.val[M12] + val[M22] * matrix.val[M22] + val[M23]
                * matrix.val[M32];
    _tmp[M23] = val[M20] * matrix.val[M03] + val[M21] * matrix.val[M13] + val[M22] * matrix.val[M23] + val[M23]
                * matrix.val[M33];
    _tmp[M30] = val[M30] * matrix.val[M00] + val[M31] * matrix.val[M10] + val[M32] * matrix.val[M20] + val[M33]
                * matrix.val[M30];
    _tmp[M31] = val[M30] * matrix.val[M01] + val[M31] * matrix.val[M11] + val[M32] * matrix.val[M21] + val[M33]
                * matrix.val[M31];
    _tmp[M32] = val[M30] * matrix.val[M02] + val[M31] * matrix.val[M12] + val[M32] * matrix.val[M22] + val[M33]
                * matrix.val[M32];
    _tmp[M33] = val[M30] * matrix.val[M03] + val[M31] * matrix.val[M13] + val[M32] * matrix.val[M23] + val[M33]
                * matrix.val[M33];
    return this->set(_tmp);
}

Matrix4& Matrix4::tra() {
    _tmp[M00] = val[M00];
    _tmp[M01] = val[M10];
    _tmp[M02] = val[M20];
    _tmp[M03] = val[M30];
    _tmp[M10] = val[M01];
    _tmp[M11] = val[M11];
    _tmp[M12] = val[M21];
    _tmp[M13] = val[M31];
    _tmp[M20] = val[M02];
    _tmp[M21] = val[M12];
    _tmp[M22] = val[M22];
    _tmp[M23] = val[M32];
    _tmp[M30] = val[M03];
    _tmp[M31] = val[M13];
    _tmp[M32] = val[M23];
    _tmp[M33] = val[M33];
    return this->set(_tmp);
}

/** Sets the matrix to an identity matrix
 *
 * @return This matrix for chaining */
Matrix4& Matrix4::idt() {
    val[M00] = 1;
    val[M01] = 0;
    val[M02] = 0;
    val[M03] = 0;
    val[M10] = 0;
    val[M11] = 1;
    val[M12] = 0;
    val[M13] = 0;
    val[M20] = 0;
    val[M21] = 0;
    val[M22] = 1;
    val[M23] = 0;
    val[M30] = 0;
    val[M31] = 0;
    val[M32] = 0;
    val[M33] = 1;
    return *this;
}

Matrix4& Matrix4::inv() {
    float l_det = val[M30] * val[M21] * val[M12] * val[M03] - val[M20] * val[M31] * val[M12] * val[M03] - val[M30] * val[M11]
                  * val[M22] * val[M03] + val[M10] * val[M31] * val[M22] * val[M03] + val[M20] * val[M11] * val[M32] * val[M03] - val[M10]
                  * val[M21] * val[M32] * val[M03] - val[M30] * val[M21] * val[M02] * val[M13] + val[M20] * val[M31] * val[M02] * val[M13]
                  *                        + val[M30] * val[M01] * val[M22] * val[M13] - val[M00] * val[M31] * val[M22] * val[M13] - val[M20] * val[M01] * val[M32]
                  * val[M13] + val[M00] * val[M21] * val[M32] * val[M13] + val[M30] * val[M11] * val[M02] * val[M23] - val[M10] * val[M31]
                  * val[M02] * val[M23] - val[M30] * val[M01] * val[M12] * val[M23] + val[M00] * val[M31] * val[M12] * val[M23] + val[M10]
                  * val[M01] * val[M32] * val[M23] - val[M00] * val[M11] * val[M32] * val[M23] - val[M20] * val[M11] * val[M02] * val[M33]
                  *                        + val[M10] * val[M21] * val[M02] * val[M33] + val[M20] * val[M01] * val[M12] * val[M33] - val[M00] * val[M21] * val[M12]
                  * val[M33] - val[M10] * val[M01] * val[M22] * val[M33] + val[M00] * val[M11] * val[M22] * val[M33];
    if (l_det == 0) {
        std::cerr << "non-invertible matrix" << std::endl;
        assert(false);
    }
    float inv_det = 1.0f / l_det;
    _tmp[M00] = val[M12] * val[M23] * val[M31] - val[M13] * val[M22] * val[M31] + val[M13] * val[M21] * val[M32] - val[M11]
                * val[M23] * val[M32] - val[M12] * val[M21] * val[M33] + val[M11] * val[M22] * val[M33];
    _tmp[M01] = val[M03] * val[M22] * val[M31] - val[M02] * val[M23] * val[M31] - val[M03] * val[M21] * val[M32] + val[M01]
                * val[M23] * val[M32] + val[M02] * val[M21] * val[M33] - val[M01] * val[M22] * val[M33];
    _tmp[M02] = val[M02] * val[M13] * val[M31] - val[M03] * val[M12] * val[M31] + val[M03] * val[M11] * val[M32] - val[M01]
                * val[M13] * val[M32] - val[M02] * val[M11] * val[M33] + val[M01] * val[M12] * val[M33];
    _tmp[M03] = val[M03] * val[M12] * val[M21] - val[M02] * val[M13] * val[M21] - val[M03] * val[M11] * val[M22] + val[M01]
                * val[M13] * val[M22] + val[M02] * val[M11] * val[M23] - val[M01] * val[M12] * val[M23];
    _tmp[M10] = val[M13] * val[M22] * val[M30] - val[M12] * val[M23] * val[M30] - val[M13] * val[M20] * val[M32] + val[M10]
                * val[M23] * val[M32] + val[M12] * val[M20] * val[M33] - val[M10] * val[M22] * val[M33];
    _tmp[M11] = val[M02] * val[M23] * val[M30] - val[M03] * val[M22] * val[M30] + val[M03] * val[M20] * val[M32] - val[M00]
                * val[M23] * val[M32] - val[M02] * val[M20] * val[M33] + val[M00] * val[M22] * val[M33];
    _tmp[M12] = val[M03] * val[M12] * val[M30] - val[M02] * val[M13] * val[M30] - val[M03] * val[M10] * val[M32] + val[M00]
                * val[M13] * val[M32] + val[M02] * val[M10] * val[M33] - val[M00] * val[M12] * val[M33];
    _tmp[M13] = val[M02] * val[M13] * val[M20] - val[M03] * val[M12] * val[M20] + val[M03] * val[M10] * val[M22] - val[M00]
                * val[M13] * val[M22] - val[M02] * val[M10] * val[M23] + val[M00] * val[M12] * val[M23];
    _tmp[M20] = val[M11] * val[M23] * val[M30] - val[M13] * val[M21] * val[M30] + val[M13] * val[M20] * val[M31] - val[M10]
                * val[M23] * val[M31] - val[M11] * val[M20] * val[M33] + val[M10] * val[M21] * val[M33];
    _tmp[M21] = val[M03] * val[M21] * val[M30] - val[M01] * val[M23] * val[M30] - val[M03] * val[M20] * val[M31] + val[M00]
                * val[M23] * val[M31] + val[M01] * val[M20] * val[M33] - val[M00] * val[M21] * val[M33];
    _tmp[M22] = val[M01] * val[M13] * val[M30] - val[M03] * val[M11] * val[M30] + val[M03] * val[M10] * val[M31] - val[M00]
                * val[M13] * val[M31] - val[M01] * val[M10] * val[M33] + val[M00] * val[M11] * val[M33];
    _tmp[M23] = val[M03] * val[M11] * val[M20] - val[M01] * val[M13] * val[M20] - val[M03] * val[M10] * val[M21] + val[M00]
                * val[M13] * val[M21] + val[M01] * val[M10] * val[M23] - val[M00] * val[M11] * val[M23];
    _tmp[M30] = val[M12] * val[M21] * val[M30] - val[M11] * val[M22] * val[M30] - val[M12] * val[M20] * val[M31] + val[M10]
                * val[M22] * val[M31] + val[M11] * val[M20] * val[M32] - val[M10] * val[M21] * val[M32];
    _tmp[M31] = val[M01] * val[M22] * val[M30] - val[M02] * val[M21] * val[M30] + val[M02] * val[M20] * val[M31] - val[M00]
                * val[M22] * val[M31] - val[M01] * val[M20] * val[M32] + val[M00] * val[M21] * val[M32];
    _tmp[M32] = val[M02] * val[M11] * val[M30] - val[M01] * val[M12] * val[M30] - val[M02] * val[M10] * val[M31] + val[M00]
                * val[M12] * val[M31] + val[M01] * val[M10] * val[M32] - val[M00] * val[M11] * val[M32];
    _tmp[M33] = val[M01] * val[M12] * val[M20] - val[M02] * val[M11] * val[M20] + val[M02] * val[M10] * val[M21] - val[M00]
                * val[M12] * val[M21] - val[M01] * val[M10] * val[M22] + val[M00] * val[M11] * val[M22];
    val[M00] = _tmp[M00] * inv_det;
    val[M01] = _tmp[M01] * inv_det;
    val[M02] = _tmp[M02] * inv_det;
    val[M03] = _tmp[M03] * inv_det;
    val[M10] = _tmp[M10] * inv_det;
    val[M11] = _tmp[M11] * inv_det;
    val[M12] = _tmp[M12] * inv_det;
    val[M13] = _tmp[M13] * inv_det;
    val[M20] = _tmp[M20] * inv_det;
    val[M21] = _tmp[M21] * inv_det;
    val[M22] = _tmp[M22] * inv_det;
    val[M23] = _tmp[M23] * inv_det;
    val[M30] = _tmp[M30] * inv_det;
    val[M31] = _tmp[M31] * inv_det;
    val[M32] = _tmp[M32] * inv_det;
    val[M33] = _tmp[M33] * inv_det;
    return *this;
}

float Matrix4::det() {
    return val[M30] * val[M21] * val[M12] * val[M03] - val[M20] * val[M31] * val[M12] * val[M03] - val[M30] * val[M11]
           * val[M22] * val[M03] + val[M10] * val[M31] * val[M22] * val[M03] + val[M20] * val[M11] * val[M32] * val[M03] - val[M10]
           * val[M21] * val[M32] * val[M03] - val[M30] * val[M21] * val[M02] * val[M13] + val[M20] * val[M31] * val[M02] * val[M13]
           *                        + val[M30] * val[M01] * val[M22] * val[M13] - val[M00] * val[M31] * val[M22] * val[M13] - val[M20] * val[M01] * val[M32]
           * val[M13] + val[M00] * val[M21] * val[M32] * val[M13] + val[M30] * val[M11] * val[M02] * val[M23] - val[M10] * val[M31]
           * val[M02] * val[M23] - val[M30] * val[M01] * val[M12] * val[M23] + val[M00] * val[M31] * val[M12] * val[M23] + val[M10]
           * val[M01] * val[M32] * val[M23] - val[M00] * val[M11] * val[M32] * val[M23] - val[M20] * val[M11] * val[M02] * val[M33]
           *                        + val[M10] * val[M21] * val[M02] * val[M33] + val[M20] * val[M01] * val[M12] * val[M33] - val[M00] * val[M21] * val[M12]
           * val[M33] - val[M10] * val[M01] * val[M22] * val[M33] + val[M00] * val[M11] * val[M22] * val[M33];
}

Matrix4& Matrix4::setToProjection(float near, float far, float fov, float aspectRatio) {
    this->idt();
    float l_fd = (float)(1.0f / std::tan((fov * (detail::PI / 180.f)) / 2.0f));
    float l_a1 = (far + near) / (near - far);
    float l_a2 = (2 * far * near) / (near - far);
    val[M00] = l_fd / aspectRatio;
    val[M10] = 0;
    val[M20] = 0;
    val[M30] = 0;
    val[M01] = 0;
    val[M11] = l_fd;
    val[M21] = 0;
    val[M31] = 0;
    val[M02] = 0;
    val[M12] = 0;
    val[M22] = l_a1;
    val[M32] = -1;
    val[M03] = 0;
    val[M13] = 0;
    val[M23] = l_a2;
    val[M33] = 0;

    return *this;
}

Matrix4& Matrix4::setToOrtho2D(float x, float y, float width, float height) {
    setToOrtho(x, x + width, y, y + height, 0, 1);
    return *this;
}

Matrix4& Matrix4::setToOrtho2D(float x, float y, float width, float height, float near, float far) {
    setToOrtho(x, x + width, y, y + height, near, far);
    return *this;
}

Matrix4& Matrix4::setToOrtho(float left, float right, float bottom, float top, float near, float far) {
    this->idt();
    float x_orth = 2 / (right - left);
    float y_orth = 2 / (top - bottom);
    float z_orth = -2 / (far - near);

    float tx = -(right + left) / (right - left);
    float ty = -(top + bottom) / (top - bottom);
    float tz = -(far + near) / (far - near);

    val[M00] = x_orth;
    val[M10] = 0;
    val[M20] = 0;
    val[M30] = 0;
    val[M01] = 0;
    val[M11] = y_orth;
    val[M21] = 0;
    val[M31] = 0;
    val[M02] = 0;
    val[M12] = 0;
    val[M22] = z_orth;
    val[M32] = 0;
    val[M03] = tx;
    val[M13] = ty;
    val[M23] = tz;
    val[M33] = 1;

    return *this;
}

Matrix4& Matrix4::setToTranslation(const Vector3& vector) {
    this->idt();
    val[M03] = vector.x;
    val[M13] = vector.y;
    val[M23] = vector.z;
    return *this;
}

Matrix4& Matrix4::setToTranslation(float x, float y, float z) {
    idt();
    val[M03] = x;
    val[M13] = y;
    val[M23] = z;
    return *this;
}

Matrix4& Matrix4::setToTranslationAndScaling(const Vector3& translation, const Vector3& scaling) {
    idt();
    val[M03] = translation.x;
    val[M13] = translation.y;
    val[M23] = translation.z;
    val[M00] = scaling.x;
    val[M11] = scaling.y;
    val[M22] = scaling.z;
    return *this;
}

Matrix4& Matrix4::setToTranslationAndScaling (float translationX, float translationY, float translationZ, float scalingX,
        float scalingY, float scalingZ) {
    this->idt();
    val[M03] = translationX;
    val[M13] = translationY;
    val[M23] = translationZ;
    val[M00] = scalingX;
    val[M11] = scalingY;
    val[M22] = scalingZ;
    return *this;
}

static Quaternion quat;

Matrix4& Matrix4::setToRotation(Vector3 axis, float angle) {
    idt();
    if (angle == 0) return *this;
    return this->set(quat.set(axis, angle));
}

static Vector3 tmpV;

Matrix4& Matrix4::setToRotation(float axisX, float axisY, float axisZ, float angle) {
    idt();
    if (angle == 0) return *this;
    return this->set(quat.set(tmpV.set(axisX, axisY, axisZ), angle));
}

Matrix4& Matrix4::setFromEulerAngles(float yaw, float pitch, float roll) {
    idt();
    quat.setEulerAngles(yaw, pitch, roll);
    return this->set(quat);
}

Matrix4& Matrix4::setToScaling(const Vector3& vector) {
    idt();
    val[M00] = vector.x;
    val[M11] = vector.y;
    val[M22] = vector.z;
    return *this;
}

Matrix4& Matrix4::setToScaling(float x, float y, float z) {
    idt();
    val[M00] = x;
    val[M11] = y;
    val[M22] = z;
    return *this;
}

static Vector3 l_vez;
static Vector3 l_vex;
static Vector3 l_vey;

Matrix4& Matrix4::setToLookAt(const Vector3& direction, const Vector3& up) {
    l_vez.set(direction).nor();
    l_vex.set(direction).nor();
    l_vex.crs(up).nor();
    l_vey.set(l_vex).crs(l_vez).nor();
    idt();
    val[M00] = l_vex.x;
    val[M01] = l_vex.y;
    val[M02] = l_vex.z;
    val[M10] = l_vey.x;
    val[M11] = l_vey.y;
    val[M12] = l_vey.z;
    val[M20] = -l_vez.x;
    val[M21] = -l_vez.y;
    val[M22] = -l_vez.z;

    return *this;
}

static Vector3 tmpVec;
static Matrix4 tmpMat;

Matrix4& Matrix4::setToLookAt(Vector3& position, const Vector3& target, const Vector3& up) {
    tmpVec.set(target).sub(position);
    setToLookAt(tmpVec, up);
    this->mul(tmpMat.setToTranslation(position.tmp().mul(-1)));

    return *this;
}

static Vector3 right;
static Vector3 tmpForward;
static Vector3 tmpUp;

Matrix4& Matrix4::setToWorld(const Vector3& position, const Vector3& forward, const Vector3& up) {
    tmpForward.set(forward).nor();
    right.set(tmpForward).crs(up).nor();
    tmpUp.set(right).crs(tmpForward).nor();

    this->set(right, tmpUp, tmpForward, position);
    return *this;
}

std::string Matrix4::toString() {
    std::stringstream ss;

    ss << "[" << val[M00] << "|" << val[M01] << "|" << val[M02] << "|" << val[M03] << "]\n" << "[" << val[M10] << "|" << val[M11] << "|"
    << val[M12] << "|" << val[M13] << "]\n" << "[" << val[M20] << "|" << val[M21] << "|" << val[M22] << "|" << val[M23] << "]\n" << "["
    << val[M30] << "|" << val[M31] << "|" << val[M32] << "|" << val[M33] << "]\n";

    return ss.str();
}

void Matrix4::lerp(const Matrix4& matrix, float alpha) {
    for (int i = 0; i < 16; i++)
        this->val[i] = this->val[i] * (1 - alpha) + matrix.val[i] * alpha;
}

Matrix4& Matrix4::set(const Matrix3& mat) {
    val[0] = mat.vals[0];
    val[1] = mat.vals[1];
    val[2] = mat.vals[2];
    val[3] = 0;
    val[4] = mat.vals[3];
    val[5] = mat.vals[4];
    val[6] = mat.vals[5];
    val[7] = 0;
    val[8] = 0;
    val[9] = 0;
    val[10] = 1;
    val[11] = 0;
    val[12] = mat.vals[6];
    val[13] = mat.vals[7];
    val[14] = 0;
    val[15] = mat.vals[8];
    return *this;
}

void Matrix4::scl(const Vector3& scale) {
    val[M00] *= scale.x;
    val[M11] *= scale.y;
    val[M22] *= scale.z;
}

void Matrix4::getTranslation(Vector3& position) {
    position.x = val[M03];
    position.y = val[M13];
    position.z = val[M23];
}

void Matrix4::getRotation(Quaternion& rotation) {
    rotation.setFromMatrix(*this);
}

Matrix4& Matrix4::toNormalMatrix() {
    val[M03] = 0;
    val[M13] = 0;
    val[M23] = 0;
    inv();
    return tra();
}

void Matrix4::mul (float* mata, float* matb) {
    float _tmp[16];
    _tmp[M00] = mata[M00] * matb[M00] + mata[M01] * matb[M10] + mata[M02] * matb[M20] + mata[M03] * matb[M30];
    _tmp[M01] = mata[M00] * matb[M01] + mata[M01] * matb[M11] + mata[M02] * matb[M21] + mata[M03] * matb[M31];
    _tmp[M02] = mata[M00] * matb[M02] + mata[M01] * matb[M12] + mata[M02] * matb[M22] + mata[M03] * matb[M32];
    _tmp[M03] = mata[M00] * matb[M03] + mata[M01] * matb[M13] + mata[M02] * matb[M23] + mata[M03] * matb[M33];
    _tmp[M10] = mata[M10] * matb[M00] + mata[M11] * matb[M10] + mata[M12] * matb[M20] + mata[M13] * matb[M30];
    _tmp[M11] = mata[M10] * matb[M01] + mata[M11] * matb[M11] + mata[M12] * matb[M21] + mata[M13] * matb[M31];
    _tmp[M12] = mata[M10] * matb[M02] + mata[M11] * matb[M12] + mata[M12] * matb[M22] + mata[M13] * matb[M32];
    _tmp[M13] = mata[M10] * matb[M03] + mata[M11] * matb[M13] + mata[M12] * matb[M23] + mata[M13] * matb[M33];
    _tmp[M20] = mata[M20] * matb[M00] + mata[M21] * matb[M10] + mata[M22] * matb[M20] + mata[M23] * matb[M30];
    _tmp[M21] = mata[M20] * matb[M01] + mata[M21] * matb[M11] + mata[M22] * matb[M21] + mata[M23] * matb[M31];
    _tmp[M22] = mata[M20] * matb[M02] + mata[M21] * matb[M12] + mata[M22] * matb[M22] + mata[M23] * matb[M32];
    _tmp[M23] = mata[M20] * matb[M03] + mata[M21] * matb[M13] + mata[M22] * matb[M23] + mata[M23] * matb[M33];
    _tmp[M30] = mata[M30] * matb[M00] + mata[M31] * matb[M10] + mata[M32] * matb[M20] + mata[M33] * matb[M30];
    _tmp[M31] = mata[M30] * matb[M01] + mata[M31] * matb[M11] + mata[M32] * matb[M21] + mata[M33] * matb[M31];
    _tmp[M32] = mata[M30] * matb[M02] + mata[M31] * matb[M12] + mata[M32] * matb[M22] + mata[M33] * matb[M32];
    _tmp[M33] = mata[M30] * matb[M03] + mata[M31] * matb[M13] + mata[M32] * matb[M23] + mata[M33] * matb[M33];
    memcpy(mata, _tmp, sizeof(float) *  16);
}

void Matrix4::mulVec (float* mat, float* vec) {
    float x = vec[0] * mat[M00] + vec[1] * mat[M01] + vec[2] * mat[M02] + mat[M03];
    float y = vec[0] * mat[M10] + vec[1] * mat[M11] + vec[2] * mat[M12] + mat[M13];
    float z = vec[0] * mat[M20] + vec[1] * mat[M21] + vec[2] * mat[M22] + mat[M23];
    vec[0] = x;
    vec[1] = y;
    vec[2] = z;
}

void Matrix4::mulVec (float* mat, float* vecs, int offset, int numVecs, int stride) {
    float* vecPtr = vecs + offset;
    for (int i = 0; i < numVecs; i++) {
        mulVec(mat, vecPtr);
        vecPtr += stride;
    }
}

void Matrix4::prj (const float* mat, float* vec) {
    float inv_w = 1.0f / (vec[0] * mat[M30] + vec[1] * mat[M31] + vec[2] * mat[M32] + mat[M33]);
    float x = (vec[0] * mat[M00] + vec[1] * mat[M01] + vec[2] * mat[M02] + mat[M03]) * inv_w;
    float y = (vec[0] * mat[M10] + vec[1] * mat[M11] + vec[2] * mat[M12] + mat[M13]) * inv_w;
    float z = (vec[0] * mat[M20] + vec[1] * mat[M21] + vec[2] * mat[M22] + mat[M23]) * inv_w;
    vec[0] = x;
    vec[1] = y;
    vec[2] = z;
}

void Matrix4::prj (const float* mat, float* vecs, int offset, int numVecs, int stride)  {
    float* vecPtr = vecs + offset;
    for (int i = 0; i < numVecs; i++) {
        prj(mat, vecPtr);
        vecPtr += stride;
    }
}

void Matrix4::rot (float* mat, float* vec) {
    float x = vec[0] * mat[M00] + vec[1] * mat[M01] + vec[2] * mat[M02];
    float y = vec[0] * mat[M10] + vec[1] * mat[M11] + vec[2] * mat[M12];
    float z = vec[0] * mat[M20] + vec[1] * mat[M21] + vec[2] * mat[M22];
    vec[0] = x;
    vec[1] = y;
    vec[2] = z;
}

void Matrix4::rot (float* mat, float* vecs, int offset, int numVecs, int stride)  {
    float* vecPtr = vecs + offset;
    for (int i = 0; i < numVecs; i++) {
        rot(mat, vecPtr);
        vecPtr += stride;
    }
}

float Matrix4::det (float* val) {
    return val[M30] * val[M21] * val[M12] * val[M03] - val[M20] * val[M31] * val[M12] * val[M03] - val[M30] * val[M11]
           * val[M22] * val[M03] + val[M10] * val[M31] * val[M22] * val[M03] + val[M20] * val[M11] * val[M32] * val[M03] - val[M10]
           * val[M21] * val[M32] * val[M03] - val[M30] * val[M21] * val[M02] * val[M13] + val[M20] * val[M31] * val[M02] * val[M13]
           *          + val[M30] * val[M01] * val[M22] * val[M13] - val[M00] * val[M31] * val[M22] * val[M13] - val[M20] * val[M01] * val[M32]
           * val[M13] + val[M00] * val[M21] * val[M32] * val[M13] + val[M30] * val[M11] * val[M02] * val[M23] - val[M10] * val[M31]
           * val[M02] * val[M23] - val[M30] * val[M01] * val[M12] * val[M23] + val[M00] * val[M31] * val[M12] * val[M23] + val[M10]
           * val[M01] * val[M32] * val[M23] - val[M00] * val[M11] * val[M32] * val[M23] - val[M20] * val[M11] * val[M02] * val[M33]
           *          + val[M10] * val[M21] * val[M02] * val[M33] + val[M20] * val[M01] * val[M12] * val[M33] - val[M00] * val[M21] * val[M12]
           * val[M33] - val[M10] * val[M01] * val[M22] * val[M33] + val[M00] * val[M11] * val[M22] * val[M33];
}

bool Matrix4::inv (float* val) {
    float _tmp[16];
    float l_det = det(val);
    if (l_det == 0) return false;

    _tmp[M00] = val[M12] * val[M23] * val[M31] - val[M13] * val[M22] * val[M31] + val[M13] * val[M21] * val[M32] - val[M11]
               * val[M23] * val[M32] - val[M12] * val[M21] * val[M33] + val[M11] * val[M22] * val[M33];
    _tmp[M01] = val[M03] * val[M22] * val[M31] - val[M02] * val[M23] * val[M31] - val[M03] * val[M21] * val[M32] + val[M01]
               * val[M23] * val[M32] + val[M02] * val[M21] * val[M33] - val[M01] * val[M22] * val[M33];
    _tmp[M02] = val[M02] * val[M13] * val[M31] - val[M03] * val[M12] * val[M31] + val[M03] * val[M11] * val[M32] - val[M01]
               * val[M13] * val[M32] - val[M02] * val[M11] * val[M33] + val[M01] * val[M12] * val[M33];
    _tmp[M03] = val[M03] * val[M12] * val[M21] - val[M02] * val[M13] * val[M21] - val[M03] * val[M11] * val[M22] + val[M01]
               * val[M13] * val[M22] + val[M02] * val[M11] * val[M23] - val[M01] * val[M12] * val[M23];
    _tmp[M10] = val[M13] * val[M22] * val[M30] - val[M12] * val[M23] * val[M30] - val[M13] * val[M20] * val[M32] + val[M10]
               * val[M23] * val[M32] + val[M12] * val[M20] * val[M33] - val[M10] * val[M22] * val[M33];
    _tmp[M11] = val[M02] * val[M23] * val[M30] - val[M03] * val[M22] * val[M30] + val[M03] * val[M20] * val[M32] - val[M00]
               * val[M23] * val[M32] - val[M02] * val[M20] * val[M33] + val[M00] * val[M22] * val[M33];
    _tmp[M12] = val[M03] * val[M12] * val[M30] - val[M02] * val[M13] * val[M30] - val[M03] * val[M10] * val[M32] + val[M00]
               * val[M13] * val[M32] + val[M02] * val[M10] * val[M33] - val[M00] * val[M12] * val[M33];
    _tmp[M13] = val[M02] * val[M13] * val[M20] - val[M03] * val[M12] * val[M20] + val[M03] * val[M10] * val[M22] - val[M00]
               * val[M13] * val[M22] - val[M02] * val[M10] * val[M23] + val[M00] * val[M12] * val[M23];
    _tmp[M20] = val[M11] * val[M23] * val[M30] - val[M13] * val[M21] * val[M30] + val[M13] * val[M20] * val[M31] - val[M10]
               * val[M23] * val[M31] - val[M11] * val[M20] * val[M33] + val[M10] * val[M21] * val[M33];
    _tmp[M21] = val[M03] * val[M21] * val[M30] - val[M01] * val[M23] * val[M30] - val[M03] * val[M20] * val[M31] + val[M00]
               * val[M23] * val[M31] + val[M01] * val[M20] * val[M33] - val[M00] * val[M21] * val[M33];
    _tmp[M22] = val[M01] * val[M13] * val[M30] - val[M03] * val[M11] * val[M30] + val[M03] * val[M10] * val[M31] - val[M00]
               * val[M13] * val[M31] - val[M01] * val[M10] * val[M33] + val[M00] * val[M11] * val[M33];
    _tmp[M23] = val[M03] * val[M11] * val[M20] - val[M01] * val[M13] * val[M20] - val[M03] * val[M10] * val[M21] + val[M00]
               * val[M13] * val[M21] + val[M01] * val[M10] * val[M23] - val[M00] * val[M11] * val[M23];
    _tmp[M30] = val[M12] * val[M21] * val[M30] - val[M11] * val[M22] * val[M30] - val[M12] * val[M20] * val[M31] + val[M10]
               * val[M22] * val[M31] + val[M11] * val[M20] * val[M32] - val[M10] * val[M21] * val[M32];
    _tmp[M31] = val[M01] * val[M22] * val[M30] - val[M02] * val[M21] * val[M30] + val[M02] * val[M20] * val[M31] - val[M00]
               * val[M22] * val[M31] - val[M01] * val[M20] * val[M32] + val[M00] * val[M21] * val[M32];
    _tmp[M32] = val[M02] * val[M11] * val[M30] - val[M01] * val[M12] * val[M30] - val[M02] * val[M10] * val[M31] + val[M00]
               * val[M12] * val[M31] + val[M01] * val[M10] * val[M32] - val[M00] * val[M11] * val[M32];
    _tmp[M33] = val[M01] * val[M12] * val[M20] - val[M02] * val[M11] * val[M20] + val[M02] * val[M10] * val[M21] - val[M00]
               * val[M12] * val[M21] - val[M01] * val[M10] * val[M22] + val[M00] * val[M11] * val[M22];

    float inv_det = 1.0f / l_det;
    val[M00] = _tmp[M00] * inv_det;
    val[M01] = _tmp[M01] * inv_det;
    val[M02] = _tmp[M02] * inv_det;
    val[M03] = _tmp[M03] * inv_det;
    val[M10] = _tmp[M10] * inv_det;
    val[M11] = _tmp[M11] * inv_det;
    val[M12] = _tmp[M12] * inv_det;
    val[M13] = _tmp[M13] * inv_det;
    val[M20] = _tmp[M20] * inv_det;
    val[M21] = _tmp[M21] * inv_det;
    val[M22] = _tmp[M22] * inv_det;
    val[M23] = _tmp[M23] * inv_det;
    val[M30] = _tmp[M30] * inv_det;
    val[M31] = _tmp[M31] * inv_det;
    val[M32] = _tmp[M32] * inv_det;
    val[M33] = _tmp[M33] * inv_det;
    return true;
}


void Matrix4::translate(float x, float y, float z)
{
    _tmp[M00] = 1;
    _tmp[M01] = 0;
    _tmp[M02] = 0;
    _tmp[M03] = x;
    _tmp[M10] = 0;
    _tmp[M11] = 1;
    _tmp[M12] = 0;
    _tmp[M13] = y;
    _tmp[M20] = 0;
    _tmp[M21] = 0;
    _tmp[M22] = 1;
    _tmp[M23] = z;
    _tmp[M30] = 0;
    _tmp[M31] = 0;
    _tmp[M32] = 0;
    _tmp[M33] = 1;

    mul(val, _tmp);
}

void Matrix4::rotate(float axisX, float axisY, float axisZ, float angle)
{
    if (angle == 0) return;
    quat.set(tmpV.set(axisX, axisY, axisZ), angle);
    Quaternion quaternion = quat;
    float l_xx = quaternion.x * quaternion.x;
    float l_xy = quaternion.x * quaternion.y;
    float l_xz = quaternion.x * quaternion.z;
    float l_xw = quaternion.x * quaternion.w;
    float l_yy = quaternion.y * quaternion.y;
    float l_yz = quaternion.y * quaternion.z;
    float l_yw = quaternion.y * quaternion.w;
    float l_zz = quaternion.z * quaternion.z;
    float l_zw = quaternion.z * quaternion.w;
    // Set matrix from quaternion
    _tmp[M00] = 1 - 2 * (l_yy + l_zz);
    _tmp[M01] = 2 * (l_xy - l_zw);
    _tmp[M02] = 2 * (l_xz + l_yw);
    _tmp[M03] = 0;
    _tmp[M10] = 2 * (l_xy + l_zw);
    _tmp[M11] = 1 - 2 * (l_xx + l_zz);
    _tmp[M12] = 2 * (l_yz - l_xw);
    _tmp[M13] = 0;
    _tmp[M20] = 2 * (l_xz - l_yw);
    _tmp[M21] = 2 * (l_yz + l_xw);
    _tmp[M22] = 1 - 2 * (l_xx + l_yy);
    _tmp[M23] = 0;
    _tmp[M30] = 0;
    _tmp[M31] = 0;
    _tmp[M32] = 0;
    _tmp[M33] = 1;

    mul(val, _tmp);
}

void Matrix4::scale(float scaleX, float scaleY, float scaleZ)
{
    _tmp[M00] = scaleX;
    _tmp[M01] = 0;
    _tmp[M02] = 0;
    _tmp[M03] = 0;
    _tmp[M10] = 0;
    _tmp[M11] = scaleY;
    _tmp[M12] = 0;
    _tmp[M13] = 0;
    _tmp[M20] = 0;
    _tmp[M21] = 0;
    _tmp[M22] = scaleZ;
    _tmp[M23] = 0;
    _tmp[M30] = 0;
    _tmp[M31] = 0;
    _tmp[M32] = 0;
    _tmp[M33] = 1;

    mul(val, _tmp);
}


