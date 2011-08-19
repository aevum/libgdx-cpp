
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

namespace gdx_cpp {
namespace physics {
namespace box2d {

class World: public gdx_cpp::utils::Disposable {
public:
    void rayCast (const RayCastCallback& callback,const gdx_cpp::math::Vector2& point1,const gdx_cpp::math::Vector2& point2);
    void setDestructionListener (const DestructionListener& listener);
    void setContactFilter (const ContactFilter& filter);
    void setContactListener (const ContactListener& listener);
    Body& createBody (const BodyDef& def);
    void destroyBody (const Body& body);
    Joint& createJoint (const JointDef& def);
    void destroyJoint (const Joint& joint);
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
    void QueryAABB (const QueryCallback& callback,float lowerX,float lowerY,float upperX,float upperY);
    std::list<Contact>& getContactList ();
    Iterator<Body>& getBodies ();
    Iterator<Joint>& getJoints ();
    void dispose ();

protected:
    Body& newObject ();
    Fixture& newObject ();

private:
    float reportRayFixture (long addr,float pX,float pY,float nX,float nY,float fraction);
    long createProperJoint (const JointDef& def);
    bool contactFilter (long fixtureA,long fixtureB);
    void beginContact (long contactAddr);
    void endContact (long contactAddr);
    void preSolve (long contactAddr,long manifoldAddr);
    void postSolve (long contactAddr,long impulseAddr);
    bool reportFixture (long addr);
    long addr;
};

} // namespace gdx_cpp
} // namespace physics
} // namespace box2d

#endif // GDX_CPP_PHYSICS_BOX2D_WORLD_HPP_
