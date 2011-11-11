#include <gdx-cpp/Gdx.hpp>
#include <gdx-cpp/Application.hpp>
#include <gdx-cpp/ApplicationListener.hpp>
#include <gdx-cpp/graphics/Mesh.hpp>
#include <gdx-cpp/graphics/GL10.hpp>
#include <gdx-cpp/graphics/Texture.hpp>
#include <gdx-cpp/graphics/g2d/SpriteBatch.hpp>
#include <gdx-cpp/utils/ApplicationListenerDecorator.hpp>

using namespace gdx_cpp::graphics::g2d;
using namespace gdx_cpp::graphics;
using namespace gdx_cpp;

class AlphaTest : public gdx_cpp::ApplicationListener {
public:
    AlphaTest() {
    }
    
    void create() {
        Pixmap::ptr pixmap = Pixmap::newFromRect(256, 256, Pixmap::Format::RGBA8888, Pixmap::Gdx2d);
        pixmap->setColor(0, 1, 0, 0.7f);
        pixmap->fill();
        
        spriteBatch = new SpriteBatch();
        texture = Texture::ptr(new Texture(pixmap, false));
        texture->setFilter(Texture::TextureFilter::Linear, Texture::TextureFilter::Linear);
    }
    
    void dispose() {
    }
    
    void pause() {
    }
    
    void render() {
        Gdx::graphics->getGL10()->glClear(GL10::GL_COLOR_BUFFER_BIT);
        
        spriteBatch->begin();
        spriteBatch->draw(*texture, 0, 0, 256, 256, 0, 0, 256, 256, false, false);
        spriteBatch->end();
    }
    
    void resize(int width, int height) {
    }
    
    void resume() {
    }
    
private:
    SpriteBatch* spriteBatch;
    Texture::ptr texture;
};

void init(int argc, char** argv) {
    createApplication(new utils::ApplicationListenerDecorator<AlphaTest>(), "Alpha Test", 640, 480);
}