
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

#include "Shape.hpp"
#include "Box2D/Box2D.h"

using namespace gdx_cpp::physics::box2d;


//TODO Remove daqui depois
inline int jniGetType(b2Shape* shape)
{
        if( shape->m_type == b2Shape::e_circle )
                return 0;
        else
                return 1;
}


float Shape::getRadius () {
    return addr->m_radius;
}

void Shape::setRadius (float radius) {
    addr->m_radius = radius;
}

void Shape::dispose () {
    delete addr;
}