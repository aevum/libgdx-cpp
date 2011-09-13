
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

#include "RevoluteJoint.hpp"
#include "Box2D.h"

using namespace gdx_cpp::physics::box2d::joints;

RevoluteJoint::RevoluteJoint(ref_ptr_maker< gdx_cpp::physics::box2d::World >::type _world, b2RevoluteJoint* joint) : Joint(_world, joint)
{

}

float RevoluteJoint::getJointAngle () {
    return static_cast<b2RevoluteJoint * >(addr)->GetJointAngle();
}

float RevoluteJoint::getJointSpeed () {
    return static_cast<b2RevoluteJoint * >(addr)->GetJointSpeed();
}

bool RevoluteJoint::isLimitEnabled () {
    return static_cast<b2RevoluteJoint * >(addr)->IsLimitEnabled();
}

void RevoluteJoint::enableLimit (bool flag) {
    static_cast<b2RevoluteJoint * >(addr)->EnableLimit(flag);
}

float RevoluteJoint::getLowerLimit () {
    return static_cast<b2RevoluteJoint * >(addr)->GetLowerLimit();
}

float RevoluteJoint::getUpperLimit () {
    return static_cast<b2RevoluteJoint * >(addr)->GetUpperLimit();
}

void RevoluteJoint::setLimits (float lower,float upper) {
    static_cast<b2RevoluteJoint * >(addr)->SetLimits(lower, upper);
}

bool RevoluteJoint::isMotorEnabled () {
    return static_cast<b2RevoluteJoint * >(addr)->IsMotorEnabled();
}

void RevoluteJoint::enableMotor (bool flag) {
    static_cast<b2RevoluteJoint * >(addr)->EnableMotor(flag);
}

void RevoluteJoint::setMotorSpeed (float speed) {
    static_cast<b2RevoluteJoint * >(addr)->SetMotorSpeed(speed);
}

float RevoluteJoint::getMotorSpeed () {
    return static_cast<b2RevoluteJoint * >(addr)->GetMotorSpeed();
}

void RevoluteJoint::setMaxMotorTorque (float torque) {
    static_cast<b2RevoluteJoint * >(addr)->SetMaxMotorTorque(torque);
}

float RevoluteJoint::getMotorTorque () {
    return static_cast<b2RevoluteJoint * >(addr)->GetMotorTorque();
}

