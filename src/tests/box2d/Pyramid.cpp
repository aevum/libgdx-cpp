#include <gdx-cpp/Gdx.hpp>
#include "Box2DTest.cpp"
#include "Box2D/Box2D.h"

using namespace gdx_cpp::graphics;
using namespace gdx_cpp;

class Pyramid : public Box2DTest {
public:
    void createWorld (b2World& world) {
        {
            b2BodyDef bd ;
            b2Body * ground = world.CreateBody(&bd);

            b2EdgeShape* shape = new b2EdgeShape();
            shape->Set(b2Vec2(-40, 0), b2Vec2(40, 0));
            ground->CreateFixture(shape, 0.0f);
            delete shape;
        }

        {
            float a = 0.5f;
            b2PolygonShape * shape = new b2PolygonShape();
            shape->SetAsBox(a, a);

            b2Vec2 x(-7.0f, 0.75f);
            b2Vec2 y;
            b2Vec2 deltaX (0.5625f, 1.25f);
            b2Vec2 deltaY(1.125f, 0.0f);

            for (int i = 0; i < 20; i++) {
                y = x;

                for (int j = i; j < 20; j++) {
                    b2BodyDef bd;
                    bd.type = b2_dynamicBody;
                    bd.position.Set(y.x, y.y);
                    b2Body * body = world.CreateBody(&bd);
                    body->CreateFixture(shape, 5.0f);

                   y = y + deltaY;
                }

                x = x + deltaX;
            }

        }
    }
private:
};

void init(int argc, char** argv) {
    createApplication(new Pyramid, "Pyramid test", 640, 480);
}
