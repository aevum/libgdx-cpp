
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

#ifndef GDX_CPP_MATH_PLANE_HPP_
#define GDX_CPP_MATH_PLANE_HPP_

#include <string>
#include "Vector3.hpp"

namespace gdx {

class Plane {
public:
    
      enum PlaneSide {
        PlaneSide_OnPlane, PlaneSide_Back, PlaneSide_Front
      };
    
    Plane (const Vector3& normal, float d);

    void set (const Vector3& point1, const Vector3& point2, const Vector3& point3);
    void set (float nx,float ny,float nz,float d);
    float distance (const Vector3& point);
    PlaneSide testPoint (const Vector3& point);
    bool isFrontFacing (const Vector3& direction);
    Vector3& getNormal ();
    float getD ();
    void set (const Vector3& point, const Vector3& normal);
    void set (const Plane& plane);
    std::string toString ();

    Vector3 normal;
    float d;

protected:


private:

};

} // namespace gdx

#endif // GDX_CPP_MATH_PLANE_HPP_
