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

class SvgBackendTest : public gdx_cpp::ApplicationListener {
public:
    SvgBackendTest() {
    }
    
    void create() {
        Pixmap::ptr pixmap = Pixmap::newFromFile(Gdx::files->internal("data/example.svg"));
        
        texture = Texture::ptr(new Texture(pixmap, false));
        pixmap->setScale(2, 2);
        texture2 = Texture::ptr(new Texture(pixmap, false));

        texture2->setFilter(Texture::TextureFilter::Linear, Texture::TextureFilter::Linear);
        texture->setFilter(Texture::TextureFilter::Linear, Texture::TextureFilter::Linear);        

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
        spriteBatch->draw(*texture, 0.f, 0.f, 64.f, 64.f);
        spriteBatch->draw(*texture, 200.f, 0.f, 256.f, 256.f);
        spriteBatch->draw(*texture2, 0.f, 400.f, 128.f, 128.f);
        spriteBatch->draw(*texture2, 200.f, 250.f, 256.f, 256.f);
        spriteBatch->end();
    }
    
    void resize(int width, int height) {
    }
    
    void resume() {
    }
    
private:
    SpriteBatch* spriteBatch;
    Texture::ptr texture;
    Texture::ptr texture2;
};

void init(int argc, char** argv) {
    createApplication(new utils::ApplicationListenerDecorator<SvgBackendTest>(), "Svg Backend Test", 640, 480);
}