
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
#include "Box2D.h"

using namespace gdx_cpp::physics::box2d::joints;

MouseJoint::MouseJoint(ref_ptr_maker< gdx_cpp::physics::box2d::World >::type _world, b2MouseJoint* joint) : Joint(_world, joint)
{

}

void MouseJoint::setTarget (const gdx_cpp::math::Vector2& target) {
    static_cast<b2MouseJoint * >(addr)->SetTarget( b2Vec2(target.x, target.y));
}

gdx_cpp::math::Vector2& MouseJoint::getTarget () {
    target.x = static_cast<b2MouseJoint * >(addr)->GetTarget().x;
    target.y = static_cast<b2MouseJoint * >(addr)->GetTarget().y;
    return target;
}

void MouseJoint::setMaxForce (float force) {
    static_cast<b2MouseJoint * >(addr)->SetMaxForce(force);
}

float MouseJoint::getMaxForce () {
    return static_cast<b2MouseJoint * >(addr)->GetMaxForce();
}

void MouseJoint::setFrequency (float hz) {
    static_cast<b2MouseJoint * >(addr)->SetFrequency(hz);
}

float MouseJoint::getFrequency () {
    return static_cast<b2MouseJoint * >(addr)->GetFrequency();
}

void MouseJoint::setDampingRatio (float ratio) {
    static_cast<b2MouseJoint * >(addr)->SetDampingRatio(ratio);
}

float MouseJoint::getDampingRatio () {
    return static_cast<b2MouseJoint * >(addr)->GetDampingRatio();
}

