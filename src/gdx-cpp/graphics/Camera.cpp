
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

#include "Camera.hpp"

using namespace gdx;

#include "gdx-cpp/Gdx.hpp"
#include "gdx-cpp/Graphics.hpp"
#include "gdx-cpp/gl.hpp"

Camera::Camera()
: direction(0, 0, -1)
, up(0, 1, 0)
, near(1)
, far(100)
, viewportWidth(0)
, viewportHeight(0)
{
}

Camera::Camera(float viewportHeight, float viewportWidth, float near, float far)
: direction(0, 0, -1)
, up(0, 1, 0)
, near(near)
, far(far)
, viewportWidth(viewportWidth)
, viewportHeight(viewportHeight)
{
}

void Camera::apply (const GL10& gl) {
    gl.glMatrixMode(GL_PROJECTION);
    gl.glLoadMatrixf(projection.val);
    gl.glMatrixMode(GL_MODELVIEW);
    gl.glLoadMatrixf(view.val);
}

void Camera::lookAt (float x,float y,float z) {
    direction.set(x, y, z).sub(position).nor();
}

void Camera::normalizeUp () {
    right.set(direction).crs(up).nor();
    up.set(right).crs(direction).nor();
}

void Camera::rotate (float angle,float axisX,float axisY,float axisZ) {
    tmpMat.setToRotation(tmpVec.set(axisX, axisY, axisZ), angle);
    direction.mul(tmpMat).nor();
    up.mul(tmpMat).nor();
}

void Camera::translate (float x,float y,float z) {
    position.add(x, y, z);
}

void Camera::unproject (Vector3& vec,float viewportX,float viewportY,float viewportWidth,float viewportHeight) {
    float x = vec.x, y = vec.y;
    x = x - viewportX;
    y = Gdx::graphics->getHeight() - y - 1;
    y = y - viewportY;
    vec.x = (2 * x) / viewportWidth - 1;
    vec.y = (2 * y) / viewportHeight - 1;
    vec.z = 2 * vec.z - 1;
    vec.prj(invProjectionView);
}

void Camera::unproject (Vector3& vec) {
    unproject(vec, 0, 0, Gdx::graphics->getWidth(), Gdx::graphics->getHeight());
}

void Camera::project (Vector3& vec) {
    project(vec, 0, 0, Gdx::graphics->getWidth(),Gdx::graphics->getHeight());
}

void Camera::project (Vector3& vec,float viewportX,float viewportY,float viewportWidth,float viewportHeight) {
    vec.prj(combined);
    vec.x = viewportWidth * (vec.x + 1) / 2 + viewportX;
    vec.y = viewportHeight * (vec.y + 1) / 2 + viewportY;
    vec.z = (vec.z + 1) / 2;
}

Ray& Camera::getPickRay (float x,float y,float viewportX,float viewportY,float viewportWidth,float viewportHeight) {
    unproject(ray.origin.set(x, y, 0), viewportX, viewportY, viewportWidth, viewportHeight);
    unproject(ray.direction.set(x, y, 1), viewportX, viewportY, viewportWidth, viewportHeight);
    ray.direction.sub(ray.origin).nor();
    return ray;
}

Ray& Camera::getPickRay (float x,float y) {
    return getPickRay(x, y, 0, 0, Gdx::graphics->getWidth(), Gdx::graphics->getHeight());
}

