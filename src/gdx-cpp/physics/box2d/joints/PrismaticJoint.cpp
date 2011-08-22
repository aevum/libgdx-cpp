
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

using namespace gdx_cpp::physics::box2d::joints;

float PrismaticJoint::getJointTranslation () {
    return jniGetJointTranslation(addr);
}

float PrismaticJoint::getJointSpeed () {
    return jniGetJointSpeed(addr);
}

bool PrismaticJoint::isLimitEnabled () {
    return jniIsLimitEnabled(addr);
}

void PrismaticJoint::enableLimit (bool flag) {
    jniEnableLimit(addr, flag);
}

float PrismaticJoint::getLowerLimit () {
    return jniGetLowerLimit(addr);
}

float PrismaticJoint::getUpperLimit () {
    return jniGetUpperLimit(addr);
}

void PrismaticJoint::setLimits (float lower,float upper) {
    jniSetLimits(addr, lower, upper);
}

bool PrismaticJoint::isMotorEnabled () {
    return jniIsMotorEnabled(addr);
}

void PrismaticJoint::enableMotor (bool flag) {
    jniEnableMotor(addr, flag);
}

void PrismaticJoint::setMotorSpeed (float speed) {
    jniSetMotorSpeed(addr, speed);
}

float PrismaticJoint::getMotorSpeed () {
    return jniGetMotorSpeed(addr);
}

void PrismaticJoint::setMaxMotorForce (float force) {
    jniSetMaxMotorForce(addr, force);
}

float PrismaticJoint::getMotorForce () {
    return jniGetMotorForce(addr);
}

