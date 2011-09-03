
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


#include "Box2D.h"
#include "CircleShape.hpp"

using namespace gdx_cpp::physics::box2d;


        CircleShape::CircleShape () {
                addr = new b2CircleShape( );
        }


        CircleShape::CircleShape (b2CircleShape * _addr) {
                this->addr = _addr;
        }


Shape::Type CircleShape::getType () {
    return Shape::Circle;
}

gdx_cpp::math::Vector2& CircleShape::getPosition () {
    position.x = static_cast<b2CircleShape*>(addr)->m_p.x;
    position.y = static_cast<b2CircleShape*>(addr)->m_p.y;
    return position;
}

void CircleShape::setPosition (const gdx_cpp::math::Vector2& position) {
    static_cast<b2CircleShape*>(addr)->m_p.x = position.x;
    static_cast<b2CircleShape*>(addr)->m_p.y = position.y;
}

