
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

#ifndef GDX_CPP_PHYSICS_BOX2D_BOX2DDEBUGRENDERER_HPP_
#define GDX_CPP_PHYSICS_BOX2D_BOX2DDEBUGRENDERER_HPP_

#include "Box2D.h"
#include "gdx-cpp/graphics/Color.hpp"
#include "gdx-cpp/math/Vector2.hpp"

namespace gdx_cpp {
namespace physics {
namespace box2d {

class Box2DDebugRenderer {
public:
    void render (b2World& world);
    void dispose ();

protected:


private:
    void renderBodies (b2World& world);
    void drawShape (b2Fixture& fixture, const b2Transform& transform, gdx_cpp::graphics::Color& color);
    void drawSolidCircle (gdx_cpp::math::Vector2& center,float radius,const gdx_cpp::math::Vector2& axis, const gdx_cpp::graphics::Color& color);
    void drawSolidPolygon (int vertexCount,const gdx_cpp::graphics::Color& color);
    void drawJoint (b2Joint& joint);
    void drawSegment (const gdx_cpp::math::Vector2& x1,const gdx_cpp::math::Vector2& x2, gdx_cpp::graphics::Color& color);
    void drawContact (b2Contact& contact);


    gdx_cpp::graphics::Color SHAPE_NOT_ACTIVE;
    gdx_cpp::graphics::Color SHAPE_STATIC;
    gdx_cpp::graphics::Color SHAPE_KINEMATIC;
    gdx_cpp::graphics::Color SHAPE_NOT_AWAKE;
    gdx_cpp::graphics::Color SHAPE_AWAKE;
    gdx_cpp::graphics::Color JOINT_COLOR;
};

} // namespace gdx_cpp
} // namespace physics
} // namespace box2d

#endif // GDX_CPP_PHYSICS_BOX2D_BOX2DDEBUGRENDERER_HPP_
