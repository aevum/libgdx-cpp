#include "../backends/current_backend.hpp"
#include "Box2DTest.cpp"
#include "Box2D/Box2D.h"

using namespace gdx_cpp::graphics;
using namespace gdx_cpp;

class Chain : public Box2DTest {
public:
    void createWorld (b2World& world) {
        b2Body * ground;

        {
            b2BodyDef bd;
            ground = world.CreateBody(&bd);

            b2PolygonShape * shape = new b2PolygonShape;
            shape->SetAsEdge(b2Vec2(-40, 0), b2Vec2(40, 0));

            ground->CreateFixture(shape, 0.0f);
            delete shape;
        }

        {
            b2PolygonShape * shape = new b2PolygonShape;
            shape->SetAsBox(0.6f, 0.125f);

            b2FixtureDef * fd = new b2FixtureDef;
            fd->shape = shape;
            fd->density = 20.0f;
            fd->friction = 0.2f;

            b2RevoluteJointDef * jd = new b2RevoluteJointDef;
            jd->collideConnected = false;

            float y = 25.0f;

            for (int i = 0; i < 30; i++) {
                b2BodyDef * bd = new b2BodyDef;
                bd->type = b2_dynamicBody;
                bd->position.Set(0.5f + i, y);
                b2Body * body = world.CreateBody(bd);
                body->CreateFixture(fd);

                b2Vec2 anchor(i, y);
                jd->Initialize(ground, body, anchor);
                world.CreateJoint(jd);
            }
            delete shape;
        }
    }
private:
};

void init() {
    createApplication(new Chain, "Chain test", 640, 480);
}