
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

#include "Manifold.hpp"
#include "Box2D.h"

using namespace gdx_cpp::physics::box2d;


Manifold::Manifold(World::ptr _world, b2Manifold * mani): world(world), addr(mani)
{
  
}

Manifold::ManifoldType Manifold::getType () {
    if (addr->type == 0) return Circle;
    if (addr->type == 1) return FaceA;
    if (addr->type == 2) return FaceB;
    return Circle;
}

int Manifold::getPointCount () {
    return addr->pointCount;
}

gdx_cpp::math::Vector2& Manifold::getLocalNormal () {
    localNormal.set(addr->localNormal.x, addr->localNormal.y);
    return localNormal;
}

gdx_cpp::math::Vector2& Manifold::getLocalPoint () {
    localPoint.set(addr->localPoint.x, localPoint.y);
    return localPoint;
}

gdx_cpp::physics::box2d::ManifoldPoint* Manifold::getPoints () {
    int count = addr->pointCount;

    for (int i = 0; i < count; i++) {
        int contactID = addr->points[i].id.key;
        ManifoldPoint point = points[i];
        point.contactID = contactID;
        point.localPoint.set(addr->points[i].localPoint.x, addr->points[i].localPoint.y);
        point.normalImpulse = addr->points[i].normalImpulse;
        point.tangentImpulse = addr->points[i].tangentImpulse;
    }

    return points;
}

