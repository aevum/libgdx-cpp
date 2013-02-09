
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

#include <sstream>

#include "Plane.hpp"
#include "gdx-cpp/math/Vector3.hpp"

using namespace gdx;

Plane::Plane (const Vector3& normal, float d) : d(d) {
  this->normal.set(normal).nor();
}

void Plane::set (const Vector3& point1,const Vector3& point2,const Vector3& point3) {
    Vector3 l = point1.tmp().sub(point2);
    Vector3 r = point2.tmp2().sub(point3);
    Vector3 nor = l.crs(r).nor();
    normal.set(nor);
    d = -point1.dot(nor);
}

void Plane::set (float nx,float ny,float nz,float d) {
    normal.set(nx, ny, nz);
    this->d = d;
}

float Plane::distance (const Vector3& point) {
    return normal.dot(point) + d;
}

Plane::PlaneSide Plane::testPoint (const Vector3& point) {
    float dist = normal.dot(point) + d;

    if (dist == 0)
      return PlaneSide_OnPlane;
    else if (dist < 0)
      return PlaneSide_Back;
    else
      return PlaneSide_Front;
}

bool Plane::isFrontFacing (const Vector3& direction) {
    float dot = normal.dot(direction);
    return dot <= 0;
}

Vector3& Plane::getNormal () {
    return normal;
}

float Plane::getD () {
    return d;
}

void Plane::set (const Vector3& point,const Vector3& normal){
    this->normal.set(normal);
    d = -point.dot(normal);
}

void Plane::set (const Plane& plane) {
    this->normal.set(plane.normal);
    this->d = plane.d;
}

std::string Plane::toString () {
    std::stringstream ss;
    ss << normal.toString() << ", " << d;
    
    return ss.str();
}

