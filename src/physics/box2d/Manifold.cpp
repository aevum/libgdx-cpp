
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

using namespace gdx_cpp::physics::box2d;

ManifoldType& Manifold::getType () {
    int type = jniGetType(addr);
    if (type == 0) return ManifoldType.Circle;
    if (type == 1) return ManifoldType.FaceA;
    if (type == 2) return ManifoldType.FaceB;
    return ManifoldType.Circle;
}

int Manifold::getPointCount () {
    return jniGetPointCount(addr);
}

gdx_cpp::math::Vector2& Manifold::getLocalNormal () {
    jniGetLocalNormal(addr, tmpFloat);
    localNormal.set(tmpFloat[0], tmpFloat[1]);
    return localNormal;
}

gdx_cpp::math::Vector2& Manifold::getLocalPoint () {
    jniGetLocalPoint(addr, tmpFloat);
    localPoint.set(tmpFloat[0], tmpFloat[1]);
    return localPoint;
}

ManifoldPoint* Manifold::getPoints () {
    int count = jniGetPointCount(addr);

    for (int i = 0; i < count; i++) {
        int contactID = jniGetPoint(addr, tmpFloat, i);
        ManifoldPoint point = points[i];
        point.contactID = contactID;
        point.localPoint.set(tmpFloat[0], tmpFloat[1]);
        point.normalImpulse = tmpFloat[2];
        point.tangentImpulse = tmpFloat[3];
    }

    return points;
}

std::string& Manifold::toString () {
    return "id: " + contactID + ", " + localPoint + ", " + normalImpulse + ", " + tangentImpulse;
}

