#include <gdx-cpp/Application.hpp>
#include "gdx-cpp/InputProcessor.hpp"
#include <gdx-cpp/Gdx.hpp>
#include <gdx-cpp/graphics/GL10.hpp>
#include <gdx-cpp/ApplicationListener.hpp>
#include "Box2D/Box2D.h"
#include <gdx-cpp/graphics/g2d/SpriteBatch.hpp>
#include <gdx-cpp/graphics/g2d/BitmapFont.hpp>
#include <gdx-cpp/graphics/OrthographicCamera.hpp>

using namespace gdx_cpp;
using namespace gdx_cpp::graphics;
using namespace gdx_cpp::graphics::g2d;

class Box2DTest : public ApplicationListener, InputProcessor {

public:

    class QueryCallbackTest : public b2QueryCallback {
        Box2DTest * box2d;

        QueryCallbackTest(Box2DTest * _box2d) {
            box2d = _box2d;
        }

        bool reportFixture (b2Fixture * fixture) {
            // if the hit point is inside the fixture of the body
            // we report it
            if (fixture->testPoint(box2d->testPoint.x, box2d->testPoint.y)) {
                box2d->hitBody = fixture->getBody();
                return false;
            } else
                return true;
        }
    };

    void render () {
        // update the world with a fixed time step
        long startTime = System.nanoTime();
        world.step(Gdx.app.getGraphics().getDeltaTime(), 3, 3);
        float updateTime = (System.nanoTime() - startTime) / 1000000000.0f;

        startTime = System.nanoTime();
        // clear the screen and setup the projection matrix
        GL10 gl = Gdx::app->getGraphics()->getGL10();
        gl.glClear(GL10.GL_COLOR_BUFFER_BIT);
        camera.update();
        camera.apply(gl);

        // render the world using the debug renderer
        renderer.render(world);
        float renderTime = (System.nanoTime() - startTime) / 1000000000.0f;

        batch.begin();
        font.draw(batch, "fps:" + Gdx.graphics.getFramesPerSecond() + ", update: " + updateTime + ", render: " + renderTime, 0, 20);
        batch.end();
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
        camera.position.set(0, 15, 0);

        // create the debug renderer
        renderer = new Box2DDebugRenderer();

        // create the world
        world = new World(new Vector2(0, -10), true);

        // we also need an invisible zero size ground body
        // to which we can connect the mouse joint
        BodyDef bodyDef = new BodyDef();
        groundBody = world.createBody(bodyDef);

        // call abstract method to populate the world
        createWorld(world);

        batch = new SpriteBatch();
        font = new BitmapFont();
    }


    void dispose () {
        renderer.dispose();
        world.dispose();

        renderer = null;
        world = null;
        mouseJoint = null;
        hitBody = null;
    }


    bool keyDown (int keycode) {
        return false;
    }


    bool keyTyped (char character) {
        return false;
    }


    bool keyUp (int keycode) {
        return false;
    }

    bool touchDown (int x, int y, int pointer, int button) {
        // translate the mouse coordinates to world coordinates
        camera.unproject(testPoint.set(x, y, 0));
        // ask the world which bodies are within the given
        // bounding box around the mouse pointer
        hitBody = null;
        world.QueryAABB(callback, testPoint.x - 0.0001f, testPoint.y - 0.0001f, testPoint.x + 0.0001f, testPoint.y + 0.0001f);

        if (hitBody == groundBody) hitBody = null;

        // ignore kinematic bodies, they don't work with the mouse joint
        if (hitBody != null && hitBody.getType() == BodyType.KinematicBody) return false;

        // if we hit something we create a new mouse joint
        // and attach it to the hit body.
        if (hitBody != null) {
            MouseJointDef def = new MouseJointDef();
            def.bodyA = groundBody;
            def.bodyB = hitBody;
            def.collideConnected = true;
            def.target.set(testPoint.x, testPoint.y);
            def.maxForce = 1000.0f * hitBody.getMass();

            mouseJoint = (MouseJoint)world.createJoint(def);
            hitBody.setAwake(true);
        }

        return false;
    }


    bool touchDragged (int x, int y, int pointer) {
        // if a mouse joint exists we simply update
        // the target of the joint based on the new
        // mouse coordinates
        if (mouseJoint != null) {
            camera.unproject(testPoint.set(x, y, 0));
            mouseJoint.setTarget(target.set(testPoint.x, testPoint.y));
        }
        return false;
    }


    bool touchUp (int x, int y, int pointer, int button) {
        // if a mouse joint exists we simply destroy it
        if (mouseJoint != null) {
            world.destroyJoint(mouseJoint);
            mouseJoint = null;
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
    BitmapFont * font;
    b2Vec2 target;
    b2Vec3 testPoint;

    QueryCallbackTest * callback = new QueryCallbackTest;
protected:
    virtual void createWorld (World world) = 0;

    OrthographicCamera * camera;
    Box2DDebugRenderer * renderer;
    b2World * world;
    b2Body  * groundBody;
    b2MouseJoint * mouseJoint;
    b2Body * hitBody;
    b2Vec2 tmp;

private:
  
};

