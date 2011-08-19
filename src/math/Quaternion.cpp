
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

#include "Quaternion.hpp"

using namespace gdx_cpp::math;

Quaternion& Quaternion::set (float x,float y,float z,float w) {
    this.x = x;
    this.y = y;
    this.z = z;
    this.w = w;
    return this;
}

Quaternion& Quaternion::set (const Quaternion& quaternion) {
    return this.set(quaternion.x, quaternion.y, quaternion.z, quaternion.w);
}

Quaternion& Quaternion::set (const Vector3& axis,float angle) {
    float l_ang = (float)Math.toRadians(angle);
    float l_sin = (float)Math.sin(l_ang / 2);
    float l_cos = (float)Math.cos(l_ang / 2);
    return this.set(axis.x * l_sin, axis.y * l_sin, axis.z * l_sin, l_cos).nor();
}

Quaternion& Quaternion::cpy () {
    return new Quaternion(this);
}

float Quaternion::len () {
    return (float)Math.sqrt(x * x + y * y + z * z + w * w);
}

std::string& Quaternion::toString () {
    return "[" + x + "|" + y + "|" + z + "|" + w + "]";
}

Quaternion& Quaternion::setEulerAngles (float yaw,float pitch,float roll) {
    yaw = (float)Math.toRadians(yaw);
    pitch = (float)Math.toRadians(pitch);
    roll = (float)Math.toRadians(roll);
    float num9 = roll * 0.5f;
    float num6 = (float)Math.sin(num9);
    float num5 = (float)Math.cos(num9);
    float num8 = pitch * 0.5f;
    float num4 = (float)Math.sin(num8);
    float num3 = (float)Math.cos(num8);
    float num7 = yaw * 0.5f;
    float num2 = (float)Math.sin(num7);
    float num = (float)Math.cos(num7);
    x = ((num * num4) * num5) + ((num2 * num3) * num6);
    y = ((num2 * num3) * num5) - ((num * num4) * num6);
    z = ((num * num3) * num6) - ((num2 * num4) * num5);
    w = ((num * num3) * num5) + ((num2 * num4) * num6);
    return this;
}

float Quaternion::len2 () {
    return x * x + y * y + z * z + w * w;
}

Quaternion& Quaternion::nor () {
    float len = len2();
    if (len != 0.f && (Math.abs(len - 1.0f) > NORMALIZATION_TOLERANCE)) {
        len = (float)Math.sqrt(len);
        w /= len;
        x /= len;
        y /= len;
        z /= len;
    }
    return this;
}

Quaternion& Quaternion::conjugate () {
    x = -x;
    y = -y;
    z = -z;
    return this;
}

void Quaternion::transform (const Vector3& v) {
    tmp2.set(this);
    tmp2.conjugate();
    tmp2.mulLeft(tmp1.set(v.x, v.y, v.z, 0)).mulLeft(this);

    v.x = tmp2.x;
    v.y = tmp2.y;
    v.z = tmp2.z;
}

Quaternion& Quaternion::mul (const Quaternion& q) {
    float newX = w * q.x + x * q.w + y * q.z - z * q.y;
    float newY = w * q.y + y * q.w + z * q.x - x * q.z;
    float newZ = w * q.z + z * q.w + x * q.y - y * q.x;
    float newW = w * q.w - x * q.x - y * q.y - z * q.z;
    x = newX;
    y = newY;
    z = newZ;
    w = newW;
    return this;
}

Quaternion& Quaternion::mulLeft (const Quaternion& q) {
    float newX = q.w * x + q.x * w + q.y * z - q.z * y;
    float newY = q.w * y + q.y * w + q.z * x - q.x * z;
    float newZ = q.w * z + q.z * w + q.x * y - q.y * x;
    float newW = q.w * w - q.x * x - q.y * y - q.z * z;
    x = newX;
    y = newY;
    z = newZ;
    w = newW;
    return this;
}

void Quaternion::toMatrix () {
    float xx = x * x;
    float xy = x * y;
    float xz = x * z;
    float xw = x * w;
    float yy = y * y;
    float yz = y * z;
    float yw = y * w;
    float zz = z * z;
    float zw = z * w;
    // Set matrix from quaternion
    matrix[Matrix4.M00] = 1 - 2 * (yy + zz);
    matrix[Matrix4.M01] = 2 * (xy - zw);
    matrix[Matrix4.M02] = 2 * (xz + yw);
    matrix[Matrix4.M03] = 0;
    matrix[Matrix4.M10] = 2 * (xy + zw);
    matrix[Matrix4.M11] = 1 - 2 * (xx + zz);
    matrix[Matrix4.M12] = 2 * (yz - xw);
    matrix[Matrix4.M13] = 0;
    matrix[Matrix4.M20] = 2 * (xz - yw);
    matrix[Matrix4.M21] = 2 * (yz + xw);
    matrix[Matrix4.M22] = 1 - 2 * (xx + yy);
    matrix[Matrix4.M23] = 0;
    matrix[Matrix4.M30] = 0;
    matrix[Matrix4.M31] = 0;
    matrix[Matrix4.M32] = 0;
    matrix[Matrix4.M33] = 1;
}

