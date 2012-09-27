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

using namespace gdx::ios;
using namespace gdx;

gdx::ios::IosGraphics::IosGraphics() :
vsync(false),
width(0),
height(0),
gl10(0),
gl11(0),
gl20(0),
glu(new IosGLU),
glCommon(0),
lastTime(0),
frames(0),
frameStart(0),
deltaTime(0)
{
}

gdx::GL10* gdx::ios::IosGraphics::getGL10()
{
    return gl10;
}

gdx::GL11* gdx::ios::IosGraphics::getGL11()
{
    return gl11;
}

gdx::GL20* gdx::ios::IosGraphics::getGL20()
{
    return gl20;
}

gdx::GLU* gdx::ios::IosGraphics::getGLU()
{
    return glu;
}

gdx::Graphics::BufferFormat gdx::ios::IosGraphics::getBufferFormat()
{
    gdx_log_error("gdx","not implemented yet");
}

float gdx::ios::IosGraphics::getDeltaTime()
{
    return deltaTime;
}

float gdx::ios::IosGraphics::getDensity()
{
    return 0;
}

gdx::Graphics::DisplayMode gdx::ios::IosGraphics::getDesktopDisplayMode()
{
    gdx_log_error("gdx","not implemented yet");
}

std::vector< gdx::Graphics::DisplayMode >& gdx::ios::IosGraphics::getDisplayModes()
{
    gdx_log_error("gdx","not implemented yet");
}

int gdx::ios::IosGraphics::getFramesPerSecond()
{
    return this->fps;
}

gdx::GLCommon* gdx::ios::IosGraphics::getGLCommon()
{
    return gl10;
}

int gdx::ios::IosGraphics::getHeight()
{
    return this->height;
}

float gdx::ios::IosGraphics::getPpcX()
{
    return 0;
}

float gdx::ios::IosGraphics::getPpcY()
{
    return 0;
}

float gdx::ios::IosGraphics::getPpiX()
{
    return 0;
}

float gdx::ios::IosGraphics::getPpiY()
{
    return 0;
}

void gdx::ios::IosGraphics::updateTime()
{
    uint64_t time = system->nanoTime();

    deltaTime = (time - lastTime) / 1000000000.0f;
    lastTime = time;
    
    if (time - frameStart >= 1000000000) {
        fps = frames;
        frames = 0;
        frameStart = time;
    }
    frames++;
}

gdx::Graphics::GraphicsType gdx::ios::IosGraphics::getType()
{
    return gdx::Graphics::IOsGL;
}

int gdx::ios::IosGraphics::getWidth()
{
    return this->width;
}

bool gdx::ios::IosGraphics::isGL11Available()
{
    return gl11 != NULL;
}

bool gdx::ios::IosGraphics::isGL20Available()
{
    return gl20 != NULL;
}

bool gdx::ios::IosGraphics::setDisplayMode(gdx::Graphics::DisplayMode displayMode)
{
    if (!supportsDisplayModeChange())
        return false;
    return true;
}

void gdx::ios::IosGraphics::setIcon(gdx::Pixmap::ptr pixmap)
{
    this->iconPixmap = pixmap;
}

void gdx::ios::IosGraphics::setTitle(const std::string& title)
{
}

void gdx::ios::IosGraphics::setVSync(bool vsync)
{
    this->vsync = true;
}

bool gdx::ios::IosGraphics::supportsDisplayModeChange()
{
    return false;
}

bool gdx::ios::IosGraphics::supportsExtension(const std::string& extension)
{
    return false;
}

void gdx::ios::IosGraphics::initialize()
{   
	this->lastTime = system->nanoTime();   
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
        gdx_log_error("gdx","IosGraphics: Failed to recover the GL_VERSION, aborting");
    } 
}

bool gdx::ios::IosGraphics::setDisplayMode(int width, int height, bool fullscreen)
{
	this->width = width;
	this->height = height;
	
	return true;
}

void gdx::ios::IosGraphics::update()
{
}

TextureData::ptr ios::IosGraphics::resolveTextureData(gdx::FileHandle::ptr fileHandle,
                                                                  Pixmap::ptr preloadedPixmap,
                                                                  const gdx::Pixmap::Format* format,
                                                                  bool useMipMaps)
{
    return TextureData::ptr(new FileTextureData(fileHandle, preloadedPixmap, format, useMipMaps));
}

Pixmap* ios::IosGraphics::resolvePixmap(int width, int height, const gdx::Pixmap::Format& format, int pixType)
{
    switch(pixType) {
        case Pixmap::Gdx2d:
            return Gdx2DPixmap::newPixmap(width, height, Gdx2DPixmap::Format::toGdx2DPixmapFormat(format));
        case Pixmap::Svg:
            return new gdx::AggSvgPixmap(width, height);
    }
    return NULL;
}

Pixmap* ios::IosGraphics::resolvePixmap(const gdx::Pixmap& other)
{
    switch(other.getType()) {
        case Pixmap::Gdx2d:
            return new Gdx2DPixmap((Gdx2DPixmap&)other);
		case Pixmap::Svg:
			break;			
    } 
    return NULL;
}

Pixmap* ios::IosGraphics::resolvePixmap(const gdx::FileHandle::ptr& file)
{
    std::string extension = file->extension();
    
    if (extension == "png" || extension == "jpg" || extension == "tga" || extension == "bmp") {
		gdx::FileHandle::buffer_ptr buffer;
		int length = file->readBytes(buffer);
		return Gdx2DPixmap::pixmapFromByteArray((unsigned char*) buffer.get(), length, 0);
	}
    else if (extension == "svg") {
        return gdx::AggSvgPixmap::newFromFile(file);        
    } else {
        gdx_log_error("gdx","unsupported image format: " + extension);
    }
}
