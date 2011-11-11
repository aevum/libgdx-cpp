#include <gdx-cpp/Gdx.hpp>
#include "Box2DTest.cpp"
#include "Box2D/Box2D.h"

using namespace gdx_cpp::graphics;
using namespace gdx_cpp;

class VerticalStack : public Box2DTest {
public:
    const static int e_columnCount = 5;
    const static int e_rowCount = 16;

    b2Body * m_bullet;
    b2Body * m_bodies[e_rowCount * e_columnCount];
    int m_indices[e_rowCount * e_columnCount];

    void createWorld (b2World& world) {
        {
            b2BodyDef bd;
            b2Body * ground = world.CreateBody(&bd);

            b2EdgeShape* shape = new b2EdgeShape();
            shape->Set(b2Vec2(-40, 0), b2Vec2(40, 0));
            ground->CreateFixture(shape, 0.0f);

            shape->Set(b2Vec2(20, 0), b2Vec2(20, 20));
            ground->CreateFixture(shape, 0);
            delete shape;
        }

        float xs[e_columnCount] = {0, -10, -5, 5, 10};

        for (int j = 0; j < e_columnCount; j++) {
            b2PolygonShape * shape = new b2PolygonShape();
            shape->SetAsBox(0.5f, 0.5f);

            b2FixtureDef fd;
            fd.shape = shape;
            fd.density = 1.0f;
            fd.friction = 0.3f;

            for (int i = 0; i < e_rowCount; i++) {
                b2BodyDef bd;
                bd.type = b2_dynamicBody;

                int n = j * e_rowCount + i;
                m_indices[n] = n;

                float x = 0;
                bd.position.Set(xs[j] + x, 0.752f + 1.54f * i);
                b2Body * body = world.CreateBody(&bd);
                body->SetUserData((void *)n);

                m_bodies[n] = body;
                body->CreateFixture(&fd);
            }

            delete shape;
        }

        m_bullet = NULL;
    }

    bool keyDown (int keyCode) {
        if (keyCode == gdx_cpp::Input::Keys::COMMA) {
            if (m_bullet != NULL) {
                world->DestroyBody(m_bullet);
                m_bullet = NULL;
            }

            {
                b2CircleShape * shape = new b2CircleShape();
                shape->m_radius = 0.25f;

                b2FixtureDef fd;
                fd.shape = shape;
                fd.density = 20.0f;
                fd.restitution = 0.05f;

                b2BodyDef bd;
                bd.type = b2_dynamicBody;
                bd.bullet = true;
                bd.position.Set(-31, 5);

                m_bullet = world->CreateBody(&bd);
                m_bullet->CreateFixture(&fd);

                m_bullet->SetLinearVelocity(b2Vec2(400, 0));
            }
        }

        return false;
    }

    void render () {
        Box2DTest::render();

//         if (renderer.batch != null) {
        renderer->batch.begin();
// renderer.batch.drawText(renderer.font, "Press: (,) to launch a bullet", 0, Gdx.app.getGraphics().getHeight(),
// Color.WHITE);
        renderer->batch.end();
//         }
    }
private:
};

void init(int argc, char** argv) {
    createApplication(new VerticalStack, "VerticalStack test", 640, 480);
}
