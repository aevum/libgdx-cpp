#include <gdx-cpp/Gdx.hpp>
#include "Box2DTest.cpp"
#include "Box2D/Box2D.h"
#include "gdx-cpp/math/MathUtils.hpp"

using namespace gdx_cpp::graphics;
using namespace gdx_cpp;

class ContinuousTest : public Box2DTest {
public:
    int m_stepCount;
    b2Body * m_body;
    float m_angularVelocity;

    void createWorld (b2World& world) {
        m_stepCount = 0;
        m_angularVelocity = 0;
        {          
            b2BodyDef bd;
            bd.position.Set(0, 0);
            b2Body * body = world.CreateBody(&bd);

            b2EdgeShape * shape = new b2EdgeShape();
            shape->Set(b2Vec2(-10, 0), b2Vec2(10, 0));
            body->CreateFixture(shape, 0);
            delete shape;

            b2PolygonShape* poly = new b2PolygonShape;
            poly->SetAsBox(0.2f, 1.0f, b2Vec2(0.5f, 1.0f), 0);
            body->CreateFixture(shape, 0);
            delete poly;
        }

        {
            b2BodyDef bd;
            bd.type = b2_dynamicBody;
            bd.position.Set(0, 20);

            b2PolygonShape * shape = new b2PolygonShape();
            shape->SetAsBox(2, 0.1f);

            m_body = world.CreateBody(&bd);
            m_body->CreateFixture(shape, 1);

            m_angularVelocity = 33.468121f;
            m_body->SetLinearVelocity(b2Vec2(0, -100));
            m_body->SetAngularVelocity(m_angularVelocity);
            delete shape;
        }
    }


    void render () {
        Box2DTest::render();
        m_stepCount++;
        if (m_stepCount % 60 == 0) launch();
    }
private:
    void launch () {
        m_body->SetTransform(b2Vec2(0, 20), 0);
        m_angularVelocity = (float)gdx_cpp::math::utils::random() * 100 - 50;
        m_body->SetLinearVelocity(b2Vec2(0, -100));
        m_body->SetAngularVelocity(m_angularVelocity);
    }

};

void init(int argc, char** argv) {
    createApplication(new ContinuousTest, "ContinuousTest test", 640, 480);
}
