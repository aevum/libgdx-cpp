
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

#include "ContactImpulse.hpp"
#include "Box2D.h"

using namespace gdx_cpp::physics::box2d;

ContactImpulse::ContactImpulse (World::ptr _world, b2ContactImpulse * _addr) : world(_world), addr(_addr)
{
  
}

float* ContactImpulse::getNormalImpulses () {
    normalImpulses[0] = addr->normalImpulses[0];
    normalImpulses[1] = addr->normalImpulses[1];
    return normalImpulses;
}

float* ContactImpulse::getTangentImpulses () {
    tangentImpulses[0] = addr->tangentImpulses[0];
    tangentImpulses[1] = addr->tangentImpulses[1];
    return tangentImpulses;
}

