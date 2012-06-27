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


#ifndef GDX_CPP_MATH_RECTANGLE_HPP
#define GDX_CPP_MATH_RECTANGLE_HPP

#include <string>

namespace gdx {

class Rectangle
{

public:
    float x, y;
    float width, height;
    Rectangle();
    Rectangle(const Rectangle& other);
    Rectangle(float x, float y, float width, float height);
    virtual ~Rectangle();
    virtual Rectangle& operator=(const Rectangle& other);
    float getX () const;
    void setX (float _x);
    float getY () const;
    void setY (float _y);
    float getWidth () const;
    void setWidth (float _width);
    float getHeight () const;
    void setHeight (float _height);
    bool contains (const Rectangle& rectangle);
    bool overlaps (const Rectangle& rectangle);
    void set (float x, float y, float width, float height);
    bool contains (float x, float y);
    void set (const Rectangle& rect);
    void merge(const Rectangle& rect);
    std::string toString ();
};

}

#endif // GDX_CPP_MATH_RECTANGLE_HPP
