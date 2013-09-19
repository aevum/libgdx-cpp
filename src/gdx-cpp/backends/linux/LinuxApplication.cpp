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

using namespace gdx::nix;
using namespace gdx;

gdx::nix::LinuxApplication::LinuxApplication(gdx::ApplicationListener* listener,
        std::string  title, int width, int height,
        bool useGL20IfAvailable)
    :  Synchronizable(gdx::system->getMutexFactory()),
useGL20iFAvailable(useGL20IfAvailable),
title(std::move(title)),
height(height),
width(width),
listener(listener),
graphics(nullptr),
input(nullptr)
{
}

void LinuxApplication::initialize() {

    graphics = new LinuxGraphics(useGL20iFAvailable);
    input = new LinuxInput();
    files = new LinuxFiles();
    audio = new LinuxOpenALAudio();

    graphics->initialize();
    graphics->setTitle(this->title);
    graphics->setDisplayMode(width, height, false);

    SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_INTERVAL);

    ::initialize(this, graphics, audio, input, files);

    this->run();
}

void nix::LinuxApplication::onRunnableStop()
{
    //DUMMY
}

void nix::LinuxApplication::run()
{
    listener->create();
    listener->resize(graphics->getWidth(), graphics->getHeight());

    graphics->updateTime(); // ensuring that the first loop will came with no time difference
    while (true) {
        graphics->updateTime();

        if (!processEvents()) {
            return;
        }

        {
            lock_holder hnd = synchronize();

            auto it = runnables.begin();
            auto end = runnables.end();

            for (; it != end; ++it) {
                (*it)->run();
            }

            runnables.clear();
        }

        listener->render();
        graphics->update();
        audio->update();
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

void gdx::nix::LinuxApplication::exit()
{
    if (listener) {
        this->listener->dispose();
        delete listener;
        listener = nullptr;
    }
    
    std::exit(0);
}

Audio* gdx::nix::LinuxApplication::getAudio()
{
    return this->audio;
}

Files* gdx::nix::LinuxApplication::getFiles()
{
    return files;
}

Graphics* gdx::nix::LinuxApplication::getGraphics()
{
    return graphics;
}

Input* gdx::nix::LinuxApplication::getInput()
{
    return input;
}

Preferences* gdx::nix::LinuxApplication::getPreferences(std::string& name)
{
    return nullptr;
}

gdx::Application::ApplicationType gdx::nix::LinuxApplication::getType()
{
    return gdx::Application::Desktop;
}

int gdx::nix::LinuxApplication::getVersion()
{
    return 1;
}

void gdx::nix::LinuxApplication::postRunnable(Runnable::ptr runnable)
{
    lock_holder hnd = synchronize();
    runnables.push_back(runnable);
}

bool gdx::nix::LinuxApplication::processEvents()
{
    static SDL_Event event;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            this->exit();
            return false;
        } else {
            this->input->processEvents(event);
        }
    }

    return true;
}

void LinuxApplication::pause()
{
    this->listener->pause();
}

void LinuxApplication::update()
{
}

LinuxApplication::~LinuxApplication()
{
    delete graphics;
    delete audio;
    delete files;
    delete input;
}

void LinuxApplication::postRunnable(std::function< void() > runnable)
{
    this->postRunnable(Runnable::ptr(new RunnableFunctionExecutor(runnable)));
}
