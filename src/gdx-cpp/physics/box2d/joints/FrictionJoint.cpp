
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

#include "FrictionJoint.hpp"
#include <Box2D.h>

using namespace gdx_cpp::physics::box2d::joints;

FrictionJoint::FrictionJoint(ref_ptr_maker< gdx_cpp::physics::box2d::World >::type _world, b2FrictionJoint* joint) : Joint(_world, joint)
{

}

void FrictionJoint::setMaxForce (float force) {
    static_cast<b2FrictionJoint *>(addr)->SetMaxForce(force);
}

float FrictionJoint::getMaxForce () {
    return static_cast<b2FrictionJoint *>(addr)->GetMaxForce();
}

void FrictionJoint::setMaxTorque (float torque) {
    static_cast<b2FrictionJoint *>(addr)->SetMaxTorque(torque);
}

float FrictionJoint::getMaxTorque () {
    return static_cast<b2FrictionJoint *>(addr)->GetMaxTorque();
}

