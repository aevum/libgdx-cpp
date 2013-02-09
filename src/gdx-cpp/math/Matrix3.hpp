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


#ifndef GDX_CPP_MATH_MATRIX3_HPP
#define GDX_CPP_MATH_MATRIX3_HPP

#include <gdx-cpp/math/Vector2.hpp>
#include <string>

namespace gdx {

class Vector3;
class Vector2;

class Matrix3
{
public:
    Matrix3();
    Matrix3(const Matrix3& other);
    virtual ~Matrix3();
    virtual Matrix3& operator=(const Matrix3& other);
    virtual bool operator==(const Matrix3& other) const;

    Matrix3& idt();
    Matrix3& mul(const Matrix3& m);
    Matrix3& setToRotation(float angle);
    Matrix3& setToTranslation(float x, float y);
    Matrix3& setToScaling(float sx, float sy);
    std::string toString();
    float det();
    Matrix3& inv();
    Matrix3& set(const Matrix3& mat);
    Matrix3& trn(const Vector3& vector);
    Matrix3& trn(float x, float y);
    float* getValues();
    void translate(float x, float y);
    void rotate(float angle);
    void scale(float scaleX, float scaleY);
    
    void getTranslation(Vector2& position) ;
    
    const static int length = 9;
    float vals[length];
private:
    void mul(float* mata,float* matb);
    float tmp[9];
};

}

#endif // GDX_CPP_MATH_MATRIX3_HPP
