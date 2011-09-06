#include <iostream>
#include "backends/current_backend.hpp"
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

extern "C" void init() {
    createApplication(new DullListener, "Dull Listener", 640, 480);
}
