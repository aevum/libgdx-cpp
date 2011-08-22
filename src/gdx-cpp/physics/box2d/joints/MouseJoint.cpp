
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

#include "MouseJoint.hpp"

using namespace gdx_cpp::physics::box2d::joints;

void MouseJoint::setTarget (const gdx_cpp::math::Vector2& target) {
    jniSetTarget(addr, target.x, target.y);
}

gdx_cpp::math::Vector2& MouseJoint::getTarget () {
    jniGetTarget(addr, tmp);
    target.x = tmp[0];
    target.y = tmp[1];
    return target;
}

void MouseJoint::setMaxForce (float force) {
    jniSetMaxForce(addr, force);
}

float MouseJoint::getMaxForce () {
    return jniGetMaxForce(addr);
}

void MouseJoint::setFrequency (float hz) {
    jniSetFrequency(addr, hz);
}

float MouseJoint::getFrequency () {
    return jniGetFrequency(addr);
}

void MouseJoint::setDampingRatio (float ratio) {
    jniSetDampingRatio(addr, ratio);
}

float MouseJoint::getDampingRatio () {
    return jniGetDampingRatio(addr);
}

