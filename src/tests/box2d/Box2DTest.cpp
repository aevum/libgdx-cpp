#include <gdx-cpp/Application.hpp>
#include "gdx-cpp/InputProcessor.hpp"
#include <gdx-cpp/Gdx.hpp>
#include <gdx-cpp/graphics/GL10.hpp>
#include <gdx-cpp/ApplicationListener.hpp>
#include "Box2D/Box2D.h"
#include <gdx-cpp/graphics/g2d/SpriteBatch.hpp>
// #include <gdx-cpp/graphics/g2d/BitmapFont.hpp>
#include <gdx-cpp/graphics/OrthographicCamera.hpp>
#include "gdx-cpp/physics/box2d/Box2DDebugRenderer.hpp"
#include <gdx-cpp/implementation/System.hpp>
#include <gdx-cpp/Graphics.hpp>
#include <iostream>
#include "gdx-cpp/Input.hpp"
#include <gdx-cpp/graphics/FPSLogger.hpp>

using namespace gdx_cpp;
using namespace gdx_cpp::graphics;
using namespace gdx_cpp::graphics::g2d;

class Box2DTest : public ApplicationListener, public InputProcessor {

public:

    class QueryCallbackTest : public b2QueryCallback {
    public:
        Box2DTest * box2d;

        QueryCallbackTest(Box2DTest * _box2d) {
            box2d = _box2d;
        }

        bool ReportFixture (b2Fixture * fixture) {
            // if the hit point is inside the fixture of the body
            // we report it
            if (fixture->TestPoint(b2Vec2(box2d->testPoint.x, box2d->testPoint.y))) {
                box2d->hitBody = fixture->GetBody();
                return false;
            } else
                return true;
        }
    };

  Box2DTest()
  {
    callback = new QueryCallbackTest(this);
  }
    
    void render () {
        logger.log();
        // update the world with a fixed time step
        long startTime = gdx_cpp::Gdx::system->nanoTime();
        world->Step(gdx_cpp::Gdx::app->getGraphics()->getDeltaTime(), 3, 3);
        float updateTime = (gdx_cpp::Gdx::system->nanoTime() - startTime) / 1000000000.0f;

        startTime = gdx_cpp::Gdx::system->nanoTime();
        // clear the screen and setup the projection matrix
        gdx_cpp::graphics::GL10 * gl = Gdx::app->getGraphics()->getGL10();
        gl->glClear(gdx_cpp::graphics::GL10::GL_COLOR_BUFFER_BIT);
        camera->update();
        camera->apply(*gl);

        // render the world using the debug renderer
        renderer->render(*world, camera->combined);
        
        float renderTime = (gdx_cpp::Gdx::system->nanoTime() - startTime) / 1000000000.0f;

    }


    void create () {
        // setup the camera. In Box2D we operate on a
        // meter scale, pixels won't do it. So we use
        // an orthographic camera with a viewport of
        // 48 meters in width and 32 meters in height.
        // We also position the camera so that it
        // looks at (0,16) (that's where the middle of the
        // screen will be located).
        camera = new OrthographicCamera(48, 32);
        camera->position.set(0, 15, 0);

        // create the debug renderer
        renderer = new gdx_cpp::physics::box2d::Box2DDebugRenderer();

        // create the world
        world = new b2World(b2Vec2(0, -10));
        world->SetAllowSleeping(true);
        
        // we also need an invisible zero size ground body
        // to which we can connect the mouse joint
        b2BodyDef bodyDef;
        groundBody = world->CreateBody(&bodyDef);

        // call abstract method to populate the world
        createWorld(*world);
        gdx_cpp::Gdx::input->setInputProcessor(this);

        batch = new SpriteBatch();
//         font = new BitmapFont();
    }


    void dispose () {
        renderer->dispose();
        delete world;
        delete renderer;
        renderer = NULL;
        delete world;
        world = NULL;
        delete mouseJoint;
        mouseJoint = NULL;
//         delete hitBody;
        hitBody = NULL;
    }


    virtual bool keyDown (int keycode) {
        return false;
    }


    bool keyTyped (char character) {
        return false;
    }


    bool keyUp (int keycode) {
        return false;
    }

    bool touchDown (int x, int y, int pointer, int button) {
        Gdx::app->log("Box2DTest", "touchdown x: %d, y: %d, button %d", x, y, button);
        // translate the mouse coordinates to world coordinates
        testPoint.set(x, y, 0);
        camera->unproject(testPoint);

        Gdx::app->log("Box2DTest", "unprojected x: %f y: %f", testPoint.x, testPoint.y);
        
        // ask the world which bodies are within the given
        // bounding box around the mouse pointer
        hitBody = NULL;
        b2AABB aabb;
        aabb.lowerBound = b2Vec2( testPoint.x - 0.0001f, testPoint.y - 0.0001f );
        aabb.upperBound = b2Vec2( testPoint.x + 0.0001f, testPoint.y + 0.0001f );
        world->QueryAABB(callback, aabb);

        if (hitBody == groundBody) hitBody = NULL;

        // ignore kinematic bodies, they don't work with the mouse joint
        if (hitBody != NULL && hitBody->GetType() == b2_kinematicBody) return false;

        // if we hit something we create a new mouse joint
        // and attach it to the hit body.
        if (hitBody != NULL) {
            b2MouseJointDef def;
            def.bodyA = groundBody;
            def.bodyB = hitBody;
            def.collideConnected = true;
            def.target.Set(testPoint.x, testPoint.y);
            def.maxForce = 1000.0f * hitBody->GetMass();

            mouseJoint = (b2MouseJoint *)world->CreateJoint(&def);
            
            hitBody->SetAwake(true);
        }

        return false;
    }


    bool touchDragged (int x, int y, int pointer) {
        // if a mouse joint exists we simply update
        // the target of the joint based on the new
        // mouse coordinates
        if (mouseJoint != NULL) {
            camera->unproject(testPoint.set(x, y, 0));
            target.Set(testPoint.x, testPoint.y);
            mouseJoint->SetTarget(target);
        }
        return false;
    }


    bool touchUp (int x, int y, int pointer, int button) {
        // if a mouse joint exists we simply destroy it
        if (mouseJoint != NULL) {
            world->DestroyJoint(mouseJoint);
            mouseJoint = NULL;
        }
        return false;
    }


    bool touchMoved (int x, int y) {
        return false;
    }


    bool scrolled (int amount) {
        return false;
    }

    void pause () {

    }

    void resume () {

    }

    void resize (int width, int height) {

    }

    SpriteBatch * batch;
//     BitmapFont * font;
    b2Vec2 target;
    gdx_cpp::math::Vector3 testPoint;

    QueryCallbackTest * callback;
        
protected:
    virtual void createWorld (b2World& world) = 0;
    FPSLogger logger;
    OrthographicCamera * camera;
    gdx_cpp::physics::box2d::Box2DDebugRenderer * renderer;
    b2World * world;
    b2Body  * groundBody;
    b2MouseJoint * mouseJoint;
    b2Body * hitBody;
    b2Vec2 tmp;

private:
  
};
