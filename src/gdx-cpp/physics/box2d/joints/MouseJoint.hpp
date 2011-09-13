
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

#ifndef GDX_CPP_PHYSICS_BOX2D_JOINTS_MOUSEJOINT_HPP_
#define GDX_CPP_PHYSICS_BOX2D_JOINTS_MOUSEJOINT_HPP_

#include <gdx-cpp/physics/box2d/Joint.hpp>

class b2MouseJoint;
namespace gdx_cpp {
namespace physics {
namespace box2d {
namespace joints {

class MouseJoint: public gdx_cpp::physics::box2d::Joint {
public:
    MouseJoint(ref_ptr_maker< gdx_cpp::physics::box2d::World >::type _world, b2MouseJoint* joint);
    void setTarget (const gdx_cpp::math::Vector2& target);
    gdx_cpp::math::Vector2& getTarget ();
    void setMaxForce (float force);
    float getMaxForce ();
    void setFrequency (float hz);
    float getFrequency ();
    void setDampingRatio (float ratio);
    float getDampingRatio ();


protected:


private:
    gdx_cpp::math::Vector2 target;

};

} // namespace gdx_cpp
} // namespace physics
} // namespace box2d
} // namespace joints

#endif // GDX_CPP_PHYSICS_BOX2D_JOINTS_MOUSEJOINT_HPP_
