#include <gdx-cpp/Application.hpp>
#include <gdx-cpp/ApplicationListener.hpp>
#include <gdx-cpp/graphics/Mesh.hpp>
#include <gdx-cpp/graphics/GL10.hpp>
#include <gdx-cpp/graphics/Pixmap.hpp>
#include <gdx-cpp/graphics/Texture.hpp>
#include <gdx-cpp/graphics/g2d/SpriteBatch.hpp>
#include <gdx-cpp/graphics/g2d/TextureRegion.hpp>

using namespace gdx_cpp::graphics::g2d;
using namespace gdx_cpp::graphics;
using namespace gdx_cpp;

class PixmapTest : public gdx_cpp::ApplicationListener {
public:
    PixmapTest() :
    width(0)
    ,height(0)
    {
    }

    void create() {
        Texture::ptr texture = Texture::ptr(new Texture(1024,1024, Pixmap::Format::RGBA8888, Pixmap::Gdx2d));

        Pixmap::ptr pixmap = Pixmap::newFromRect(840, 480, Pixmap::Format::RGBA8888, Pixmap::Gdx2d);
        texture->setFilter(Texture::TextureFilter::Nearest, Texture::TextureFilter::Linear);
        texture->setWrap(Texture::TextureWrap::ClampToEdge, Texture::TextureWrap::ClampToEdge);
        pixmap->setColor(1.0f, 0.0f, 0.0f, 1.0f); // Red
        pixmap->drawLine(0, 0, 100, 100);
        
        pixmap->setColor(0.0f, 0.0f, 1.0f, 1.0f); // Blue
        pixmap->drawLine(100, 100, 200, 0);
        
        pixmap->setColor(0.0f, 1.0f, 0.0f, 1.0f); // Green
        pixmap->drawLine(100, 0, 100, 100);
        
        pixmap->setColor(1.0f, 1.0f, 1.0f, 1.0f); // White
        pixmap->drawCircle(400, 300, 100);

        texture->draw(*pixmap, 0, 0);
        region = new TextureRegion(texture, 0, 0, 800, 480);
        batch = new SpriteBatch();

        Pixmap::ptr px = Pixmap::newFromRect(512, 1024, Pixmap::Format::RGBA8888, Pixmap::Gdx2d);
        for (int y = 0; y < pixmap->getHeight(); y++) { // 1024
            for (int x = 0; x < pixmap->getWidth(); x++) { // 512
                                pixmap->getPixel(x, y);
                        }
        }
        px->dispose();
    }

    void dispose() {
    }

    void pause() {
    }
    void render() {
        Gdx::gl->glClearColor(0.6f, 0.6f, 0.6f, 1);
        Gdx::gl->glClear(GL10::GL_COLOR_BUFFER_BIT);
        batch->begin();
        batch->draw(*region, 0, 0);
        batch->end();
    }

    void resize(int p_width, int p_height) {
        width = p_width;
        height = p_height;
    }

    void resume() {
    }
    
private:
    Pixmap::ptr pixmap;
    Texture::ptr texture;
    SpriteBatch* batch;
    TextureRegion* region;
    int width;
    int height;
};

void init(int argc, char** argv) {
    createApplication(new PixmapTest, "Pixmap test", 640, 480);
}