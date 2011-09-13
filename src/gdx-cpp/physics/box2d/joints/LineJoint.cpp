
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

#include "LineJoint.hpp"
#include "Box2D.h"

using namespace gdx_cpp::physics::box2d::joints;

LineJoint::LineJoint(ref_ptr_maker< gdx_cpp::physics::box2d::World >::type _world, b2LineJoint* joint) : Joint(_world, joint)
{

}

float LineJoint::getJointTranslation () {
    return static_cast<b2LineJoint * >(addr)->GetJointTranslation();
}

float LineJoint::getJointSpeed () {
    return static_cast<b2LineJoint * >(addr)->GetJointSpeed();
}

bool LineJoint::isLimitEnabled () {
    return static_cast<b2LineJoint * >(addr)->IsLimitEnabled();
}

void LineJoint::enableLimit (bool flag) {
    static_cast<b2LineJoint * >(addr)->EnableLimit(flag);
}

float LineJoint::getLowerLimit () {
    return static_cast<b2LineJoint * >(addr)->GetLowerLimit();
}

float LineJoint::getUpperLimit () {
    return static_cast<b2LineJoint * >(addr)->GetUpperLimit();
}

void LineJoint::setLimits (float lower,float upper) {
    static_cast<b2LineJoint * >(addr)->SetLimits(lower, upper);
}

bool LineJoint::isMotorEnabled () {
    return static_cast<b2LineJoint * >(addr)->IsMotorEnabled();
}

void LineJoint::enableMotor (bool flag) {
    static_cast<b2LineJoint * >(addr)->EnableMotor(flag);
}

void LineJoint::setMotorSpeed (float speed) {
    static_cast<b2LineJoint * >(addr)->SetMotorSpeed(speed);
}

float LineJoint::getMotorSpeed () {
    return static_cast<b2LineJoint * >(addr)->GetMotorSpeed();
}

void LineJoint::setMaxMotorForce (float force) {
    static_cast<b2LineJoint * >(addr)->SetMaxMotorForce(force);
}

float LineJoint::getMaxMotorForce () {
    return static_cast<b2LineJoint * >(addr)->GetMaxMotorForce();
}

float LineJoint::getMotorForce () {
    return static_cast<b2LineJoint * >(addr)->GetMotorForce();
}

