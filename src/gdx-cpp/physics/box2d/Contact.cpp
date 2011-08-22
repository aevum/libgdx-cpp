
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

#include "Contact.hpp"

using namespace gdx_cpp::physics::box2d;

WorldManifold& Contact::getWorldManifold () {
    int numContactPoints = jniGetWorldManifold(addr, tmp);

    worldManifold.numContactPoints = numContactPoints;
    worldManifold.normal.set(tmp[0], tmp[1]);
    for (int i = 0; i < numContactPoints; i++) {
        Vector2 point = worldManifold.points[i];
        point.x = tmp[2 + i * 2];
        point.y = tmp[2 + i * 2 + 1];
    }

    return worldManifold;
}

bool Contact::isTouching () {
    return jniIsTouching(addr);
}

void Contact::setEnabled (bool flag) {
    jniSetEnabled(addr, flag);
}

bool Contact::isEnabled () {
    return jniIsEnabled(addr);
}

Fixture& Contact::getFixtureA () {
    return world.fixtures.get(jniGetFixtureA(addr));
}

Fixture& Contact::getFixtureB () {
    return world.fixtures.get(jniGetFixtureB(addr));
}