Quaternion& Quaternion::idt () {
    return new Quaternion(0, 0, 0, 1);
}

Quaternion& Quaternion::setFromAxis (const Vector3& axis,float angle) {
    return setFromAxis(axis.x, axis.y, axis.z, angle);
}

Quaternion& Quaternion::setFromAxis (float x,float y,float z,float angle) {
    float l_ang = angle * MathUtils.degreesToRadians;
    float l_sin = MathUtils.sin(l_ang / 2);
    float l_cos = MathUtils.cos(l_ang / 2);
    return this.set(x * l_sin, y * l_sin, z * l_sin, l_cos).nor();
}

Quaternion& Quaternion::setFromMatrix (const Matrix4& matrix) {
    return setFromAxes(matrix.val[Matrix4.M00], matrix.val[Matrix4.M01], matrix.val[Matrix4.M02], matrix.val[Matrix4.M10],
                       matrix.val[Matrix4.M11], matrix.val[Matrix4.M12], matrix.val[Matrix4.M20], matrix.val[Matrix4.M21],
                       matrix.val[Matrix4.M22]);
}

Quaternion& Quaternion::setFromAxes (float xx,float xy,float xz,float yx,float yy,float yz,float zx,float zy,float zz) {
    // the trace is the sum of the diagonal elements; see
    // http://mathworld.wolfram.com/MatrixTrace.html
    final float m00 = xx, m01 = yx, m02 = zx;
    final float m10 = xy, m11 = yy, m12 = zy;
    final float m20 = xz, m21 = yz, m22 = zz;
    final float t = m00 + m11 + m22;

    // we protect the division by s by ensuring that s>=1
    double x, y, z, w;
    if (t >= 0) { // |w| >= .5
        double s = Math.sqrt(t + 1); // |s|>=1 ...
        w = 0.5 * s;
        s = 0.5 / s; // so this division isn't bad
        x = (m21 - m12) * s;
        y = (m02 - m20) * s;
        z = (m10 - m01) * s;
    } else if ((m00 > m11) && (m00 > m22)) {
        double s = Math.sqrt(1.0 + m00 - m11 - m22); // |s|>=1
        x = s * 0.5; // |x| >= .5
        s = 0.5 / s;
        y = (m10 + m01) * s;
        z = (m02 + m20) * s;
        w = (m21 - m12) * s;
    } else if (m11 > m22) {
        double s = Math.sqrt(1.0 + m11 - m00 - m22); // |s|>=1
        y = s * 0.5; // |y| >= .5
        s = 0.5 / s;
        x = (m10 + m01) * s;
        z = (m21 + m12) * s;
        w = (m02 - m20) * s;
    } else {
        double s = Math.sqrt(1.0 + m22 - m00 - m11); // |s|>=1
        z = s * 0.5; // |z| >= .5
        s = 0.5 / s;
        x = (m02 + m20) * s;
        y = (m21 + m12) * s;
        w = (m10 - m01) * s;
    }

    return set((float)x, (float)y, (float)z, (float)w);
}

Quaternion& Quaternion::slerp (const Quaternion& end,float alpha) {
    if (this.equals(end)) {
        return this;
    }

    float result = dot(end);

    if (result < 0.0) {
        // Negate the second quaternion and the result of the dot product
        end.mul(-1);
        result = -result;
    }

    // Set the first and second scale for the interpolation
    float scale0 = 1 - alpha;
    float scale1 = alpha;

    // Check if the angle between the 2 quaternions was big enough to
    // warrant such calculations
    if ((1 - result) > 0.1) {// Get the angle between the 2 quaternions,
        // and then store the sin() of that angle
        final double theta = Math.acos(result);
        final double invSinTheta = 1f / Math.sin(theta);

        // Calculate the scale for q1 and q2, according to the angle and
        // it's sine value
        scale0 = (float)(Math.sin((1 - alpha) * theta) * invSinTheta);
        scale1 = (float)(Math.sin((alpha * theta)) * invSinTheta);
    }

    // Calculate the x, y, z and w values for the quaternion by using a
    // special form of linear interpolation for quaternions.
    final float x = (scale0 * this.x) + (scale1 * end.x);
    final float y = (scale0 * this.y) + (scale1 * end.y);
    final float z = (scale0 * this.z) + (scale1 * end.z);
    final float w = (scale0 * this.w) + (scale1 * end.w);
    set(x, y, z, w);

    // Return the interpolated quaternion
    return this;
}

bool Quaternion::equals (const final& Object) {
    if (this == o) {
        return true;
    }
    if (!(o instanceof Quaternion)) {
        return false;
    }
    final Quaternion comp = (Quaternion)o;
    return this.x == comp.x && this.y == comp.y && this.z == comp.z && this.w == comp.w;

}

float Quaternion::dot (const Quaternion& other) {
    return x * other.x + y * other.y + z * other.z + w * other.w;
}

Quaternion& Quaternion::mul (float scalar) {
    this.x *= scalar;
    this.y *= scalar;
    this.z *= scalar;
    this.w *= scalar;
    return this;
}

