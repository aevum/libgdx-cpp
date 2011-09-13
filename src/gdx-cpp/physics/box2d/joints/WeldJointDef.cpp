
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

#include "WeldJointDef.hpp"

using namespace gdx_cpp::physics::box2d::joints;

void WeldJointDef::initialize (gdx_cpp::physics::box2d::Body::ptr body1,gdx_cpp::physics::box2d::Body::ptr body2, gdx_cpp::math::Vector2& anchor) {
    this->bodyA = body1;
    this->bodyB = body2;
    this->localAnchorA.set(body1->getLocalPoint(anchor));
    this->localAnchorB.set(body2->getLocalPoint(anchor));
    referenceAngle = body2->getAngle() - body1->getAngle();
}

