#include <gdx-cpp/Gdx.hpp>
#include "Box2DTest.cpp"
#include "Box2D/Box2D.h"

using namespace gdx_cpp::graphics;
using namespace gdx_cpp;

class CollisionFiltering : public Box2DTest {
public:

    const static short k_smallGroup = 1;
    const static short k_largeGroup = -1;

    const static short k_defaultCategory = 0x0001;
    const static short k_triangleCategory = 0x0002;
    const static short k_boxCategory = 0x0004;
    const static short k_circleCategory = 0x0008;

    const static short k_triangleMask = -1;
    const static short k_boxMask = -1 ^ k_triangleCategory;
    const static short k_circleMask = -1;

    void createWorld (b2World& world) {
        {
            b2EdgeShape* shape = new b2EdgeShape();
            shape->Set(b2Vec2(-40.0f, 0), b2Vec2(40, 0));

            b2FixtureDef fd;
            fd.shape = shape;
            fd.friction = 0.3f;

            b2BodyDef bd;
            b2Body * ground = world.CreateBody(&bd);
            ground->CreateFixture(&fd);
            delete shape;
        }

        b2Vec2 vertices[3];
        vertices[0].Set(-1, 0);
        vertices[1].Set(1, 0);
        vertices[2].Set(0, 2);
        b2PolygonShape * polygon = new b2PolygonShape;
        polygon->Set(vertices, 3);


        b2FixtureDef triangleShapeDef;
        triangleShapeDef.shape = polygon;
        triangleShapeDef.density = 1.0f;

        triangleShapeDef.filter.groupIndex = k_smallGroup;
        triangleShapeDef.filter.categoryBits = k_triangleCategory;
        triangleShapeDef.filter.maskBits = k_triangleMask;

        b2BodyDef triangleBodyDef;
        triangleBodyDef.type = b2_dynamicBody;
        triangleBodyDef.position.Set(-5, 2);

        b2Body * body1 = world.CreateBody(&triangleBodyDef);
        body1->CreateFixture(&triangleShapeDef);

        vertices[0].x *= 2;
        vertices[0].y *= 2;
        vertices[1].x *= 2;
        vertices[1].y *= 2;
        vertices[2].x *= 2;
        vertices[2].y *= 2;

        polygon->Set(vertices, 3);
        triangleShapeDef.filter.groupIndex = k_largeGroup;
        triangleBodyDef.position.Set(-5, 6);
        triangleBodyDef.fixedRotation = true;

        b2Body * body2 = world.CreateBody(&triangleBodyDef);
        body2->CreateFixture(&triangleShapeDef);

        {
            b2BodyDef bd;
            bd.type = b2_dynamicBody;
            bd.position.Set(-5, 10);
            b2Body * body = world.CreateBody(&bd);

            b2PolygonShape * p = new b2PolygonShape;
            p->SetAsBox(0.5f, 1.0f);
            body->CreateFixture(p, 1);

            b2PrismaticJointDef jd;
            jd.bodyA = body2;
            jd.bodyB = body;
            jd.enableLimit = true;
            jd.localAnchorA.Set(0, 4);
            jd.localAnchorB.Set(0, 0);
            jd.localAxisA.Set(0, 1);
            jd.lowerTranslation = -1;
            jd.upperTranslation = 1;

            world.CreateJoint(&jd);

            delete p;
        }

        polygon->SetAsBox(1, 0.5f);
        b2FixtureDef boxShapeDef;
        boxShapeDef.shape = polygon;
        boxShapeDef.density = 1;
        boxShapeDef.restitution = 0.1f;

        boxShapeDef.filter.groupIndex = k_smallGroup;
        boxShapeDef.filter.categoryBits = k_boxCategory;
        boxShapeDef.filter.maskBits = k_boxMask;

        b2BodyDef boxBodyDef;
        boxBodyDef.type = b2_dynamicBody;
        boxBodyDef.position.Set(0, 2);

        b2Body * body3 = world.CreateBody(&boxBodyDef);
        body3->CreateFixture(&boxShapeDef);

        polygon->SetAsBox(2, 1);
        boxShapeDef.filter.groupIndex = k_largeGroup;
        boxBodyDef.position.Set(0, 6);

        b2Body * body4 = world.CreateBody(&boxBodyDef);
        body4->CreateFixture(&boxShapeDef);

        b2CircleShape * circle = new b2CircleShape;
        circle->m_radius = 1;

        b2FixtureDef circleShapeDef;
        circleShapeDef.shape = circle;
        circleShapeDef.density = 1.0f;

        circleShapeDef.filter.groupIndex = k_smallGroup;
        circleShapeDef.filter.categoryBits = k_circleCategory;
        circleShapeDef.filter.maskBits = k_circleMask;

        b2BodyDef circleBodyDef;
        circleBodyDef.type = b2_dynamicBody;
        circleBodyDef.position.Set(5, 2);

        b2Body * body5 = world.CreateBody(&circleBodyDef);
        body5->CreateFixture(&circleShapeDef);

        circle->m_radius = 2;
        circleShapeDef.filter.groupIndex = k_largeGroup;
        circleBodyDef.position.Set(5, 6);

        b2Body * body6 = world.CreateBody(&circleBodyDef);
        body6->CreateFixture(&circleShapeDef);
    }
private:
};

void init(int argc, char** argv) {
    createApplication(new CollisionFiltering, "CollisionFiltering test", 640, 480);
}
