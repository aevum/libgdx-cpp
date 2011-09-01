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

namespace gdx_cpp {

namespace backends {

namespace nix {

class LinuxApplication : public Application, public Runnable, public Synchronizable
{
public:
    LinuxApplication(gdx_cpp::ApplicationListener* listener, const std::string& title,
                     int width, int height, bool useGL20IfAvailable);
    
    std::ostream& error(const std::string& tag);
    void exit();
    Audio& getAudio();
    Files& getFiles();
    Graphics& getGraphics();
    Input& getInput();
    Preferences& getPreferences(std::string& name);
    ApplicationType getType();
    int getVersion();
    std::ostream& log(const std::string& tag);
    void postRunnable(Runnable::ptr runnable);
    void setLogLevel(int logLevel);

    void onRunnableStop();
protected:

    void run();
    
    bool useGL20iFAvailable;
    std::string title;
    int height;
    int width;
    ApplicationListener* listener;
    LinuxGraphics* graphics;
    
    std::list< Runnable::ptr > runnables;

    gdx_cpp::implementation::Thread::ptr mainLoopThread;
    
    void initialize();
};

}

}

}

#endif // GDX_CPP_BACKENDS_LINUX_LINUXAPPLICATION_HPP
