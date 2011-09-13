
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
#include "RayCastCallback.hpp"

#include "World.hpp"
#include "RayCastCallback.hpp"
#include "Box2D.h"
#include "JointEdge.hpp"
#include "Joint.hpp"
#include "gdx-cpp/physics/box2d/joints/DistanceJoint.hpp"
#include "gdx-cpp/physics/box2d/joints/FrictionJoint.hpp"
#include "gdx-cpp/physics/box2d/joints/GearJoint.hpp"
#include "gdx-cpp/physics/box2d/joints/LineJoint.hpp"
#include "gdx-cpp/physics/box2d/joints/MouseJoint.hpp"
#include "gdx-cpp/physics/box2d/joints/PrismaticJoint.hpp"
#include "gdx-cpp/physics/box2d/joints/PulleyJoint.hpp"
#include "gdx-cpp/physics/box2d/joints/RevoluteJoint.hpp"
#include "gdx-cpp/physics/box2d/joints/WeldJoint.hpp"
#include "gdx-cpp/physics/box2d/joints/DistanceJointDef.hpp"
#include "gdx-cpp/physics/box2d/joints/FrictionJointDef.hpp"
#include "gdx-cpp/physics/box2d/joints/GearJointDef.hpp"
#include "gdx-cpp/physics/box2d/joints/LineJointDef.hpp"
#include "gdx-cpp/physics/box2d/joints/MouseJointDef.hpp"
#include "gdx-cpp/physics/box2d/joints/PrismaticJointDef.hpp"
#include "gdx-cpp/physics/box2d/joints/PulleyJointDef.hpp"
#include "gdx-cpp/physics/box2d/joints/RevoluteJointDef.hpp"
#include "gdx-cpp/physics/box2d/joints/WeldJointDef.hpp"
#include "Contact.hpp"
#include "Manifold.hpp"
#include "ContactImpulse.hpp"
#include "QueryCallback.hpp"

using namespace gdx_cpp::physics::box2d;
using namespace gdx_cpp::physics::box2d::joints;

//TODO checar todos os destroys(para deletar objetos da memoria)

class CustomRayCastCallback: public b2RayCastCallback
{
private:
    World * world;
public:
    CustomRayCastCallback( World* _world)
    {
        this->world = _world;
    }

    virtual float32 ReportFixture( b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction)
    {
        return this->world->reportRayFixture(fixture, point.x, point.y, normal.x, normal.y, (float)fraction);
    }
};

class CustomContactFilter: public b2ContactFilter
{
private:
    World * world;

public:
    CustomContactFilter( World* _world)
    {
        this->world = _world;
    }

    virtual bool ShouldCollide(b2Fixture* fixtureA, b2Fixture* fixtureB)
    {
        return this->world->contactFilter( fixtureA, fixtureB );
    }
};

class CustomContactListener: public b2ContactListener
{
private:
    World * world;

public:
    CustomContactListener( World* _world)
    {
        this->world = _world;
    }

    /// Called when two fixtures begin to touch.
    virtual void BeginContact(b2Contact* contact)
    {
        this->world->beginContact( contact );
    }

    /// Called when two fixtures cease to touch.
    virtual void EndContact(b2Contact* contact)
    {
        this->world->endContact(contact);
    }

    /// This is called after a contact is updated.
    virtual void PreSolve(b2Contact* contact, b2Manifold* oldManifold)
    {
        this->world->preSolve(contact, oldManifold);
    }

    /// This lets you inspect a contact after the solver is finished.
    virtual void PostSolve(b2Contact* contact, b2ContactImpulse* impulse)
    {
        this->world->postSolve(contact, impulse);
    }
};

class CustomQueryCallback: public b2QueryCallback
{
private:
    World * world;

public:
    CustomQueryCallback( World* _world)
    {
        this->world = _world;
    }

    virtual bool ReportFixture( b2Fixture* fixture )
    {
        return this->world->reportFixture(fixture );
    }
};


void World::rayCast (RayCastCallback * callback, const gdx_cpp::math::Vector2& point1,const gdx_cpp::math::Vector2& point2) {
    rayCastCallback = callback;
    b2World *world = (b2World*)addr;

    CustomRayCastCallback b2callback(this);
    world->RayCast( &b2callback, b2Vec2(point1.x, point1.y), b2Vec2(point2.x, point2.y) );
}

