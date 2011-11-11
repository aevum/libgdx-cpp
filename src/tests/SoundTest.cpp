#include <gdx-cpp/Application.hpp>
#include <gdx-cpp/ApplicationListener.hpp>
#include <gdx-cpp/graphics/Mesh.hpp>
#include <gdx-cpp/graphics/GL10.hpp>
#include <gdx-cpp/graphics/Pixmap.hpp>
#include <gdx-cpp/graphics/Texture.hpp>
#include <gdx-cpp/graphics/g2d/SpriteBatch.hpp>
#include <gdx-cpp/graphics/g2d/TextureRegion.hpp>
#include <gdx-cpp/Files.hpp>
#include <gdx-cpp/audio/Sound.hpp>
#include <gdx-cpp/audio/Music.hpp>
#include <gdx-cpp/InputProcessor.hpp>

using namespace gdx_cpp::graphics::g2d;
using namespace gdx_cpp::graphics;
using namespace gdx_cpp;

class SoundTest : public gdx_cpp::ApplicationListener {
public:

    class InputProcessorTest : public InputProcessor {
    public:
        SoundTest * test;

        InputProcessorTest(SoundTest * _emitter)
        {
            test = _emitter;
        }
        bool touchUp (int x, int y, int pointer, int button) {
            return false;
        }

        bool touchDragged (int x, int y, int pointer) {
            return false;
        }

        bool touchDown (int x, int y, int pointer, int newParam) {
            test->touchDown(x,y,pointer,newParam);
            return false;
        }

        bool keyUp (int keycode) {
            test->keyUp(keycode);
            return false;
        }

        bool keyTyped (char character) {
            return false;
        }

        bool keyDown (int keycode) {
            test->keyDown(keycode);
            return false;
        }

        bool touchMoved (int x, int y) {
            return false;
        }


        bool scrolled (int amount) {
            return false;
        }
    };

    gdx_cpp::audio::Sound * sound;
    gdx_cpp::audio::Music * music;

    float volume;


    SoundTest() : width(0), height(0), volume(0.5f), sound(NULL), music(NULL)
    {
    }

    void create() {
//         sound = Gdx::audio->newSound(Gdx::files->getFileHandle("/home/ozires/tiao.ogg", gdx_cpp::Files::Internal));
        music = Gdx::audio->newMusic(Gdx::files->getFileHandle("data/trombom.ogg", gdx_cpp::Files::Internal));

        Gdx::input->setInputProcessor(new InputProcessorTest(this));
    }

    void dispose() {
    }

    void pause() {
    }
    void render() {
    }

    void resize(int p_width, int p_height) {
        width = p_width;
        height = p_height;
    }

    void resume() {
    }

    bool keyDown (int keycode) {
        if (keycode == gdx_cpp::Input::Keys::PLUS) volume += 0.1f;
        if (keycode == gdx_cpp::Input::Keys::MINUS) volume -= 0.1f;
        music->setVolume(volume);

        return false;
    }

    bool keyUp (int keycode) {
        if (keycode != gdx_cpp::Input::Keys::SPACE) return false;

        if (music != NULL) {
            if (music->isPlaying())
                music->pause();
            else
                music->play();
        }
        return false;
    }

    bool touchDown (int x, int y, int pointer, int newParam) {
        if (sound != NULL)
            sound->play(1.f);
        if (music != NULL) {
             if (music->isPlaying())
                music->stop();
            else
                music->play();
        }
        return false;
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
    createApplication(new SoundTest, "SoundTest test", 640, 480);
}
