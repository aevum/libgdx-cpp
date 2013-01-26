
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

#ifndef GDX_CPP_MATH_FRUSTUM_HPP_
#define GDX_CPP_MATH_FRUSTUM_HPP_

#include "Plane.hpp"
#include "Vector3.hpp"

namespace gdx {

class BoundingBox;
class Matrix4;
class Ray;
class Plane;

class Frustum {
public:
    Frustum();
    void update (const Matrix4& inverseProjectionView);
    bool pointInFrustum (const Vector3& point);
    bool sphereInFrustum (const Vector3& center,float radius);
    bool sphereInFrustumWithoutNearFar (const Vector3& center,float radius);
    bool boundsInFrustum (BoundingBox& bounds);
//     Ray& calculatePickRay (float screen_width,float screen_height,float mouse_x,float mouse_y,const Vector3& pos,const Vector3& dir,const Vector3& up);
    static void main ();

    Plane* planes[6];
    Vector3 planePoints[8];

    virtual ~Frustum();
    
protected:
    static Vector3 clipSpacePlanePoints[];
    static float clipSpacePlanePointsArray[];
    float planePointsArray[24];
private:
    static class init {
        init() {
            int j = 0;
            for (int i = 0; i < 8; ++i) {
                clipSpacePlanePointsArray[j++] = clipSpacePlanePoints[i].x;
                clipSpacePlanePointsArray[j++] = clipSpacePlanePoints[i].y;
                clipSpacePlanePointsArray[j++] = clipSpacePlanePoints[i].z;
            }
        }
    } _i;
};

} // namespace gdx

#endif // GDX_CPP_MATH_FRUSTUM_HPP_
