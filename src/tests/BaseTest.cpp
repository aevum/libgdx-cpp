#include <gdx-cpp/Gdx.hpp>
#include <gdx-cpp/Application.hpp>
#include <gdx-cpp/ApplicationListener.hpp>
#include <gdx-cpp/graphics/Mesh.hpp>
#include <gdx-cpp/graphics/GL10.hpp>

using namespace gdx_cpp::graphics;
using namespace gdx_cpp;

class BaseApplication : public gdx_cpp::ApplicationListener {
public:
    BaseApplication() {

    }
    
    void create() {
    }
    
    void dispose() {
    }
    
    void pause() {
    }
    
    void render() {
    }

    void resize(int width, int height) {
    }
    
    void resume() {
    }
private:
};

void init(int argc, char** argv) {
    createApplication(new BaseApplication, "Base App", 640, 480);
}