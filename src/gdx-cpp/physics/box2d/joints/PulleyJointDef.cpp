
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

#include "PulleyJointDef.hpp"

using namespace gdx_cpp::physics::box2d::joints;

PulleyJointDef::PulleyJointDef(): groundAnchorA(-1, 1), groundAnchorB(1,1), localAnchorA(-1,0), localAnchorB(1,0),
                                  lengthA(0), maxLengthA(0), lengthB(0), maxLengthB(0), ratio(1)
{
  type=JointDef::PulleyJoint;
}
void PulleyJointDef::initialize (gdx_cpp::physics::box2d::Body::ptr bodyA,gdx_cpp::physics::box2d::Body::ptr bodyB,const gdx_cpp::math::Vector2& groundAnchorA, gdx_cpp::math::Vector2& groundAnchorB, gdx_cpp::math::Vector2& anchorA, gdx_cpp::math::Vector2& anchorB,float ratio) {
    this->bodyA = bodyA;
    this->bodyB = bodyB;
    this->groundAnchorA.set(groundAnchorA);
    this->groundAnchorB.set(groundAnchorB);
    this->localAnchorA.set(bodyA->getLocalPoint(anchorA));
    this->localAnchorB.set(bodyB->getLocalPoint(anchorB));
    lengthA = anchorA.dst(groundAnchorA);
    lengthB = anchorB.dst(groundAnchorB);
    this->ratio = ratio;
    float C = lengthA + ratio * lengthB;
    maxLengthA = C - ratio * minPulleyLength;
    maxLengthB = (C - minPulleyLength) / ratio;

}