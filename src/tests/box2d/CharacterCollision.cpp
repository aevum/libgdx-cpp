#include <gdx-cpp/Gdx.hpp>
#include "Box2DTest.cpp"
#include "Box2D/Box2D.h"
#include "gdx-cpp/math/MathUtils.hpp"
#include <cmath>

using namespace gdx_cpp::graphics;
using namespace gdx_cpp;

class CharacterCollision : public Box2DTest {
public:
    void createWorld (b2World& world) {
        {
            b2BodyDef bd;
            b2Body * ground = world.CreateBody(&bd);

            b2EdgeShape * shape = new b2EdgeShape();
            shape->Set(b2Vec2(-20, 0), b2Vec2(20, 0));
            ground->CreateFixture(shape, 0);
            delete shape;
        }

        {
            b2BodyDef bd;
            b2Body * ground = world.CreateBody(&bd);

            b2EdgeShape * shape = new b2EdgeShape();
            shape->m_radius = 0;
            shape->Set(b2Vec2(-8, 1), b2Vec2(-6, 1));
            ground->CreateFixture(shape, 0);
            shape->Set(b2Vec2(-6, 1), b2Vec2(-4, 1));
            ground->CreateFixture(shape, 0);
            shape->Set(b2Vec2(-4, 1), b2Vec2(-2, 1));
            ground->CreateFixture(shape, 0);
            delete shape;
        }

        {
            b2BodyDef bd;
            b2Body * ground = world.CreateBody(&bd);

            b2PolygonShape * shape = new b2PolygonShape();
            shape->SetAsBox(1, 1, b2Vec2(4, 3), 0);
            ground->CreateFixture(shape, 0);
            shape->SetAsBox(1, 1, b2Vec2(6, 3), 0);
            ground->CreateFixture(shape, 0);
            shape->SetAsBox(1, 1, b2Vec2(8, 3), 0);
            ground->CreateFixture(shape, 0);
            delete shape;
        }

        {
            b2BodyDef bd;
            b2Body * ground = world.CreateBody(&bd);

            b2EdgeShape * shape = new b2EdgeShape();
            float d = 2 * 2 * 0.005f;
            shape->m_radius = 0;
            shape->Set(b2Vec2(-1 + d, 3), b2Vec2(1 - d, 3));
            ground->CreateFixture(shape, 0);
            shape->Set(b2Vec2(1, 3 + d), b2Vec2(1, 5 - d));
            ground->CreateFixture(shape, 0);
            shape->Set(b2Vec2(1 - d, 5), b2Vec2(-1 + d, 5));
            ground->CreateFixture(shape, 0);
            shape->Set(b2Vec2(-1, 5 - d), b2Vec2(-1, 3 + d));
            ground->CreateFixture(shape, 0);
            delete shape;
        }

        {
            b2BodyDef bd;
            bd.position.Set(-3, 5);
            bd.type = b2_dynamicBody;
            bd.fixedRotation = true;
            bd.allowSleep = false;

            b2Body * body = world.CreateBody(&bd);

            b2PolygonShape * shape = new b2PolygonShape();
            shape->SetAsBox(0.5f, 0.5f);

            b2FixtureDef fd ;
            fd.shape = shape;
            fd.density = 20.0f;
            body->CreateFixture(&fd);
            delete shape;
        }

        {
            b2BodyDef bd;
            bd.position.Set(-5, 5);
            bd.type = b2_dynamicBody;
            bd.fixedRotation = true;
            bd.allowSleep = false;

            b2Body * body = world.CreateBody(&bd);

            float angle = 0;
            float delta = (float)gdx_cpp::math::utils::detail::PI / 3;
            b2Vec2 vertices[6];
            for (int i = 0; i < 6; i++) {
                vertices[i].Set(0.5f * (float)std::cos(angle), 0.5f * (float)std::sin(angle));
                angle += delta;
            }

            b2PolygonShape * shape = new b2PolygonShape();
            shape->Set(vertices, 6);

            b2FixtureDef fd ;
            fd.shape = shape;
            fd.density = 20.0f;
            body->CreateFixture(&fd);
            delete shape;
        }

        {
            b2BodyDef bd;
            bd.position.Set(3, 5);
            bd.type = b2_dynamicBody;
            bd.fixedRotation = true;
            bd.allowSleep = false;

            b2Body * body = world.CreateBody(&bd);

            b2CircleShape * shape = new b2CircleShape();
            shape->m_radius = 0.5f;

            b2FixtureDef fd ;
            fd.shape = shape;
            fd.density = 20.0f;
            body->CreateFixture(&fd);
            delete shape;
        }
    }
private:
};

void init(int argc, char** argv) {
    createApplication(new CharacterCollision, "CharacterCollision test", 640, 480);
}
