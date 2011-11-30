#include <gdx-cpp/Application.hpp>
#include <gdx-cpp/Graphics.hpp>
#include <gdx-cpp/Files.hpp>
#include <gdx-cpp/implementation/System.hpp>
#include <gdx-cpp/ApplicationListener.hpp>
#include <gdx-cpp/graphics/Mesh.hpp>
#include <gdx-cpp/graphics/GL10.hpp>
#include <gdx-cpp/graphics/Texture.hpp>
#include <gdx-cpp/graphics/g2d/SpriteBatch.hpp>
#include <gdx-cpp/graphics/g2d/Sprite.hpp>
#include <gdx-cpp/math/MathUtils.hpp>

#include <iostream>
#include <gdx-cpp/graphics/FPSLogger.hpp>

using namespace gdx_cpp;
using namespace gdx_cpp::graphics;
using namespace gdx_cpp::graphics::g2d;

#define SPRITES 25000

class SpriteBatchTest : public gdx_cpp::ApplicationListener {
public:

    SpriteBatchTest() :
            angle(0),
            scale(1),
            SCALE_SPEED(-1),
            renderMethod(0),
            ROTATION_SPEED(20),
            frames(0)
    {
    }

    void create() {        
        spriteBatch = new SpriteBatch(1000);
        gdx_cpp::files::FileHandle::ptr file = gdx_cpp::Gdx::files->internal("data/badlogicsmall.jpg");
        Pixmap::ptr pixmap = Pixmap::newFromFile(file);

        texture = Texture::ptr(new Texture(32, 32, gdx_cpp::graphics::Pixmap::Format::RGB565, Pixmap::Gdx2d));
        texture->setFilter(Texture::TextureFilter::Linear, Texture::TextureFilter::Linear);
        texture->draw(*pixmap, 0, 0);
        pixmap->dispose();
        
        pixmap = Pixmap::newFromRect(2, 2, Pixmap::Format::RGBA8888, Pixmap::Gdx2d);
        pixmap->setColor(1,1,0 , 0.5f);
        pixmap->fill();

        texture2 = Texture::ptr(new Texture(pixmap, false));
        texture2->setFilter(Texture::TextureFilter::Linear, Texture::TextureFilter::Linear);
        
        for (int i = 0; i < SPRITES * 6; i += 6) {
            sprites[i] = (int)(math::utils::random() * (Gdx::graphics->getWidth() - 32));
            sprites[i + 1] = (int)(math::utils::random() * (Gdx::graphics->getHeight() - 32));
            sprites[i + 2] = 0;
            sprites[i + 3] = 0;
            sprites[i + 4] = 2;
            sprites[i + 5] = 2;
            sprites2[i] = (int)(math::utils::random() * (Gdx::graphics->getWidth() - 32));
            sprites2[i + 1] = (int)(math::utils::random() * (Gdx::graphics->getHeight() - 32));
            sprites2[i + 2] = 0;
            sprites2[i + 3] = 0;
            sprites2[i + 4] = 2;
            sprites2[i + 5] = 2;
        }

        for (int i = 0; i < SPRITES * 2; i++) {
            int x = (int)(math::utils::random() * (Gdx::graphics->getWidth() - 32));
            int y = (int)(math::utils::random() * (Gdx::graphics->getHeight() - 32));

            if (i >= SPRITES)
                sprites3[i] = new Sprite(texture2, 32, 32);
            else
                sprites3[i] = new Sprite(texture, 32, 32);
            sprites3[i]->setPosition(x, y);
            sprites3[i]->setOrigin(16, 16);
        }
    }

    void dispose() {
    }

    void pause() {
    }

    void render() {
         renderNormal();
    }

    void resize(int width, int height) {
    }

    void resume() {
    }

