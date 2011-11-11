#include <gdx-cpp/Gdx.hpp>
#include <gdx-cpp/Application.hpp>
#include <gdx-cpp/ApplicationListener.hpp>
#include <gdx-cpp/graphics/Mesh.hpp>
#include <gdx-cpp/graphics/GL10.hpp>
#include <gdx-cpp/graphics/Texture.hpp>
#include <gdx-cpp/graphics/g2d/SpriteBatch.hpp>
#include <gdx-cpp/graphics/g2d/Sprite.hpp>
#include <gdx-cpp/graphics/g2d/SpriteCache.hpp>
#include <gdx-cpp/math/MathUtils.hpp>

using namespace gdx_cpp::graphics::g2d;
using namespace gdx_cpp::graphics;
using namespace gdx_cpp;

const char* modes[10] = {"SpriteBatch blended", "SpriteBatch not blended", "SpriteBatch animated blended",
"SpriteBatch animated not blended", "SpriteBatch VBO blended", "SpriteBatch VBO not blended",
"SpriteBatch VBO animated blended", "SpriteBatch VBO animated not blended", "SpriteCache blended",
"SpriteCache not blended"
};

class SpritePerformanceTest : public gdx_cpp::ApplicationListener {
public:
    SpritePerformanceTest()
            : frames(0),
            startTime(0),
            vaBatch(NULL),
            vboBatch(NULL),
            cache(0),
            rotation(0),
            mode(0)
    {
    }

    void create() {
        texture = Texture::fromFile(Gdx::files->internal("data/badlogicsmall.jpg"));
        texture->setFilter(Texture::TextureFilter::Linear, Texture::TextureFilter::Linear);

        vaBatch = new SpriteBatch();
        Mesh::forceVBO = true;
        vboBatch = new SpriteBatch(1000, 1);
        Mesh::forceVBO = false;
        cache = new SpriteCache;

        for (int i = 0; i < SPRITES; i++) {
            int x = (int)(math::utils::random() * (Gdx::graphics->getWidth() - 32));
            int y = (int)(math::utils::random() * (Gdx::graphics->getHeight() - 32));

            sprites[i] = new Sprite(texture);
            sprites[i]->setPosition(x, y);
        }

        cache->beginCache();
        for (int i = 0; i < SPRITES; i++) {
            cache->add(*sprites[i]);
        }

        spritesHandle = cache->endCache();

        startTime = Gdx::system->nanoTime();
        frames = 0;
    }

    void dispose() {
    }

    void pause() {
    }

    void render() {
        Gdx::gl->glClear(GL10::GL_COLOR_BUFFER_BIT);

        switch (mode) {
        case 0:
            renderSpriteBatch();
            break;
        case 1:
            renderSpriteBatchBlendDisabled();
            break;
        case 2:
            renderSpriteBatchAnimated();
            break;
        case 3:
            renderSpriteBatchAnimatedBlendDisabled();
            break;
        case 4:
            renderSpriteBatchVBO();
            break;
        case 5:
            renderSpriteBatchBlendDisabledVBO();
            break;
        case 6:
            renderSpriteBatchAnimatedVBO();
            break;
        case 7:
            renderSpriteBatchAnimatedBlendDisabledVBO();
            break;
        case 8:
             renderSpriteCache();
            break;
        case 9:
            renderSpriteCacheBlendDisabled();
            break;
        }

        int error = Gdx::gl->glGetError();
        if (error != GL10::GL_NO_ERROR) {
            Gdx::app->log("SpritePerformanceTest", "gl error: %s", error);
        }

        frames++;
        if (Gdx::system->nanoTime() - startTime > 5000000000l) {
            Gdx::app->log("SpritePerformanceTest", "mode: %s, fps: %f" , modes[mode], frames / 5.0f);
            log << "mode: " << modes[mode] << ", fps: " << frames / 5.0f << std::endl;

            frames = 0;
            startTime = Gdx::system->nanoTime();
            mode++;
            if (mode > 9) mode = 0;
        }
    }

    void resize(int width, int height) {
    }

    void resume() {
    }

    void renderSpriteBatch () {
        vaBatch->enableBlending();
        vaBatch->begin();
        for (int i = 0; i < SPRITES; i++) {
            sprites[i]->draw(*vaBatch);
        }
        vaBatch->end();
    }

    void renderSpriteBatchBlendDisabled () {
        vaBatch->disableBlending();
        vaBatch->begin();
        for (int i = 0; i < SPRITES; i++) {
            sprites[i]->draw(*vaBatch);
        }
        vaBatch->end();
    }

    void renderSpriteBatchAnimated () {
        rotation += 25 * Gdx::graphics->getDeltaTime();
        vaBatch->enableBlending();
        vaBatch->begin();
        for (int i = 0; i < SPRITES; i++) {
            sprites[i]->setRotation(rotation);
            sprites[i]->draw(*vaBatch);
        }
        vaBatch->end();
    }

    void renderSpriteBatchAnimatedBlendDisabled () {
        rotation += 25 * Gdx::graphics->getDeltaTime();
        vaBatch->disableBlending();
        vaBatch->begin();
        for (int i = 0; i < SPRITES; i++) {
            sprites[i]->setRotation(rotation);
            sprites[i]->draw(*vaBatch);
        }
        vaBatch->end();
    }

    void renderSpriteBatchVBO () {
        vaBatch->enableBlending();
        vaBatch->begin();
        for (int i = 0; i < SPRITES; i++) {
            sprites[i]->draw(*vaBatch);
        }
        vaBatch->end();
    }

    void renderSpriteBatchBlendDisabledVBO () {
        vaBatch->disableBlending();
        vaBatch->begin();
        for (int i = 0; i < SPRITES; i++) {
            sprites[i]->draw(*vaBatch);
        }
        vaBatch->end();
    }

    void renderSpriteBatchAnimatedVBO () {
        rotation += 25 * Gdx::graphics->getDeltaTime();
        vaBatch->enableBlending();
        vaBatch->begin();
        for (int i = 0; i < SPRITES; i++) {
            sprites[i]->setRotation(rotation);
            sprites[i]->draw(*vaBatch);
        }
        vaBatch->end();
    }

    void renderSpriteBatchAnimatedBlendDisabledVBO () {
        rotation += 25 * Gdx::graphics->getDeltaTime();
        vaBatch->disableBlending();
        vaBatch->begin();
        for (int i = 0; i < SPRITES; i++) {
            sprites[i]->setRotation(rotation);
            sprites[i]->draw(*vaBatch);
        }
        vaBatch->end();
    }

    void renderSpriteCache () {
        Gdx::gl->glEnable(GL10::GL_BLEND);
        cache->begin();
        cache->draw(spritesHandle);
        cache->end();
    }

    void renderSpriteCacheBlendDisabled () {
        Gdx::gl->glDisable(GL10::GL_BLEND);
        cache->begin();
        cache->draw(spritesHandle);
        cache->end();
    }

private:
    int mode;
    std::stringstream log;
    static const int SPRITES = 500;
    Sprite* sprites[SPRITES];
    Texture::ptr texture;
    SpriteBatch* vaBatch;
    SpriteBatch* vboBatch;
    SpriteCache* cache;
    int spritesHandle;
    float rotation;
    uint64_t startTime;
    int frames;
};

void init(int argc, char** argv) {
    createApplication(new SpritePerformanceTest, "Sprite Performance Test", 640, 480);
}
