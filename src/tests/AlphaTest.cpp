#include "backends/current_backend.hpp"

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

class AplhaTest : public gdx_cpp::ApplicationListener {
public:
    AplhaTest() {
    }
    
    void create() {
        Pixmap::ptr pixmap = Pixmap::ptr(new Pixmap(256, 256, Pixmap::Format::RGBA8888));
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

void init() {
    createApplication(new AplhaTest, "Alpha Test", 640, 480);
}