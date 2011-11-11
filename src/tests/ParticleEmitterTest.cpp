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
#include <cmath>

#include <iostream>
#include <gdx-cpp/graphics/FPSLogger.hpp>
#include "gdx-cpp/graphics/g2d/ParticleEffect.hpp"
#include "gdx-cpp/graphics/g2d/ParticleEmitter.hpp"
#include "gdx-cpp/Input.hpp"
#include "gdx-cpp/InputProcessor.hpp"


using namespace gdx_cpp;
using namespace gdx_cpp::graphics;
using namespace gdx_cpp::graphics::g2d;

class ParticleEmitterTest : public ApplicationListener {
public:

    class InputProcessorTest : public InputProcessor {
    public:
        ParticleEmitterTest * emitterTest;

        InputProcessorTest(ParticleEmitterTest * _emitter)
        {
            emitterTest = _emitter;
        }
        bool touchUp (int x, int y, int pointer, int button) {
            return false;
        }

        bool touchDragged (int x, int y, int pointer) {
            emitterTest->effect.setPosition(x, Gdx::graphics->getHeight() - y);
            return false;
        }

        bool touchDown (int x, int y, int pointer, int newParam) {
            emitterTest->effect.setPosition(x, Gdx::graphics->getHeight() - y);
            return false;
        }

        bool keyUp (int keycode) {
            return false;
        }

        bool keyTyped (char character) {
            return false;
        }

        bool keyDown (int keycode) {
            ParticleEmitter * emitter = emitterTest->emitters[emitterTest->emitterIndex];
            if (keycode ==  gdx_cpp::Input::Keys::DPAD_UP)
                emitterTest->particleCount += 5;
            else if (keycode == gdx_cpp::Input::Keys::DPAD_DOWN)
                emitterTest->particleCount -= 5;
            else if (keycode == gdx_cpp::Input::Keys::SPACE) {
                emitterTest->emitterIndex = (emitterTest->emitterIndex + 1) % emitterTest->emitters.size();
                emitter = emitterTest->emitters[emitterTest->emitterIndex];
                emitterTest->particleCount = (int)(emitter->getEmission().getHighMax() * emitter->getLife().getHighMax() / 1000.f);
            } else
                return false;
            emitterTest->particleCount = std::max(0, emitterTest->particleCount);
            if (emitterTest->particleCount > emitter->getMaxParticleCount()) emitter->setMaxParticleCount(emitterTest->particleCount * 2);
            emitter->getEmission().setHigh(emitterTest->particleCount / emitter->getLife().getHighMax() * 1000);
            emitterTest->effect.getEmitters().clear();
            emitterTest->effect.getEmitters().push_back(emitter);
            return false;
        }

        bool touchMoved (int x, int y) {
            return false;
        }


        bool scrolled (int amount) {
            return false;
        }
    };


    ParticleEffect effect;
    int emitterIndex;
    std::vector<ParticleEmitter *> emitters;
    int particleCount;
    float fpsCounter;
    InputProcessorTest * inputProcessor;
    ParticleEmitterTest():emitterIndex(0), particleCount(10), fpsCounter(0)
    {

    }
    void create() {
        spriteBatch = new SpriteBatch;
        effect.load("/home/ozires/desenvolvimento/libgdxcpp/data/test.p");
        effect.setPosition(Gdx::graphics->getWidth() / 2, Gdx::graphics->getHeight() / 2);
        // Of course, a ParticleEffect is normally just used, without messing around with its emitters.
        emitters = effect.getEmitters();
        effect.getEmitters().clear();
        effect.getEmitters().push_back(emitters[0]);

        inputProcessor = new InputProcessorTest(this);
        Gdx::input->setInputProcessor(inputProcessor);
    }

    void dispose() {
    }

    void pause() {
    }

    void render() {
        spriteBatch->getProjectionMatrix().setToOrtho2D(0, 0, Gdx::graphics->getWidth(), Gdx::graphics->getHeight());
        float delta = Gdx::graphics->getDeltaTime();
        GL10 * gl = Gdx::graphics->getGL10();
        gl->glClear(GL10::GL_COLOR_BUFFER_BIT);
        spriteBatch->begin();
        effect.draw(*spriteBatch, delta);
        spriteBatch->end();
        fpsCounter += delta;
        if (fpsCounter > 3) {
            fpsCounter = 0;
            int activeCount = emitters[emitterIndex]->getActiveCount();
            Gdx::app->log("ParticleEmmiterTest", "%d / %d particles, FPS: %lu", particleCount, activeCount, Gdx::graphics->getFramesPerSecond());
        }
    }

    void resize(int width, int height) {
    }

    void resume() {
    }

    bool needsGL20 ()
    {
        return false;
    }

protected:

private:
    SpriteBatch * spriteBatch;

};

void init(int argc, char** argv) {
    createApplication(new ParticleEmitterTest, "ParticleEmitter Test", 640, 480);
}


