#include <gdx-cpp/Gdx.hpp>
#include "Box2DTest.cpp"
#include "Box2D/Box2D.h"
#include "gdx-cpp/math/MathUtils.hpp"

using namespace gdx_cpp::graphics;
using namespace gdx_cpp;

class DebugRendererTest : public Box2DTest {
public:
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

        {
            b2PolygonShape * shape = new b2PolygonShape();
            shape->SetAsBox(1, 2.f);

            b2BodyDef def;
            def.position.y = 10;
            def.angle = (float)gdx_cpp::math::utils::toRadians(90);
            def.type = b2_dynamicBody;

            b2Body * body = world.CreateBody(&def);
            body->CreateFixture(shape, 1);

            def = b2BodyDef();
            def.position.x = 10;
            def.position.y = 10;
            def.angle = 0;
            def.type = b2_dynamicBody;

            body = world.CreateBody(&def);
            body->CreateFixture(shape, 1);

            delete shape;
        }
    }
private:
};

void init(int argc, char** argv) {
    createApplication(new DebugRendererTest, "DebugRendererTest test", 640, 480);
}
