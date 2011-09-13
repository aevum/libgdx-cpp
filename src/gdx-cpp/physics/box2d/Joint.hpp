
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

#ifndef GDX_CPP_PHYSICS_BOX2D_JOINT_HPP_
#define GDX_CPP_PHYSICS_BOX2D_JOINT_HPP_

#include <gdx-cpp/utils/Aliases.hpp>
#include "JointDef.hpp"
#include "JointEdge.hpp"
#include "gdx-cpp/math/Vector2.hpp"
#include "gdx-cpp/math/Vector2.hpp"



class b2Joint;
namespace gdx_cpp {
namespace physics {
namespace box2d {

class World;
class Body;

class Joint {
public:
    typedef ref_ptr_maker<Joint>::type ptr;

    Joint(ref_ptr_maker<World>::type _world, b2Joint* joint);
    JointDef::JointType getType ();
    Body* getBodyA ();
    Body* getBodyB ();
    gdx_cpp::math::Vector2& getAnchorA ();
    gdx_cpp::math::Vector2& getAnchorB ();
    gdx_cpp::math::Vector2& getReactionForce (float inv_dt);
    float getReactionTorque (float inv_dt);
    bool isActive ();

    b2Joint* addr;


    JointEdge * jointEdgeA;

    JointEdge * jointEdgeB;
protected:

    

private:
    ref_ptr_maker<World>::type world;
    gdx_cpp::math::Vector2 anchorA;
    gdx_cpp::math::Vector2 anchorB;
    gdx_cpp::math::Vector2 reactionForce;
};

} // namespace gdx_cpp
} // namespace physics
} // namespace box2d

#endif // GDX_CPP_PHYSICS_BOX2D_JOINT_HPP_
