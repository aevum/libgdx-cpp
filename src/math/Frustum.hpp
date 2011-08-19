
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

namespace gdx_cpp {
namespace math {

class Frustum {
public:
    void update (const Matrix4& inverseProjectionView);
    bool pointInFrustum (const Vector3& point);
    bool sphereInFrustum (const Vector3& center,float radius);
    bool sphereInFrustumWithoutNearFar (const Vector3& center,float radius);
    bool boundsInFrustum (const gdx_cpp::math::collision::BoundingBox& bounds);
    Ray& calculatePickRay (float screen_width,float screen_height,float mouse_x,float mouse_y,const Vector3& pos,const Vector3& dir,const Vector3& up);
    static void main ();

protected:


private:

};

} // namespace gdx_cpp
} // namespace math

#endif // GDX_CPP_MATH_FRUSTUM_HPP_
