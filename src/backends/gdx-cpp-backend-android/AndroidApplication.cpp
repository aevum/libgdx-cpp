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


#include "AndroidApplication.hpp"
#include <iostream>
#include <cstdlib>
#include <gdx-cpp/Graphics.hpp>
#include <gdx-cpp/Gdx.hpp>
#include <gdx-cpp/implementation/System.hpp>
#include <android/log.h>
#include <stdexcept>
#include <cassert>


using namespace gdx::android;
using namespace gdx;

gdx::android::AndroidApplication::AndroidApplication(gdx::ApplicationListener* listener,
        const std::string& title, int width, int height, bool useGL20IfAvailable)
        :  Synchronizable(Gdx::system->getMutexFactory())
        , title(title)
        , useGL20iFAvailable(useGL20IfAvailable)
        , width(width)
        , height(height)
        , listener(listener)
        , graphics(NULL)
        , input(NULL)
        , logLevel(gdx::Application::LOG_INFO)
        , files(NULL)
        , audio(NULL)
{
    initialize();
}

void AndroidApplication::initialize() {
    graphics = new AndroidGraphics();
    input = new AndroidInput();
    files = new AndroidFiles();
    audio = new AndroidAudio();
    
    graphics->initialize();
    graphics->setTitle(this->title);
    graphics->setDisplayMode(width, height, false);

    Gdx::initialize(this, graphics, audio, input, files);
}

void android::AndroidApplication::onRunnableStop()
{
    //DUMMY
}

void android::AndroidApplication::run()
{
    graphics->updateTime();

    {
        lock_holder hnd = synchronize();

        std::list < Runnable::ptr >::iterator it = runnables.begin();
        std::list < Runnable::ptr >::iterator end = runnables.end();

        for (;it != end; ++it) {
            (*it)->run();
        }

        runnables.clear();
    }

    listener->render();
    graphics->update();
}

void AndroidApplication::error(const std::string& tag, const char* format, ...)
{
    va_list list;
    va_start(list, format);
    __android_log_vprint(ANDROID_LOG_ERROR, tag.c_str(),format, list);

#if DEBUG
    assert(false);
#endif
}

void gdx::android::AndroidApplication::exit()
{
    ::exit(0);
}

Audio* gdx::android::AndroidApplication::getAudio()
{
    return audio;
}

Files* gdx::android::AndroidApplication::getFiles()
{
    return files;
}

Graphics* gdx::android::AndroidApplication::getGraphics()
{    
    return graphics;
}

Input* gdx::android::AndroidApplication::getInput()
{
    return input;
}

Preferences* gdx::android::AndroidApplication::getPreferences(std::string& name)
{
    throw std::runtime_error("not implemented");
}

gdx::Application::ApplicationType gdx::android::AndroidApplication::getType()
{
    return gdx::Application::Desktop;
}

void android::AndroidApplication::pause()
{
    listener->pause();
}

void AndroidApplication::resume() {
    listener->resume();
}


void android::AndroidApplication::update()
{
    run();
}

void android::AndroidApplication::create()
{
    listener->create();
    listener->resize(graphics->getWidth(), graphics->getHeight());
}


void gdx::android::AndroidApplication::log(const std::string& tag, const char* format, ...)
{
    if (logLevel == gdx::Application::LOG_NONE)
        return;
    
    va_list list;
    va_start(list, format);
    __android_log_vprint(ANDROID_LOG_INFO, tag.c_str(),format, list);
}

int gdx::android::AndroidApplication::getVersion()
{
    return 0.1;
}

void gdx::android::AndroidApplication::postRunnable(Runnable::ptr runnable)
{
    lock_holder hnd = synchronize();
    runnables.push_back(runnable);
}

void gdx::android::AndroidApplication::setLogLevel(int logLevel)
{
    this->logLevel = logLevel;
}

