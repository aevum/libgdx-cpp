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

            b2EdgeShape* shape = new b2EdgeShape;
            shape->Set(b2Vec2(-40, 0), b2Vec2(40, 0));

            ground->CreateFixture(shape, 0.0f);
            delete shape;
        }

        {
            b2PolygonShape * shape = new b2PolygonShape;
            shape->SetAsBox(0.6f, 0.125f);

            b2FixtureDef fd;
            fd.shape = shape;
            fd.density = 20.0f;
            fd.friction = 0.2f;

            b2RevoluteJointDef jd;
            jd.collideConnected = false;

            float y = 25.0f;
            b2Body * prevBody = ground;
            for (int i = 0; i < 30; i++) {
                b2BodyDef bd;
                bd.type = b2_dynamicBody;
                bd.position.Set(0.5f + i, y);
                b2Body * body = world.CreateBody(&bd);
                body->CreateFixture(&fd);

                b2Vec2 * anchor = new b2Vec2(i, y);
                jd.Initialize(prevBody, body, *anchor);
                world.CreateJoint(&jd);
                prevBody = body;
            }
            delete shape;
        }

    }
private:
};

void init(int argc, char** argv) {
    createApplication(new Chain, "Chain test", 640, 480);
}