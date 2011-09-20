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


using namespace gdx_cpp::backends::android;
using namespace gdx_cpp;

gdx_cpp::backends::android::AndroidApplication::AndroidApplication(gdx_cpp::ApplicationListener* listener,
        const std::string& title, int width, int height, bool useGL20IfAvailable)
        :  Synchronizable(Gdx::system->getMutexFactory())
        , title(title)
        , useGL20iFAvailable(useGL20IfAvailable)
        , width(width)
        , height(height)
        , listener(listener)
        , graphics(0)
        , input(0)
        , logLevel(gdx_cpp::Application::LOG_INFO)
        , files(0)
{
    initialize();
}

void AndroidApplication::initialize() {
    graphics = new AndroidGraphics();
    input = new AndroidInput();
    files = new AndroidFiles();
    
    graphics->initialize();
    graphics->setTitle(this->title);
    graphics->setDisplayMode(width, height, false);

    Gdx::initialize(this, graphics, NULL, input, files);
}

void backends::android::AndroidApplication::onRunnableStop()
{
    //DUMMY
}

void backends::android::AndroidApplication::run()
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

void gdx_cpp::backends::android::AndroidApplication::exit()
{
    ::exit(0);
}

Audio* gdx_cpp::backends::android::AndroidApplication::getAudio()
{

}

Files* gdx_cpp::backends::android::AndroidApplication::getFiles()
{

}

Graphics* gdx_cpp::backends::android::AndroidApplication::getGraphics()
{
    
    return graphics;
}

Input* gdx_cpp::backends::android::AndroidApplication::getInput()
{
    return input;
}

Preferences* gdx_cpp::backends::android::AndroidApplication::getPreferences(std::string& name)
{

}

gdx_cpp::Application::ApplicationType gdx_cpp::backends::android::AndroidApplication::getType()
{
    return gdx_cpp::Application::Desktop;
}

void backends::android::AndroidApplication::pause()
{

}

void backends::android::AndroidApplication::update()
{
    run();
}

void backends::android::AndroidApplication::create()
{
    listener->create();
    listener->resize(graphics->getWidth(), graphics->getHeight());
}


void gdx_cpp::backends::android::AndroidApplication::log(const std::string& tag, const char* format, ...)
{
    if (logLevel == gdx_cpp::Application::LOG_NONE)
        return;
    
    va_list list;
    va_start(list, format);
    __android_log_vprint(ANDROID_LOG_INFO, tag.c_str(),format, list);
}

int gdx_cpp::backends::android::AndroidApplication::getVersion()
{
    return 0.1;
}

void gdx_cpp::backends::android::AndroidApplication::postRunnable(Runnable::ptr runnable)
{
    lock_holder hnd = synchronize();
    runnables.push_back(runnable);
}

void gdx_cpp::backends::android::AndroidApplication::setLogLevel(int logLevel)
{
    logLevel = logLevel;
}
