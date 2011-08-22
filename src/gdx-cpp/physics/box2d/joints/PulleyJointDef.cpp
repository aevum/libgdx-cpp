
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

void PulleyJointDef::initialize (const gdx_cpp::physics::box2d::Body& bodyA,const gdx_cpp::physics::box2d::Body& bodyB,const gdx_cpp::math::Vector2& groundAnchorA,const gdx_cpp::math::Vector2& groundAnchorB,const gdx_cpp::math::Vector2& anchorA,const gdx_cpp::math::Vector2& anchorB,float ratio) {
    this.bodyA = bodyA;
    this.bodyB = bodyB;
    this.groundAnchorA.set(groundAnchorA);
    this.groundAnchorB.set(groundAnchorB);
    this.localAnchorA.set(bodyA.getLocalPoint(anchorA));
    this.localAnchorB.set(bodyB.getLocalPoint(anchorB));
    lengthA = anchorA.dst(groundAnchorA);
    lengthB = anchorB.dst(groundAnchorB);
    this.ratio = ratio;
    float C = lengthA + ratio * lengthB;
    maxLengthA = C - ratio * minPulleyLength;
    maxLengthB = (C - minPulleyLength) / ratio;

}

