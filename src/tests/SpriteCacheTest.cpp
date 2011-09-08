#include "backends/current_backend.hpp"

#include <gdx-cpp/Application.hpp>
#include <gdx-cpp/Graphics.hpp>
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
#include <gdx-cpp/InputProcessor.hpp>
#include <gdx-cpp/graphics/g2d/SpriteCache.hpp>
#include <gdx-cpp/Input.hpp>

using namespace gdx_cpp;
using namespace gdx_cpp::graphics;
using namespace gdx_cpp::graphics::g2d;

#define SPRITES 200

class SpriteCacheTest : public gdx_cpp::ApplicationListener, gdx_cpp::InputProcessor {
public:

    SpriteCacheTest() :
            renderMethod(0),
            frames(0)
    {
    }

    void create() {
        spriteCache = new SpriteCache(1000, true);

        Pixmap::ptr pixmap = Pixmap::ptr(new Pixmap(32, 32, Pixmap::Format::RGBA8888));
        pixmap->setColor(1 ,1 ,0 ,0.5f);
        pixmap->fill();

        texture = Texture::ptr(new Texture(pixmap, false));
        texture->setFilter(Texture::TextureFilter::Linear, Texture::TextureFilter::Linear);

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

            //             if (i >= SPRITES)
            //                 sprites3[i] = new Sprite(texture2, 32, 32);
            //             else
            sprites3[i] = new Sprite(texture, 32, 32);
            sprites3[i]->setPosition(x, y);
            sprites3[i]->setOrigin(16, 16);
        }

        float scale = 1;
        float angle = 15;

        spriteCache->beginCache();
        for (int i = 0; i < SPRITES * 6; i += 6)
            spriteCache->add(texture, sprites2[i], sprites2[i + 1], 16, 16, 32, 32, scale, scale, angle, 0, 0, 32, 32, false, false);
        for (int i = 0; i < SPRITES * 6; i += 6)
            spriteCache->add(texture, sprites[i], sprites[i + 1], 16, 16, 32, 32, scale, scale, angle, 0, 0, 32, 32, false, false);
        normalCacheID = spriteCache->endCache();

        angle = -15;

        spriteCache->beginCache();
        for (int i = SPRITES; i < SPRITES << 1; i++) {
            sprites3[i]->setRotation(angle);
            sprites3[i]->setScale(scale);
            spriteCache->add(*sprites3[i]);
        }
        for (int i = 0; i < SPRITES; i++) {
            sprites3[i]->setRotation(angle);
            sprites3[i]->setScale(scale);
            spriteCache->add(*sprites3[i]);
        }
        spriteCacheID = spriteCache->endCache();

        Gdx::input->setInputProcessor(this);
    }

    void dispose() {
    }

    void pause() {
    }

    void render() {
        renderMethod == 0 ? renderNormal() : renderSprites();
    }

    void resize(int width, int height) {
    }

    void resume() {
    }

    void renderNormal() {
        GL10& gl = *Gdx::gl10;

        gl.glClearColor(0.7f, 0.7f, 0.7f, 1);
        gl.glClear(GL10::GL_COLOR_BUFFER_BIT);
        
        float begin = 0;
        float end = 0;
        float draw1 = 0;
        
        long start = Gdx::system->nanoTime();
        spriteCache->begin();
        begin = (Gdx::system->nanoTime() - start) / 1000000000.0f;
        
        start = Gdx::system->nanoTime();
        spriteCache->draw(normalCacheID);
        draw1 = (Gdx::system->nanoTime() - start) / 1000000000.0f;
        
        start = Gdx::system->nanoTime();
        spriteCache->end();
        end = (Gdx::system->nanoTime() - start) / 1000000000.0f;
        
        if (Gdx::system->nanoTime() - startTime > 1000000000) {
            // Gdx.app.log( "SpriteBatch", "fps: " + frames + ", render calls: " + spriteBatch.renderCalls + ", " + begin + ", " + draw1 +
            // ", " + draw2 + ", " + drawText + ", " + end );
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
        spriteCache->begin();
        begin = (Gdx::system->nanoTime() - start) / 1000000000.0f;
        
        start = Gdx::system->nanoTime();
        spriteCache->draw(spriteCacheID);
        draw1 = (Gdx::system->nanoTime() - start) / 1000000000.0f;
        
        start = Gdx::system->nanoTime();
        spriteCache->end();
        end = (Gdx::system->nanoTime() - start) / 1000000000.0f;
        
        if (Gdx::system->nanoTime() - startTime > 1000000000) {
            // Gdx.app.log( "SpriteBatch", "fps: " + frames + ", render calls: " + spriteBatch.renderCalls + ", " + begin + ", " + draw1 +
            // ", " + draw2 + ", " + drawText + ", " + end );
            frames = 0;
            startTime = Gdx::system->nanoTime();
        }
        frames++;
    }

    bool keyDown(int keycode) {
    }

    bool keyTyped(char character) {

    }

    bool keyUp(int keycode) {

    }

    bool scrolled(int amount) {
    }

    bool touchDown(int x, int y, int pointer, int button) {

    }

    bool touchDragged(int x, int y, int pointer) {
        
    }

    bool touchMoved(int x, int y) {

    }

    bool touchUp(int x, int y, int pointer, int button) {

    }

protected:
    Texture::ptr texture;
    SpriteCache* spriteCache;

    Sprite* sprites3[SPRITES *2];
    float sprites[SPRITES * 6];
    float sprites2[SPRITES * 6];

    int renderMethod;
    uint64_t startTime;
    int frames;
    int normalCacheID, spriteCacheID;
};

void init() {
    createApplication(new SpriteCacheTest, "SpriteCache Test", 640, 480);
}
