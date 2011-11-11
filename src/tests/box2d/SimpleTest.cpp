#include <gdx-cpp/Gdx.hpp>
#include "Box2DTest.cpp"
#include "Box2D/Box2D.h"
#include "gdx-cpp/math/MathUtils.hpp"

using namespace gdx_cpp::graphics;
using namespace gdx_cpp;

class SimpleTest : public Box2DTest {
public:
    void createWorld (b2World& world) {
        // next we create a static ground platform. This platform
        // is not moveable and will not react to any influences from
        // outside. It will however influence other bodies. First we
        // create a PolygonShape that holds the form of the platform.
        // it will be 100 meters wide and 2 meters high, centered
        // around the origin
        b2PolygonShape * groundPoly = new b2PolygonShape();
        groundPoly->SetAsBox(50, 1);

        // next we create the body for the ground platform. It's
        // simply a static body.
        b2BodyDef groundBodyDef;
        groundBodyDef.type = b2_staticBody;
        groundBody = world.CreateBody(&groundBodyDef);

        // finally we add a fixture to the body using the polygon
        // defined above. Note that we have to dispose PolygonShapes
        // and CircleShapes once they are no longer used. This is the
        // only time you have to care explicitely for memomry managment.
        groundBody->CreateFixture(groundPoly, 10);
        delete groundPoly;

        // next we create 50 boxes at random locations above the ground
        // body. First we create a nice polygon representing a box 2 meters
        // wide and high.
        b2PolygonShape * boxPoly = new b2PolygonShape();
        boxPoly->SetAsBox(1, 1);

        // next we create the 50 box bodies using the PolygonShape we just
        // defined. This process is similar to the one we used for the ground
        // body. Note that we reuse the polygon for each body fixture.
        for (int i = 0; i < 20; i++) {
            // Create the BodyDef, set a random position above the
            // ground and create a new body
            b2BodyDef boxBodyDef;
            boxBodyDef.type = b2_dynamicBody;
            boxBodyDef.position.x = -24 + (float)(gdx_cpp::math::utils::random() * 48);
            boxBodyDef.position.y = 10 + (float)(gdx_cpp::math::utils::random() * 100);
            b2Body * boxBody = world.CreateBody(&boxBodyDef);

            // add the boxPoly shape as a fixture
            boxBody->CreateFixture(boxPoly, 10);
        }

        // we are done, all that's left is disposing the boxPoly
        delete boxPoly;

        // next we add a few more circles
        b2CircleShape * circleShape = new b2CircleShape();
        circleShape->m_radius = 1;

        for (int i = 0; i < 10; i++) {
            b2BodyDef circleBodyDef;
            circleBodyDef.type = b2_dynamicBody;
            circleBodyDef.position.x = -24 + (float)(gdx_cpp::math::utils::random() * 48);
            circleBodyDef.position.y = 10 + (float)(gdx_cpp::math::utils::random() * 100);
            b2Body * circleBody = world.CreateBody(&circleBodyDef);

            // add the boxPoly shape as a fixture
            circleBody->CreateFixture(circleShape, 10);
        }
        delete circleShape;
    }
private:
};

void init(int argc, char** argv) {
    createApplication(new SimpleTest, "SimpleTest test", 640, 480);
}
