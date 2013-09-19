
/*
    Copyright 2011 Aevum Software aevum @ aevumlab.com

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.

    @author Victor Vicente de Carvalho victor.carvalho@aevumlab.com
    @author Ozires Bortolon de Faria ozires@aevumlab.com
*/

#include <stdarg.h>

#include "Gdx.hpp"
#include "gdx-cpp/Graphics.hpp"
#include "gdx-cpp/Log.hpp"

namespace gdx {
class Application;
class Audio;
class Files;
class Input;

Application* app = nullptr;
Graphics* graphics = nullptr;
Audio* audio = nullptr;
Input* input = nullptr;
Files* files = nullptr; 
GLCommon* gl = nullptr;
GL10* gl10 = nullptr;
GL11* gl11 = nullptr;
GL20* gl20 = nullptr;
GLU* glu = nullptr;

System* system = nullptr;
Log* log = nullptr;
}

void gdx::initialize(gdx::Application* application,
                     gdx::Graphics* graphics, gdx::Audio* audio, gdx::Input*  input , gdx::Files* files)
{
    gdx::app = application;
    gdx::graphics = graphics;
    gdx::audio = audio;
    gdx::input = input;
    gdx::files = files;
    gdx::gl = graphics->getGLCommon();
    gdx::gl10 = graphics->getGL10();
    gdx::gl20 = graphics->getGL20();
    gdx::gl11 = graphics->getGL11();
    gdx::glu = graphics->getGLU();
}

void gdx::initializeSystem(gdx::System* system, Log* log)
{
    gdx::system = system;
    gdx::log = log;
}
