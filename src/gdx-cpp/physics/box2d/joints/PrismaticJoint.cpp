
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

#include "PrismaticJoint.hpp"
#include "Box2D.h"

using namespace gdx_cpp::physics::box2d::joints;

PrismaticJoint::PrismaticJoint(ref_ptr_maker< gdx_cpp::physics::box2d::World >::type _world, b2PrismaticJoint* joint) : Joint(_world, joint)
{

}

float PrismaticJoint::getJointTranslation () {
    return static_cast<b2PrismaticJoint * >(addr)->GetJointTranslation();
}

float PrismaticJoint::getJointSpeed () {
    return static_cast<b2PrismaticJoint * >(addr)->GetJointSpeed();
}

bool PrismaticJoint::isLimitEnabled () {
    return static_cast<b2PrismaticJoint * >(addr)->IsLimitEnabled();
}

void PrismaticJoint::enableLimit (bool flag) {
    static_cast<b2PrismaticJoint * >(addr)->EnableLimit(flag);
}

float PrismaticJoint::getLowerLimit () {
    return static_cast<b2PrismaticJoint * >(addr)->GetLowerLimit();
}

float PrismaticJoint::getUpperLimit () {
    return static_cast<b2PrismaticJoint * >(addr)->GetUpperLimit();
}

void PrismaticJoint::setLimits (float lower,float upper) {
    static_cast<b2PrismaticJoint * >(addr)->SetLimits(lower, upper);
}

bool PrismaticJoint::isMotorEnabled () {
    return static_cast<b2PrismaticJoint * >(addr)->IsMotorEnabled();
}

void PrismaticJoint::enableMotor (bool flag) {
    static_cast<b2PrismaticJoint * >(addr)->EnableMotor(flag);
}

void PrismaticJoint::setMotorSpeed (float speed) {
    static_cast<b2PrismaticJoint * >(addr)->SetMotorSpeed(speed);
}

float PrismaticJoint::getMotorSpeed () {
    return static_cast<b2PrismaticJoint * >(addr)->GetMotorSpeed();
}

void PrismaticJoint::setMaxMotorForce (float force) {
    static_cast<b2PrismaticJoint * >(addr)->SetMaxMotorForce(force);
}

float PrismaticJoint::getMotorForce () {
    return static_cast<b2PrismaticJoint * >(addr)->GetMotorForce();
}

