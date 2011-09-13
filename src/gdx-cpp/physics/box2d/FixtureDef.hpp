
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

#ifndef GDX_CPP_PHYSICS_BOX2D_FIXTUREDEF_HPP_
#define GDX_CPP_PHYSICS_BOX2D_FIXTUREDEF_HPP_
#include "Shape.hpp"
#include "Filter.hpp"

namespace gdx_cpp {
namespace physics {
namespace box2d {

class FixtureDef {
public:

    FixtureDef();

    /** The shape, this must be set. The shape will be cloned, so you can create the shape on the stack. */
    Shape::ptr shape;

    /** The friction coefficient, usually in the range [0,1]. **/
    float friction;

    /** The restitution (elasticity) usually in the range [0,1]. **/
    float restitution;

    /** The density, usually in kg/m^2. **/
    float density;

    /** A sensor shape collects contact information but never generates a collision response. */
    bool isSensor;

    /** Contact filtering data. **/
    Filter filter;


protected:


private:

};

} // namespace gdx_cpp
} // namespace physics
} // namespace box2d

#endif // GDX_CPP_PHYSICS_BOX2D_FIXTUREDEF_HPP_
