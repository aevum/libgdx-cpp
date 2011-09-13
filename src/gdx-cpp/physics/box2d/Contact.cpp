
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
#include "Box2D.h"
#include "gdx-cpp/math/Vector2.hpp"
#include "World.hpp"

using namespace gdx_cpp::physics::box2d;

Contact::Contact (World::ptr _world, b2Contact* _addr): world(_world), contact(_addr)
{
  
}



WorldManifold& Contact::getWorldManifold () {
    b2WorldManifold manifold;
    contact->GetWorldManifold(&manifold);
    int numContactPoints = contact->GetManifold()->pointCount;

    float tmp[2];
    tmp[0] = manifold.normal.x;
    tmp[1] = manifold.normal.y;

    for ( int i = 0; i < numContactPoints; i++ )
    {
        tmp[2 + i*2] = manifold.points[i].x;
        tmp[2 + i*2+1] = manifold.points[i].y;
    }



    worldManifold.numContactPoints = numContactPoints;
    worldManifold.normal.set(tmp[0], tmp[1]);
    for (int i = 0; i < numContactPoints; i++) {
        gdx_cpp::math::Vector2 point = worldManifold.points[i];//TODO ver se ñ esta fazendo copia
        point.x = tmp[2 + i * 2];
        point.y = tmp[2 + i * 2 + 1];
    }

    return worldManifold;
}

bool Contact::isTouching () {
    return contact->IsTouching();
}

void Contact::setEnabled (bool flag) {
    contact->SetEnabled(flag);
}

bool Contact::isEnabled () {
    return contact->IsEnabled();
}

Fixture& Contact::getFixtureA () {
    return *world->fixtures[contact->GetFixtureA()];
}

Fixture& Contact::getFixtureB () {
    return *world->fixtures[contact->GetFixtureB()];
}

