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


#include "LinuxGraphics.hpp"

#include "LinuxGL10.hpp"
#include "LinuxGL11.hpp"
#include "LinuxGL20.hpp"
#include "LinuxGLU.hpp"
#include <stdexcept>

using namespace gdx_cpp::backends::nix;
using namespace gdx_cpp::graphics;

gdx_cpp::backends::nix::LinuxGraphics::LinuxGraphics() :
gl10(new LinuxGL10)
,gl11(new LinuxGL11)
,gl20(0)
,glu(new LinuxGLU)
{
}

gdx_cpp::graphics::GL10* gdx_cpp::backends::nix::LinuxGraphics::getGL10()
{
    return gl10;
}

gdx_cpp::graphics::GL11* gdx_cpp::backends::nix::LinuxGraphics::getGL11()
{
    return gl11;
}

gdx_cpp::graphics::GL20* gdx_cpp::backends::nix::LinuxGraphics::getGL20()
{
    return gl20;
}

gdx_cpp::graphics::GLU* gdx_cpp::backends::nix::LinuxGraphics::getGLU()
{
    return glu;
}

gdx_cpp::Graphics::BufferFormat gdx_cpp::backends::nix::LinuxGraphics::getBufferFormat()
{

}

float gdx_cpp::backends::nix::LinuxGraphics::getDeltaTime()
{

}

float gdx_cpp::backends::nix::LinuxGraphics::getDensity()
{

}

gdx_cpp::Graphics::DisplayMode gdx_cpp::backends::nix::LinuxGraphics::getDesktopDisplayMode()
{

}

std::vector< gdx_cpp::Graphics::DisplayMode >& gdx_cpp::backends::nix::LinuxGraphics::getDisplayModes()
{

}

int gdx_cpp::backends::nix::LinuxGraphics::getFramesPerSecond()
{

}

gdx_cpp::graphics::GLCommon* gdx_cpp::backends::nix::LinuxGraphics::getGLCommon()
{
    return gl10;
}

int gdx_cpp::backends::nix::LinuxGraphics::getHeight()
{

}

float gdx_cpp::backends::nix::LinuxGraphics::getPpcX()
{

}

float gdx_cpp::backends::nix::LinuxGraphics::getPpcY()
{

}

float gdx_cpp::backends::nix::LinuxGraphics::getPpiX()
{

}

float gdx_cpp::backends::nix::LinuxGraphics::getPpiY()
{

}

gdx_cpp::Graphics::GraphicsType gdx_cpp::backends::nix::LinuxGraphics::getType()
{

}

int gdx_cpp::backends::nix::LinuxGraphics::getWidth()
{

}

bool gdx_cpp::backends::nix::LinuxGraphics::isGL11Available()
{
    return gl11 != NULL;
}

bool gdx_cpp::backends::nix::LinuxGraphics::isGL20Available()
{
    return gl20 != NULL;
}

bool gdx_cpp::backends::nix::LinuxGraphics::setDisplayMode(gdx_cpp::Graphics::DisplayMode displayMode)
{
    if (!supportsDisplayModeChange())
        return false;
}

void gdx_cpp::backends::nix::LinuxGraphics::setIcon(gdx_cpp::Pixmap& pixmap)
{

}

void gdx_cpp::backends::nix::LinuxGraphics::setTitle(const std::string& title)
{
    this->title = title;
}

void gdx_cpp::backends::nix::LinuxGraphics::setVSync(bool vsync)
{
    
}

bool gdx_cpp::backends::nix::LinuxGraphics::supportsDisplayModeChange()
{
    return false;
}

bool gdx_cpp::backends::nix::LinuxGraphics::supportsExtension(const std::string& extension)
{
    return false;
}

void gdx_cpp::backends::nix::LinuxGraphics::initialize()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw std::runtime_error("Failed to initialize SDL video");
    }
}

bool gdx_cpp::backends::nix::LinuxGraphics::setDisplayMode(int width, int height, bool fullscreen)
{
    Uint32 flags = SDL_OPENGL;
    if (fullscreen)
        flags |= SDL_FULLSCREEN;

    const SDL_VideoInfo* info = SDL_GetVideoInfo();

    SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 );
    SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 5 );
    SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 );
    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
    
    if (!SDL_SetVideoMode(width, height, 32, SDL_OPENGL)) {
        throw std::runtime_error("Failed to initialize SDL video");
    }

    gl10->glViewport(0, 0, width, height);
}

void gdx_cpp::backends::nix::LinuxGraphics::update()
{
    SDL_GL_SwapBuffers();
}

