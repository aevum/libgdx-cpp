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

#include <stdexcept>
#include <gdx-cpp/Gdx.hpp>
#include <gdx-cpp/Graphics.hpp>
#include <gdx-cpp/implementation/System.hpp>
#include <iostream>
#include <stdlib.h>

#include <cassert>
#include <gdx-cpp/Application.hpp>
#include <gdx-cpp/graphics/glutils/FileTextureData.hpp>

#include <gdx-cpp/graphics/g2d/Gdx2DPixmap.hpp>
#include <gdx-cpp/graphics/g2d/svg/AggSvgPixmap.hpp>

#include <gdx-cpp/graphics/GL10.hpp>
#include <gdx-cpp/graphics/GL11.hpp>
#include <gdx-cpp/graphics/GLCommon.hpp>
#include <gdx-cpp/graphics/GL20.hpp>
#include <gdx-cpp/graphics/GLU.hpp>
#include <gdx-cpp/gl.hpp>
#include "AndroidGLU.hpp"

using namespace gdx::android;
using namespace gdx;

gdx::android::AndroidGraphics::AndroidGraphics() :
vsync(false),
title("GDX-ANDROID"),
gl10(0),
gl11(0),
gl20(0),
glu(new AndroidGLU),
glCommon(0),
lastTime(0),
frames(0),
frameStart(0),
deltaTime(0)
{
}

gdx::GL10* gdx::android::AndroidGraphics::getGL10()
{
    return gl10;
}

gdx::GL11* gdx::android::AndroidGraphics::getGL11()
{
    return gl11;
}

gdx::GL20* gdx::android::AndroidGraphics::getGL20()
{
    return gl20;
}

gdx::GLU* gdx::android::AndroidGraphics::getGLU()
{
    return glu;
}

gdx::Graphics::BufferFormat gdx::android::AndroidGraphics::getBufferFormat()
{

}

float gdx::android::AndroidGraphics::getDeltaTime()
{
    return deltaTime;
}

float gdx::android::AndroidGraphics::getDensity()
{

}

gdx::Graphics::DisplayMode gdx::android::AndroidGraphics::getDesktopDisplayMode()
{

}

std::vector< gdx::Graphics::DisplayMode >& gdx::android::AndroidGraphics::getDisplayModes()
{

}

int gdx::android::AndroidGraphics::getFramesPerSecond()
{
    return this->fps;
}

gdx::GLCommon* gdx::android::AndroidGraphics::getGLCommon()
{
    return gl10;
}

int gdx::android::AndroidGraphics::getHeight()
{
    return this->height;
}

float gdx::android::AndroidGraphics::getPpcX()
{

}

float gdx::android::AndroidGraphics::getPpcY()
{

}

float gdx::android::AndroidGraphics::getPpiX()
{

}

float gdx::android::AndroidGraphics::getPpiY()
{

}

void gdx::android::AndroidGraphics::updateTime()
{
    uint64_t time = system->nanoTime();

    //This is to fix a nasty bug on HTC devices. Somehow sometimes the nanotime returns
    //with a very big value, this making the delta time go kucko :(
    if (time - lastTime > 10000000000LL) {
        lastTime = system->nanoTime();        
        return;
    }
    
    deltaTime = (time - lastTime) / 1000000000.0f;
    lastTime = time;
    
    if (time - frameStart >= 1000000000) {
        fps = frames;
        frames = 0;
        frameStart = time;
    }
    frames++;
}

gdx::Graphics::GraphicsType gdx::android::AndroidGraphics::getType()
{
    return gdx::Graphics::AndroidGL;
}

int gdx::android::AndroidGraphics::getWidth()
{
    return this->width;
}

bool gdx::android::AndroidGraphics::isGL11Available()
{
    return gl11 != NULL;
}

bool gdx::android::AndroidGraphics::isGL20Available()
{
    return gl20 != NULL;
}

bool gdx::android::AndroidGraphics::setDisplayMode(gdx::Graphics::DisplayMode displayMode)
{    
    if (!supportsDisplayModeChange())
        return false;
}

void gdx::android::AndroidGraphics::setIcon(gdx::Pixmap::ptr pixmap)
{
    this->iconPixmap = pixmap;
}

void gdx::android::AndroidGraphics::setTitle(const std::string& title)
{
    this->title = title;
}

void gdx::android::AndroidGraphics::setVSync(bool vsync)
{
    this->vsync = true;
}

bool gdx::android::AndroidGraphics::supportsDisplayModeChange()
{
    return false;
}

bool gdx::android::AndroidGraphics::supportsExtension(const std::string& extension)
{
    return false;
}

void gdx::android::AndroidGraphics::initialize()
{
    const GLubyte* version = ::glGetString(GL_VERSION);
    int major = atoi((const char*) version);
    int minor = atoi((const char*) &version[2]);
    
    if (false && major >= 2) {
        
        
    } else {
        if (major == 1 && minor < 5) {
            glCommon = gl10 = new GL10;
        } else {
            glCommon = gl10 = gl11 = new GL11;
        }
    }

    assert(glCommon);    
}

bool gdx::android::AndroidGraphics::setDisplayMode(int width, int height, bool fullscreen)
{
    this->width = width;
    this->height = height;

    this->lastTime = system->nanoTime();
    glCommon->glViewport(0, 0, width, height);
}

void gdx::android::AndroidGraphics::update()
{
}

void android::AndroidGraphics::resize(int width, int height)
{
    this->width = width;
    this->height = height;
    this->lastTime = system->nanoTime();
    glCommon->glViewport(0, 0, width, height);
}

TextureData::ptr android::AndroidGraphics::resolveTextureData(FileHandle::ptr fileHandle,
                                                                        Pixmap::ptr preloadedPixmap,
                                                                        const gdx::Pixmap::Format* format,
                                                                        bool useMipMaps)
{
    return TextureData::ptr(new FileTextureData(fileHandle, preloadedPixmap, format, useMipMaps));
}

Pixmap* android::AndroidGraphics::resolvePixmap(int width, int height, const gdx::Pixmap::Format& format, int pixType)
{
    switch(pixType) {
        case Pixmap::Gdx2d:
            return Gdx2DPixmap::newPixmap(width, height, Gdx2DPixmap::Format::toGdx2DPixmapFormat(format));
        case Pixmap::Svg:
            return new AggSvgPixmap(width, height);
    }
}

Pixmap* android::AndroidGraphics::resolvePixmap(const gdx::Pixmap& other)
{
    switch(other.getType()) {
        case Pixmap::Gdx2d:
            return new Gdx2DPixmap((Gdx2DPixmap&)other);
        case Pixmap::Svg:
        default:
            gdx_log_error("gdx","Pixmap of type Svg doesnt provide a copy constructor");
    } 
}

Pixmap* android::AndroidGraphics::resolvePixmap(const gdx::FileHandle::ptr& file)
{
    std::string extension = file->extension();
    
    if (extension == "png" || extension == "jpg" || extension == "tga" || extension == "bmp") {
        gdx::FileHandle::buffer_ptr data;
        int len = file->readBytes(data);
        return Gdx2DPixmap::newPixmapFromBuffer((unsigned char*) data.get(), len, 0);
    } else if (extension == "svg") {
        return AggSvgPixmap::newFromFile(file);
    } else {
        gdx_log_error("gdx","unsupported image format: %s", extension.c_str());
    }
}
