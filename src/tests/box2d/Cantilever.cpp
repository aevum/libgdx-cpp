#include <gdx-cpp/Gdx.hpp>
#include "Box2DTest.cpp"
#include "Box2D/Box2D.h"

using namespace gdx_cpp::graphics;
using namespace gdx_cpp;

class Cantilever : public Box2DTest {
public:

    const static int e_count = 8;
//     const static b2Body m_middle();
    void createWorld (b2World& world) {
        b2Body * ground;
        {
            b2BodyDef bd;
            ground = world.CreateBody(&bd);

            b2EdgeShape * shape = new b2EdgeShape();
            shape->Set(b2Vec2(-40, 0), b2Vec2(40, 0));
            ground->CreateFixture(shape, 0);
            delete shape;
        }

        {
            b2PolygonShape * shape = new b2PolygonShape();
            shape->SetAsBox(0.5f, 0.125f);

            b2FixtureDef fd;
            fd.shape = shape;
            fd.density = 20.0f;

            b2WeldJointDef jd;

            b2Body * prevb2Body = ground;
            for (int i = 0; i < e_count; i++) {
                b2BodyDef bd;
                bd.type = b2_dynamicBody;
                bd.position.Set(-14.5f + 1.0f * i, 5.0f);
                b2Body * body = world.CreateBody(&bd);
                body->CreateFixture(&fd);

                b2Vec2 anchor(-15.0f + 1 * i, 5.0f);
                jd.Initialize(prevb2Body, body, anchor);
                world.CreateJoint(&jd);
                prevb2Body = body;
            }

            delete shape;
        }

        {
            b2PolygonShape * shape = new b2PolygonShape();
            shape->SetAsBox(0.5f, 0.125f);

            b2FixtureDef fd;
            fd.shape = shape;
            fd.density = 20.0f;

            b2WeldJointDef jd;

            b2Body * prevb2Body = ground;
            for (int i = 0; i < e_count; i++) {
                b2BodyDef bd;
                
                bd.type = b2_dynamicBody;
                bd.position.Set(-14.5f + 1.0f * i, 15.0f);
                b2Body * body = world.CreateBody(&bd);
                body->CreateFixture(&fd);

                b2Vec2 anchor(-15.0f + 1.0f * i, 15.0f);
                jd.Initialize(prevb2Body, body, anchor);
                world.CreateJoint(&jd);

                prevb2Body = body;
            }

            delete shape;
        }

        {
            b2PolygonShape * shape = new b2PolygonShape();
            shape->SetAsBox(0.5f, 0.125f);

            b2FixtureDef fd;
            fd.shape = shape;
            fd.density = 20.0f;

            b2WeldJointDef jd;

            b2Body * prevb2Body = ground;
            for (int i = 0; i < e_count; i++) {
                b2BodyDef bd;
                bd.type = b2_dynamicBody;
                bd.position.Set(-4.5f + 1.0f * i, 5.0f);
                b2Body * body = world.CreateBody(&bd);
                body->CreateFixture(&fd);

                if (i > 0) {
                    b2Vec2 anchor(-5.0f + 1.0f * i, 5.0f);
                    jd.Initialize(prevb2Body, body, anchor);
                    world.CreateJoint(&jd);
                }

                prevb2Body = body;
            }

            delete shape;
        }

        {
            b2PolygonShape * shape = new b2PolygonShape();
            shape->SetAsBox(0.5f, 0.125f);

            b2FixtureDef fd;
            fd.shape = shape;
            fd.density = 20.0f;

            b2WeldJointDef jd;

            b2Body * prevb2Body = ground;
            for (int i = 0; i < e_count; i++) {
                b2BodyDef bd;
                bd.type = b2_dynamicBody;
                bd.position.Set(5.5f + 1.0f * i, 10.0f);
                b2Body * body = world.CreateBody(&bd);
                body->CreateFixture(&fd);

                if (i > 0) {
                    b2Vec2 anchor(5.0f + 1.0f * i, 10.0f);
                    jd.Initialize(prevb2Body, body, anchor);
                    world.CreateJoint(&jd);
                }

                prevb2Body = body;
            }

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

        for (int i = 0; i < 2; i++) {
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
    createApplication(new Cantilever, "Cantilever test", 640, 480);
}
