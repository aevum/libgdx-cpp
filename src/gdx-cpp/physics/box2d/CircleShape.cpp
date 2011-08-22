
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

#include "CircleShape.hpp"

using namespace gdx_cpp::physics::box2d;

Type& CircleShape::getType () {
    return Type.Circle;
}

gdx_cpp::math::Vector2& CircleShape::getPosition () {
    jniGetPosition(addr, tmp);
    position.x = tmp[0];
    position.y = tmp[1];
    return position;
}

void CircleShape::setPosition (const gdx_cpp::math::Vector2& position) {
    jniSetPosition(addr, position.x, position.y);
}

