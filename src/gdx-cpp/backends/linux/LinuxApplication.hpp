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


#ifndef GDX_CPP_BACKENDS_LINUX_LINUXAPPLICATION_HPP
#define GDX_CPP_BACKENDS_LINUX_LINUXAPPLICATION_HPP

#include <gdx-cpp/Application.hpp>
#include <list>
#include <gdx-cpp/ApplicationListener.hpp>
#include "LinuxGraphics.hpp"
#include <gdx-cpp/implementation/Thread.hpp>
#include <gdx-cpp/implementation/Mutex.hpp>
#include <gdx-cpp/utils/Synchronized.hpp>
#include "LinuxInput.hpp"
#include "LinuxFiles.hpp"
#include "LinuxOpenALAudio.hpp"

namespace gdx {

namespace nix {

class LinuxApplication : public Application, public Runnable, public Synchronizable
{
public:
    LinuxApplication(gdx::ApplicationListener* listener, std::string  title,
                     int width, int height, bool useGL20IfAvailable);

    void error(const std::string& tag, const char* format, ...);
    void exit() override;
    Audio* getAudio() override;
    Files* getFiles() override;
    Graphics* getGraphics() override;
    Input* getInput() override;
    Preferences* getPreferences(std::string& name) override;
    ApplicationType getType() override;
    int getVersion() override;
    void postRunnable(Runnable::ptr runnable) override;
    virtual void postRunnable(std::function< void() > runnable) override;

    void onRunnableStop() override;
    virtual void initialize();

    virtual void pause() override;
    virtual void update() override;

    virtual ~LinuxApplication();

protected:
    virtual void run() override;
    virtual bool processEvents();

    bool useGL20iFAvailable;
    std::string title;
    int height;
    int width;
    ApplicationListener* listener;
    LinuxGraphics* graphics;
    LinuxInput* input;
    LinuxFiles* files;
    LinuxOpenALAudio* audio;

    std::list< Runnable::ptr > runnables;

    gdx::Thread::ptr mainLoopThread;

    int logLevel;
};

}

}

#endif // GDX_CPP_BACKENDS_LINUX_LINUXAPPLICATION_HPP
