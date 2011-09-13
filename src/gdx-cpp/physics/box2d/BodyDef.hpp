
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

#ifndef GDX_CPP_PHYSICS_BOX2D_BODYDEF_HPP_
#define GDX_CPP_PHYSICS_BOX2D_BODYDEF_HPP_

#include "gdx-cpp/math/Vector2.hpp"

namespace gdx_cpp {
namespace physics {
namespace box2d {

class  BodyDef{
public:
    enum BodyType {
        StaticBody = 0, KinematicBody, DynamicBody
    };

    BodyDef();
    /** The body type: static, kinematic, or dynamic. Note: if a dynamic body would have zero mass, the mass is set to one. **/
    BodyType type;

    /** The world position of the body. Avoid creating bodies at the origin since this can lead to many overlapping shapes. **/
    gdx_cpp::math::Vector2 position;

    /** The world angle of the body in radians. **/
    float angle;

    /** The linear velocity of the body's origin in world co-ordinates. **/
    gdx_cpp::math::Vector2 linearVelocity;

    /** The angular velocity of the body. **/
    float angularVelocity;

    /** Linear damping is use to reduce the linear velocity. The damping parameter can be larger than 1.0f but the damping effect
     * becomes sensitive to the time step when the damping parameter is large. **/
    float linearDamping;

    /** Angular damping is use to reduce the angular velocity. The damping parameter can be larger than 1.0f but the damping effect
     * becomes sensitive to the time step when the damping parameter is large. **/
    float angularDamping;

    /** Set this flag to false if this body should never fall asleep. Note that this increases CPU usage. **/
    bool allowSleep;

    /** Is this body initially awake or sleeping? **/
    bool awake;

    /** Should this body be prevented from rotating? Useful for characters. **/
    bool fixedRotation;

    /** Is this a fast moving body that should be prevented from tunneling through other moving bodies? Note that all bodies are
     * prevented from tunneling through kinematic and static bodies. This setting is only considered on dynamic bodies.
     * @warning You should use this flag sparingly since it increases processing time. **/
    bool bullet;

    /** Does this body start out active? **/
    bool active;

    /** Experimental: scales the inertia tensor. **/
    float inertiaScale;

protected:


private:

};

} // namespace gdx_cpp
} // namespace physics
} // namespace box2d

#endif // GDX_CPP_PHYSICS_BOX2D_BODYDEF_HPP_
