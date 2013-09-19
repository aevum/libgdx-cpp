
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

#include <stddef.h>
#include <algorithm>
#include <cmath>

#include "Box2D/Collision/Shapes/b2ChainShape.h"
#include "Box2D/Collision/Shapes/b2CircleShape.h"
#include "Box2D/Collision/Shapes/b2EdgeShape.h"
#include "Box2D/Collision/Shapes/b2PolygonShape.h"
#include "Box2D/Collision/Shapes/b2Shape.h"
#include "Box2D/Collision/b2Collision.h"
#include "Box2D/Dynamics/Contacts/b2Contact.h"
#include "Box2D/Dynamics/Joints/b2Joint.h"
#include "Box2D/Dynamics/Joints/b2PulleyJoint.h"
#include "Box2D/Dynamics/b2Body.h"
#include "Box2D/Dynamics/b2Fixture.h"
#include "Box2D/Dynamics/b2World.h"
#include "Box2DDebugRenderer.hpp"
#include "gdx-cpp/Gdx.hpp"
#include "gdx-cpp/graphics/GL10.hpp"
#include "gdx-cpp/math/MathUtils.hpp"

using namespace gdx;

b2Vec2 Box2DDebugRenderer::mLower;
b2Vec2 Box2DDebugRenderer::mUpper;

void Box2DDebugRenderer::render (b2World& world,const Matrix4& projMatrix) {
    renderer.setProjectionMatrix(projMatrix);
    renderBodies(world);
}

void Box2DDebugRenderer::renderBodies ( b2World& world) {
    renderer.begin(ShapeRenderer::ShapeType::Line);

    if (mDrawBodies || mDrawAABBs) {        
        for (b2Body * body = world.GetBodyList(); body; body = body->GetNext())  {
            
            const b2Transform& transform = body->GetTransform();
            for (b2Fixture* fixture = body->GetFixtureList(); fixture; fixture = fixture->GetNext()) {
                if (mDrawBodies) {
                    if (body->IsActive() == false)
                        drawShape(*fixture, transform, SHAPE_NOT_ACTIVE);
                    else if (body->GetType() == b2_staticBody)
                        drawShape(*fixture, transform, SHAPE_STATIC);
                    else if (body->GetType() == b2_kinematicBody)
                        drawShape(*fixture, transform, SHAPE_KINEMATIC);
                    else if (body->IsAwake() == false)
                        drawShape(*fixture, transform, SHAPE_NOT_AWAKE);
                    else
                        drawShape(*fixture, transform, SHAPE_AWAKE);
                }

                if (mDrawAABBs) {
                    drawAABB(*fixture, transform);
                }
            }
        }
    }

    if (mDrawJoints) {
        for (b2Joint* joint = world.GetJointList(); joint; joint= joint->GetNext())
        {
            drawJoint(*joint);            
        }
    }
    
    renderer.end();

    if (gl10 != nullptr) {
        gl10->glPointSize(3);
    }
    
    renderer.begin(ShapeRenderer::ShapeType::Point);

    for (b2Contact* contact = world.GetContactList(); contact; contact = contact->GetNext()) {
        drawContact(*contact);
    }
    renderer.end();
    
    if (gl10 != nullptr) {
        gl10->glPointSize(1);
    }
}

void Box2DDebugRenderer::drawAABB (const b2Fixture& fixture, const b2Transform& transform) {
    if (fixture.GetType() == b2Shape::e_circle) {

        b2CircleShape* shape = (b2CircleShape*)fixture.GetShape();
                
        vertices[0] = shape->m_p;
        vertices[0] = b2Mul(transform.q, vertices[0]) + transform.p;
             
        mLower.Set(vertices[0].x - shape->m_radius, vertices[0].y - shape->m_radius);
        mUpper.Set(vertices[0].x + shape->m_radius, vertices[0].y + shape->m_radius);

        // define vertices in ccw fashion...
        vertices[0].Set(mLower.x, mLower.y);
        vertices[1].Set(mUpper.x, mLower.y);
        vertices[2].Set(mUpper.x, mUpper.y);
        vertices[3].Set(mLower.x, mUpper.y);

        drawSolidPolygon(vertices, 4, AABB_COLOR);
    } else if (fixture.GetType() == b2Shape::e_polygon) {
        b2PolygonShape* shape = (b2PolygonShape*)fixture.GetShape();
        int vertexCount = shape->GetVertexCount();

        vertices[0] = shape->GetVertex(0);
        
        mUpper = mLower = b2Mul(transform, vertices[0]);

        for (int i = 1; i < vertexCount; i++) {
            vertices[i] = shape->GetVertex(i);
            vertices[i] = b2Mul(transform,vertices[i]);
            
            mLower.x = std::min(mLower.x, vertices[i].x);
            mLower.y = std::min(mLower.y, vertices[i].y);
            mUpper.x = std::max(mUpper.x, vertices[i].x);
            mUpper.y = std::max(mUpper.y, vertices[i].y);
        }

        // define vertices in ccw fashion...
        vertices[0].Set(mLower.x, mLower.y);
        vertices[1].Set(mUpper.x, mLower.y);
        vertices[2].Set(mUpper.x, mUpper.y);
        vertices[3].Set(mLower.x, mUpper.y);

        drawSolidPolygon(vertices, 4, AABB_COLOR);
    }
}