float World::reportRayFixture (b2Fixture* addr,float pX,float pY,float nX,float nY,float fraction) {
    if (rayCastCallback != NULL)
        return rayCastCallback->reportRayFixture(*fixtures[addr], rayPoint.set(pX, pY), rayNormal.set(nX, nY), fraction);
    else
        return 0.0f;
}

void World::setDestructionListener (const DestructionListener& listener) {

}

void World::setContactFilter (gdx_cpp::physics::box2d::ContactFilter::ptr filter) {
    this->contactFilterVar = filter;
}

void World::setContactListener (gdx_cpp::physics::box2d::ContactListener::ptr listener) {
    this->contactListener = listener;
}

inline b2BodyType getBodyType( int type )
{
    switch ( type )
    {
    case 0:
        return b2_staticBody;
    case 1:
        return b2_kinematicBody;
    case 2:
        return b2_dynamicBody;
    default:
        return b2_staticBody;
    }
}

Body& World::createBody (const BodyDef& def) {
    b2BodyDef bodyDef;
    bodyDef.type = getBodyType((int)def.type);
    bodyDef.position.Set( def.position.x, def.position.y );
    bodyDef.angle = def.angle;
    bodyDef.linearVelocity.Set( def.linearVelocity.x, def.linearVelocity.y );
    bodyDef.angularVelocity = def.angularVelocity;
    bodyDef.linearDamping = def.linearDamping;
    bodyDef.angularDamping = def.angularDamping;
    bodyDef.allowSleep = def.allowSleep;
    bodyDef.awake = def.awake;
    bodyDef.fixedRotation = def.fixedRotation;
    bodyDef.bullet = def.bullet;
    bodyDef.active = def.active;
    bodyDef.inertiaScale = def.inertiaScale;

    b2Body* body = this->addr->CreateBody( &bodyDef );
//#ifdef ANDROID
//      __android_log_write(ANDROID_LOG_ERROR,"Tag","HIIII");
//#endif
    Body& _body = freeBodies.obtain();
    _body.reset(body);
    this->bodies[body] = &_body;
    return _body;
}

void World::destroyBody (Body& body) {
    this->bodies.erase(body.body);
    std::set<Fixture *>::iterator it = body.getFixtureList().begin();
    for (; it != body.getFixtureList().end(); ++it)
        this->fixtures.erase((*it)->addr);

    std::set<JointEdge *>::iterator itj = body.getJointList().begin();
    for (; itj != body.getJointList().end(); ++itj)
        this->joints.erase((*itj)->joint->addr);
    addr->DestroyBody(body.body);
    freeBodies.free(&body);
}

Joint& World::createJoint (JointDef& def) {
    b2Joint * jointAddr = createProperJoint(def);
    Joint * joint = NULL;
    if (def.type == JointDef::DistanceJoint) joint = new DistanceJoint(shared_from_this(), (b2DistanceJoint *) jointAddr);
    if (def.type == JointDef::FrictionJoint) joint = new FrictionJoint(shared_from_this(), (b2FrictionJoint *) jointAddr);
    if (def.type == JointDef::GearJoint) joint = new GearJoint(shared_from_this(), (b2GearJoint *) jointAddr);
    if (def.type == JointDef::LineJoint) joint = new LineJoint(shared_from_this(), (b2LineJoint *) jointAddr);
    if (def.type == JointDef::MouseJoint) joint = new MouseJoint(shared_from_this(), (b2MouseJoint *) jointAddr);
    if (def.type == JointDef::PrismaticJoint) joint = new PrismaticJoint(shared_from_this(), (b2PrismaticJoint *) jointAddr);
    if (def.type == JointDef::PulleyJoint) joint = new PulleyJoint(shared_from_this(), (b2PulleyJoint *) jointAddr);
    if (def.type == JointDef::RevoluteJoint) joint = new RevoluteJoint(shared_from_this(), (b2RevoluteJoint *) jointAddr);
    if (def.type == JointDef::WeldJoint) joint = new WeldJoint(shared_from_this(), (b2WeldJoint *) jointAddr);
    if (joint != NULL) joints[joint->addr] = joint;
    JointEdge * jointEdgeA = new JointEdge(def.bodyB, joint);
    JointEdge * jointEdgeB = new JointEdge(def.bodyA, joint);
    joint->jointEdgeA = jointEdgeA;
    joint->jointEdgeB = jointEdgeB;
    def.bodyA->joints.insert(jointEdgeA);
    def.bodyB->joints.insert(jointEdgeB);
    return *joint;
}

