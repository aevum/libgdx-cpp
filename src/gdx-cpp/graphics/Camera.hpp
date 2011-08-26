
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

#ifndef GDX_CPP_GRAPHICS_CAMERA_HPP_
#define GDX_CPP_GRAPHICS_CAMERA_HPP_

#include "gdx-cpp/math/Vector3.hpp"
#include "gdx-cpp/math/Matrix4.hpp"
#include "gdx-cpp/math/collision/Ray.hpp"
#include "gdx-cpp/math/Frustum.hpp"
#include "gdx-cpp/graphics/GL10.hpp"

namespace gdx_cpp {
namespace graphics {

class Camera {
public:
    Camera();
    Camera(float viewportHeight, float viewportWidth,float near, float far);
    
    virtual   void update () = 0;
    void apply (const GL10& gl);
    void lookAt (float x,float y,float z);
    void normalizeUp ();
    void rotate (float angle,float axisX,float axisY,float axisZ);
    void translate (float x,float y,float z);
    void unproject (gdx_cpp::math::Vector3& vec, float viewportX, float viewportY, float viewportWidth, float viewportHeight);
    void unproject (gdx_cpp::math::Vector3& vec);
    void project (gdx_cpp::math::Vector3& vec);
    void project (gdx_cpp::math::Vector3& vec, float viewportX, float viewportY, float viewportWidth, float viewportHeight);
    math::collision::Ray& getPickRay (float x,float y,float viewportX,float viewportY,float viewportWidth,float viewportHeight);
    math::collision::Ray& getPickRay (float x,float y);
    
    math::Vector3 position;
    math::Vector3 direction;
    math::Vector3 up;
    
    math::Matrix4 projection;
    math::Matrix4 view;
    math::Matrix4 combined ;
    math::Matrix4 invProjectionView;
    
    float near;
    float far;    
    float viewportWidth;
    
    float viewportHeight;
    
    math::Frustum frustum;
protected:
    math::Vector3 right;
    math::collision::Ray ray;
    
private:
    math::Matrix4 tmpMat;
    math::Vector3 tmpVec;
};

} // namespace gdx_cpp
} // namespace graphics

#endif // GDX_CPP_GRAPHICS_CAMERA_HPP_
