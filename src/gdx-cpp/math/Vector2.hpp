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


#ifndef GDX_CPP_MATH_VECTOR2_H
#define GDX_CPP_MATH_VECTOR2_H

#include <string>

namespace gdx {

class Matrix3;
  
class Vector2
{
public:
    Vector2();
    Vector2(const Vector2& other);
    Vector2(float x, float y);
    
    virtual ~Vector2();
    virtual Vector2& operator=(const Vector2& other);
    virtual bool operator==(const Vector2& other) const;

    Vector2& set (const Vector2& v);
    Vector2& set (float _x, float _y);
    Vector2& sub (const Vector2& v);
    Vector2& nor ();
    Vector2& add (const Vector2& v);
    Vector2& add (float x, float y);
    float dot (const Vector2& v);
    Vector2& mul (float scalar);
    float dst (const Vector2& v) const;
    float dst (float x, float y);
    float dst2 (const Vector2& v);
    std::string toString ();
    Vector2& sub (float x, float y);
    Vector2& tmp ();
    Vector2& mul (const Matrix3& mat);
    float crs (const Vector2& v);
    float crs (float x, float y);
    float angle ();
    Vector2 rotate (float angle);
    Vector2 lerp (Vector2& target, float alpha);
    float len ();
    
    float x;
    float y;

private:
    static Vector2 _tmp;
};

}

#endif // GDX_CPP_MATH_VECTOR2_H
