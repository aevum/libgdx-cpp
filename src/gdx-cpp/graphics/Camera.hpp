
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

namespace gdx {

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
    void unproject (Vector3& vec, float viewportX, float viewportY, float viewportWidth, float viewportHeight);
    void unproject (Vector3& vec);
    void project (Vector3& vec);
    void project (Vector3& vec, float viewportX, float viewportY, float viewportWidth, float viewportHeight);
    Ray& getPickRay (float x,float y,float viewportX,float viewportY,float viewportWidth,float viewportHeight);
    Ray& getPickRay (float x,float y);
    
    Vector3 position;
    Vector3 direction;
    Vector3 up;
    
    Matrix4 projection;
    Matrix4 view;
    Matrix4 combined ;
    Matrix4 invProjectionView;
    
    float near;
    float far;    
    float viewportWidth;
    
    float viewportHeight;
    
    Frustum frustum;
protected:
    Vector3 right;
    Ray ray;
    
private:
    Matrix4 tmpMat;
    Vector3 tmpVec;
};

} // namespace gdx

#endif // GDX_CPP_GRAPHICS_CAMERA_HPP_
