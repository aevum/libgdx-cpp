
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

#include "Ray.hpp"

#include "gdx-cpp/math/Matrix4.hpp"

#include <sstream>
#include <string>

using namespace gdx;

Vector3 Ray::tmp = Vector3();

Ray::Ray()
{
    direction.nor();
}

Ray::Ray (Vector3& origin, Vector3& direction)
:
origin(origin),
direction(direction)
{
    direction.nor();
}

Ray Ray::cpy () {
    return Ray(this->origin, this->direction);
}

Vector3& Ray::getEndPoint (float distance) {
    Vector3 o(origin);
    return o.add(direction.tmp().mul(distance));
}

Ray& Ray::mul (const Matrix4& matrix) {
    tmp.set(origin).add(direction);
    tmp.mul(matrix);
    origin.mul(matrix);
    direction.set(tmp.sub(origin));
    return *this;
}

std::string Ray::toString () {
    std::stringstream ss;
    ss << "ray [" << origin.toString() << ":" << direction.toString() << "]";
    return ss.str();
}

Ray& Ray::set (const Vector3& origin,const Vector3& direction) {
    this->origin.set(origin);
    this->direction.set(direction);
    return *this;
}

Ray& Ray::set (float x,float y,float z,float dx,float dy,float dz) {
  this->origin.set(x, y, z);
  this->direction.set(dx, dy, dz);
    return *this;
}

Ray& Ray::set (const Ray& ray) {

    this->origin.set(ray.origin);
    this->direction.set(ray.direction);
    return *this;
}

