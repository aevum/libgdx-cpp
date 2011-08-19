
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

using namespace gdx_cpp::physics::box2d;

gdx_cpp::physics::box2d::JointDef::JointType& Joint::getType () {
    int type = jniGetType(addr);
    if (type > 0 && type < JointType.valueTypes.length)
        return JointType.valueTypes[type];
    else
        return JointType.Unknown;
}

Body& Joint::getBodyA () {
    return world.bodies.get(jniGetBodyA(addr));
}

Body& Joint::getBodyB () {
    return world.bodies.get(jniGetBodyB(addr));
}

gdx_cpp::math::Vector2& Joint::getAnchorA () {
    jniGetAnchorA(addr, tmp);
    anchorA.x = tmp[0];
    anchorA.y = tmp[1];
    return anchorA;
}

gdx_cpp::math::Vector2& Joint::getAnchorB () {
    jniGetAnchorB(addr, tmp);
    anchorB.x = tmp[0];
    anchorB.y = tmp[1];
    return anchorB;
}

gdx_cpp::math::Vector2& Joint::getReactionForce (float inv_dt) {
    jniGetReactionForce(addr, inv_dt, tmp);
    reactionForce.x = tmp[0];
    reactionForce.y = tmp[1];
    return reactionForce;
}

float Joint::getReactionTorque (float inv_dt) {
    return jniGetReactionTorque(addr, inv_dt);
}

bool Joint::isActive () {
    return jniIsActive(addr);
}