void Box2DDebugRenderer::drawShape (const b2Fixture& fixture,
                                    const b2Transform& transform,
                                    const Color& color) {
    if (fixture.GetType() == b2Shape::e_circle) {
        b2CircleShape* circle = (b2CircleShape*)fixture.GetShape();        
        t = b2Mul(transform, circle->m_p);                
        drawSolidCircle(t, circle->m_radius, transform.q.GetXAxis() , color);
    } else if (fixture.GetType() == b2Shape::e_edge) {
        b2EdgeShape* edge = (b2EdgeShape*)fixture.GetShape();
        vertices[0] = edge->m_vertex1;
        
        vertices[1] = edge->m_vertex2;
        vertices[0] = b2Mul(transform, vertices[0]);
        vertices[1] = b2Mul(transform, vertices[1]);
        
        drawSolidPolygon(vertices, 2, color);
    } else if (fixture.GetType() == b2Shape::e_polygon) {
        
        b2PolygonShape* chain = (b2PolygonShape*)fixture.GetShape();
        int vertexCount = chain->GetVertexCount();
        for (int i = 0; i < vertexCount; i++) {
            vertices[i] = chain->GetVertex(i);
            vertices[i] = b2Mul(transform, vertices[i]);
        }
        
        drawSolidPolygon(vertices, vertexCount, color);
    }
    else if (fixture.GetType() == b2Shape::e_chain) {
        b2ChainShape* chain = (b2ChainShape*)fixture.GetShape();
        int vertexCount = chain->m_count;
        for (int i = 0; i < vertexCount; i++) {
            vertices[i] = chain->m_vertices[i];
            vertices[i] = b2Mul(transform, vertices[i]);
        }
        drawSolidPolygon(vertices, vertexCount, color);
    }
}

void Box2DDebugRenderer::drawSolidCircle (const b2Vec2& center,float radius,const b2Vec2& axis,const Color& color) {
    float angle = 0;
    float angleInc = 2 * detail::PI / 20.f;
    renderer.setColor(color.r, color.g, color.b, color.a);
    for (int i = 0; i < 20; i++, angle += angleInc) {
        v.Set((float)std::cos(angle) * radius + center.x, (float)std::sin(angle) * radius + center.y);
        if (i == 0) {
            lv = v;
            f = v;
            continue;
        }
        renderer.line(lv.x, lv.y, v.x, v.y);
        lv = v;
    }
    renderer.line(f.x, f.y, lv.x, lv.y);
    renderer.line(center.x, center.y, 0, center.x + axis.x * radius, center.y + axis.y * radius, 0);
}

void Box2DDebugRenderer::drawSolidPolygon (b2Vec2* vertices, int vertexCount, const Color& color) {
    renderer.setColor(color.r, color.g, color.b, color.a);
    
    for (int i = 0; i < vertexCount; i++) {
        b2Vec2& v = vertices[i];
        if (i == 0) {
            lv = v;
            f = v;
            continue;
        }
        renderer.line(lv.x, lv.y, v.x, v.y);
        lv = v;
    }
    renderer.line(f.x, f.y, lv.x, lv.y);
}

void Box2DDebugRenderer::drawJoint (b2Joint& joint) {

    b2Body* bodyA = joint.GetBodyA();
    b2Body* bodyB = joint.GetBodyB();
    const b2Transform& xf1 = bodyA->GetTransform();
    const b2Transform& xf2 = bodyB->GetTransform();

    const b2Vec2& x1 = xf1.p;
    const b2Vec2& x2 = xf2.p;
    b2Vec2 p1 = joint.GetAnchorA();
    b2Vec2 p2 = joint.GetAnchorB();

    if (joint.GetType() == e_distanceJoint) {
        drawSegment(joint.GetAnchorA(), joint.GetAnchorB(), JOINT_COLOR);
    } else if (joint.GetType() == e_pulleyJoint) {
        b2PulleyJoint& pulley = (b2PulleyJoint&)joint;
        b2Vec2 s1 = pulley.GetGroundAnchorA();
        b2Vec2 s2 = pulley.GetGroundAnchorB();
        drawSegment(s1, p1, JOINT_COLOR);
        drawSegment(s2, p2, JOINT_COLOR);
        drawSegment(s1, s2, JOINT_COLOR);
    } else if (joint.GetType() == e_mouseJoint) {
        drawSegment(joint.GetAnchorA(), joint.GetAnchorB(), JOINT_COLOR);
    } else {
        drawSegment(x1, p1, JOINT_COLOR);
        drawSegment(p1, p2, JOINT_COLOR);
        drawSegment(x2, p2, JOINT_COLOR);
    }
}

void Box2DDebugRenderer::drawSegment (const b2Vec2& x1, const b2Vec2& x2, const Color& color) {
    renderer.setColor(color);
    renderer.line(x1.x, x1.y, x2.x, x2.y);
}

void Box2DDebugRenderer::drawContact (const b2Contact& contact) {
    b2WorldManifold worldManifold;
    contact.GetWorldManifold(&worldManifold);
    
    if (contact.GetManifold()->pointCount == 0) return;
    b2Vec2& point = worldManifold.points[0];
    renderer.point(point.x, point.y, 0);
}

void Box2DDebugRenderer::dispose () {
    batch.dispose();
}

Box2DDebugRenderer::Box2DDebugRenderer (bool drawBodies,bool drawJoints,bool drawAABBs)
: mDrawBodies(drawBodies),
mDrawJoints(drawJoints),
mDrawAABBs(drawAABBs),
SHAPE_NOT_ACTIVE(0.5f, 0.5f, 0.3f, 1),
SHAPE_STATIC(0.5f, 0.9f, 0.5f, 1),
SHAPE_KINEMATIC(0.5f, 0.5f, 0.9f, 1),
SHAPE_NOT_AWAKE(0.6f, 0.6f, 0.6f, 1),
SHAPE_AWAKE(0.9f, 0.7f, 0.7f, 1),
JOINT_COLOR(0.5f, 0.8f, 0.8f, 1),
AABB_COLOR(1.0f, 0, 1.0f, 1)
{
}

