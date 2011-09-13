
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

#ifndef GDX_CPP_PHYSICS_BOX2D_TRANSFORM_HPP_
#define GDX_CPP_PHYSICS_BOX2D_TRANSFORM_HPP_

#include <gdx/math/Vector2.hpp>

namespace gdx_cpp {
namespace physics {
namespace box2d {

class Transform {
public:

    Transform () ;
    Transform (gdx_cpp::math::Vector2& position, float angle);
    gdx_cpp::math::Vector2& mul (gdx_cpp::math::Vector2& v);
    gdx_cpp::math::Vector2& getPosition ();
    void setRotation (float angle);
    void setPosition (const gdx_cpp::math::Vector2& pos);

    const static int POS_X = 0;
    const static int POS_Y = 1;
    const static int COL1_X = 2;
    const static int COL1_Y = 3;
    const static int COL2_X = 4;
    const static int COL2_Y = 5;
    const static int vals_sise = 6;
    
    float vals [vals_sise];

protected:


private:
    gdx_cpp::math::Vector2 position;

};

} // namespace gdx_cpp
} // namespace physics
} // namespace box2d

#endif // GDX_CPP_PHYSICS_BOX2D_TRANSFORM_HPP_
