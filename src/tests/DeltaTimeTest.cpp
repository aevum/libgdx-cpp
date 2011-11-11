#include <gdx-cpp/Gdx.hpp>
#include <gdx-cpp/Application.hpp>
#include <gdx-cpp/ApplicationListener.hpp>
#include <gdx-cpp/graphics/Mesh.hpp>
#include <gdx-cpp/graphics/GL10.hpp>
#include <gdx-cpp/graphics/Texture.hpp>
#include <gdx-cpp/graphics/g2d/SpriteBatch.hpp>

using namespace gdx_cpp::graphics::g2d;
using namespace gdx_cpp::graphics;
using namespace gdx_cpp;

class DeltaTimeTest : public gdx_cpp::ApplicationListener {
public:
    DeltaTimeTest() {
    }
    
    void create() {
        lastFrameTime = Gdx::system->nanoTime();
    }
    
    void dispose() {
    }
    
    void pause() {
    }
    
    void render() {
        long frameTime = Gdx::system->nanoTime();
        float deltaTime = (frameTime - lastFrameTime) / 1000000000.0f;
        lastFrameTime = frameTime;
        
        Gdx::app->log("DeltaTimeTest", "delta: %f, gdx delta: %f" , deltaTime , Gdx::graphics->getDeltaTime());
    }
    
    void resize(int width, int height) {
    }
    
    void resume() {
    }
private:
    uint64_t lastFrameTime;
};

void init(int argc, char** argv) {
    createApplication(new DeltaTimeTest, "Delta Time Test", 640, 480);
}