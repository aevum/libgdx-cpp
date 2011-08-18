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

#include <string>
#ifndef GDX_CPP_MATH_QUATERNION_HPP
#define GDX_CPP_MATH_QUATERNION_HPP

namespace gdx_cpp {

namespace math {
class Vector3;
class Matrix4;
class Quaternion
{
  
public:
    Quaternion();
    Quaternion(float x, float y, float z, float w);
    Quaternion(const Quaternion& quaternion);
    Quaternion(const Vector3& axis, float angle);
    virtual ~Quaternion();
    virtual Quaternion& operator=(const Quaternion& other);
    virtual bool operator==(const Quaternion& other) const;
    Quaternion& set (float x, float y, float z, float w);
    Quaternion& set (const Quaternion& quaternion);
    Quaternion& set (const Vector3& axis, float angle);
    Quaternion& cpy ();
    float len ();
    std::string toString ();
    Quaternion& setEulerAngles (float yaw, float pitch, float roll);
    float len2 ();
    Quaternion& nor ();
    Quaternion& conjugate ();
    void transform (Vector3& v);
    Quaternion& mul (const Quaternion& q);
    Quaternion& mulLeft (const Quaternion& q);
    void toMatrix (float *matrix);
    static Quaternion& idt ();
    Quaternion& setFromAxis (const Vector3& axis, float angle);
    Quaternion& setFromAxis (float x, float y, float z, float angle);
    Quaternion& setFromMatrix (const Matrix4& matrix);
    Quaternion& setFromAxes (float xx, float xy, float xz, float yx, float yy, float yz, float zx, float zy, float zz);
    Quaternion& slerp (Quaternion& end, float alpha);
    float dot (const Quaternion& other);
    Quaternion& mul (float scalar);
    
    float x;
    float y;
    float z;
    float w;	
	
private:

    
    static Quaternion tmp1;
    static Quaternion tmp2;
    static const float NORMALIZATION_TOLERANCE;
};

}

}

#endif // GDX_CPP_MATH_QUATERNION_HPP
