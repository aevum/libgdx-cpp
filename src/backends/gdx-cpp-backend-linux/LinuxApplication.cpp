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


#include "LinuxApplication.hpp"
#include <iostream>
#include <cstdlib>
#include <gdx-cpp/Graphics.hpp>
#include <gdx-cpp/Gdx.hpp>
#include <gdx-cpp/implementation/System.hpp>

using namespace gdx_cpp::backends::nix;
using namespace gdx_cpp;

gdx_cpp::backends::nix::LinuxApplication::LinuxApplication(gdx_cpp::ApplicationListener* listener,
                                                           const std::string& title, int width, int height,
                                                           bool useGL20IfAvailable)
:  Synchronizable(Gdx::system->getMutexFactory())
    , width(width)
    , height(height)
    , title(title)
    , useGL20iFAvailable(useGL20IfAvailable)
    , listener(listener)
    , graphics(0)
    , input(0)
    , logLevel(gdx_cpp::Application::LOG_INFO)
{
    initialize();
}

void LinuxApplication::initialize() {
        graphics = new LinuxGraphics();
        input = new LinuxInput();
        files = new LinuxFiles();
        
        graphics->initialize();
        graphics->setTitle(this->title);
        graphics->setDisplayMode(width, height, false);
        
        Gdx::initialize(this, graphics, NULL, NULL, files);
        
        this->run();
}

void backends::nix::LinuxApplication::onRunnableStop()
{
    //DUMMY
}

void backends::nix::LinuxApplication::run()
{
    listener->create();
    listener->resize(graphics->getWidth(), graphics->getHeight());
    
    while (true) {
        graphics->updateTime();

        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                this->exit();
                return;
            } else {
                this->input->processEvents(event);
            }
        }        
        
        {
            lock_holder hnd = synchronize();

            std::list < Runnable::ptr >::iterator it = runnables.begin();
            std::list < Runnable::ptr >::iterator end = runnables.end();

            for(;it != end; ++it) {
                (*it)->run();
            }

            runnables.clear();
        }
        
        listener->render();
        graphics->update();
    }
}


void LinuxApplication::error(const std::string& tag, const char* format, ...)
{
    va_list list;
    va_start(list, format);
    std::string newTag = tag + ":" + format + "\n";
    
    vfprintf(stderr, newTag.c_str(), list);
    fflush(stderr);
#if DEBUG
    assert(false);
#endif
}

void gdx_cpp::backends::nix::LinuxApplication::exit()
{
    ::exit(0);
}

Audio* gdx_cpp::backends::nix::LinuxApplication::getAudio()
{

}

Files* gdx_cpp::backends::nix::LinuxApplication::getFiles()
{
    return files;
}

Graphics* gdx_cpp::backends::nix::LinuxApplication::getGraphics()
{
    return graphics;
}

Input* gdx_cpp::backends::nix::LinuxApplication::getInput()
{
    return input;
}

Preferences* gdx_cpp::backends::nix::LinuxApplication::getPreferences(std::string& name)
{

}

gdx_cpp::Application::ApplicationType gdx_cpp::backends::nix::LinuxApplication::getType()
{
    return gdx_cpp::Application::Desktop;
}

void LinuxApplication::log(const std::string& tag, const char* format, ...)
{
    if (logLevel == gdx_cpp::Application::LOG_NONE)
        return;

    va_list list;
    va_start(list, format);
    std::string newTag = tag + ":" + format + "\n"; 
    
    vfprintf(stdout, newTag.c_str(), list);
    fflush(stdout);
}

int gdx_cpp::backends::nix::LinuxApplication::getVersion()
{
    return 0.1;
}

void gdx_cpp::backends::nix::LinuxApplication::postRunnable(Runnable::ptr runnable)
{
    lock_holder hnd = synchronize();
    runnables.push_back(runnable);
}

void gdx_cpp::backends::nix::LinuxApplication::setLogLevel(int logLevel)
{
    logLevel = logLevel;
}
