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


#include "AndroidGraphics.hpp"

#include "AndroidGL10.hpp"
#include "AndroidGL11.hpp"
#include "AndroidGL20.hpp"
#include "AndroidGLU.hpp"
#include <stdexcept>
#include <gdx-cpp/Gdx.hpp>
#include <gdx-cpp/Graphics.hpp>
#include <gdx-cpp/implementation/System.hpp>
#include <iostream>
#include <stdlib.h>

#include <cassert>

using namespace gdx_cpp::backends::android;
using namespace gdx_cpp::graphics;
using namespace gdx_cpp;

gdx_cpp::backends::android::AndroidGraphics::AndroidGraphics() :
gl10(0)
,gl11(0)
,gl20(0)
,glu(new AndroidGLU)
,glCommon(0)
,deltaTime(0)
,lastTime(0)
,frameStart(0)
,frames(0)
,vsync(false)
,title("GDX-ANDROID")
{
}

gdx_cpp::graphics::GL10* gdx_cpp::backends::android::AndroidGraphics::getGL10()
{
    return gl10;
}

gdx_cpp::graphics::GL11* gdx_cpp::backends::android::AndroidGraphics::getGL11()
{
    return gl11;
}

gdx_cpp::graphics::GL20* gdx_cpp::backends::android::AndroidGraphics::getGL20()
{
    return gl20;
}

gdx_cpp::graphics::GLU* gdx_cpp::backends::android::AndroidGraphics::getGLU()
{
    return glu;
}

gdx_cpp::Graphics::BufferFormat gdx_cpp::backends::android::AndroidGraphics::getBufferFormat()
{

}

float gdx_cpp::backends::android::AndroidGraphics::getDeltaTime()
{
    return deltaTime;
}

float gdx_cpp::backends::android::AndroidGraphics::getDensity()
{

}

gdx_cpp::Graphics::DisplayMode gdx_cpp::backends::android::AndroidGraphics::getDesktopDisplayMode()
{

}

std::vector< gdx_cpp::Graphics::DisplayMode >& gdx_cpp::backends::android::AndroidGraphics::getDisplayModes()
{

}

int gdx_cpp::backends::android::AndroidGraphics::getFramesPerSecond()
{
    return this->fps;
}

gdx_cpp::graphics::GLCommon* gdx_cpp::backends::android::AndroidGraphics::getGLCommon()
{
    return gl10;
}

int gdx_cpp::backends::android::AndroidGraphics::getHeight()
{
    return this->height;
}

float gdx_cpp::backends::android::AndroidGraphics::getPpcX()
{

}

float gdx_cpp::backends::android::AndroidGraphics::getPpcY()
{

}

float gdx_cpp::backends::android::AndroidGraphics::getPpiX()
{

}

float gdx_cpp::backends::android::AndroidGraphics::getPpiY()
{

}

void gdx_cpp::backends::android::AndroidGraphics::updateTime()
{
    uint64_t time = Gdx::system->nanoTime();

    deltaTime = (time - lastTime) / 1000000000.0f;
    lastTime = time;
    
    if (time - frameStart >= 1000000000) {
        fps = frames;
        frames = 0;
        frameStart = time;
    }
    frames++;
}

gdx_cpp::Graphics::GraphicsType gdx_cpp::backends::android::AndroidGraphics::getType()
{
    return gdx_cpp::Graphics::AndroidGL;
}

int gdx_cpp::backends::android::AndroidGraphics::getWidth()
{
    return this->width;
}

bool gdx_cpp::backends::android::AndroidGraphics::isGL11Available()
{
    return gl11 != NULL;
}

bool gdx_cpp::backends::android::AndroidGraphics::isGL20Available()
{
    return gl20 != NULL;
}

bool gdx_cpp::backends::android::AndroidGraphics::setDisplayMode(gdx_cpp::Graphics::DisplayMode displayMode)
{    
    if (!supportsDisplayModeChange())
        return false;
}

void gdx_cpp::backends::android::AndroidGraphics::setIcon(gdx_cpp::graphics::Pixmap::ptr pixmap)
{
    this->iconPixmap = pixmap;
}

void gdx_cpp::backends::android::AndroidGraphics::setTitle(const std::string& title)
{
    this->title = title;
}

void gdx_cpp::backends::android::AndroidGraphics::setVSync(bool vsync)
{
    this->vsync = true;
}

bool gdx_cpp::backends::android::AndroidGraphics::supportsDisplayModeChange()
{
    return false;
}

bool gdx_cpp::backends::android::AndroidGraphics::supportsExtension(const std::string& extension)
{
    return false;
}

void gdx_cpp::backends::android::AndroidGraphics::initialize()
{
    const GLubyte* version = glGetString(GL_VERSION);
    int major = atoi((const char*) version);
    int minor = atoi((const char*) &version[2]);
    
    if (false && major >= 2) {
        
        
    } else {
        if (major == 1 && minor < 5) {
            glCommon = gl10 = new AndroidGL10;
        } else {
            glCommon = gl10 = gl11 = new AndroidGL11;
        }
    }

    assert(glCommon);    
}

bool gdx_cpp::backends::android::AndroidGraphics::setDisplayMode(int width, int height, bool fullscreen)
{
    this->width = width;
    this->height = height;

    this->lastTime = Gdx::system->nanoTime();
    glCommon->glViewport(0, 0, width, height);
}

void gdx_cpp::backends::android::AndroidGraphics::update()
{
}

void backends::android::AndroidGraphics::resize(int width, int height)
{
    this->width = width;
    this->height = height;
    this->lastTime = Gdx::system->nanoTime();
    glCommon->glViewport(0, 0, width, height);
}

