
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
#include "Box2D.h"
#include "Shape.hpp"
#include "PolygonShape.hpp"
#include "CircleShape.hpp"

using namespace gdx_cpp::physics::box2d;

void Fixture::reset (Body::ptr body, b2Fixture * addr) {
    this->body = body;
    this->addr = addr;
    this->shape = Shape::ptr();
    this->userData = NULL;
}

Shape::Type Fixture::getType () {
    b2Shape::Type type = addr->GetType();
    if ( type == b2Shape::e_circle )
    {
        return Shape::Circle;
    }

    return Shape::Polygon;

}

Shape::ptr Fixture::getShape () {
    if (shape == NULL) {
        b2Shape * shapeAddr = addr->GetShape();
        int type = shapeAddr->GetType();

        if (type == 0)
            shape = Shape::ptr(new CircleShape(static_cast<b2CircleShape*>(shapeAddr)));
        else
            shape = Shape::ptr(new PolygonShape(static_cast<b2PolygonShape*>(shapeAddr)));
    }

    return shape;
}

void Fixture::setSensor (bool sensor) {
    addr->SetSensor(sensor);
}

bool Fixture::isSensor () {
    return addr->IsSensor();;
}

void Fixture::setFilterData (const Filter& _filter) {
    b2Filter filter;
    filter.categoryBits = _filter.categoryBits;
    filter.maskBits = _filter.maskBits;
    filter.groupIndex = _filter.groupIndex;
    addr->SetFilterData(filter);
}

Filter& Fixture::getFilterData () {
    b2Filter f = addr->GetFilterData();
    filter.maskBits = f.maskBits;
    filter.categoryBits = f.categoryBits;
    filter.groupIndex = f.groupIndex;
    return filter;
}

Body::ptr Fixture::getBody () {
    return body;
}

bool Fixture::testPoint (const gdx_cpp::math::Vector2& p) {
    addr->TestPoint( b2Vec2( p.x, p.y ) );
}

bool Fixture::testPoint (float x,float y) {
    addr->TestPoint( b2Vec2( x, y ) );
}

void Fixture::setDensity (float density) {
    addr->SetDensity(density);
}

float Fixture::getDensity () {
    return addr->GetDensity();
}

float Fixture::getFriction () {
    return addr->GetFriction();
}

void Fixture::setFriction (float friction) {
    addr->SetFriction(friction);
}

float Fixture::getRestitution () {
    return addr->GetRestitution();
}

void Fixture::setRestitution (float restitution) {
    addr->SetRestitution(restitution);
}

void Fixture::setUserData (void* userData) {
    this->userData = userData;
}

void* Fixture::getUserData () {
    return userData;
}

