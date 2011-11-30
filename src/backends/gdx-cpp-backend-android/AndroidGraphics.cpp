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
#include <gdx-cpp/Application.hpp>
#include <gdx-cpp/graphics/glutils/FileTextureData.hpp>

#include <gdx-cpp/graphics/g2d/Gdx2DPixmap.hpp>
#include <gdx-cpp/graphics/g2d/svg/AggSvgPixmap.hpp>

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

    //This is to fix a nasty bug on HTC devices. Somehow sometimes the nanotime returns
    //with a very big value, this making the delta time go kucko :(
    if (time - lastTime > 10000000000LL) {
        lastTime = Gdx::system->nanoTime();        
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

TextureData::ptr backends::android::AndroidGraphics::resolveTextureData(files::FileHandle::ptr fileHandle,
                                                                        graphics::Pixmap::ptr preloadedPixmap,
                                                                        const gdx_cpp::graphics::Pixmap::Format* format,
                                                                        bool useMipMaps)
{
    return TextureData::ptr(new glutils::FileTextureData(fileHandle, preloadedPixmap, format, useMipMaps));
}

graphics::Pixmap* backends::android::AndroidGraphics::resolvePixmap(int width, int height, const gdx_cpp::graphics::Pixmap::Format& format, int pixType)
{
    switch(pixType) {
        case graphics::Pixmap::Gdx2d:
            return g2d::Gdx2DPixmap::newPixmap(width, height, g2d::Gdx2DPixmap::Format::toGdx2DPixmapFormat(format));
        case graphics::Pixmap::Svg:
            return new g2d::svg::AggSvgPixmap(width, height);
    }
}

graphics::Pixmap* backends::android::AndroidGraphics::resolvePixmap(const gdx_cpp::graphics::Pixmap& other)
{
    switch(other.getType()) {
        case graphics::Pixmap::Gdx2d:
            return new g2d::Gdx2DPixmap((g2d::Gdx2DPixmap&)other);
        case graphics::Pixmap::Svg:
        default:
            throw std::runtime_error("Pixmap of type Svg doesnt provide a copy constructor");
    } 
}

graphics::Pixmap* backends::android::AndroidGraphics::resolvePixmap(const gdx_cpp::files::FileHandle::ptr& file)
{
    std::string extension = file->extension();
    
    if (extension == "png" || extension == "jpg" || extension == "tga" || extension == "bmp") {
        gdx_cpp::files::FileHandle::char_ptr data;
        int len = file->readBytes(data);
        return g2d::Gdx2DPixmap::newPixmapFromBuffer((unsigned char*) data.get(), len, 0);
    } else if (extension == "svg") {
        return g2d::svg::AggSvgPixmap::newFromFile(file);
    } else {
        throw std::runtime_error("unsupported image format: " + extension);
    }
}
