
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

#include "Gdx.hpp"

#include "graphics/GL10.hpp"
#include "graphics/GL11.hpp"
#include "graphics/GL20.hpp"
#include "graphics/GLCommon.hpp"
#include "graphics/GLU.hpp"
#include <cassert>

namespace gdx {
Application* app = 0;
Graphics* graphics = 0;
Audio* audio = 0;
Input* input = 0;
Files* files = 0; 
GLCommon* gl = 0;
GL10* gl10 = 0;
GL11* gl11 = 0;
GL20* gl20 = 0;
GLU* glu = 0;

System* system = 0;       

Log* log = 0;
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

void gdx::internal_log_debug(const std::string& tag, const std::string& line, const std::string& file, const char* format, ...) {
    va_list ap;
    va_start(ap, format);
    log->debug(tag, line, file, format, ap);
    va_end(ap);
}

void gdx::internal_log_info(const std::string& tag, const std::string& line, const std::string& file, const char* format, ...) {
    va_list ap;
    va_start(ap, format);
    log->info(tag, line, file, format, ap);
    va_end(ap);
}

void gdx::internal_log_error(const std::string& tag, const std::string& line, const std::string& file, const char* format, ...) {
    va_list ap;
    va_start(ap, format);
    log->info(tag, line, file, format, ap);
    va_end(ap);
}