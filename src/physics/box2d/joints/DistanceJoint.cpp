
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

#include "DistanceJoint.hpp"

using namespace gdx_cpp::physics::box2d::joints;

void DistanceJoint::setLength (float length) {
    jniSetLength(addr, length);
}

float DistanceJoint::getLength () {
    return jniGetLength(addr);
}

void DistanceJoint::setFrequency (float hz) {
    jniSetFrequency(addr, hz);
}

float DistanceJoint::getFrequency () {
    return jniGetFrequency(addr);
}

void DistanceJoint::setDampingRatio (float ratio) {
    jniSetDampingRatio(addr, ratio);
}

float DistanceJoint::getDampingRatio () {
    return jniGetDampingRatio(addr);
}

