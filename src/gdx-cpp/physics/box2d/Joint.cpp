
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

#include "Joint.hpp"
#include "Box2D.h"
#include "World.hpp"
#include "Body.hpp"

using namespace gdx_cpp::physics::box2d;

Joint::Joint(ref_ptr_maker< gdx_cpp::physics::box2d::World >::type _world, b2Joint* joint): world(_world), addr(joint)
{
  
}

JointDef::JointType Joint::getType () {
    int type = addr->GetType();
    if (type > 0 && type < JointDef::joint_type_size)
        return (JointDef::JointType)type;
    else
        return JointDef::Unknown;
}

gdx_cpp::physics::box2d::Body* Joint::getBodyA () {
    return world->bodies[addr->GetBodyA()];
}

gdx_cpp::physics::box2d::Body* Joint::getBodyB () {
    return world->bodies[addr->GetBodyB()];
}

gdx_cpp::math::Vector2& Joint::getAnchorA () {
    b2Vec2 a = addr->GetAnchorA();
    anchorA.x = a.x;
    anchorA.y = a.y;
    return anchorA;
}

gdx_cpp::math::Vector2& Joint::getAnchorB () {
    b2Vec2 b = addr->GetAnchorB();
    anchorB.x = b.x;
    anchorB.y = b.y;
    return anchorB;
}

gdx_cpp::math::Vector2& Joint::getReactionForce (float inv_dt) {
    b2Vec2 f = addr->GetReactionForce(inv_dt);
    reactionForce.x = f.x;
    reactionForce.y = f.x;
    return reactionForce;
}

float Joint::getReactionTorque (float inv_dt) {
    return addr->GetReactionTorque(inv_dt);
}

bool Joint::isActive () {
    return addr->IsActive();
}

