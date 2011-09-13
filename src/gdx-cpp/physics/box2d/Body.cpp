
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

#include "Body.hpp"
#include "FixtureDef.hpp"
#include "Box2D.h"
#include "Fixture.hpp"
#include "World.hpp"

using namespace gdx_cpp::physics::box2d;

void Body::reset (b2Body* addr) {
    this->body = addr;
    this->userData = NULL;
    std::set<Fixture *>::iterator it = fixtures.begin();
    for (; it != fixtures.end(); ++it)
         this->world->freeFixtures.free(*it);
    fixtures.clear();
    this->joints.clear();
}

Fixture& Body::createFixture (const FixtureDef& def) {
    b2Shape* shape = def.shape->addr;
    b2FixtureDef fixtureDef;

#ifdef ANDROID
    //__android_log_print( ANDROID_LOG_INFO, "Box2DTest", "body: %d, shape: %d", body, shape );
#endif

    fixtureDef.shape = shape;
    fixtureDef.friction = def.friction;
    fixtureDef.restitution = def.restitution;
    fixtureDef.density = def.density;
    fixtureDef.isSensor = def.isSensor;
    fixtureDef.filter.maskBits = def.filter.maskBits;
    fixtureDef.filter.categoryBits = def.filter.categoryBits;
    fixtureDef.filter.groupIndex = def.filter.groupIndex;
    b2Fixture* fixtureAddr =    body->CreateFixture( &fixtureDef );

    Fixture* fixture = &this->world->freeFixtures.obtain();
    fixture->reset(shared_from_this(), fixtureAddr);
    this->world->fixtures[fixture->addr] = fixture;
    this->fixtures.insert(fixture);
    return *fixture;
}

Fixture& Body::createFixture (const Shape& _shape,float density) {
    b2Fixture* fixtureAddr =  body->CreateFixture( _shape.addr, density );
    Fixture* fixture = &this->world->freeFixtures.obtain();
    fixture->reset(shared_from_this(), fixtureAddr);
    this->world->fixtures[fixture->addr] = fixture;
    this->fixtures.insert(fixture);
    return *fixture;
}

void Body::destroyFixture (Fixture& fixture) {
    body->DestroyFixture(fixture.addr);
    this->world->fixtures.erase(fixture.addr);
    this->fixtures.erase(&fixture);
    this->world->freeFixtures.free(&fixture);
}

void Body::setTransform (const gdx_cpp::math::Vector2& position,float angle) {
    body->SetTransform(b2Vec2(position.x, position.y), angle);
}

void Body::setTransform (float x,float y,float angle) {
    body->SetTransform(b2Vec2(x, y), angle);
}

Transform& Body::getTransform () {
    float* valOut = transform.vals;
    b2Transform t = body->GetTransform();

    valOut[0] = t.position.x;
    valOut[1] = t.position.y;
    valOut[2] = t.R.col1.x;
    valOut[3] = t.R.col1.y;
    valOut[4] = t.R.col2.x;
    valOut[5] = t.R.col2.y;
    return transform;
}

gdx_cpp::math::Vector2& Body::getPosition () {
    b2Vec2 p = body->GetPosition();
    position.x = p.x;
    position.y = p.y;
    return position;
}

float Body::getAngle () {
    return body->GetAngle();
}

gdx_cpp::math::Vector2& Body::getWorldCenter () {
    b2Vec2 w = body->GetWorldCenter();
    worldCenter.x = w.x;
    worldCenter.y = w.y;
    return worldCenter;
}

gdx_cpp::math::Vector2& Body::getLocalCenter () {
    b2Vec2 w = body->GetLocalCenter();
    localCenter.x = w.x;
    localCenter.y = w.y;
    return localCenter;
}

void Body::setLinearVelocity (const gdx_cpp::math::Vector2& v) {
    body->SetLinearVelocity(b2Vec2(v.x, v.y) );
}

void Body::setLinearVelocity (float vX,float vY) {
    body->SetLinearVelocity(b2Vec2(vX, vY) );
}

gdx_cpp::math::Vector2& Body::getLinearVelocity () {
    b2Vec2 l = body->GetLinearVelocity();
    linearVelocity.x = l.x;
    linearVelocity.y = l.y;
    return linearVelocity;
}

void Body::setAngularVelocity (float omega) {
    body->SetAngularVelocity(omega);
}

float Body::getAngularVelocity () {
    return body->GetAngularVelocity();
}

void Body::applyForce (const gdx_cpp::math::Vector2& force,const gdx_cpp::math::Vector2& point) {
    body->ApplyForce( b2Vec2( force.x, force.y), b2Vec2(point.x, point.y) );
}

void Body::applyForce (float forceX,float forceY,float pointX,float pointY) {
    body->ApplyForce( b2Vec2( forceX, forceY), b2Vec2(pointX, pointY) );
}

void Body::applyTorque (float torque) {
    body->ApplyTorque(torque);
}

void Body::applyLinearImpulse (const gdx_cpp::math::Vector2& impulse,const gdx_cpp::math::Vector2& point) {
    body->ApplyLinearImpulse( b2Vec2( impulse.x, impulse.y), b2Vec2( point.x, point.y) );
}

