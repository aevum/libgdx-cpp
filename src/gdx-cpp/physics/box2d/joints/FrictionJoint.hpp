
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

#ifndef GDX_CPP_PHYSICS_BOX2D_JOINTS_FRICTIONJOINT_HPP_
#define GDX_CPP_PHYSICS_BOX2D_JOINTS_FRICTIONJOINT_HPP_

#include <gdx-cpp/physics/box2d/Joint.hpp>

class b2FrictionJoint;

namespace gdx_cpp {
namespace physics {
namespace box2d {
namespace joints {

class FrictionJoint: public gdx_cpp::physics::box2d::Joint {
public:
    FrictionJoint(ref_ptr_maker< gdx_cpp::physics::box2d::World >::type _world, b2FrictionJoint* joint);
    void setMaxForce (float force);
    float getMaxForce ();
    void setMaxTorque (float torque);
    float getMaxTorque ();

protected:


private:

};

} // namespace gdx_cpp
} // namespace physics
} // namespace box2d
} // namespace joints

#endif // GDX_CPP_PHYSICS_BOX2D_JOINTS_FRICTIONJOINT_HPP_
