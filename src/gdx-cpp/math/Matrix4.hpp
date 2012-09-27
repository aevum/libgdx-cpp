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


#ifndef GDX_CPP_MATH_MATRIX4_HPP
#define GDX_CPP_MATH_MATRIX4_HPP

#include <string>

#include "gdx-cpp/internal/memory"

namespace gdx {

class Quaternion;
class Vector3;
class Matrix3;

class Matrix4
{
public:
    static const int M00 = 0;
    static const int M01 = 4;
    static const int M02 = 8;
    static const int M03 = 12;
    static const int M10 = 1;
    static const int M11 = 5;
    static const int M12 = 9;
    static const int M13 = 13;
    static const int M20 = 2;
    static const int M21 = 6;
    static const int M22 = 10;
    static const int M23 = 14;
    static const int M30 = 3;
    static const int M31 = 7;
    static const int M32 = 11;
    static const int M33 = 15;

    typedef ref_ptr_maker<Matrix4>::shared_ptr_t ptr;

    Matrix4(const Matrix4& other);
    ~Matrix4();
    Matrix4& operator=(const Matrix4& other);
    Matrix4 ();
    Matrix4 (float* values);
    Matrix4 (const Quaternion& quaternion);
    Matrix4& set(const Matrix4& matrix);
    Matrix4& set(const float* values);
    Matrix4& set(const Quaternion& quaternion);
    void set(Vector3& xAxis, Vector3& yAxis, Vector3& zAxis, const Vector3& pos);
    Matrix4::ptr cpy();
    Matrix4& trn(const Vector3& vector);
    Matrix4& trn(float x, float y, float z);
    float* getValues();
    Matrix4& mul(const Matrix4& matrix);
    Matrix4& tra();
    Matrix4& idt();
    Matrix4& inv();
    float det();
    Matrix4& setToProjection(float near, float far, float fov, float aspectRatio);
    Matrix4& setToOrtho2D(float x, float y, float width, float height);
    Matrix4& setToOrtho2D(float x, float y, float width, float height, float near, float far);
    Matrix4& setToOrtho(float left, float right, float bottom, float top, float near, float far);
    Matrix4& setToTranslation(const Vector3& vector);
    Matrix4& setToTranslation(float x, float y, float z);
    Matrix4& setToTranslationAndScaling(const Vector3& translation, const Vector3& scaling);
    Matrix4& setToTranslationAndScaling (float translationX, float translationY, float translationZ, float scalingX,
                                         float scalingY, float scalingZ);
    Matrix4& setToRotation(Vector3 axis, float angle);
    Matrix4& setToRotation(float axisX, float axisY, float axisZ, float angle);
    Matrix4& setFromEulerAngles(float yaw, float pitch, float roll);
    Matrix4& setToScaling(const Vector3& vector);
    Matrix4& setToScaling(float x, float y, float z);
    Matrix4& setToLookAt(const Vector3& direction, const Vector3& up);
    Matrix4& setToLookAt(Vector3& position, const Vector3& target, const Vector3& up);
    Matrix4& setToWorld(const Vector3& position, const Vector3& forward, const Vector3& up);
    std::string toString();
    void lerp(const Matrix4& matrix, float alpha);
    Matrix4& set(const Matrix3& mat);
    void scl(const Vector3& scale);
    void getTranslation(Vector3& position);
    void getRotation(Quaternion& rotation);
    Matrix4& toNormalMatrix();
    
    void translate(float x, float y, float z);
    void rotate(float axisX, float axisY, float axisZ, float angle);
    void scale(float scaleX, float scaleY, float scaleZ);
    
    static bool inv (float* val);
    static float det (float* val);
    static void rot (float* mat, float* vecs, int offset, int numVecs, int stride) ;
    static void rot (float* mat, float* vec);
    static void prj (const float* mat, float* vecs, int offset, int numVecs, int stride) ;
    static void prj (const float* mat, float* vec);
    static void mulVec (float* mat, float* vecs, int offset, int numVecs, int stride);
    static void mulVec (float* mat, float* vec);
    static void mul (float* mata, float* matb);

    const static int length = 16;
    float val[length];
    
};

}

#endif // GDX_CPP_MATH_MATRIX4_HPP
