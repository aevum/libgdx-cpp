#include <gdx-cpp/Gdx.hpp>
#include "Box2DTest.cpp"
#include "Box2D/Box2D.h"

using namespace gdx_cpp::graphics;
using namespace gdx_cpp;

class ShepereStack : public Box2DTest {
public:
  const static int e_count = 10;
    void createWorld (b2World& world) {
        {
            b2BodyDef bd;
            b2Body * ground = world.CreateBody(&bd);

            b2EdgeShape* shape = new b2EdgeShape();
            shape->Set(b2Vec2(-40, 0), b2Vec2(40, 0));
            ground->CreateFixture(shape, 0);
            delete shape;
        }

        {
            b2CircleShape * shape = new b2CircleShape();
            shape->m_radius = 1.0f;

            for (int i = 0; i < e_count; i++) {
                b2BodyDef bd;
                bd.type = b2_dynamicBody;
                bd.position.Set(0, 4.0f + 3.0f * i);
                b2Body * body = world.CreateBody(&bd);
                body->CreateFixture(shape, 1.0f);
            }

            delete shape;
        }
    }
private:
};

void init(int argc, char** argv) {
    createApplication(new ShepereStack, "ShepereStack test", 640, 480);
}
