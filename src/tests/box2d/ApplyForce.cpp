#include <gdx-cpp/Gdx.hpp>
#include "Box2DTest.cpp"
#include "Box2D/Box2D.h"
#include "gdx-cpp/math/MathUtils.hpp"
#include <cmath>

using namespace gdx_cpp::graphics;
using namespace gdx_cpp;

class ApplyForce : public Box2DTest {
public:
    void createWorld (b2World& world) {
        world.SetGravity(b2Vec2(0, 0));

        float k_restitution = 0.4f;
        b2Body * ground;

        {
            b2BodyDef bd;
            bd.position.Set(0, 20);
            ground = world.CreateBody(&bd);

            b2EdgeShape * shape = new b2EdgeShape;

            b2FixtureDef sd;
            sd.shape = shape;
            sd.density = 0;
            sd.restitution = k_restitution;
            
            shape->Set(b2Vec2(-20, -20), b2Vec2(-20, 20));
            ground->CreateFixture(&sd);

            shape->Set(b2Vec2(20, -20), b2Vec2(20, 20));
            ground->CreateFixture(&sd);

            shape->Set(b2Vec2(-20, 20), b2Vec2(20, 20));
            ground->CreateFixture(&sd);

            shape->Set(b2Vec2(-20, -20), b2Vec2(20, -20));
            ground->CreateFixture(&sd);

            delete shape;
        }

        {
            b2Transform xf1;
            xf1.Set(b2Vec2(0,0), 0.3524f * (float)gdx_cpp::math::utils::detail::PI);
            
            xf1.p = b2Mul(xf1, b2Vec2(1, 0));

            b2Vec2 vertices[3];
            vertices[0] = b2Mul(xf1, b2Vec2(-1, 0));
            vertices[1] = b2Mul(xf1, b2Vec2(1, 0));
            vertices[2] = b2Mul(xf1, b2Vec2(0, 0.5f));

            b2PolygonShape * poly1 = new b2PolygonShape();
            poly1->Set(&vertices[0] , 3);

            b2FixtureDef sd1;
            sd1.shape = poly1;
            sd1.density = 4.0f;

            b2Transform xf2;
            xf2.Set(b2Vec2(), -0.3524f * (float)gdx_cpp::math::utils::detail::PI);
            xf2.p = b2Mul(xf2, b2Vec2(-1, 0));

            vertices[0] = b2Mul(xf2, b2Vec2(-1, 0));
            vertices[1] = b2Mul(xf2, b2Vec2(1, 0));
            vertices[2] = b2Mul(xf2, b2Vec2(0, 0.5f));

            b2PolygonShape * poly2 = new b2PolygonShape();
            poly2->Set(&vertices[0], 3);

            b2FixtureDef sd2;
            sd2.shape = poly2;
            sd2.density = 2.0f;

            b2BodyDef bd;
            bd.type = b2_dynamicBody;
            bd.angularDamping = 5.0f;
            bd.linearDamping = 0.1f;

            bd.position.Set(0, 2);
            bd.angle = (float)gdx_cpp::math::utils::detail::PI;
            bd.allowSleep = false;
            m_body = world.CreateBody(&bd);
            m_body->CreateFixture(&sd1);
            m_body->CreateFixture(&sd2);
            delete poly1;
            delete poly2;
        }

        {
            b2PolygonShape * shape = new b2PolygonShape();
            shape->SetAsBox(0.5f, 0.5f);

            b2FixtureDef fd;
            fd.shape = shape;
            fd.density = 1.0f;
            fd.friction = 0.3f;

            for (int i = 0; i < 10; i++) {
                b2BodyDef bd;
                bd.type = b2_dynamicBody;

                bd.position.Set(0, 5 + 1.54f * i);
                b2Body * body = world.CreateBody(&bd);

                body->CreateFixture(&fd);

                float gravity = 10.0f;
                float I = body->GetInertia();
                float mass = body->GetMass();

                float radius = (float)std::sqrt(2 * I / mass);

                b2FrictionJointDef jd;
                jd.localAnchorA.Set(0, 0);
                jd.localAnchorB.Set(0, 0);
                jd.bodyA = ground;
                jd.bodyB = body;
                jd.collideConnected = true;
                jd.maxForce = mass * gravity;
                jd.maxTorque = mass * radius * gravity;

                world.CreateJoint(&jd);
            }

            delete shape;
        }
    }


    bool keyDown (int keyCode) {
        if (keyCode == gdx_cpp::Input::Keys::W) {
            b2Vec2 f = m_body->GetWorldVector(b2Vec2(0, -200));
            b2Vec2 p = m_body->GetWorldPoint(b2Vec2(0, 2));
            m_body->ApplyForce(f, p);
        }
        if (keyCode == gdx_cpp::Input::Keys::A) m_body->ApplyTorque(50);
        if (keyCode == gdx_cpp::Input::Keys::D) m_body->ApplyTorque(-50);

        return false;
    }

    void render () {
        Box2DTest::render();

//         if (renderer->batch != NULL) {
            renderer->batch.begin();
            // renderer.batch.drawText(renderer.font, "Keys (w), (a), (d) to fly", 0, Gdx.app.getGraphics().getHeight(), Color.WHITE);
            renderer->batch.end();
//         }
    }


    b2Body * m_body;
private:

};

void init(int argc, char** argv) {
    createApplication(new ApplyForce, "ApplyForce test", 640, 480);
}
