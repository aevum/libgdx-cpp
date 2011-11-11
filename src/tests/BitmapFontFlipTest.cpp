#include <gdx-cpp/Gdx.hpp>
#include <gdx-cpp/Application.hpp>
#include <gdx-cpp/ApplicationListener.hpp>
#include <gdx-cpp/graphics/GL10.hpp>
#include <gdx-cpp/graphics/g2d/SpriteBatch.hpp>
#include <gdx-cpp/utils/ApplicationListenerDecorator.hpp>
#include <gdx-cpp/graphics/g2d/BitmapFont.hpp>
#include <gdx-cpp/graphics/g2d/BitmapFontCache.hpp>
#include <gdx-cpp/graphics/g2d/Sprite.hpp>
#include <cmath>

using namespace gdx_cpp::graphics::g2d;
using namespace gdx_cpp::graphics;
using namespace gdx_cpp;

class BitmapFontFlipTest : public gdx_cpp::ApplicationListener {
public:
    BitmapFontFlipTest() : red(graphics::Color::RED) , renderMode(0)
    {
    }
    
    void create() {
        spriteBatch = new SpriteBatch();
        spriteBatch->setProjectionMatrix(math::Matrix4().setToOrtho(0, Gdx::graphics->getWidth(), Gdx::graphics->getHeight(), 0, 0, 1));

        logoSprite = new Sprite(Texture::fromFile(Gdx::files->internal("data/badlogic.jpg")));
        
        logoSprite->flip(false, true);
        logoSprite->setPosition(0, 320 - 256);
        logoSprite->setColor(1, 1, 1, 0.5f);

        
        font = BitmapFont::fromFiles(Gdx::files->internal("data/verdana39.fnt"), null_shared_ptr(), true);

        cache1 = new BitmapFontCache(font);
        cache2 = new BitmapFontCache(font);
        cache3 = new BitmapFontCache(font);
        cache4 = new BitmapFontCache(font);
        cache5 = new BitmapFontCache(font);
        
        createCaches("cached", cache1, cache2, cache3, cache4, cache5);
        
        font->setScale(1.33f);

        cacheScaled1 = new BitmapFontCache(font);
        cacheScaled2 = new BitmapFontCache(font);
        cacheScaled3 = new BitmapFontCache(font);
        cacheScaled4 = new BitmapFontCache(font);
        cacheScaled5 = new BitmapFontCache(font);
        
        createCaches("cache scaled", cacheScaled1, cacheScaled2, cacheScaled3, cacheScaled4, cacheScaled5);
    }
    
    void dispose() {
    }
    
    void pause() {
    }
    
    void render() {
        red.a = std::fmod((red.a + Gdx::graphics->getDeltaTime() * 0.1f) , 1.f);
        
        GL10& gl = *Gdx::graphics->getGL10();
        
        gl.glClear(GL10::GL_COLOR_BUFFER_BIT);

        spriteBatch->begin();
        logoSprite->draw(*spriteBatch);
        
        switch (renderMode) {
            case 0:
                font->setScale(1);
                renderNormal("normal");
                break;
            case 1:
                font->setScale(1);
                renderCached();
                break;
            case 2:
                font->setScale(red.a + 0.5f);
                renderNormal("normal scaled");
                break;
            case 3:
                font->setScale(1);
                renderCachedScaled();
                break;
        }
        spriteBatch->end();
    }
    
    void createCaches (const std::string& type, BitmapFontCache* cache1, BitmapFontCache* cache2, BitmapFontCache* cache3,
                       BitmapFontCache* cache4, BitmapFontCache* cache5) {
        cache1->setText("(" + type + ")", 10, 320 - 66);
        
        std::string text = "Sphinx of black quartz,\njudge my vow.";
        cache2->setColor(Color::RED);
        cache2->setMultiLineText(text, 5, 320 - 300);
        
        text = "How quickly\ndaft jumping zebras vex.";
        cache3->setColor(Color::BLUE);
        cache3->setMultiLineText(text, 5, 320 - 200, 470, BitmapFont::HALIGNMENT_CENTER);
        
        text = "Kerning: LYA moo";
        cache4->setText(text, 210, 320 - 66, 0, text.length() - 3);
        
        text = "Forsaking monastic tradition, twelve jovial friars gave\nup their vocation for a questionable existence on the flying trapeze.";
        cache5->setColor(Color::RED);
        cache5->setWrappedText(text, 0, 320 - 300, 480, BitmapFont::HALIGNMENT_CENTER);
    }

    void renderNormal (const std::string& type) {
        static std::string text = "Forsaking monastic tradition, twelve jovial friars gave\nup their vocation for a questionable existence on the flying trapeze.";
        font->setColor(red);
        font->drawWrapped(*spriteBatch, text, 0, 320 - 300, 480, BitmapFont::HALIGNMENT_CENTER);
        
        font->setColor(Color::WHITE);
        font->draw(*spriteBatch, "(" + type + ")", 10, 320 - 66);
        
        if (red.a > 0.6f) return;
        
        static std::string text1 = "Sphinx of black quartz,\njudge my vow.";
        font->setColor(Color::RED);
        font->drawMultiLine(*spriteBatch, text1, 5, 320 - 300);
        
        static std::string text2 = "How quickly\ndaft jumping zebras vex.";
        font->setColor(Color::BLUE);
        font->drawMultiLine(*spriteBatch, text2, 5, 320 - 200, 470, BitmapFont::HALIGNMENT_RIGHT);
        
        static std::string text3 = "Kerning: LYA moo";
        font->setColor(Color::WHITE);
        font->draw(*spriteBatch, text3, 210, 320 - 66, 0, text3.length() - 3);
    }

    void renderCached () {
        cache5->setColor(red);
        cache5->draw(*spriteBatch);
        
        cache1->draw(*spriteBatch);
        
        if (red.a > 0.6f) return;
        
        cache2->draw(*spriteBatch);
        cache3->draw(*spriteBatch);
        cache4->draw(*spriteBatch);
    }


    void renderCachedScaled () {
        cacheScaled5->setColor(red);
        cacheScaled5->draw(*spriteBatch);
        
        cacheScaled1->draw(*spriteBatch);
        
        if (red.a > 0.6f) return;
        
        cacheScaled2->draw(*spriteBatch);
        cacheScaled3->draw(*spriteBatch);
        cacheScaled4->draw(*spriteBatch);
    }
    
    void resize(int width, int height) {
    }
    
    void resume() {
    }
    
private:
    SpriteBatch* spriteBatch;
    g2d::BitmapFont* font;
    int renderMode;
    Sprite* logoSprite;
    BitmapFontCache *cache1, *cache2, *cache3, *cache4, *cache5;
    BitmapFontCache *cacheScaled1, *cacheScaled2, *cacheScaled3, *cacheScaled4, *cacheScaled5;
    graphics::Color red;
};

void init(int argc, char** argv) {
    createApplication(new utils::ApplicationListenerDecorator<BitmapFontFlipTest>(), "BitmapFontFlipTest Test", 640, 480);
}