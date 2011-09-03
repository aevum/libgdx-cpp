
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

#include "PulleyJoint.hpp"
#include "Box2D.h"

using namespace gdx_cpp::physics::box2d::joints;

PulleyJoint::PulleyJoint(ref_ptr_maker< gdx_cpp::physics::box2d::World >::type _world, b2PulleyJoint* joint) : Joint(_world, joint)
{

}

gdx_cpp::math::Vector2& PulleyJoint::getGroundAnchorA () {
    groundAnchorA.set(static_cast<b2PulleyJoint * >(addr)->GetAnchorA().x, static_cast<b2PulleyJoint * >(addr)->GetAnchorA().y);
    return groundAnchorA;
}

gdx_cpp::math::Vector2& PulleyJoint::getGroundAnchorB () {
    groundAnchorB.set(static_cast<b2PulleyJoint * >(addr)->GetAnchorB().x, static_cast<b2PulleyJoint * >(addr)->GetAnchorB().y);
    return groundAnchorB;
}

float PulleyJoint::getLength1 () {
    return static_cast<b2PulleyJoint * >(addr)->GetLength1();
}

float PulleyJoint::getLength2 () {
    return static_cast<b2PulleyJoint * >(addr)->GetLength2();
}

float PulleyJoint::getRatio () {
    return static_cast<b2PulleyJoint * >(addr)->GetRatio();
}