b2Joint* World::createProperJoint (gdx_cpp::physics::box2d::JointDef& def) {
    if (def.type == JointDef::DistanceJoint) {
        DistanceJointDef& d = static_cast<DistanceJointDef&>(def);
        b2DistanceJointDef def;
        def.bodyA = d.bodyA->body;
        def.bodyB = d.bodyB->body;
        def.collideConnected = d.collideConnected;
        def.localAnchorA = b2Vec2(d.localAnchorA.x, d.localAnchorA.y);
        def.localAnchorB = b2Vec2(d.localAnchorB.x, d.localAnchorB.y);
        def.length = d.length;
        def.frequencyHz = d.frequencyHz;
        def.dampingRatio = d.dampingRatio;

        return this->addr->CreateJoint(&def);
    }
    if (def.type == JointDef::FrictionJoint) {
        FrictionJointDef& d = static_cast<FrictionJointDef&>(def);
        b2FrictionJointDef def;
        def.bodyA = d.bodyA->body;
        def.bodyB = d.bodyB->body;
        def.collideConnected = d.collideConnected;
        def.localAnchorA = b2Vec2(d.localAnchorA.x, d.localAnchorA.y);
        def.localAnchorB = b2Vec2(d.localAnchorB.x, d.localAnchorB.y);
        def.maxForce = d.maxForce;
        def.maxTorque = d.maxTorque;
        return this->addr->CreateJoint(&def);
    }
    if (def.type == JointDef::GearJoint) {
        GearJointDef& d = static_cast<GearJointDef&>(def);
        b2GearJointDef def;
        def.bodyA = d.bodyA->body;
        def.bodyB = d.bodyB->body;
        def.collideConnected = d.collideConnected;
        def.joint1 = d.joint1->addr;
        def.joint2 = d.joint2->addr;
        def.ratio = d.ratio;

        return this->addr->CreateJoint(&def);

    }
    if (def.type == JointDef::LineJoint) {
        LineJointDef& d = static_cast<LineJointDef&>(def);

        b2World* world = (b2World*)addr;
        b2LineJointDef def;
        def.bodyA = d.bodyA->body;
        def.bodyB = d.bodyB->body;
        def.collideConnected = d.collideConnected;
        def.localAnchorA = b2Vec2(d.localAnchorA.x, d.localAnchorA.y);
        def.localAnchorB = b2Vec2(d.localAnchorB.x, d.localAnchorB.y);
        def.localAxisA = b2Vec2(d.localAxisA.x,  d.localAxisA.y);
        def.enableLimit = d.enableLimit;
        def.lowerTranslation = d.lowerTranslation;
        def.upperTranslation = d.upperTranslation;
        def.enableMotor = d.enableMotor;
        def.maxMotorForce = d.maxMotorForce;
        def.motorSpeed = d.motorSpeed;

        return this->addr->CreateJoint(&def);

    }
    if (def.type == JointDef::MouseJoint) {
        MouseJointDef& d = static_cast<MouseJointDef&>(def);
        b2World* world = (b2World*)addr;
        b2MouseJointDef def;
        def.bodyA = d.bodyA->body;
        def.bodyB = d.bodyB->body;
        def.collideConnected = d.collideConnected;
        def.target = b2Vec2( d.target.x, d.target.y );
        def.maxForce = d.maxForce;
        def.frequencyHz =d. frequencyHz;
        def.dampingRatio = d.dampingRatio;

        return this->addr->CreateJoint(&def);
    }
    if (def.type == JointDef::PrismaticJoint) {
        PrismaticJointDef& d = static_cast<PrismaticJointDef&>(def);
        b2PrismaticJointDef def;
        def.bodyA = d.bodyA->body;
        def.bodyB = d.bodyB->body;
        def.collideConnected = d.collideConnected;
        def.localAnchorA = b2Vec2(d.localAnchorA.x, d.localAnchorA.y);
        def.localAnchorB = b2Vec2(d.localAnchorB.x, d.localAnchorB.y);
        def.localAxis1 = b2Vec2(d.localAxis1.x,  d.localAxis1.y);
        def.referenceAngle = d.referenceAngle;
        def.enableLimit = d.enableLimit;
        def.lowerTranslation = d.lowerTranslation;
        def.upperTranslation = d.upperTranslation;
        def.enableMotor = d.enableMotor;
        def.maxMotorForce = d.maxMotorForce;
        def.motorSpeed = d.motorSpeed;

        return this->addr->CreateJoint(&def);
    }
    if (def.type == JointDef::PulleyJoint) {
        PulleyJointDef& d = static_cast<PulleyJointDef&>(def);
        b2PulleyJointDef def;
        def.bodyA = d.bodyA->body;
        def.bodyB = d.bodyB->body;
        def.collideConnected = d.collideConnected;
        def.groundAnchorA = b2Vec2( d.groundAnchorA.x, d.groundAnchorA.y );
        def.groundAnchorB = b2Vec2( d.groundAnchorB.x, d.groundAnchorB.y );
        def.localAnchorA = b2Vec2(d.localAnchorA.x, d.localAnchorA.y);
        def.localAnchorB = b2Vec2(d.localAnchorB.x, d.localAnchorB.y);
        def.lengthA = d.lengthA;
        def.maxLengthA = d.maxLengthA;
        def.lengthB = d.lengthB;
        def.maxLengthB = d.maxLengthB;
        def.ratio = d.ratio;

        return this->addr->CreateJoint(&def);

    }
    if (def.type == JointDef::RevoluteJoint) {
        RevoluteJointDef& d = static_cast<RevoluteJointDef&>(def);
        b2RevoluteJointDef def;
        def.bodyA = d.bodyA->body;
        def.bodyB = d.bodyB->body;
        def.collideConnected = d.collideConnected;
        def.localAnchorA = b2Vec2(d.localAnchorA.x, d.localAnchorA.y);
        def.localAnchorB = b2Vec2(d.localAnchorB.x, d.localAnchorB.y);
        def.referenceAngle = d.referenceAngle;
        def.enableLimit = d.enableLimit;
        def.lowerAngle = d.lowerAngle;
        def.upperAngle = d.upperAngle;
        def.enableMotor = d.enableMotor;
        def.motorSpeed = d.motorSpeed;
        def.maxMotorTorque = d.maxMotorTorque;

        return this->addr->CreateJoint(&def);
    }
    if (def.type == JointDef::WeldJoint) {
        WeldJointDef& d = static_cast<WeldJointDef&>(def);

        b2World* world = (b2World*)addr;
        b2WeldJointDef def;
        def.bodyA = d.bodyA->body;
        def.bodyB = d.bodyB->body;
        def.collideConnected = d.collideConnected;
        def.localAnchorA = b2Vec2(d.localAnchorA.x, d.localAnchorA.y);
        def.localAnchorB = b2Vec2(d.localAnchorB.x, d.localAnchorB.y);
        def.referenceAngle = d.referenceAngle;

        return this->addr->CreateJoint(&def);
    }

    return 0;
}

