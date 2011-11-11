#include <gdx-cpp/Gdx.hpp>
#include "Box2DTest.cpp"
#include "Box2D/Box2D.h"

using namespace gdx_cpp::graphics;
using namespace gdx_cpp;

class Bridge : public Box2DTest {
public:

    const static int e_count = 30;
    
    void createWorld (b2World& world) {
        b2Body * ground;
        {
            b2BodyDef bd;
            ground = world.CreateBody(&bd);

            b2EdgeShape * shape = new b2EdgeShape;
            shape->Set(b2Vec2(-40, 0), b2Vec2(40.0f, 0));

            ground->CreateFixture(shape, 0);
            delete shape;
        }

        {
            b2PolygonShape * shape = new b2PolygonShape;
            shape->SetAsBox(0.5f, 0.125f);
            b2FixtureDef fd ;
            fd.shape = shape;
            fd.density = 20.0f;
            fd.friction = 0.2f;

            b2RevoluteJointDef jd;

            b2Body * prevBody = ground;

            for (int i = 0; i < e_count; i++) {
                b2BodyDef bd;
                bd.type = b2_dynamicBody;
                bd.position.Set(-14.5f + 1.0f * i, 5.0f);
                b2Body * body = world.CreateBody(&bd);
                body->CreateFixture(&fd);

                b2Vec2 anchor(-15.0f + 1.0f * i, 5.0f);
                jd.Initialize(prevBody, body, anchor);
                world.CreateJoint(&jd);
                prevBody = body;
            }

            b2Vec2 anchor(-15.0f + 1.0f * e_count, 5.0f);
            jd.Initialize(prevBody, ground, anchor);
            world.CreateJoint(&jd);
            delete shape;
        }

        for (int i = 0; i < 2; i++) {
            b2Vec2 vertices[3];
            vertices[0].Set(-0.5f, 0);
            vertices[1].Set(0.5f, 0);
            vertices[2].Set(0, 1.5f);

            b2PolygonShape * shape = new b2PolygonShape();
            shape->Set(&vertices[0], 3);

            b2FixtureDef fd;
            fd.shape = shape;
            fd.density = 1.0f;

            b2BodyDef bd;
            bd.type = b2_dynamicBody;
            bd.position.Set(-8.0f + 8.0f * i, 12.0f);
            b2Body * body = world.CreateBody(&bd);
            body->CreateFixture(&fd);

            delete shape;
        }

        for (int i = 0; i < 3; i++) {
            b2CircleShape * shape = new b2CircleShape();
            shape->m_radius = 0.5f;

            b2FixtureDef fd;
            fd.shape = shape;
            fd.density = 1.0f;

            b2BodyDef bd;
            bd.type = b2_dynamicBody;
            bd.position.Set(-6.0f + 6.0f * i, 10.0f);

            b2Body * body = world.CreateBody(&bd);
            body->CreateFixture(&fd);

            delete shape;
        }
    }
private:
};

void init(int argc, char** argv) {
    createApplication(new Bridge, "Bridge test", 640, 480);
}
