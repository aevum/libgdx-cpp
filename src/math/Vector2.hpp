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

namespace gdx_cpp {

namespace math {

class Vector2
{
public:
    Vector2();
    Vector2(const Vector2& other);

    virtual ~Vector2();
    virtual Vector2& operator=(const Vector2& other);
    virtual bool operator==(const Vector2& other) const;

    float x;
    float y;

private:
    static Vector2 tmp;
};

}
}

#endif // GDX_CPP_MATH_VECTOR2_H
