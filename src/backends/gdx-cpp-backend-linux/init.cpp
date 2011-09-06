#include "init.hpp"

#include "LinuxSystem.hpp"
#include <cassert>

#include <gdx-cpp/Gdx.hpp>
#include "LinuxApplication.hpp"

using namespace gdx_cpp;
using namespace gdx_cpp::backends::nix;

gdx_cpp::ApplicationListener* applicationListener = 0;
int width,height = 0;
std::string title;

void createApplication(gdx_cpp::ApplicationListener* listener, const std::string& applicationName, int p_width, int p_height) {
    applicationListener = listener;
    width = p_width;
    height = p_height;
    title = applicationName;
}

int main(int argc, char** argv) {
    Gdx::initializeSystem(new LinuxSystem);
   
    init();
    assert(applicationListener);
    
    gdx_cpp::backends::nix::LinuxApplication app(applicationListener, title, width, height, false);
    
    return 0;    
}