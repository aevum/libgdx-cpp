
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

#ifndef GDX_CPP_MATH_POLYGON_HPP_
#define GDX_CPP_MATH_POLYGON_HPP_

#include <vector>

#include "Rectangle.hpp"

namespace gdx {
class Rectangle;

class Polygon {
public:
    Polygon (const std::vector<float>& vertices);
  
    std::vector<float>& getVertices ();

    void setOrigin (float originX,float originY);
    void setPosition (float x,float y);
    void translate (float x,float y);
    void setRotation (float degrees);
    void rotate (float degrees);
    void setScale (float scaleX,float scaleY);
    void scale (float amount);
    float area ();
    Rectangle& getBoundingRectangle ();
    bool contains (float x,float y);
    float getX ();
    float getY ();
    float getOriginX ();
    float getOriginY ();
    float getRotation ();
    float getScaleX ();
    float getScaleY ();

protected:


private:
  std::vector<float> vertices;
  float x, y;
  float originX, originY;
  float rotation;
  float scaleX, scaleY;
  bool dirty;
  Rectangle bounds;
};

} // namespace gdx

#endif // GDX_CPP_MATH_POLYGON_HPP_
