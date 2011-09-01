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
{
    initialize();
}

void LinuxApplication::initialize() {
        graphics = new LinuxGraphics();

        Gdx::initialize(this, graphics, NULL, NULL, NULL);
        
        graphics->initialize();
        graphics->setDisplayMode(width, height, false);

        this->run();
}

void backends::nix::LinuxApplication::onRunnableStop()
{
}

void backends::nix::LinuxApplication::run()
{
    listener->create();
    listener->resize(graphics->getWidth(), graphics->getHeight());
    
    while (true) {
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


std::ostream& LinuxApplication::error(const std::string& tag)
{
    std::cerr << "LIBGDX-CPP: " << tag;
    return std::cerr;
}

void gdx_cpp::backends::nix::LinuxApplication::exit()
{
    ::exit(0);
}

gdx_cpp::Audio& gdx_cpp::backends::nix::LinuxApplication::getAudio()
{

}

gdx_cpp::Files& gdx_cpp::backends::nix::LinuxApplication::getFiles()
{

}

gdx_cpp::Graphics& gdx_cpp::backends::nix::LinuxApplication::getGraphics()
{
    return *graphics;
}

gdx_cpp::Input& gdx_cpp::backends::nix::LinuxApplication::getInput()
{

}

gdx_cpp::Preferences& gdx_cpp::backends::nix::LinuxApplication::getPreferences(std::string& name)
{

}

gdx_cpp::Application::ApplicationType gdx_cpp::backends::nix::LinuxApplication::getType()
{

}

std::ostream& gdx_cpp::backends::nix::LinuxApplication::log(const std::string& tag)
{
    std::cout << tag;

    return std::cout;
}

int gdx_cpp::backends::nix::LinuxApplication::getVersion()
{
    return 0.1;
}

void gdx_cpp::backends::nix::LinuxApplication::postRunnable(Runnable::ptr runnable)
{

}

void gdx_cpp::backends::nix::LinuxApplication::setLogLevel(int logLevel)
{

}







