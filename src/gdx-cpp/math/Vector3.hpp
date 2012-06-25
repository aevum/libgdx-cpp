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


#ifndef GDX_CPP_MATH_VECTOR3_HPP
#define GDX_CPP_MATH_VECTOR3_HPP

#include <string>

namespace gdx {

class Matrix4;
  
class Vector3
{

public:
    Vector3();
    Vector3(float* values);
    Vector3(float x, float y, float z);
    Vector3(const Vector3& other);
    virtual ~Vector3();
    virtual Vector3& operator=(const Vector3& other);
    virtual bool operator==(const Vector3& other) const;

    Vector3& set(float x, float y, float z);
    Vector3& set(const Vector3& vector);
    Vector3& set(const float* values);
    Vector3 cpy();
    Vector3& tmp() const;
    Vector3& tmp2() const;
    Vector3& tmp3() const;

    
    Vector3& add(const Vector3& vector);
    Vector3& add(float x, float y, float z);
    Vector3& add(float values);
    Vector3& sub(const Vector3& a_vec);
    Vector3& sub(float x, float y, float z);
    Vector3& sub(float value);
    Vector3& mul(float value);
    Vector3& div(float value);
    float len() const;
    float len2();
    bool idt(const Vector3& vector);
    float dst(const Vector3& vector);
    Vector3& nor();
    float dot(const Vector3& vector) const;
    Vector3& crs(const Vector3& vector);
    Vector3 crs(float x, float y, float z);
    Vector3& mul(const Matrix4& matrix);
    Vector3& prj(const Matrix4& matrix);
    Vector3& rot(const Matrix4& matrix);
    bool isUnit() const;
    bool isZero();
    Vector3 lerp(Vector3& target, float alpha);
    Vector3& slerp(Vector3& target, float alpha);
    std::string toString();
    float dot(float x, float y, float z);
    float dst2(Vector3 point);
    float dst2(float x, float y, float z);
    float dst(float x, float y, float z);
    int hashCode();
    Vector3& scale(float scalarX, float scalarY, float scalarZ);


    /** the x-component of this vector **/
    float x;
    /** the x-component of this vector **/
    float y;
    /** the x-component of this vector **/
    float z;
    
    static Vector3 X;
    static Vector3 Y;
    static Vector3 Z;
private:
    static Vector3 _tmp;
    static Vector3 _tmp2;
    static Vector3 _tmp3;
};

}

#endif // GDX_CPP_MATH_VECTOR3_HPP
