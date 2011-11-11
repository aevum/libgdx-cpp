#include <gdx-cpp/Gdx.hpp>
#include "Box2DTest.cpp"
#include "Box2D/Box2D.h"

using namespace gdx_cpp::graphics;
using namespace gdx_cpp;

class OneSidedPlatform : public Box2DTest {

    class TestContactFilter : public b2ContactFilter{
    public :
        OneSidedPlatform *  plat;
        TestContactFilter(OneSidedPlatform *  _plat):  plat(_plat)
        {
          
        }
        
        bool ShouldCollide (b2Fixture * fixtureA, b2Fixture * fixtureB) {
            if ((fixtureA == plat->m_platform && fixtureB == plat->m_character) || (fixtureA == plat->m_platform && fixtureB == plat->m_character)) {
                const b2Vec2& position = plat->m_character->GetBody()->GetPosition();
                if (position.y < plat->m_top + plat->m_radius - 3.0f * 0.005f)
                    return false;
                else
                    return true;
            } else
                return true;
        }
    };
    enum State {
        Unknown, Above, Below
    };

    b2Fixture * m_platform;
    b2Fixture * m_character;
    float m_bottom;
    float m_top;
    float m_radius;
    State m_state;
public:
    void createWorld (b2World& world) {

        {
            b2BodyDef bd;
            b2Body * ground = world.CreateBody(&bd);

            b2EdgeShape* shape = new b2EdgeShape();
            shape->Set(b2Vec2(-20.0f, 0), b2Vec2(20.0f, 0.f));
            ground->CreateFixture(shape, 0);
            delete shape;
        }

        {
            b2BodyDef bd;
            bd.position.Set(0, 10);
            b2Body * body = world.CreateBody(&bd);

            b2PolygonShape * shape = new b2PolygonShape();
            shape->SetAsBox(3, 0.5f);
            m_platform = body->CreateFixture(shape, 0);
            m_bottom = 10.0f - 0.5f;
            m_top = 10.0f + 0.5f;
        }

        {
            b2BodyDef bd;
            bd.type = b2_dynamicBody;
            bd.position.Set(0, 12);
            b2Body * body = world.CreateBody(&bd);

            m_radius = 0.5f;
            b2CircleShape * shape = new b2CircleShape();
            shape->m_radius = m_radius;
            m_character = body->CreateFixture(shape, 20.0f);
            delete shape;

            m_state = Unknown;
        }

        world.SetContactFilter(new TestContactFilter(this));
    }
private:
};

void init(int argc, char** argv) {
    createApplication(new OneSidedPlatform, "OneSidedPlatform test", 640, 480);
}
