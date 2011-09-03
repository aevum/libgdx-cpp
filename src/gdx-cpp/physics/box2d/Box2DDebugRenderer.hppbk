
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

namespace gdx_cpp {
namespace physics {
namespace box2d {

class Box2DDebugRenderer {
public:
    void render (const World& world);
    void dispose ();

protected:


private:
    void renderBodies (const World& world);
    void drawShape (const Fixture& fixture,const Transform& transform,const gdx_cpp::graphics::Color& color);
    void drawSolidCircle (const gdx_cpp::math::Vector2& center,float radius,const gdx_cpp::math::Vector2& axis,const gdx_cpp::graphics::Color& color);
    void drawSolidPolygon (int vertexCount,const gdx_cpp::graphics::Color& color);
    void drawJoint (const Joint& joint);
    void drawSegment (const gdx_cpp::math::Vector2& x1,const gdx_cpp::math::Vector2& x2,const gdx_cpp::graphics::Color& color);
    void drawContact (const Contact& contact);
};

} // namespace gdx_cpp
} // namespace physics
} // namespace box2d

#endif // GDX_CPP_PHYSICS_BOX2D_BOX2DDEBUGRENDERER_HPP_
