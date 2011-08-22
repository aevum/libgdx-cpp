
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

using namespace gdx_cpp::physics::box2d::joints;

float LineJoint::getJointTranslation () {
    return jniGetJointTranslation(addr);
}

float LineJoint::getJointSpeed () {
    return jniGetJointSpeed(addr);
}

bool LineJoint::isLimitEnabled () {
    return jniIsLimitEnabled(addr);
}

void LineJoint::enableLimit (bool flag) {
    jniEnableLimit(addr, flag);
}

float LineJoint::getLowerLimit () {
    return jniGetLowerLimit(addr);
}

float LineJoint::getUpperLimit () {
    return jniGetUpperLimit(addr);
}

void LineJoint::setLimits (float lower,float upper) {
    jniSetLimits(addr, lower, upper);
}

bool LineJoint::isMotorEnabled () {
    return jniIsMotorEnabled(addr);
}

void LineJoint::enableMotor (bool flag) {
    jniEnableMotor(addr, flag);
}

void LineJoint::setMotorSpeed (float speed) {
    jniSetMotorSpeed(addr, speed);
}

float LineJoint::getMotorSpeed () {
    return jniGetMotorSpeed(addr);
}

void LineJoint::setMaxMotorForce (float force) {
    jniSetMaxMotorForce(addr, force);
}

float LineJoint::getMaxMotorForce () {
    return jniGetMaxMotorForce(addr);
}

float LineJoint::getMotorForce () {
    return jniGetMotorForce(addr);
}

