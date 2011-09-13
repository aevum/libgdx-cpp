
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

#ifndef GDX_CPP_PHYSICS_BOX2D_CONTACTLISTENER_HPP_
#define GDX_CPP_PHYSICS_BOX2D_CONTACTLISTENER_HPP_
#include <gdx-cpp/utils/Aliases.hpp>

namespace gdx_cpp {
namespace physics {
namespace box2d {

class ContactImpulse;
class Manifold;
class Contact;

class ContactListener {
public:
    typedef ref_ptr_maker<ContactListener>::type ptr;
    
    virtual   void beginContact (const Contact& contact) = 0;
    virtual   void endContact (const Contact& contact) = 0;
    virtual   void preSolve (const Contact& contact,const Manifold& oldManifold) = 0;
    virtual   void postSolve (const Contact& contact,const ContactImpulse& impulse) = 0;

protected:


private:

};

} // namespace gdx_cpp
} // namespace physics
} // namespace box2d

#endif // GDX_CPP_PHYSICS_BOX2D_CONTACTLISTENER_HPP_
