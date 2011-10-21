
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

#ifndef GDX_CPP_GRAPHICS_ORTHOGRAPHICCAMERA_HPP_
#define GDX_CPP_GRAPHICS_ORTHOGRAPHICCAMERA_HPP_

#include "Camera.hpp"

namespace gdx_cpp {
namespace graphics {

class OrthographicCamera : public graphics::Camera {
public:
    OrthographicCamera();
    OrthographicCamera (float viewportWidth, float viewportHeight);
    OrthographicCamera (float viewportWidth, float viewportHeight, float diamondAngle);
    
    void findDirectionForIsoView (float targetAngle,float epsilon,int maxIterations);
    void update ();
    void setToOrtho(bool yDown);
    void setToOrtho(bool yDown, float viewportWidth, float viewportHeight);
    
    float zoom;
    
protected:
    math::Vector3 tmp;
    
private:
    float calculateAngle (float a);
    void calculateDirection (float angle, gdx_cpp::math::Vector3& dir);
};

} // namespace gdx_cpp
} // namespace graphics

#endif // GDX_CPP_GRAPHICS_ORTHOGRAPHICCAMERA_HPP_
