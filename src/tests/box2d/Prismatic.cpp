#include <gdx-cpp/Gdx.hpp>
#include "Box2DTest.cpp"
#include "Box2D/Box2D.h"
#include "gdx-cpp/math/MathUtils.hpp"
#include "gdx-cpp/Input.hpp"

using namespace gdx_cpp::graphics;
using namespace gdx_cpp;

class Prismatic : public Box2DTest {
public:
    b2PrismaticJoint * m_joint;
    void createWorld (b2World& world) {
        b2Body * ground;

        {
            b2BodyDef bd;
            ground = world.CreateBody(&bd);
            b2EdgeShape* shape = new b2EdgeShape();
            shape->Set(b2Vec2(-40, 0), b2Vec2(40, 0));
            ground->CreateFixture(shape, 0);
            delete shape;
        }

        {
            b2PolygonShape * shape = new b2PolygonShape();
            shape->SetAsBox(2, 5);

            b2BodyDef bd;
            bd.type = b2_dynamicBody;
            bd.position.Set(-10, 10);
            bd.angle = 0.5f * (float)gdx_cpp::math::utils::detail::PI;
            bd.allowSleep = false;

            b2Body * body = world.CreateBody(&bd);
            body->CreateFixture(shape, 5.0f);

            b2PrismaticJointDef pjd;

            b2Vec2 axis(2, 1);
            axis.Normalize();
            pjd.Initialize(ground, body, b2Vec2(0, 0), axis);

            pjd.motorSpeed = 10.0f;
            pjd.maxMotorForce = 10000.0f;
            pjd.enableMotor = true;
            pjd.lowerTranslation = 0;
            pjd.upperTranslation = 20.0f;
            pjd.enableLimit = true;

            m_joint = (b2PrismaticJoint *)world.CreateJoint(&pjd);
        }
    }
    bool keyDown (int keyCode) {
        if (keyCode == gdx_cpp::Input::Keys::L) m_joint->EnableLimit(!m_joint->IsLimitEnabled());
        if (keyCode == gdx_cpp::Input::Keys::M) m_joint->EnableMotor(!m_joint->IsMotorEnabled());
        if (keyCode == gdx_cpp::Input::Keys::S) m_joint->SetMotorSpeed(-m_joint->GetMotorSpeed());

        return false;

    }

    void render () {
        Box2DTest::render();

//         if (renderer->batch != NULL) {
            renderer->batch.begin();
// renderer.batch.drawText(renderer.font, "Keys: (l) limits, (m) motors, (s) speed", 0, Gdx.app.getGraphics().getHeight(),
// Color.WHITE);
// renderer.batch.drawText(renderer.font, "Motor Force = " + m_joint.getMotorForce(), 0,
// Gdx.app.getGraphics().getHeight() - 15, Color.WHITE);
            renderer->batch.end();
//         }
    }

private:
};

void init(int argc, char** argv) {
    createApplication(new Prismatic, "Prismatic test", 640, 480);
}
