
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

#include "Fixture.hpp"

using namespace gdx_cpp::physics::box2d;

void Fixture::reset (const Body& body,long addr) {
    this.body = body;
    this.addr = addr;
    this.shape = null;
    this.userData = null;
}

gdx_cpp::physics::box2d::Shape::Type& Fixture::getType () {
    int type = jniGetType(addr);
    if (type == 0)
        return Type.Circle;
    else
        return Type.Polygon;
}

Shape& Fixture::getShape () {
    if (shape == null) {
        long shapeAddr = jniGetShape(addr);
        int type = Shape.jniGetType(shapeAddr);

        if (type == 0)
            shape = new CircleShape(shapeAddr);
        else
            shape = new PolygonShape(shapeAddr);
    }

    return shape;
}

void Fixture::setSensor (bool sensor) {
    jniSetSensor(addr, sensor);
}

bool Fixture::isSensor () {
    return jniIsSensor(addr);
}

void Fixture::setFilterData (const Filter& filter) {
    jniSetFilterData(addr, filter.categoryBits, filter.maskBits, filter.groupIndex);
}

Filter& Fixture::getFilterData () {
    jniGetFilterData(addr, tmp);
    filter.maskBits = tmp[0];
    filter.categoryBits = tmp[1];
    filter.groupIndex = tmp[2];
    return filter;
}

Body& Fixture::getBody () {
    return body;
}

bool Fixture::testPoint (const gdx_cpp::math::Vector2& p) {
    return jniTestPoint(addr, p.x, p.y);
}

bool Fixture::testPoint (float x,float y) {
    return jniTestPoint(addr, x, y);
}

void Fixture::setDensity (float density) {
    jniSetDensity(addr, density);
}

float Fixture::getDensity () {
    return jniGetDensity(addr);
}

float Fixture::getFriction () {
    return jniGetFriction(addr);
}

void Fixture::setFriction (float friction) {
    jniSetFriction(addr, friction);
}

float Fixture::getRestitution () {
    return jniGetRestitution(addr);
}

void Fixture::setRestitution (float restitution) {
    jniSetRestitution(addr, restitution);
}

void Fixture::setUserData (const Object& userData) {
    this.userData = userData;
}

Object& Fixture::getUserData () {
    return userData;
}

