
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

#include "PerspectiveCamera.hpp"
#include <cmath>

using namespace gdx_cpp::graphics;
using namespace gdx_cpp;

gdx_cpp::graphics::PerspectiveCamera::PerspectiveCamera()
    : fieldOfView(67)
{
}

gdx_cpp::graphics::PerspectiveCamera::PerspectiveCamera(float fieldOfView, float viewportWidth, float viewportHeight)
: Camera(viewportHeight, viewportWidth, 1, 100) ,
fieldOfView(fieldOfView)
{
    update();
}


void PerspectiveCamera::update () {
    float aspect = viewportWidth / viewportHeight;
    projection.setToProjection(std::abs(near), std::abs(far), fieldOfView, aspect);
    view.setToLookAt(position, tmp.set(position).add(direction), up);
    combined.set(projection);
    math::Matrix4::mul(combined.val, view.val);
    invProjectionView.set(combined);
    math::Matrix4::inv(invProjectionView.val);
    frustum.update(invProjectionView);
}

