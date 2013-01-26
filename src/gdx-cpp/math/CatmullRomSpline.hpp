
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

#ifndef GDX_CPP_MATH_CATMULLROMSPLINE_HPP_
#define GDX_CPP_MATH_CATMULLROMSPLINE_HPP_

#include <vector>

#include "Vector3.hpp"
#include "gdx-cpp/internal/memory"

namespace gdx {
class Vector3;
  
class CatmullRomSpline {
public:
    CatmullRomSpline();

    typedef ref_ptr_maker< std::vector<Vector3> >::shared_ptr_t vector3_vector_ptr;
    
    void add (const Vector3& point);
    std::vector<Vector3>& getControlPoints ();
    vector3_vector_ptr getPath (int numPoints);
    void getPath (std::vector<Vector3>& points, int numPoints);
    
    vector3_vector_ptr getTangents (int numPoints);
    vector3_vector_ptr getTangentNormals2D (int numPoints);
    vector3_vector_ptr getTangentNormals (int numPoints,const Vector3& up);
    vector3_vector_ptr getTangentNormals (int numPoints, std::vector<Vector3>& up);
    
    Vector3 T1;
    Vector3 T2;
protected:

private:
  std::vector<Vector3> controlPoints;
};

} // namespace gdx

#endif // GDX_CPP_MATH_CATMULLROMSPLINE_HPP_
