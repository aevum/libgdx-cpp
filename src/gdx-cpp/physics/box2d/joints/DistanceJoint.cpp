
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
#include "Box2D.h"
#include "gdx-cpp/utils/Aliases.hpp"

using namespace gdx_cpp::physics::box2d::joints;

DistanceJoint::DistanceJoint(ref_ptr_maker< gdx_cpp::physics::box2d::World >::type _world, b2DistanceJoint* joint) : Joint(_world, joint)
{
  
}

void DistanceJoint::setLength (float length) {
    static_cast<b2DistanceJoint * >(addr)->SetLength(length);
}

float DistanceJoint::getLength () {
    return static_cast<b2DistanceJoint * >(addr)->GetLength();
}

void DistanceJoint::setFrequency (float hz) {
    static_cast<b2DistanceJoint * >(addr)->SetFrequency(hz);
}

float DistanceJoint::getFrequency () {
    return static_cast<b2DistanceJoint * >(addr)->GetFrequency();
}

void DistanceJoint::setDampingRatio (float ratio) {
    static_cast<b2DistanceJoint * >(addr)->SetDampingRatio(ratio);
}

float DistanceJoint::getDampingRatio () {
    return static_cast<b2DistanceJoint * >(addr)->GetDampingRatio();
}

