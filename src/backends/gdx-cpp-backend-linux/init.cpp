#include <cassert>
#include <gdx-cpp/ApplicationListener.hpp>
#include <gdx-cpp/Gdx.hpp>
#include "LinuxApplication.hpp"
#include "LinuxSystem.hpp"
#include "Log.hpp"

using namespace gdx;
using namespace gdx::nix;

gdx::ApplicationListener* applicationListener = 0;
int width,height = 0;
std::string title;
bool isUseOpenGLES2;

int main(int argc, char** argv);

extern "C" int default_main(int argc, char** argv) {
    gdx::initializeSystem(new LinuxSystem, new gdx::nix::Log);
    
    gdxcpp_init(argc, argv);

    assert(applicationListener);

    gdx::nix::LinuxApplication app(applicationListener, title, width, height, isUseOpenGLES2);
    app.initialize();

    return 0;
}

gdx_main gdxcpp_main_selector::selector = default_main;

extern "C" void gdxcpp_create_application(gdx::ApplicationListener* listener,
        const std::string& applicationName,
        int p_width, int p_height, bool useOpenGLES2) {
    applicationListener = listener;
    width = p_width;
    height = p_height;
    title = applicationName;
    isUseOpenGLES2 = useOpenGLES2;
}

void deinitialize_system() {
}

int main(int argc, char** argv) {
    atexit(deinitialize_system);
    return gdxcpp_main_selector::selector(argc, argv);
}
