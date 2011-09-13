
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

#include "Box2D/Box2D.h"
#include "gdx-cpp/graphics/Color.hpp"
#include "gdx-cpp/math/Vector2.hpp"
#include "gdx-cpp/graphics/glutils/ImmediateModeRenderer10.hpp"
#include "gdx-cpp/graphics/g2d/SpriteBatch.hpp"


namespace gdx_cpp {
namespace physics {
namespace box2d {

class Box2DDebugRenderer {
public:
    Box2DDebugRenderer();
    void render (b2World& world);
    void dispose ();

    gdx_cpp::graphics::g2d::SpriteBatch batch;

protected:
    gdx_cpp::graphics::glutils::ImmediateModeRenderer10 renderer;

private:
    void renderBodies (b2World& world);
    void drawShape (b2Fixture& fixture, const b2Transform& transform, gdx_cpp::graphics::Color& color);
    void drawSolidCircle (const b2Vec2& center, float radius, const b2Vec2& axis, const gdx_cpp::graphics::Color& color);
    void drawSolidPolygon (b2Vec2* vertices, int vertexCount, const gdx_cpp::graphics::Color& color);
    void drawJoint (b2Joint& joint);
    void drawSegment (const b2Vec2& x1, const b2Vec2& x2, const gdx_cpp::graphics::Color& color);
    void drawContact (b2Contact& contact);


    gdx_cpp::graphics::Color SHAPE_NOT_ACTIVE;
    gdx_cpp::graphics::Color SHAPE_STATIC;
    gdx_cpp::graphics::Color SHAPE_KINEMATIC;
    gdx_cpp::graphics::Color SHAPE_NOT_AWAKE;
    gdx_cpp::graphics::Color SHAPE_AWAKE;
    gdx_cpp::graphics::Color JOINT_COLOR;
    
    b2Vec2 t;
    b2Vec2 axis;
    b2Vec2 vertices[100];
    b2Vec2 v;
};

} // namespace gdx_cpp
} // namespace physics
} // namespace box2d

#endif // GDX_CPP_PHYSICS_BOX2D_BOX2DDEBUGRENDERER_HPP_
