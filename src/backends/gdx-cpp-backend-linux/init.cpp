#include <cassert>
#include <gdx-cpp/ApplicationListener.hpp>
#include <gdx-cpp/Gdx.hpp>
#include "LinuxApplication.hpp"
#include "LinuxSystem.hpp"

using namespace gdx_cpp;
using namespace gdx_cpp::backends::nix;

gdx_cpp::ApplicationListener* applicationListener = 0;
int width,height = 0;
std::string title;

int main(int argc, char** argv);

int default_main(int argc, char** argv) {
    Gdx::initializeSystem(new LinuxSystem);
    
    init(argc, argv);
    
    assert(applicationListener);
    
    gdx_cpp::backends::nix::LinuxApplication app(applicationListener, title, width, height, false);
    app.initialize();

    return 0;   
}

gdx_main main_selector::selector = default_main;

void createApplication(gdx_cpp::ApplicationListener* listener, const std::string& applicationName, int p_width, int p_height) {
    applicationListener = listener;
    width = p_width;
    height = p_height;
    title = applicationName;
}

int main(int argc, char** argv) {
    return main_selector::selector(argc, argv);
}