    void renderNormal() {
        GL10& gl = *Gdx::gl10;

        gl.glClearColor(0.7f, 0.7f, 0.7f, 1);
        gl.glClear(GL10::GL_COLOR_BUFFER_BIT);

        long begin = 0;
        long end = 0;
        long draw1 = 0;
        long draw2 = 0;
        long drawText = 0;

        float deltaTime = Gdx::graphics->getDeltaTime();
    
        angle += ROTATION_SPEED * deltaTime;
        scale += SCALE_SPEED * deltaTime;

        if (scale < 0.5f) {
            scale = 0.5f;
            SCALE_SPEED = 1;
        }
        if (scale > 1.0f) {
            scale = 1.0f;
            SCALE_SPEED = -1;
        }

        long start = Gdx::system->nanoTime();
        spriteBatch->begin();
        begin = (Gdx::system->nanoTime() - start) / 1000;

        start = Gdx::system->nanoTime();
        for (int i = 0; i < SPRITES * 6; i += 6)
            spriteBatch->draw(*texture, sprites[i], sprites[i + 1], 16, 16, 32, 32, scale, scale, angle, 0, 0, 32, 32, false, false);
        draw1 = (Gdx::system->nanoTime() - start) / 1000;

        start = Gdx::system->nanoTime();
        for (int i = 0; i < SPRITES * 6; i += 6)
            spriteBatch->draw(*texture2, sprites2[i], sprites2[i + 1], 16, 16, 32, 32, scale, scale, angle, 0, 0, 32, 32, false, false);
        draw2 = (Gdx::system->nanoTime() - start) / 1000;

        start = Gdx::system->nanoTime();
        // spriteBatch->drawText(font, "Question?", 100, 300, Color.RED);
        // spriteBatch->drawText(font, "and another this is a test", 200, 100, Color.WHITE);
        // spriteBatch->drawText(font, "all hail and another this is a test", 200, 200, Color.WHITE);
        // spriteBatch->drawText(font, "normal fps: " + Gdx::graphics->getFramesPerSecond(), 10, 30, Color.RED);
        drawText = (Gdx::system->nanoTime() - start) / 1000;

        start = Gdx::system->nanoTime();
        spriteBatch->end();
        end = (Gdx::system->nanoTime() - start) / 1000;

        if (Gdx::system->nanoTime() - startTime > 1000000000) {
            Gdx::app->log("SpriteBatch", "fps: %d , render calls: %d, begin: %d us,"
            "draw1: %d us ,draw2: %d us,drawText: %d us,end: %d us", frames, spriteBatch->renderCalls,  begin,
            draw1, draw2, drawText, end);
            frames = 0;
            startTime = Gdx::system->nanoTime();
        }
        frames++;
    }

    void renderSprites() {
        GL10& gl = *Gdx::gl10;
        gl.glClearColor(0.7f, 0.7f, 0.7f, 1);
        gl.glClear(GL10::GL_COLOR_BUFFER_BIT);

        float begin = 0;
        float end = 0;
        float draw1 = 0;
        float draw2 = 0;
        float drawText = 0;

        long start = Gdx::system->nanoTime();
        spriteBatch->begin();
        begin = (Gdx::system->nanoTime() - start) / 1000000000.0f;

        float angleInc = ROTATION_SPEED * Gdx::graphics->getDeltaTime();
        scale += SCALE_SPEED * Gdx::graphics->getDeltaTime();
        
        if (scale < 0.5f) {
            scale = 0.5f;
            SCALE_SPEED = 1;
        }
        if (scale > 1.0f) {
            scale = 1.0f;
            SCALE_SPEED = -1;
        }

        start = Gdx::system->nanoTime();
        for (int i = 0; i < SPRITES * 2; i++) {
             if (angleInc != 0) sprites3[i]->rotate(angleInc); // this is aids
             if (scale != 1) sprites3[i]->setScale(scale); // this is aids
            sprites3[i]->draw(*spriteBatch);
        }
        draw1 = (Gdx::system->nanoTime() - start) / 1000000000.0f;

//         start = Gdx::system->nanoTime();
//         for (int i = SPRITES; i < SPRITES << 1; i++) {
//             if (angleInc != 0)
//                 sprites3[i]->rotate(angleInc); // this is aids
//             if (scale != 1)
//                 sprites3[i]->setScale(scale); // this is aids
//             sprites3[i]->draw(*spriteBatch);
//         }
//         draw2 = (Gdx::system->nanoTime() - start) / 1000000000.0f;

        start = Gdx::system->nanoTime();
        drawText = (Gdx::system->nanoTime() - start) / 1000000000.0f;

        start = Gdx::system->nanoTime();
        spriteBatch->end();
        end = (Gdx::system->nanoTime() - start) / 1000000000.0f;

        if (Gdx::system->nanoTime() - startTime > 1000000000) {
            Gdx::app->log("SpriteBatch", "fps: %d , render calls: %d, %f, %f ,%f, %f, %f", frames, spriteBatch->renderCalls, frames,  begin,
            draw1, draw2, drawText, end);
            frames = 0;
            startTime = Gdx::system->nanoTime();
        }
        frames++;
    }

protected:
    Texture::ptr texture, texture2;
    SpriteBatch* spriteBatch;
    Sprite* sprites3[SPRITES *2];
    float sprites[SPRITES * 6];
    float sprites2[SPRITES * 6];

    float angle;
    float scale;
    float SCALE_SPEED;
    int renderMethod;
    float ROTATION_SPEED;
    uint64_t startTime;
    int frames;
};

void init(int argc, char** argv) {
    createApplication(new SpriteBatchTest, "SpriteBatch Test", 640, 480);
}
