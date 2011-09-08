
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

using namespace gdx_cpp::physics::box2d;
/*
Color SHAPE_NOT_ACTIVE = new Color(0.5f, 0.5f, 0.3f, 1);
Color SHAPE_STATIC = new Color(0.5f, 0.9f, 0.5f, 1);
Color SHAPE_KINEMATIC = new Color(0.5f, 0.5f, 0.9f, 1);
Color SHAPE_NOT_AWAKE = new Color(0.6f, 0.6f, 0.6f, 1);
Color SHAPE_AWAKE = new Color(0.9f, 0.7f, 0.7f, 1);
Color JOINT_COLOR = new Color(0.5f, 0.8f, 0.8f, 1);*/

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
    if (fixture.getType() == Type.Circle) {
        CircleShape circle = (CircleShape)fixture.getShape();
        t.set(circle.getPosition());
        transform.mul(t);
        drawSolidCircle(t, circle.getRadius(), axis.set(transform.vals[Transform.COL1_X], transform.vals[Transform.COL1_Y]),
                        color);
    } else {
        PolygonShape poly = (PolygonShape)fixture.getShape();
        int vertexCount = poly.getVertexCount();
        for (int i = 0; i < vertexCount; i++) {
            poly.getVertex(i, vertices[i]);
            transform.mul(vertices[i]);
        }
        drawSolidPolygon(vertices, vertexCount, color);
    }
}

void Box2DDebugRenderer::drawSolidCircle (const gdx_cpp::math::Vector2& center,float radius,const gdx_cpp::math::Vector2& axis,const gdx_cpp::graphics::Color& color) {
    renderer.begin(GL10.GL_LINE_LOOP);
    float angle = 0;
    float angleInc = 2 * (float)Math.PI / 20;
    for (int i = 0; i < 20; i++, angle += angleInc) {
        v.set((float)Math.cos(angle) * radius + center.x, (float)Math.sin(angle) * radius + center.y);
        renderer.color(color.r, color.g, color.b, color.a);
        renderer.vertex(v.x, v.y, 0);
    }
    renderer.end();

    renderer.begin(GL10.GL_LINES);
    renderer.color(color.r, color.g, color.b, color.a);
    renderer.vertex(center.x, center.y, 0);
    renderer.color(color.r, color.g, color.b, color.a);
    renderer.vertex(center.x + axis.x * radius, center.y + axis.y * radius, 0);
    renderer.end();
}

void Box2DDebugRenderer::drawSolidPolygon (int vertexCount, const gdx_cpp::graphics::Color& color) {
    renderer.begin(GL10.GL_LINE_LOOP);
    for (int i = 0; i < vertexCount; i++) {
        Vector2 v = vertices[i];
        renderer.color(color.r, color.g, color.b, color.a);
        renderer.vertex(v.x, v.y, 0);
    }
    renderer.end();
}

void Box2DDebugRenderer::drawJoint (b2Joint& joint) {
    Body bodyA = joint.getBodyA();
    Body bodyB = joint.getBodyB();
    Transform xf1 = bodyA.getTransform();
    Transform xf2 = bodyB.getTransform();

    Vector2 x1 = xf1.getPosition();
    Vector2 x2 = xf2.getPosition();
    Vector2 p1 = joint.getAnchorA();
    Vector2 p2 = joint.getAnchorB();

    if (joint.getType() == JointType.DistanceJoint) {
        drawSegment(p1, p2, JOINT_COLOR);
    } else if (joint.getType() == JointType.PulleyJoint) {
        PulleyJoint pulley = (PulleyJoint)joint;
        Vector2 s1 = pulley.getGroundAnchorA();
        Vector2 s2 = pulley.getGroundAnchorB();
        drawSegment(s1, p1, JOINT_COLOR);
        drawSegment(s2, p2, JOINT_COLOR);
        drawSegment(s1, s2, JOINT_COLOR);
    } else if (joint.getType() == JointType.MouseJoint) {
        drawSegment(joint.getAnchorA(), joint.getAnchorB(), JOINT_COLOR);
    } else {
        drawSegment(x1, p1, JOINT_COLOR);
        drawSegment(p1, p2, JOINT_COLOR);
        drawSegment(x2, p2, JOINT_COLOR);
    }
}

void Box2DDebugRenderer::drawSegment (const gdx_cpp::math::Vector2& x1,const gdx_cpp::math::Vector2& x2,const gdx_cpp::graphics::Color& color) {
    renderer.begin(GL10.GL_LINES);
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

