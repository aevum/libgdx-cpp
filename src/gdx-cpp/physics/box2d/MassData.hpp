
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

#ifndef GDX_CPP_PHYSICS_BOX2D_MASSDATA_HPP_
#define GDX_CPP_PHYSICS_BOX2D_MASSDATA_HPP_
#include <gdx/math/Vector2.hpp>

namespace gdx_cpp {
namespace physics {
namespace box2d {

class MassData {
public:

    MassData();
    /** The mass of the shape, usually in kilograms. **/
    float mass;

    /** The position of the shape's centroid relative to the shape's origin. **/
    gdx_cpp::math::Vector2  center;

    /** The rotational inertia of the shape about the local origin. **/
    float I;


protected:


private:

};

} // namespace gdx_cpp
} // namespace physics
} // namespace box2d

#endif // GDX_CPP_PHYSICS_BOX2D_MASSDATA_HPP_
