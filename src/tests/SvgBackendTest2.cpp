#include <gdx-cpp/Gdx.hpp>
#include <gdx-cpp/Application.hpp>
#include <gdx-cpp/ApplicationListener.hpp>
#include <gdx-cpp/graphics/Mesh.hpp>
#include <gdx-cpp/graphics/GL10.hpp>
#include <gdx-cpp/graphics/Texture.hpp>
#include <gdx-cpp/graphics/g2d/SpriteBatch.hpp>
#include <gdx-cpp/utils/ApplicationListenerDecorator.hpp>
#include <gdx-cpp/graphics/g2d/Sprite.hpp>
#include <gdx-cpp/utils/StringConvertion.hpp>

using namespace gdx_cpp::graphics::g2d;
using namespace gdx_cpp::graphics;
using namespace gdx_cpp;

class SvgBackendTest2 : public gdx_cpp::ApplicationListener {
public:
    SvgBackendTest2() {
    }
    
    void create() {
        Pixmap::ptr pixmap = Pixmap::newFromFile(Gdx::files->internal("data/boss.svg"));
        texture = Texture::ptr(new Texture(pixmap, false));
        
        sprite = new Sprite(texture);
        sprite->setPosition(0, 0);
        
        spriteBatch = new SpriteBatch();
    }
    
    void dispose() {
    }
    
    void pause() {
    }
    
    void render() {
        Gdx::graphics->getGL10()->glClearColor(1, 1, 1, 1);
        Gdx::graphics->getGL10()->glClear(GL10::GL_COLOR_BUFFER_BIT);
        
        spriteBatch->begin();
        sprite->draw(*spriteBatch);        
        spriteBatch->end();
    }
    
    void resize(int width, int height) {
    }
    
    void resume() {
    }
    
private:
    SpriteBatch* spriteBatch;
    Sprite* sprite;
    Texture::ptr texture;
};

void init(int argc, char** argv) {  
    createApplication(new utils::ApplicationListenerDecorator<SvgBackendTest2>(), "Svg Backend Test 2", 640, 480);
}