
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

using namespace gdx_cpp::physics::box2d;

void Body::reset (long addr) {
    this.addr = addr;
    this.userData = null;
    for (int i = 0; i < fixtures.size(); i++)
        this.world.freeFixtures.free(fixtures.get(i));
    fixtures.clear();
    this.joints.clear();
}

Fixture& Body::createFixture (const FixtureDef& def) {
    long fixtureAddr = jniCreateFixture(addr, def.shape.addr, def.friction, def.restitution, def.density, def.isSensor,
                                        def.filter.categoryBits, def.filter.maskBits, def.filter.groupIndex);
    Fixture fixture = this.world.freeFixtures.obtain();
    fixture.reset(this, fixtureAddr);
    this.world.fixtures.put(fixture.addr, fixture);
    this.fixtures.add(fixture);
    return fixture;
}

Fixture& Body::createFixture (const Shape& shape,float density) {
    long fixtureAddr = jniCreateFixture(addr, shape.addr, density);
    Fixture fixture = this.world.freeFixtures.obtain();
    fixture.reset(this, fixtureAddr);
    this.world.fixtures.put(fixture.addr, fixture);
    this.fixtures.add(fixture);
    return fixture;
}

void Body::destroyFixture (const Fixture& fixture) {
    jniDestroyFixture(addr, fixture.addr);
    this.world.fixtures.remove(fixture.addr);
    this.fixtures.remove(fixture);
    this.world.freeFixtures.free(fixture);
}

void Body::setTransform (const gdx_cpp::math::Vector2& position,float angle) {
    jniSetTransform(addr, position.x, position.y, angle);
}

void Body::setTransform (float x,float y,float angle) {
    jniSetTransform(addr, x, y, angle);
}

Transform& Body::getTransform () {
    jniGetTransform(addr, transform.vals);
    return transform;
}

gdx_cpp::math::Vector2& Body::getPosition () {
    jniGetPosition(addr, tmp);
    position.x = tmp[0];
    position.y = tmp[1];
    return position;
}

float Body::getAngle () {
    return jniGetAngle(addr);
}

gdx_cpp::math::Vector2& Body::getWorldCenter () {
    jniGetWorldCenter(addr, tmp);
    worldCenter.x = tmp[0];
    worldCenter.y = tmp[1];
    return worldCenter;
}

gdx_cpp::math::Vector2& Body::getLocalCenter () {
    jniGetLocalCenter(addr, tmp);
    localCenter.x = tmp[0];
    localCenter.y = tmp[1];
    return localCenter;
}

void Body::setLinearVelocity (const gdx_cpp::math::Vector2& v) {
    jniSetLinearVelocity(addr, v.x, v.y);
}

void Body::setLinearVelocity (float vX,float vY) {
    jniSetLinearVelocity(addr, vX, vY);
}

gdx_cpp::math::Vector2& Body::getLinearVelocity () {
    jniGetLinearVelocity(addr, tmp);
    linearVelocity.x = tmp[0];
    linearVelocity.y = tmp[1];
    return linearVelocity;
}

void Body::setAngularVelocity (float omega) {
    jniSetAngularVelocity(addr, omega);
}

float Body::getAngularVelocity () {
    return jniGetAngularVelocity(addr);
}

void Body::applyForce (const gdx_cpp::math::Vector2& force,const gdx_cpp::math::Vector2& point) {
    jniApplyForce(addr, force.x, force.y, point.x, point.y);
}

void Body::applyForce (float forceX,float forceY,float pointX,float pointY) {
    jniApplyForce(addr, forceX, forceY, pointX, pointY);
}

void Body::applyTorque (float torque) {
    jniApplyTorque(addr, torque);
}

void Body::applyLinearImpulse (const gdx_cpp::math::Vector2& impulse,const gdx_cpp::math::Vector2& point) {
    jniApplyLinearImpulse(addr, impulse.x, impulse.y, point.x, point.y);
}

void Body::applyLinearImpulse (float impulseX,float impulseY,float pointX,float pointY) {
    jniApplyLinearImpulse(addr, impulseX, impulseY, pointX, pointY);
}

void Body::applyAngularImpulse (float impulse) {
    jniApplyAngularImpulse(addr, impulse);
}

float Body::getMass () {
    return jniGetMass(addr);
}

float Body::getInertia () {
    return jniGetInertia(addr);
}

