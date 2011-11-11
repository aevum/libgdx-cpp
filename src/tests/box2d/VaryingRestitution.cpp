#include <gdx-cpp/Gdx.hpp>
#include "Box2DTest.cpp"
#include "Box2D/Box2D.h"

using namespace gdx_cpp::graphics;
using namespace gdx_cpp;

class VaryingRestitution : public Box2DTest {
public:
    void createWorld (b2World& world) {
        {
            b2BodyDef bd;
            b2Body * ground = world.CreateBody(&bd);

            b2EdgeShape* shape = new b2EdgeShape();
            shape->Set(b2Vec2(-40, 0), b2Vec2(40, 0));
            ground->CreateFixture(shape, 0.0f);
            delete shape;
        }

        {
            b2CircleShape * shape = new b2CircleShape();
            shape->m_radius = 1;

            b2FixtureDef fd;
            fd.shape = shape;
            fd.density = 1.0f;

            const int length = 7;
            float restitution[length] = {0, 0.1f, 0.3f, 0.5f, 0.75f, 0.9f, 1.0f};
            
            for (int i = 0; i < length; i++) {
                b2BodyDef bd;
                bd.type = b2_dynamicBody;
                bd.position.Set(-10.0f + 3.0f * i, 20.0f);

                b2Body * body = world.CreateBody(&bd);
                fd.restitution = restitution[i];
                body->CreateFixture(&fd);
            }

            delete shape;
        }
    }
private:
};

void init(int argc, char** argv) {
    createApplication(new VaryingRestitution, "VaryingRestitution test", 640, 480);
}
