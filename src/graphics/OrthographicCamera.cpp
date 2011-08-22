
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

#include "OrthographicCamera.hpp"

using namespace gdx_cpp::graphics;

void OrthographicCamera::findDirectionForIsoView (float targetAngle,float epsilon,int maxIterations) {
    float start = targetAngle - 5;
    float end = targetAngle + 5;
    float mid = targetAngle;

    int iterations = 0;
    float aMid = 0;
    while (Math.abs(targetAngle - aMid) > epsilon && iterations++ < maxIterations) {
        aMid = calculateAngle(mid);

        if (targetAngle < aMid) {
            end = mid;
        } else {
            start = mid;
        }
        mid = start + (end - start) / 2;
    }
    position.set(calculateDirection(mid));
    position.y = -position.y;
    lookAt(0, 0, 0);
    normalizeUp();
}

float OrthographicCamera::calculateAngle (float a) {
    Vector3 camPos = calculateDirection(a);
    position.set(camPos.mul(30));
    lookAt(0, 0, 0);
    normalizeUp();
    update();

    Vector3 orig = new Vector3(0, 0, 0);
    Vector3 vec = new Vector3(1, 0, 0);
    project(orig);
    project(vec);
    Vector2 d = new Vector2(vec.x - orig.x, -(vec.y - orig.y));
    return d.angle();
}

gdx_cpp::math::Vector3& OrthographicCamera::calculateDirection (float angle) {
    Matrix4 transform = new Matrix4();
    Vector3 dir = new Vector3(-1, 0, 1).nor();
    float rotAngle = (float)Math.toDegrees(Math.asin(Math.tan(Math.toRadians(angle))));
    transform.setToRotation(new Vector3(1, 0, 1).nor(), angle);
    dir.mul(transform).nor();
    return dir;
}

void OrthographicCamera::update () {
    projection.setToOrtho(zoom * -viewportWidth / 2, zoom * viewportWidth / 2, zoom * -viewportHeight / 2, zoom
                          * viewportHeight / 2, Math.abs(near), Math.abs(far));
    view.setToLookAt(position, tmp.set(position).add(direction), up);
    combined.set(projection);
    Matrix4.mul(combined.val, view.val);
    invProjectionView.set(combined);
    Matrix4.inv(invProjectionView.val);
    frustum.update(invProjectionView);
}

