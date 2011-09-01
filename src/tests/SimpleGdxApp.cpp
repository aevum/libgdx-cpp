#include <iostream>
#include <linux/init.hpp>
#include <linux/LinuxApplication.hpp>
#include <gdx-cpp/ApplicationListener.hpp>

class DullListener : public gdx_cpp::ApplicationListener {
public:
    virtual void create() {
        
    }

    virtual void dispose() {

    }
    
    virtual void pause() {

    }
    
    virtual void render() {
    }
    
    virtual void resize(int width, int height) {
    }
    
    virtual void resume() {
    }
};

int main() {
    gdx_cpp::backends::nix::initializeSystem();
    gdx_cpp::backends::nix::LinuxApplication application(new DullListener, "GDX-TEST", 640, 480, false);
  
    return 0;
}





