
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

#include "LineJointDef.hpp"

using namespace gdx_cpp::physics::box2d::joints;

LineJointDef::LineJointDef():enableLimit(false), lowerTranslation(0),upperTranslation(0),enableMotor(false),maxMotorForce(0), motorSpeed(0), localAxisA(1.0,0)
{
  type=JointDef::LineJoint;
}

void LineJointDef::initialize (gdx_cpp::physics::box2d::Body::ptr bodyA, gdx_cpp::physics::box2d::Body::ptr bodyB, gdx_cpp::math::Vector2& anchor, gdx_cpp::math::Vector2& axis) {
    this->bodyA = bodyA;
    this->bodyB = bodyB;
    localAnchorA.set(bodyA->getLocalPoint(anchor));
    localAnchorB.set(bodyB->getLocalPoint(anchor));
    localAxisA.set(bodyA->getLocalVector(axis));
}
