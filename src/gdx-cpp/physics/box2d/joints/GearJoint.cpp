
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

#include "GearJoint.hpp"
#include "Box2D.h"

using namespace gdx_cpp::physics::box2d::joints;

GearJoint::GearJoint(ref_ptr_maker< gdx_cpp::physics::box2d::World >::type _world, b2GearJoint* joint) : Joint(_world, joint)
{

}

void GearJoint::setRatio (float ratio) {
    static_cast<b2GearJoint *>(addr)->SetRatio(ratio);
}

float GearJoint::getRatio () {
    return static_cast<b2GearJoint *> (addr)->GetRatio();
}

