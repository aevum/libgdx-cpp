
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

#include "Box2DDebugRenderer.hpp"
#include "gdx-cpp/math/MathUtils.hpp"
#include <cmath>

using namespace gdx_cpp::physics::box2d;


Box2DDebugRenderer::Box2DDebugRenderer(): SHAPE_NOT_ACTIVE(0.5f, 0.5f, 0.3f, 1), SHAPE_STATIC(0.5f, 0.9f, 0.5f, 1),
                                          SHAPE_KINEMATIC(0.5f, 0.5f, 0.9f, 1), SHAPE_NOT_AWAKE(0.6f, 0.6f, 0.6f, 1),
                                          SHAPE_AWAKE(0.9f, 0.7f, 0.7f, 1), JOINT_COLOR(0.5f, 0.8f, 0.8f, 1)                                          
{
  
}
void Box2DDebugRenderer::render (b2World& world) {
    renderBodies(world);
}

void Box2DDebugRenderer::renderBodies (b2World& world) {
    b2Body * blist = world.GetBodyList();
    for (int i = 0; i < world.GetBodyCount(); i++) {
        b2Body& body = blist[i];
        const b2Transform& transform = body.GetTransform();
        for (b2Fixture* fixture = body.GetFixtureList(); fixture; fixture = fixture->GetNext())
        {
            if (body.IsActive() == false)
                drawShape(*fixture, transform, SHAPE_NOT_ACTIVE);
            else if (body.GetType() == b2_staticBody)
                drawShape(*fixture, transform, SHAPE_STATIC);
            else if (body.GetType() == b2_kinematicBody)
                drawShape(*fixture, transform, SHAPE_KINEMATIC);
            else if (body.IsAwake() == false)
                drawShape(*fixture, transform, SHAPE_NOT_AWAKE);
            else
                drawShape(*fixture, transform, SHAPE_AWAKE);
        }
    }


    for (b2Joint* joint = world.GetJointList(); joint; joint= joint->GetNext())
    {
        drawJoint(*joint);

    }

    for (b2Contact* contact = world.GetContactList(); contact; contact= contact->GetNext())
    {
        drawContact(*contact);
    }
}



void Box2DDebugRenderer::drawShape (b2Fixture& fixture, const b2Transform& transform, gdx_cpp::graphics::Color& color) {
    if (fixture.GetType() == b2Shape::e_circle) {
        b2CircleShape * circle = (b2CircleShape *)fixture.GetShape();
        b2Vec2 t = b2Mul(transform, circle->m_p);
        drawSolidCircle(t, circle->m_radius, transform.R.col1, color);
    } else {
        b2PolygonShape * poly = (b2PolygonShape *)fixture.GetShape();
        int vertexCount = poly->GetVertexCount();
        for (int i = 0; i < vertexCount; i++) {
            vertices[i] = poly->GetVertex(i);
            vertices[i] = b2Mul(transform, vertices[i]);
        }
        drawSolidPolygon(vertices, vertexCount, color);
    }
}

void Box2DDebugRenderer::drawSolidCircle (const b2Vec2& center,float radius,const b2Vec2& axis,const gdx_cpp::graphics::Color& color) {
    renderer.begin(gdx_cpp::graphics::GL10::GL_LINE_LOOP);
    float angle = 0;
    float angleInc = 2 * (float)gdx_cpp::math::utils::detail::PI / 20;
    for (int i = 0; i < 20; i++, angle += angleInc) {
        v.Set((float)std::cos(angle) * radius + center.x, (float)std::sin(angle) * radius + center.y);
        renderer.color(color.r, color.g, color.b, color.a);
        renderer.vertex(v.x, v.y, 0);
    }
    renderer.end();

    renderer.begin(gdx_cpp::graphics::GL10::GL_LINES);
    renderer.color(color.r, color.g, color.b, color.a);
    renderer.vertex(center.x, center.y, 0);
    renderer.color(color.r, color.g, color.b, color.a);
    renderer.vertex(center.x + axis.x * radius, center.y + axis.y * radius, 0);
    renderer.end();
}

void Box2DDebugRenderer::drawSolidPolygon (b2Vec2* vertices, int vertexCount, const gdx_cpp::graphics::Color& color) {
    renderer.begin(gdx_cpp::graphics::GL10::GL_LINE_LOOP);
    for (int i = 0; i < vertexCount; i++) {
        renderer.color(color.r, color.g, color.b, color.a);
        renderer.vertex(vertices[i].x, vertices[i].y, 0);
    }
    renderer.end();
}

void Box2DDebugRenderer::drawJoint (b2Joint& joint) {
    b2Body* bodyA = joint.GetBodyA();
    b2Body* bodyB = joint.GetBodyB();
    const b2Transform& xf1 = bodyA->GetTransform();
    const b2Transform& xf2 = bodyB->GetTransform();

    b2Vec2 p1 = joint.GetAnchorA();
    b2Vec2 p2 = joint.GetAnchorB();

    if (joint.GetType() == e_distanceJoint) {
        drawSegment(p1, p2, JOINT_COLOR);
    } else if (joint.GetType() == e_pulleyJoint) {
        b2PulleyJoint * pulley = (b2PulleyJoint *)&joint;
        b2Vec2 s1 = pulley->GetGroundAnchorA();
        b2Vec2 s2 = pulley->GetGroundAnchorB();
        drawSegment(s1, p1, JOINT_COLOR);
        drawSegment(s2, p2, JOINT_COLOR);
        drawSegment(s1, s2, JOINT_COLOR);
    } else if (joint.GetType() == e_mouseJoint) {
        drawSegment(p1, p2, JOINT_COLOR);
    } else {
        drawSegment(xf1.position, p1, JOINT_COLOR);
        drawSegment(p1, p2, JOINT_COLOR);
        drawSegment(xf2.position, p2, JOINT_COLOR);
    }
}

void Box2DDebugRenderer::drawSegment (const b2Vec2& x1,const b2Vec2& x2,const gdx_cpp::graphics::Color& color) {
    renderer.begin(gdx_cpp::graphics::GL10::GL_LINES);
    renderer.color(color.r, color.g, color.b, color.a);
    renderer.vertex(x1.x, x1.y, 0);
    renderer.color(color.r, color.g, color.b, color.a);
    renderer.vertex(x2.x, x2.y, 0);
    renderer.end();
}

void Box2DDebugRenderer::drawContact (b2Contact& contact) {

}

void Box2DDebugRenderer::dispose () {
    batch.dispose();
// font.dispose();
}