void World::destroyJoint (Joint& joint) {
    joints.erase(joint.addr);
    joint.jointEdgeA->other->joints.erase(joint.jointEdgeB);
    joint.jointEdgeB->other->joints.erase(joint.jointEdgeA);
    this->addr->DestroyJoint(joint.addr);
}

void World::step (float timeStep,int velocityIterations,int positionIterations) {
    this->addr->Step(timeStep, velocityIterations, positionIterations);
}

void World::clearForces () {
    this->addr->ClearForces();
}

void World::setWarmStarting (bool flag) {
    this->addr->SetWarmStarting(flag);
}

void World::setContinuousPhysics (bool flag) {
    this->addr->SetContinuousPhysics(flag);
}

int World::getProxyCount () {
    return this->addr->GetProxyCount();
}

int World::getBodyCount () {
    return this->addr->GetBodyCount();
}

int World::getJointCount () {
    return this->addr->GetJointCount();
}

int World::getContactCount () {
    return this->addr->GetContactCount();
}

void World::setGravity (const gdx_cpp::math::Vector2& gravity) {
    this->addr->SetGravity(b2Vec2(gravity.x, gravity.y));
}

gdx_cpp::math::Vector2& World::getGravity () {
    b2Vec2 g = this->addr->GetGravity();
    gravity.x = g.x;
    gravity.y = g.x;
    return gravity;
}

