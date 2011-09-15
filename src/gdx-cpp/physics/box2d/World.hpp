
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

#ifndef GDX_CPP_PHYSICS_BOX2D_WORLD_HPP_
#define GDX_CPP_PHYSICS_BOX2D_WORLD_HPP_

#include "gdx-cpp/utils/Disposable.hpp"
#include <gdx-cpp/utils/Aliases.hpp>
#include <vector>
#include "Fixture.hpp"
#include <gdx-cpp/utils/Pool.hpp>
#include <tr1/unordered_map>
#include "ContactListener.hpp"
#include "ContactFilter.hpp"

class b2Contact;

class b2World;
class b2ContactImpulse;
class b2Manifold;
namespace gdx_cpp {
namespace physics {
namespace box2d {

class RayCastCallback;
class DestructionListener;
class ContactFilter;
class ContactListener;
class Body;
class Joint;
class QueryCallback;
class BodyDef;
class JointDef;
class Contact;
class Manifold;
class ContactImpulse;

class World: public gdx_cpp::utils::Disposable, std::tr1::enable_shared_from_this< World > {
public:

    typedef ref_ptr_maker<World>::type ptr;

    void rayCast (gdx_cpp::physics::box2d::RayCastCallback* callback, const gdx_cpp::math::Vector2& point1, const gdx_cpp::math::Vector2& point2);
    void setDestructionListener (const DestructionListener& listener);
    void setContactFilter (ContactFilter::ptr filter);
    void setContactListener (ContactListener::ptr listener);
    Body& createBody (const BodyDef& def);
    void destroyBody (gdx_cpp::physics::box2d::Body& body);
    Joint& createJoint (gdx_cpp::physics::box2d::JointDef& def);
    void destroyJoint (gdx_cpp::physics::box2d::Joint& joint);
    void step (float timeStep,int velocityIterations,int positionIterations);
    void clearForces ();
    void setWarmStarting (bool flag);
    void setContinuousPhysics (bool flag);
    int getProxyCount ();
    int getBodyCount ();
    int getJointCount ();
    int getContactCount ();
    void setGravity (const gdx_cpp::math::Vector2& gravity);
    gdx_cpp::math::Vector2& getGravity ();
    bool isLocked ();
    void setAutoClearForces (bool flag);
    bool getAutoClearForces ();
    void QueryAABB (gdx_cpp::physics::box2d::QueryCallback& callback, float lowerX, float lowerY, float upperX, float upperY);
    std::vector< Contact* >& getContactList ();
//     Iterator<Body>& getBodies ();
//     Iterator<Joint>& getJoints ();
    void dispose ();

    Fixture fixture;


    float reportRayFixture (b2Fixture* addr, float pX, float pY, float nX, float nY, float fraction);
    b2Joint * createProperJoint (gdx_cpp::physics::box2d::JointDef& def);
    bool contactFilter (b2Fixture* fixtureA, b2Fixture* fixtureB);
    void beginContact (b2Contact* contact);
    void endContact (b2Contact* contact);
    void preSolve (b2Contact* contactAddr, b2Manifold* manifoldAddr);
    void postSolve (b2Contact* contact, b2ContactImpulse* impulse);
    bool reportFixture (b2Fixture* addr);

    gdx_cpp::utils::Pool<Body> freeBodies;
    gdx_cpp::utils::Pool<Fixture> freeFixtures;
    
    std::tr1::unordered_map<b2Fixture*, Fixture*> fixtures;
    std::tr1::unordered_map<b2Body*, Body*> bodies;
    std::tr1::unordered_map<b2Joint*, Joint*> joints;
    ContactFilter::ptr contactFilterVar;
    ContactListener::ptr contactListener;

    gdx_cpp::math::Vector2 gravity;
protected:


private:
    
    b2World * addr;
    RayCastCallback * rayCastCallback;
    gdx_cpp::math::Vector2 rayPoint;
    gdx_cpp::math::Vector2 rayNormal;
    QueryCallback * queryCallback;

    std::vector<b2Contact*> contactAddrs;
    std::vector<Contact *> contacts;
    std::vector<Contact *> freeContacts;

    Contact * contact;
    Manifold * manifold;
    ContactImpulse * impulse;
};

} // namespace gdx_cpp
} // namespace physics
} // namespace box2d

#endif // GDX_CPP_PHYSICS_BOX2D_WORLD_HPP_
