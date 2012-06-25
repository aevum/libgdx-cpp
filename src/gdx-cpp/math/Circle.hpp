
/*
 *  Copyright 2011 Aevum Software aevum @ aevumlab.com
 * 
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 * 
 *      http://www.apache.org/licenses/LICENSE-2.0
 * 
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 * 
 *  @author Victor Vicente de Carvalho victor.carvalho@aevumlab.com
 *  @author Ozires Bortolon de Faria ozires@aevumlab.com
 */


#ifndef GDX_CPP_MATH_CIRCLE_HPP
#define GDX_CPP_MATH_CIRCLE_HPP

namespace gdx {

class Vector2;

class Circle
{
public:
    Circle();
    Circle(const Vector2& position, float _radius);
    Circle(float x, float y, float radius);
    virtual ~Circle();
    virtual Circle& operator=(const Circle& other);
    virtual bool operator==(const Circle& other) const;
    bool contains (const Vector2& point);
    bool contains (float x, float y);
    void set(float x, float y, float radius);
    
    float x, y;
    float radius;
};

}

#endif // GDX_CPP_MATH_CIRCLE_HPP
