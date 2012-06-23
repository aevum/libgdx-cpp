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


#include "IosGraphics.hpp"

#include "IosGLU.hpp"
#include <stdexcept>

#include <gdx-cpp/Gdx.hpp>
#include <gdx-cpp/Graphics.hpp>
#include <gdx-cpp/implementation/System.hpp>
#include <gdx-cpp/graphics/glutils/FileTextureData.hpp>

#include <iostream>
#include <gdx-cpp/Application.hpp>

#include <gdx-cpp/graphics/Texture.hpp>

#include <gdx-cpp/graphics/g2d/Gdx2DPixmap.hpp>
#include <gdx-cpp/graphics/g2d/svg/AggSvgPixmap.hpp>

#include <gdx-cpp/graphics/GL10.hpp>
#include <gdx-cpp/graphics/GL11.hpp>
#include <gdx-cpp/graphics/GL20.hpp>

#include "IosGLU.hpp"

#import <OpenGLES/ES1/gl.h>

using namespace gdx_cpp::backends::ios;
using namespace gdx_cpp::graphics;
using namespace gdx_cpp;

gdx_cpp::backends::ios::IosGraphics::IosGraphics() :
gl10(0)
,gl11(0)
,gl20(0)
,glu(new IosGLU)
,glCommon(0)
,deltaTime(0)
,lastTime(0)
,frameStart(0)
,frames(0)
,vsync(false)
{
}

gdx_cpp::graphics::GL10* gdx_cpp::backends::ios::IosGraphics::getGL10()
{
    return gl10;
}

gdx_cpp::graphics::GL11* gdx_cpp::backends::ios::IosGraphics::getGL11()
{
    return gl11;
}

gdx_cpp::graphics::GL20* gdx_cpp::backends::ios::IosGraphics::getGL20()
{
    return gl20;
}

gdx_cpp::graphics::GLU* gdx_cpp::backends::ios::IosGraphics::getGLU()
{
    return glu;
}

gdx_cpp::Graphics::BufferFormat gdx_cpp::backends::ios::IosGraphics::getBufferFormat()
{
    throw std::runtime_error("not implemented yet");
}

float gdx_cpp::backends::ios::IosGraphics::getDeltaTime()
{
    return deltaTime;
}

float gdx_cpp::backends::ios::IosGraphics::getDensity()
{
    return 0;
}

gdx_cpp::Graphics::DisplayMode gdx_cpp::backends::ios::IosGraphics::getDesktopDisplayMode()
{
    throw std::runtime_error("not implemented yet");
}

std::vector< gdx_cpp::Graphics::DisplayMode >& gdx_cpp::backends::ios::IosGraphics::getDisplayModes()
{
    throw std::runtime_error("not implemented yet");
}

int gdx_cpp::backends::ios::IosGraphics::getFramesPerSecond()
{
    return this->fps;
}

gdx_cpp::graphics::GLCommon* gdx_cpp::backends::ios::IosGraphics::getGLCommon()
{
    return gl10;
}

int gdx_cpp::backends::ios::IosGraphics::getHeight()
{
    return this->height;
}

float gdx_cpp::backends::ios::IosGraphics::getPpcX()
{
    return 0;
}

float gdx_cpp::backends::ios::IosGraphics::getPpcY()
{
    return 0;
}

float gdx_cpp::backends::ios::IosGraphics::getPpiX()
{
    return 0;
}

float gdx_cpp::backends::ios::IosGraphics::getPpiY()
{
    return 0;
}

void gdx_cpp::backends::ios::IosGraphics::updateTime()
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

gdx_cpp::Graphics::GraphicsType gdx_cpp::backends::ios::IosGraphics::getType()
{
    return gdx_cpp::Graphics::IOsGL;
}

int gdx_cpp::backends::ios::IosGraphics::getWidth()
{
    return this->width;
}

bool gdx_cpp::backends::ios::IosGraphics::isGL11Available()
{
    return gl11 != NULL;
}

bool gdx_cpp::backends::ios::IosGraphics::isGL20Available()
{
    return gl20 != NULL;
}

bool gdx_cpp::backends::ios::IosGraphics::setDisplayMode(gdx_cpp::Graphics::DisplayMode displayMode)
{
    if (!supportsDisplayModeChange())
        return false;
    return true;
}

void gdx_cpp::backends::ios::IosGraphics::setIcon(gdx_cpp::graphics::Pixmap::ptr pixmap)
{
    this->iconPixmap = pixmap;
}

void gdx_cpp::backends::ios::IosGraphics::setTitle(const std::string& title)
{
}

void gdx_cpp::backends::ios::IosGraphics::setVSync(bool vsync)
{
    this->vsync = true;
}

bool gdx_cpp::backends::ios::IosGraphics::supportsDisplayModeChange()
{
    return false;
}

bool gdx_cpp::backends::ios::IosGraphics::supportsExtension(const std::string& extension)
{
    return false;
}

void gdx_cpp::backends::ios::IosGraphics::initialize()
{   
	this->lastTime = Gdx::system->nanoTime();   
    const GLubyte* version = glGetString(GL_VERSION);
	
    if (version) {
        
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
		
        glCommon->glViewport(0, 0, width, height);
    } else {
        throw std::runtime_error("IosGraphics: Failed to recover the GL_VERSION, aborting");
    } 
}

bool gdx_cpp::backends::ios::IosGraphics::setDisplayMode(int width, int height, bool fullscreen)
{
	this->width = width;
	this->height = height;
	
	return true;
}

void gdx_cpp::backends::ios::IosGraphics::update()
{
}

TextureData::ptr backends::ios::IosGraphics::resolveTextureData(gdx_cpp::files::FileHandle::ptr fileHandle,
                                                                  Pixmap::ptr preloadedPixmap,
                                                                  const gdx_cpp::graphics::Pixmap::Format* format,
                                                                  bool useMipMaps)
{
    return TextureData::ptr(new glutils::FileTextureData(fileHandle, preloadedPixmap, format, useMipMaps));
}

Pixmap* backends::ios::IosGraphics::resolvePixmap(int width, int height, const gdx_cpp::graphics::Pixmap::Format& format, int pixType)
{
    switch(pixType) {
        case Pixmap::Gdx2d:
            return g2d::Gdx2DPixmap::newPixmap(width, height, g2d::Gdx2DPixmap::Format::toGdx2DPixmapFormat(format));
        case Pixmap::Svg:
            return new g2d::svg::AggSvgPixmap(width, height);
    }
    return NULL;
}

Pixmap* backends::ios::IosGraphics::resolvePixmap(const gdx_cpp::graphics::Pixmap& other)
{
    switch(other.getType()) {
        case Pixmap::Gdx2d:
            return new g2d::Gdx2DPixmap((g2d::Gdx2DPixmap&)other);
		case Pixmap::Svg:
			break;			
    } 
    return NULL;
}

Pixmap* backends::ios::IosGraphics::resolvePixmap(const gdx_cpp::files::FileHandle::ptr& file)
{
    std::string extension = file->extension();
    
    if (extension == "png" || extension == "jpg" || extension == "tga" || extension == "bmp") {
		gdx_cpp::files::FileHandle::buffer_ptr buffer;
		int length = file->readBytes(buffer);
		return g2d::Gdx2DPixmap::pixmapFromByteArray((unsigned char*) buffer.get(), length, 0);
	}
    else if (extension == "svg") {
        return g2d::svg::AggSvgPixmap::newFromFile(file);        
    } else {
        throw std::runtime_error("unsupported image format: " + extension);
    }
}