MassData& Body::getMassData () {
    jniGetMassData(addr, tmp);
    massData.mass = tmp[0];
    massData.center.x = tmp[1];
    massData.center.y = tmp[2];
    massData.I = tmp[3];
    return massData;
}

void Body::setMassData (const MassData& data) {
    jniSetMassData(addr, data.mass, data.center.x, data.center.y, data.I);
}

void Body::resetMassData () {
    jniResetMassData(addr);
}

gdx_cpp::math::Vector2& Body::getWorldPoint (const gdx_cpp::math::Vector2& localPoint) {
    jniGetWorldPoint(addr, localPoint.x, localPoint.y, tmp);
    this.localPoint.x = tmp[0];
    this.localPoint.y = tmp[1];
    return this.localPoint;
}

gdx_cpp::math::Vector2& Body::getWorldVector (const gdx_cpp::math::Vector2& localVector) {
    jniGetWorldVector(addr, localVector.x, localVector.y, tmp);
    worldVector.x = tmp[0];
    worldVector.y = tmp[1];
    return worldVector;
}

gdx_cpp::math::Vector2& Body::getLocalPoint (const gdx_cpp::math::Vector2& worldPoint) {
    jniGetLocalPoint(addr, worldPoint.x, worldPoint.y, tmp);
    localPoint2.x = tmp[0];
    localPoint2.y = tmp[1];
    return localPoint2;
}

gdx_cpp::math::Vector2& Body::getLocalVector (const gdx_cpp::math::Vector2& worldVector) {
    jniGetLocalVector(addr, worldVector.x, worldVector.y, tmp);
    localVector.x = tmp[0];
    localVector.y = tmp[1];
    return localVector;
}

gdx_cpp::math::Vector2& Body::getLinearVelocityFromWorldPoint (const gdx_cpp::math::Vector2& worldPoint) {
    jniGetLinearVelocityFromWorldPoint(addr, worldPoint.x, worldPoint.y, tmp);
    linVelWorld.x = tmp[0];
    linVelWorld.y = tmp[1];
    return linVelWorld;
}

gdx_cpp::math::Vector2& Body::getLinearVelocityFromLocalPoint (const gdx_cpp::math::Vector2& localPoint) {
    jniGetLinearVelocityFromLocalPoint(addr, localPoint.x, localPoint.y, tmp);
    linVelLoc.x = tmp[0];
    linVelLoc.y = tmp[1];
    return linVelLoc;
}

float Body::getLinearDamping () {
    return jniGetLinearDamping(addr);
}

void Body::setLinearDamping (float linearDamping) {
    jniSetLinearDamping(addr, linearDamping);
}

float Body::getAngularDamping () {
    return jniGetAngularDamping(addr);
}

void Body::setAngularDamping (float angularDamping) {
    jniSetAngularDamping(addr, angularDamping);
}

void Body::setType (const gdx_cpp::physics::box2d::BodyDef::BodyType& type) {
    jniSetType(addr, type.getValue());
}

gdx_cpp::physics::box2d::BodyDef::BodyType& Body::getType () {
    int type = jniGetType(addr);
    if (type == 0) return BodyType.StaticBody;
    if (type == 1) return BodyType.KinematicBody;
    if (type == 2) return BodyType.DynamicBody;
    return BodyType.StaticBody;
}

void Body::setBullet (bool flag) {
    jniSetBullet(addr, flag);
}

bool Body::isBullet () {
    return jniIsBullet(addr);
}

void Body::setSleepingAllowed (bool flag) {
    jniSetSleepingAllowed(addr, flag);
}

bool Body::isSleepingAllowed () {
    return jniIsSleepingAllowed(addr);
}

void Body::setAwake (bool flag) {
    jniSetAwake(addr, flag);
}

bool Body::isAwake () {
    return jniIsAwake(addr);
}

void Body::setActive (bool flag) {
    jniSetActive(addr, flag);
}

bool Body::isActive () {
    return jniIsActive(addr);
}

void Body::setFixedRotation (bool flag) {
    jniSetFixedRotation(addr, flag);
}

bool Body::isFixedRotation () {
    return jniIsFixedRotation(addr);
}

ArrayList<Fixture>& Body::getFixtureList () {
    return fixtures;
}

ArrayList<JointEdge>& Body::getJointList () {
    return joints;
}

World& Body::getWorld () {
    return world;
}

Object& Body::getUserData () {
    return userData;
}

void Body::setUserData (const Object& userData) {
    this.userData = userData;
}

