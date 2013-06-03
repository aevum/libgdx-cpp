#include <gdx-cpp/Gdx.hpp>
#include <stdlib.h>
#include <cassert>
#include <string>

#include "EmscriptenApplication.hpp"
#include "EmscriptenSystem.hpp"
#include "Log.hpp"
#include "gdx-cpp/backend.hpp"

namespace gdx {
class ApplicationListener;
}  // namespace gdx

using namespace gdx;
using namespace gdx::scripten;

gdx::ApplicationListener* applicationListener = nullptr;
gdx::scripten::EmscriptenApplication* g_application = nullptr;

int width,height = 0;
std::string title;
bool isUseOpenGLES2;

int main(int argc, char** argv);

extern "C" int default_main(int argc, char** argv) {
    gdx::initializeSystem(new EmscriptenSystem, new gdx::scripten::Log);
    
    gdxcpp_init(argc, argv);

    assert(applicationListener);

    g_application = new EmscriptenApplication(applicationListener, title, width, height, isUseOpenGLES2);
    g_application->initialize();

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
    isUseOpenGLES2 = true;
}

void deinitialize_system() {
}

int main(int argc, char** argv) {
    atexit(deinitialize_system);
    return gdxcpp_main_selector::selector(argc, argv);
}
