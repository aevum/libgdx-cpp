/*
    Copyright 2011 <copyright holder> <email>

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/


#include "EmscriptenApplication.hpp"
#include <iostream>
#include <cstdlib>
#include <gdx-cpp/Graphics.hpp>
#include <gdx-cpp/Gdx.hpp>
#include <gdx-cpp/implementation/System.hpp>
#include <emscripten.h>

using namespace gdx::scripten;
using namespace gdx;

static gdx::scripten::EmscriptenApplication* g_application = nullptr;

gdx::scripten::EmscriptenApplication::EmscriptenApplication ( gdx::ApplicationListener* listener,
        const std::string& title, int width, int height,
        bool useGL20IfAvailable )
    :  Synchronizable ( gdx::system->getMutexFactory() ),
       useGL20iFAvailable ( useGL20IfAvailable ),
       title ( title ),
       height ( height ),
       width ( width ),
       listener ( listener ),
       graphics ( 0 ),
       input ( 0 ),
       logLevel ( gdx::Application::LOG_INFO ) {
}

void main_looper() {
    g_application->step();
}

void EmscriptenApplication::run() {
}

void EmscriptenApplication::initialize() {
    g_application = this;
    
    graphics = new EmscriptenGraphics ( useGL20iFAvailable );
    input = new EmscriptenInput();
    files = new EmscriptenFiles();
    //audio = new EmscriptenOpenALAudio();

    graphics->initialize();
    graphics->setTitle ( this->title );
    graphics->setDisplayMode ( width, height, false );

    SDL_EnableKeyRepeat ( 1, SDL_DEFAULT_REPEAT_INTERVAL );

    ::initialize ( this, graphics, audio, input, files );

    listener->create();
    listener->resize ( graphics->getWidth(), graphics->getHeight() );

    graphics->updateTime(); // ensuring that the first loop will came with no time difference
    
    emscripten_set_main_loop(main_looper, 0, 0);
}

void scripten::EmscriptenApplication::onRunnableStop() {
    //DUMMY
}

void EmscriptenApplication::update() {
}

void scripten::EmscriptenApplication::step() {
    graphics->updateTime();

    if ( !processEvents() ) {
        return;
    }

    {
        lock_holder hnd = synchronize();

        std::list < Runnable::ptr >::iterator it = runnables.begin();
        std::list < Runnable::ptr >::iterator end = runnables.end();

        for ( ; it != end; ++it ) {
            ( *it )->run();
        }

        runnables.clear();
    }

    listener->render();
    graphics->update();
    //audio->update();
}


void EmscriptenApplication::error ( const std::string& tag, const char* format, ... ) {
    va_list list;
    va_start ( list, format );
    std::string newTag = tag + ":" + format + "\n";

    vfprintf ( stderr, newTag.c_str(), list );
    fflush ( stderr );
#if DEBUG
    assert ( false );
#endif
}

void gdx::scripten::EmscriptenApplication::exit() {
    if ( listener ) {
        this->listener->dispose();
        delete listener;
        listener = NULL;
    }

    std::exit ( 0 );
}

Audio* gdx::scripten::EmscriptenApplication::getAudio() {
    return this->audio;
}

Files* gdx::scripten::EmscriptenApplication::getFiles() {
    return files;
}

Graphics* gdx::scripten::EmscriptenApplication::getGraphics() {
    return graphics;
}

Input* gdx::scripten::EmscriptenApplication::getInput() {
    return input;
}

Preferences* gdx::scripten::EmscriptenApplication::getPreferences ( std::string& name ) {
    return nullptr;
}

gdx::Application::ApplicationType gdx::scripten::EmscriptenApplication::getType() {
    return gdx::Application::Desktop;
}

void EmscriptenApplication::log ( const std::string& tag, const char* format, ... ) {
    if ( logLevel == gdx::Application::LOG_NONE ) {
        return;
    }

    va_list list;
    va_start ( list, format );
    std::string newTag = tag + ":" + format + "\n";

    vfprintf ( stdout, newTag.c_str(), list );
    fflush ( stdout );
}

int gdx::scripten::EmscriptenApplication::getVersion() {
    return 0.1;
}

void gdx::scripten::EmscriptenApplication::postRunnable ( Runnable::ptr runnable ) {
    lock_holder hnd = synchronize();
    runnables.push_back ( runnable );
}

void gdx::scripten::EmscriptenApplication::setLogLevel ( int logLevel ) {
    logLevel = logLevel;
}

bool gdx::scripten::EmscriptenApplication::processEvents() {
    
    static SDL_Event event;

    while ( SDL_PollEvent ( &event ) ) {
        if ( event.type == SDL_QUIT ) {
            this->exit();
            return false;
        } else {
            this->input->processEvents ( event );
        }
    }

    return true;
}

void EmscriptenApplication::pause() {
    this->listener->pause();
}

EmscriptenApplication::~EmscriptenApplication() {
    delete graphics;
    delete audio;
    delete files;
    delete input;
}

void EmscriptenApplication::postRunnable ( std::function< void() > runnable ) {
    this->postRunnable ( Runnable::ptr ( new RunnableFunctionExecutor ( runnable ) ) );
}
