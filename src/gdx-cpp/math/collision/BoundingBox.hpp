
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

#ifndef GDX_CPP_MATH_COLLISION_BOUNDINGBOX_HPP_
#define GDX_CPP_MATH_COLLISION_BOUNDINGBOX_HPP_

#include <string>
#include <vector>

#include "gdx-cpp/math/Vector3.hpp"

namespace gdx {
class Vector3;
class Matrix4;

class BoundingBox {
public:
	BoundingBox();
   BoundingBox (const BoundingBox& bounds);
   
    Vector3& getCenter ();
    const std::vector< Vector3 >& getCorners ();
    Vector3& getDimensions ();
    Vector3& getMin ();
    Vector3& getMax ();
    BoundingBox& set (const BoundingBox& bounds);
    BoundingBox& set (const Vector3& minimum,const Vector3& maximum);
    BoundingBox& set ();
    BoundingBox& set (const std::vector<Vector3>& points);
    BoundingBox& inf ();
    BoundingBox& ext (const Vector3& point);
    BoundingBox& clr ();
    bool isValid ();
    BoundingBox& ext (const BoundingBox& a_bounds);
    BoundingBox& mul (const Matrix4& matrix);
    bool contains (const BoundingBox& bounds);
    bool contains (const Vector3& v);
    std::string toString ();
    BoundingBox& ext (float x,float y,float z);

    Vector3 min;
    Vector3 max;
protected:
    void updateCorners ();

    std::vector<Vector3> crn;

    Vector3 cnt;
    Vector3 dim;
    
    bool crn_dirty;

    static float _min (float a, float b) {
      return a > b ? b : a;
    }
    
    static float _max (float a, float b) {
      return a > b ? a : b;
    }
private:

};

} // namespace gdx

#endif // GDX_CPP_MATH_COLLISION_BOUNDINGBOX_HPP_
