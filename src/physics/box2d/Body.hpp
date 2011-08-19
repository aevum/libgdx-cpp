
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

#ifndef GDX_CPP_PHYSICS_BOX2D_BODY_HPP_
#define GDX_CPP_PHYSICS_BOX2D_BODY_HPP_

namespace gdx_cpp {
namespace physics {
namespace box2d {

class Body {
public:
    Fixture& createFixture (const FixtureDef& def);
    Fixture& createFixture (const Shape& shape,float density);
    void destroyFixture (const Fixture& fixture);
    void setTransform (const gdx_cpp::math::Vector2& position,float angle);
    void setTransform (float x,float y,float angle);
    Transform& getTransform ();
    gdx_cpp::math::Vector2& getPosition ();
    float getAngle ();
    gdx_cpp::math::Vector2& getWorldCenter ();
    gdx_cpp::math::Vector2& getLocalCenter ();
    void setLinearVelocity (const gdx_cpp::math::Vector2& v);
    void setLinearVelocity (float vX,float vY);
    gdx_cpp::math::Vector2& getLinearVelocity ();
    void setAngularVelocity (float omega);
    float getAngularVelocity ();
    void applyForce (const gdx_cpp::math::Vector2& force,const gdx_cpp::math::Vector2& point);
    void applyForce (float forceX,float forceY,float pointX,float pointY);
    void applyTorque (float torque);
    void applyLinearImpulse (const gdx_cpp::math::Vector2& impulse,const gdx_cpp::math::Vector2& point);
    void applyLinearImpulse (float impulseX,float impulseY,float pointX,float pointY);
    void applyAngularImpulse (float impulse);
    float getMass ();
    float getInertia ();
    MassData& getMassData ();
    void setMassData (const MassData& data);
    void resetMassData ();
    gdx_cpp::math::Vector2& getWorldPoint (const gdx_cpp::math::Vector2& localPoint);
    gdx_cpp::math::Vector2& getWorldVector (const gdx_cpp::math::Vector2& localVector);
    gdx_cpp::math::Vector2& getLocalPoint (const gdx_cpp::math::Vector2& worldPoint);
    gdx_cpp::math::Vector2& getLocalVector (const gdx_cpp::math::Vector2& worldVector);
    gdx_cpp::math::Vector2& getLinearVelocityFromWorldPoint (const gdx_cpp::math::Vector2& worldPoint);
    gdx_cpp::math::Vector2& getLinearVelocityFromLocalPoint (const gdx_cpp::math::Vector2& localPoint);
    float getLinearDamping ();
    void setLinearDamping (float linearDamping);
    float getAngularDamping ();
    void setAngularDamping (float angularDamping);
    void setType (const gdx_cpp::physics::box2d::BodyDef::BodyType& type);
    gdx_cpp::physics::box2d::BodyDef::BodyType& getType ();
    void setBullet (bool flag);
    bool isBullet ();
    void setSleepingAllowed (bool flag);
    bool isSleepingAllowed ();
    void setAwake (bool flag);
    bool isAwake ();
    void setActive (bool flag);
    bool isActive ();
    void setFixedRotation (bool flag);
    bool isFixedRotation ();
    ArrayList<Fixture>& getFixtureList ();
    ArrayList<JointEdge>& getJointList ();
    World& getWorld ();
    Object& getUserData ();
    void setUserData (const Object& userData);

protected:
    void reset (long addr);

private:
    World world;
};

} // namespace gdx_cpp
} // namespace physics
} // namespace box2d

#endif // GDX_CPP_PHYSICS_BOX2D_BODY_HPP_
