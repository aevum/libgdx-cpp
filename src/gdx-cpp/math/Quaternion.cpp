
/*
    Copyright 2011 <copyright holder> <email>

    Licensed under the Apache License, Version 2.0f(the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/


#include <cmath>
#include <sstream>
#include <string>

#include "MathUtils.hpp"
#include "Matrix4.hpp"
#include "Quaternion.hpp"
#include "Vector3.hpp"

using namespace gdx;

Quaternion Quaternion::tmp1(0, 0, 0, 0);
Quaternion Quaternion::tmp2(0, 0, 0, 0);
const float Quaternion::NORMALIZATION_TOLERANCE = 0.00001f;

Quaternion::Quaternion () : x(0), y(0), z(0), w(0)
{
}

Quaternion::~Quaternion ()
{
}

Quaternion& Quaternion::operator=(const Quaternion& other)
{
    this->set(other.x, other.y, other.z, other.w);
    return *this;
}

bool Quaternion::operator==(const Quaternion& other) const
{
    if (this == &other) return true;
    if(other.x == x && other.y == y && other.z == z && other.w == w) return true;
    return false;
}


Quaternion::Quaternion (float x, float y, float z, float w)
{
    this->set(x, y, z, w);
}

Quaternion::Quaternion (const Quaternion& quaternion)
{
    this->set(quaternion);
}

Quaternion::Quaternion (const Vector3& axis, float angle)
{
    this->set(axis, angle);
}

Quaternion& Quaternion::set (float x, float y, float z, float w)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
    return *this;
}

Quaternion& Quaternion::set (const Quaternion& quaternion)
{
    return this->set(quaternion.x, quaternion.y, quaternion.z, quaternion.w);
}

Quaternion& Quaternion::set (const Vector3& axis, float angle)
{
    float l_ang = (float) (angle * detail::degreesToRadians);
    float l_sin = (float) std::sin(l_ang / 2);
    float l_cos = (float) std::cos(l_ang / 2);
    return this->set( axis.x * l_sin, axis.y * l_sin, axis.z * l_sin, l_cos).nor();
}

Quaternion::ptr Quaternion::cpy ()
{
    return Quaternion::ptr(new Quaternion(*this));
}

float Quaternion::len ()
{
    return (float) std::sqrt(x * x + y * y + z * z + w * w);
}

std::string Quaternion::toString ()
{
    std::stringstream ss;
    ss << "[" << x << "|" << y << "|" << z << "|" << w << "]";
    return ss.str(); 
}

Quaternion& Quaternion::setEulerAngles (float yaw, float pitch, float roll)
{
    yaw = (float) (yaw * detail::degreesToRadians);
    pitch = (float) (pitch * detail::degreesToRadians);
    roll = (float) (roll * detail::degreesToRadians);
    float num9 = roll * 0.5f;
    float num6 = (float) std::sin(num9);
    float num5 = (float) std::cos(num9);
    float num8 = pitch * 0.5f;
    float num4 = (float) std::sin(num8);
    float num3 = (float) std::cos(num8);
    float num7 = yaw * 0.5f;
    float num2 = (float) std::sin(num7);
    float num = (float) std::cos(num7);
    x = ((num * num4) * num5) + ((num2 * num3) * num6);
    y = ((num2 * num3) * num5) - ((num * num4) * num6);
    z = ((num * num3) * num6) - ((num2 * num4) * num5);
    w = ((num * num3) * num5) + ((num2 * num4) * num6);
    return *this;
}

float Quaternion::len2 ()
{
    return x * x + y * y + z * z + w * w;
}

Quaternion& Quaternion::nor ()
{
    float len = len2();
    if (len != 0.f && (std::abs(len - 1.0f) > NORMALIZATION_TOLERANCE))
    {
        len = (float) std::sqrt(len);
        w /= len;
        x /= len;
        y /= len;
        z /= len;
    }
    return *this;
}

Quaternion& Quaternion::conjugate ()
{
    x = -x;
    y = -y;
    z = -z;
    return *this;
}

void Quaternion::transform (Vector3& v)
{
    tmp1.set(*this);
    tmp2.conjugate();
    tmp2.mulLeft(tmp1.set(v.x, v.y, v.z, 0)).mulLeft(*this);
    v.x = tmp2.x;
    v.y = tmp2.y;
    v.z = tmp2.z;
}

Quaternion& Quaternion::mul (const Quaternion& q)
{
    float newX = w * q.x + x * q.w + y * q.z - z * q.y;
    float newY = w * q.y + y * q.w + z * q.x - x * q.z;
    float newZ = w * q.z + z * q.w + x * q.y - y * q.x;
    float newW = w * q.w - x * q.x - y * q.y - z * q.z;
    x = newX;
    y = newY;
    z = newZ;
    w = newW;
    return *this;
}

Quaternion& Quaternion::mulLeft (const Quaternion& q)
{
    float newX = q.w * x + q.x * w + q.y * z - q.z * y;
    float newY = q.w * y + q.y * w + q.z * x - q.x * z;
    float newZ = q.w * z + q.z * w + q.x * y - q.y * x;
    float newW = q.w * w - q.x * x - q.y * y - q.z * z;
    x = newX;
    y = newY;
    z = newZ;
    w = newW;
    return *this;
}

void Quaternion::toMatrix (float *matrix)
{
    float xx = x * x;
    float xy = x * y;
    float xz = x * z;
    float xw = x * w;
    float yy = y * y;
    float yz = y * z;
    float yw = y * w;
    float zz = z * z;
    float zw = z * w;
    matrix[Matrix4::M00] = 1 - 2 * (yy + zz);
    matrix[Matrix4::M01] = 2 * (xy - zw);
    matrix[Matrix4::M02] = 2 * (xz + yw);
    matrix[Matrix4::M03] = 0;
    matrix[Matrix4::M10] = 2 * (xy + zw);
    matrix[Matrix4::M11] = 1 - 2 * (xx + zz);
    matrix[Matrix4::M12] = 2 * (yz - xw);
    matrix[Matrix4::M13] = 0;
    matrix[Matrix4::M20] = 2 * (xz - yw);
    matrix[Matrix4::M21] = 2 * (yz + xw);
    matrix[Matrix4::M22] = 1 - 2 * (xx + yy);
    matrix[Matrix4::M23] = 0;
    matrix[Matrix4::M30] = 0;
    matrix[Matrix4::M31] = 0;
    matrix[Matrix4::M32] = 0;
    matrix[Matrix4::M33] = 1;
}

const Quaternion& Quaternion::idt ()
{
    static Quaternion i(0, 0, 0, 1);
    return i;
}

Quaternion& Quaternion::setFromAxis (const Vector3& axis, float angle)
{
    return setFromAxis(axis.x, axis.y, axis.z, angle);
}

Quaternion& Quaternion::setFromAxis (float x, float y, float z, float angle)
{
    float l_ang = (angle * detail::degreesToRadians);
    float l_sin = std::sin(l_ang / 2);
    float l_cos = std::cos(l_ang / 2);
    return this->set(x * l_sin, y * l_sin, z * l_sin, l_cos).nor();
}

Quaternion& Quaternion::setFromMatrix (const Matrix4& matrix)
{
    return setFromAxes(matrix.val[Matrix4::M00], matrix.val[Matrix4::M01], matrix.val[Matrix4::M02], matrix.val[Matrix4::M10],
                        matrix.val[Matrix4::M11], matrix.val[Matrix4::M12], matrix.val[Matrix4::M20], matrix.val[Matrix4::M21],
                        matrix.val[Matrix4::M22]);
}

Quaternion& Quaternion::setFromAxes (float xx, float xy, float xz, float yx, float yy, float yz, float zx, float zy, float zz)
{
    const float m00 = xx, m01 = yx, m02 = zx;
    const float m10 = xy, m11 = yy, m12 = zy;
    const float m20 = xz, m21 = yz, m22 = zz;
    const float t = m00 + m11 + m22;
    float x, y, z, w;
    if (t >= 0) { 
        float s = std::sqrt(t + 1);
        w = 0.5f* s;
        s = 0.5f/ s;
        x = (m21 - m12) * s;
        y = (m02 - m20) * s;
        z = (m10 - m01) * s;
    }
    else if ((m00 > m11) && (m00 > m22)) {
        float s = std::sqrt(1.0f+ m00 - m11 - m22);
        x = s * 0.5f;
        s = 0.5f/ s;
        y = (m10 + m01) * s;
        z = (m02 + m20) * s;
        w = (m21 - m12) * s;
    }
    else if (m11 > m22) {
        float s = std::sqrt(1.0f + m11 - m00 - m22);
        y = s * 0.5f;
        s = 0.5f/ s;
        x = (m10 + m01) * s;
        z = (m21 + m12) * s;
        w = (m02 - m20) * s;
    }
    else {
        float s = std::sqrt(1.0f+ m22 - m00 - m11);
        z = s * 0.5f;
        s = 0.5f/ s;
        x = (m02 + m20) * s;
        y = (m21 + m12) * s;
        w = (m10 - m01) * s;
    }
    return set((float)x, (float)y, (float)z, (float)w);
}

Quaternion& Quaternion::slerp (Quaternion& end, float alpha)
{
    if (*this == end){
        return *this;
    }

    float result = dot(end);

    if (result < 0.0f) {
        end.mul(-1);
        result = -result;
    }

    float scale0 = 1 - alpha;
    float scale1 = alpha;

    if ((1 - result) > 0.1f){
        const float theta = std::acos(result);
        const float invSinTheta = 1.0f/ std::sin(theta);
        scale0 = (float)(std::sin((1 - alpha) * theta) * invSinTheta);
        scale1 = (float)(std::sin((alpha * theta)) * invSinTheta);
    }

    const float x = (scale0 * this->x) + (scale1 * end.x);
    const float y = (scale0 * this->y) + (scale1 * end.y);
    const float z = (scale0 * this->z) + (scale1 * end.z);
    const float w = (scale0 * this->w) + (scale1 * end.w);
    set(x, y, z, w);

    return *this;
}

float Quaternion::dot (const Quaternion& other)
{
    return x * other.x + y * other.y + z * other.z + w * other.w;
}

Quaternion& Quaternion::mul (float scalar)
{
    this->x *= scalar;
    this->y *= scalar;
    this->z *= scalar;
    this->w *= scalar;
    return *this;
}
