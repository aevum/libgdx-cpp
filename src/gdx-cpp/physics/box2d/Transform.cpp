
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

#include "Transform.hpp"
#include <cmath>

using namespace gdx_cpp::physics::box2d;

Transform::Transform ()
{

}

Transform::Transform (gdx_cpp::math::Vector2& position, float angle) {
    setPosition(position);
    setRotation(angle);
}

gdx_cpp::math::Vector2& Transform::mul (gdx_cpp::math::Vector2& v) {
    float x = vals[POS_X] + vals[COL1_X] * v.x + vals[COL2_X] * v.y;
    float y = vals[POS_Y] + vals[COL1_Y] * v.x + vals[COL2_Y] * v.y;

    v.x = x;
    v.y = y;
    return v;
}

gdx_cpp::math::Vector2& Transform::getPosition () {
    return position.set(vals[0], vals[1]);
}

void Transform::setRotation (float angle) {
    float c = (float)std::cos(angle), s = (float)std::sin(angle);
    vals[COL1_X] = c;
    vals[COL2_X] = -s;
    vals[COL1_Y] = s;
    vals[COL2_Y] = c;
}

void Transform::setPosition (const gdx_cpp::math::Vector2& pos) {
    vals[POS_X] = pos.x;
    vals[POS_Y] = pos.y;
}

