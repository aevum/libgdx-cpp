
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

#ifndef GDX_CPP_PHYSICS_BOX2D_CONTACT_HPP_
#define GDX_CPP_PHYSICS_BOX2D_CONTACT_HPP_

#include "WorldManifold.hpp"
#include <Dynamics/Contacts/b2Contact.h>
#include <gdx-cpp/utils/Aliases.hpp>

namespace gdx_cpp {
namespace physics {
namespace box2d {

class World;
class Fixture;


class Contact {
public:
    Contact (ref_ptr_maker<World>::type world, b2Contact* addr);
    WorldManifold& getWorldManifold ();
    bool isTouching ();
    void setEnabled (bool flag);
    bool isEnabled ();
    Fixture& getFixtureA ();
    Fixture& getFixtureB ();

    /** the address **/
    b2Contact* contact;

protected:



    /** the world **/
    ref_ptr_maker<World>::type world;

    /** the world manifold **/
    WorldManifold worldManifold;

private:

};

} // namespace gdx_cpp
} // namespace physics
} // namespace box2d

#endif // GDX_CPP_PHYSICS_BOX2D_CONTACT_HPP_