bool World::isLocked () {
    return this->addr->IsLocked();
}

void World::setAutoClearForces (bool flag) {
    this->addr->SetAutoClearForces(flag);
}

bool World::getAutoClearForces () {
    return this->addr->GetAutoClearForces();
}

void World::QueryAABB (QueryCallback& callback,float lowerX,float lowerY,float upperX,float upperY) {
    queryCallback = &callback;

    b2AABB aabb;
    aabb.lowerBound = b2Vec2( lowerX, lowerY );
    aabb.upperBound = b2Vec2( upperX, upperY );

    CustomQueryCallback customCallback( this );
    this->addr->QueryAABB( &customCallback, aabb );
}

std::vector< Contact *>& World::getContactList () {
    int numContacts = getContactCount();
    if (numContacts > contactAddrs.size()) {
        int newSize = 2 * numContacts;
        contactAddrs.reserve(newSize);
        contacts.reserve(newSize);
        freeContacts.reserve(newSize);
    }
    if (numContacts > freeContacts.size()) {
        int freeConts = freeContacts.size();
        for (int i = 0; i < numContacts - freeConts; i++)
            freeContacts.push_back(new Contact(shared_from_this(), NULL));
    }
    b2Contact* contact = this->addr->GetContactList();
    int i = 0;
    while( contact != 0 )
    {
            contactAddrs[i++] = contact;
            contact = contact->GetNext();
    }
    contacts.clear();
    for (int i = 0; i < numContacts; i++) {
        Contact * contact = freeContacts[i];
        contact->contact = contactAddrs[i];
        contacts.push_back(contact);
    }

    return contacts;
}

// Iterator<Body>& World::getBodies () {
//     return bodies.values();
// }
// 
// Iterator<Joint>& World::getJoints () {
//     return joints.values();
// }

void World::dispose () {
    delete addr;
}

bool World::contactFilter (b2Fixture* fixtureA, b2Fixture* fixtureB) {
    if (contactFilterVar != NULL)
        return contactFilterVar->shouldCollide(fixtures[fixtureA], fixtures[fixtureB]);
    else {
        Filter filterA = fixtures[fixtureA]->getFilterData();
        Filter filterB = fixtures[fixtureB]->getFilterData();

        if (filterA.groupIndex == filterB.groupIndex && filterA.groupIndex != 0) {
            return filterA.groupIndex > 0;
        }

        bool collide = (filterA.maskBits & filterB.categoryBits) != 0 && (filterA.categoryBits & filterB.maskBits) != 0;
        return collide;
    }
}

void World::beginContact (b2Contact* contactAddr) {
    contact->contact= contactAddr;
    if (contactListener != NULL) contactListener->beginContact(*contact);
}

void World::endContact (b2Contact* contactAddr) {
    contact->contact = contactAddr;
    if (contactListener != NULL) contactListener->endContact(*contact);
}

void World::preSolve (b2Contact* contactAddr, b2Manifold* manifoldAddr) {
    contact->contact = contactAddr;
    manifold->addr = manifoldAddr;
    if (contactListener != NULL ) contactListener->preSolve(*contact, *manifold);
}

void World::postSolve (b2Contact* contactAddr, b2ContactImpulse* impulseAddr) {
    contact->contact = contactAddr;
    impulse->addr = impulseAddr;
    if (contactListener != NULL) contactListener->postSolve(*contact, *impulse);
}

bool World::reportFixture (b2Fixture* addr) {
    if (queryCallback != NULL)
        return queryCallback->reportFixture(*fixtures[addr]);
    else
        return false;
}