void Body::applyLinearImpulse (float impulseX,float impulseY,float pointX,float pointY) {
    body->ApplyLinearImpulse( b2Vec2( impulseX, impulseY), b2Vec2( pointX, pointY) );
}

void Body::applyAngularImpulse (float impulse) {
    body->ApplyAngularImpulse(impulse);
}

float Body::getMass () {
    return body->GetMass();
}

float Body::getInertia () {
    return body->GetInertia();
}

MassData& Body::getMassData () {
    b2MassData m;
    body->GetMassData(&m);
    massData.mass = m.mass;
    massData.center.x = m.center.x;
    massData.center.y = m.center.y;
    massData.I = m.I;
    return massData;
}

void Body::setMassData (const MassData& data) {
    b2MassData m;
    m.mass = data.mass;
    m.center.x = data.center.x;
    m.center.y = data.center.y;
    m.I = data.I;
    body->SetMassData(&m);
}

void Body::resetMassData () {
    body->ResetMassData();
}

gdx_cpp::math::Vector2& Body::getWorldPoint (const gdx_cpp::math::Vector2& localPoint) {
    b2Vec2 w = body->GetWorldPoint( b2Vec2(localPoint.x, localPoint.y) );
    this->localPoint.x = w.x;
    this->localPoint.y = w.y;
    return this->localPoint;
}

gdx_cpp::math::Vector2& Body::getWorldVector (const gdx_cpp::math::Vector2& localVector) {
    b2Vec2 w = body->GetWorldVector( b2Vec2( localVector.x, localVector.y ) );
    worldVector.x = w.x;
    worldVector.y = w.x;
    return worldVector;
}

gdx_cpp::math::Vector2& Body::getLocalPoint (const gdx_cpp::math::Vector2& worldPoint) {
    b2Vec2 w = body->GetLocalPoint( b2Vec2(worldPoint.x, worldPoint.y) );
    this->localPoint2.x = w.x;
    this->localPoint2.y = w.y;
    return localPoint2;
}

gdx_cpp::math::Vector2& Body::getLocalVector (const gdx_cpp::math::Vector2& worldVector) {
    b2Vec2 w = body->GetLocalVector( b2Vec2(worldVector.x, worldVector.y) );
    this->localVector.x = w.x;
    this->localVector.y = w.y;
    return localVector;
}

gdx_cpp::math::Vector2& Body::getLinearVelocityFromWorldPoint (const gdx_cpp::math::Vector2& worldPoint) {
    b2Vec2 w = body->GetLinearVelocityFromWorldPoint( b2Vec2( worldPoint.x, worldPoint.y ) );
    linVelWorld.x = w.x;
    linVelWorld.y = w.y;
    return linVelWorld;
}

gdx_cpp::math::Vector2& Body::getLinearVelocityFromLocalPoint (const gdx_cpp::math::Vector2& localPoint) {
    b2Vec2 w = body->GetLinearVelocityFromLocalPoint( b2Vec2( localPoint.x, localPoint.y ) );
    linVelLoc.x = w.x;
    linVelLoc.y = w.y;
    return linVelLoc;
}

float Body::getLinearDamping () {
    return body->GetLinearDamping();
}

void Body::setLinearDamping (float linearDamping) {
    body->SetLinearDamping(linearDamping);
}

float Body::getAngularDamping () {
    return body->GetAngularDamping();
}

void Body::setAngularDamping (float angularDamping) {
    body->SetAngularDamping(angularDamping);
}

void Body::setType (const gdx_cpp::physics::box2d::BodyDef::BodyType _type) {
    b2BodyType type;
      switch( _type )
    {
    case 0: type = b2_staticBody;
    case 1: type = b2_kinematicBody;
    case 2: type = b2_dynamicBody;
    default:
            type = b2_staticBody;
    }
    body->SetType(type);
}

gdx_cpp::physics::box2d::BodyDef::BodyType Body::getType () {
    int type = body->GetType();
    if (type == 0) return BodyDef::StaticBody;
    if (type == 1) return BodyDef::KinematicBody;
    if (type == 2) return BodyDef::DynamicBody;
    return BodyDef::StaticBody;
}

void Body::setBullet (bool flag) {
    body->SetBullet(flag);
}

bool Body::isBullet () {
    return body->IsBullet();
}

void Body::setSleepingAllowed (bool flag) {
    body->SetSleepingAllowed(flag);
}

bool Body::isSleepingAllowed () {
    return body->IsSleepingAllowed();
}

void Body::setAwake (bool flag) {
    body->SetAwake(flag);
}

bool Body::isAwake () {
    return body->IsAwake();
}

void Body::setActive (bool flag) {
    body->SetActive(flag);
}

bool Body::isActive () {
    return body->IsActive();
}

void Body::setFixedRotation (bool flag) {
    body->SetFixedRotation(flag);
}

bool Body::isFixedRotation () {
    return body->IsFixedRotation();
}

std::set< Fixture* >& Body::getFixtureList () {
    return fixtures;
}

std::set<JointEdge *>& Body::getJointList () {
    return joints;
}

World& Body::getWorld () {
    return *world;
}

void* Body::getUserData () {
    return userData;
}

void Body::setUserData (void * userData) {
    this->userData = userData;
}

