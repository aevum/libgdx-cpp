
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

#include <cmath>

#include "OrthographicCamera.hpp"
#include "gdx-cpp/Gdx.hpp"
#include "gdx-cpp/Graphics.hpp"
#include "gdx-cpp/graphics/Camera.hpp"
#include "gdx-cpp/math/Frustum.hpp"
#include "gdx-cpp/math/MathUtils.hpp"
#include "gdx-cpp/math/Matrix4.hpp"
#include "gdx-cpp/math/Vector2.hpp"

using namespace gdx;

OrthographicCamera::OrthographicCamera()
 : Camera(0, 0, 0, 100),
zoom(1)
{
}

OrthographicCamera::OrthographicCamera(float viewportWidth, float viewportHeight)
: Camera(viewportHeight, viewportWidth, 0, 100),
zoom(1)
{
}

OrthographicCamera::OrthographicCamera(float viewportWidth, float viewportHeight, float diamondAngle)
: Camera(viewportHeight, viewportWidth, 0, 100),
zoom(1)
{
    findDirectionForIsoView(diamondAngle, 0.00000001f, 20);
}

void OrthographicCamera::findDirectionForIsoView (float targetAngle,float epsilon,int maxIterations) {
    float start = targetAngle - 5;
    float end = targetAngle + 5;
    float mid = targetAngle;

    int iterations = 0;
    float aMid = 0;
    while (std::abs(targetAngle - aMid) > epsilon && iterations++ < maxIterations) {
        aMid = calculateAngle(mid);

        if (targetAngle < aMid) {
            end = mid;
        } else {
            start = mid;
        }
        mid = start + (end - start) / 2;
    }
    calculateDirection(mid, position);
    position.y = -position.y;
    lookAt(0, 0, 0);
    normalizeUp();
}

float OrthographicCamera::calculateAngle (float a) {
    Vector3 camPos;
    calculateDirection(a, camPos);
    position.set(camPos.mul(30));
    lookAt(0, 0, 0);
    normalizeUp();
    update();

    Vector3 orig(0, 0, 0);
    Vector3 vec (1, 0, 0);
    project(orig);
    project(vec);
    Vector2 d(vec.x - orig.x, -(vec.y - orig.y));
    return d.angle();
}

void OrthographicCamera::calculateDirection (float angle, Vector3& dir) {
    Matrix4 transform;
    dir = Vector3(-1, 0, 1).nor();
    transform.setToRotation(Vector3(1, 0, 1).nor(), angle);
    dir.mul(transform).nor();
}

void OrthographicCamera::update () {
    projection.setToOrtho(zoom * -viewportWidth / 2, zoom * viewportWidth / 2, zoom * -viewportHeight / 2, zoom
                          * viewportHeight / 2, std::abs(near), std::abs(far));
    view.setToLookAt(position, tmp.set(position).add(direction), up);
    combined.set(projection);
    Matrix4::mul(combined.val, view.val);
    invProjectionView.set(combined);
    Matrix4::inv(invProjectionView.val);
    frustum.update(invProjectionView);
}


void OrthographicCamera::setToOrtho(bool yDown)
{
    setToOrtho(yDown, graphics->getWidth(), graphics->getHeight());
}

void OrthographicCamera::setToOrtho(bool yDown, float viewportWidth, float viewportHeight)
{
  if (yDown) {
        up.set(0, -1, 0);
        direction.set(0, 0, 1);
    }
    this->viewportWidth = viewportWidth;
    this->viewportHeight = viewportHeight;
    
    position.set(viewportWidth / 2.0f, viewportHeight / 2.0f, 0);
    update();
}
    
