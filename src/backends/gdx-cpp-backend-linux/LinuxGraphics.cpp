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

#include "LinuxGLU.hpp"
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
#include <gdx-cpp/graphics/GL20.hpp>
#include <gdx-cpp/graphics/GL11.hpp>

#include <gdx-cpp/gl.hpp>

using namespace gdx::nix;
using namespace gdx;

gdx::nix::LinuxGraphics::LinuxGraphics() :
vsync(false),
title("GDX-CPP"),
window(0),
width(0),
height(0),
gl10(0),
gl11(0),
gl20(0),
glu(new LinuxGLU),
glCommon(0),
iconPixmap(0),
lastTime(0),
frames(0),
frameStart(0),
deltaTime(0)
{
}

gdx::GL10* gdx::nix::LinuxGraphics::getGL10()
{
    return gl10;
}

gdx::GL11* gdx::nix::LinuxGraphics::getGL11()
{
    return gl11;
}

gdx::GL20* gdx::nix::LinuxGraphics::getGL20()
{
    return gl20;
}

gdx::GLU* gdx::nix::LinuxGraphics::getGLU()
{
    return glu;
}

gdx::Graphics::BufferFormat gdx::nix::LinuxGraphics::getBufferFormat()
{
    gdx_log_error("gdx","not implemented yet");
}

float gdx::nix::LinuxGraphics::getDeltaTime()
{
    return deltaTime;
}

float gdx::nix::LinuxGraphics::getDensity()
{
    return 0;
}

gdx::Graphics::DisplayMode gdx::nix::LinuxGraphics::getDesktopDisplayMode()
{
    gdx_log_error("gdx","not implemented yet");
}

std::vector< gdx::Graphics::DisplayMode >& gdx::nix::LinuxGraphics::getDisplayModes()
{
    gdx_log_error("gdx","not implemented yet");
}

int gdx::nix::LinuxGraphics::getFramesPerSecond()
{
    return this->fps;
}

gdx::GLCommon* gdx::nix::LinuxGraphics::getGLCommon()
{
    return gl10;
}

int gdx::nix::LinuxGraphics::getHeight()
{
    return this->height;
}

float gdx::nix::LinuxGraphics::getPpcX()
{
    return 0;
}

float gdx::nix::LinuxGraphics::getPpcY()
{
    return 0;
}

float gdx::nix::LinuxGraphics::getPpiX()
{
    return 0;
}

float gdx::nix::LinuxGraphics::getPpiY()
{
    return 0;
}

void gdx::nix::LinuxGraphics::updateTime()
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

gdx::Graphics::GraphicsType gdx::nix::LinuxGraphics::getType()
{
    return gdx::Graphics::SdlGL;
}

int gdx::nix::LinuxGraphics::getWidth()
{
    return this->width;
}

bool gdx::nix::LinuxGraphics::isGL11Available()
{
    return gl11 != NULL;
}

bool gdx::nix::LinuxGraphics::isGL20Available()
{
    return gl20 != NULL;
}

bool gdx::nix::LinuxGraphics::setDisplayMode(gdx::Graphics::DisplayMode displayMode)
{
    if (!supportsDisplayModeChange())
        return false;
    return true;
}

void gdx::nix::LinuxGraphics::setIcon(gdx::Pixmap::ptr pixmap)
{
    this->iconPixmap = pixmap;
}

void gdx::nix::LinuxGraphics::setTitle(const std::string& title)
{
    this->title = title;
}

void gdx::nix::LinuxGraphics::setVSync(bool vsync)
{
    this->vsync = true;
}

bool gdx::nix::LinuxGraphics::supportsDisplayModeChange()
{
    return false;
}

bool gdx::nix::LinuxGraphics::supportsExtension(const std::string& extension)
{
    return false;
}

void gdx::nix::LinuxGraphics::initialize()
{   
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        gdx_log_error("gdx","Failed to initialize SDL video");
    }
}

bool gdx::nix::LinuxGraphics::setDisplayMode(int width, int height, bool fullscreen)
{
    this->lastTime = system->nanoTime();
    this->width = width;
    this->height = height;
    
    Uint32 flags = SDL_OPENGL | SDL_HWSURFACE;
    if (fullscreen)
        flags |= SDL_FULLSCREEN;

    const SDL_VideoInfo* info = SDL_GetVideoInfo();

    SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
    SDL_GL_SetAttribute( SDL_GL_BUFFER_SIZE, 32 );
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
    
    if (!SDL_SetVideoMode(width, height, info->vfmt->BitsPerPixel, flags)) {
        gdx_log_error("gdx","Failed to initialize SDL video");
    }

    return setupGLModes();
}

void gdx::nix::LinuxGraphics::update()
{
    SDL_GL_SwapBuffers();
}

TextureData::ptr nix::LinuxGraphics::resolveTextureData(FileHandle::ptr fileHandle,
                                                                  Pixmap::ptr preloadedPixmap,
                                                                  const gdx::Pixmap::Format* format,
                                                                  bool useMipMaps)
{
    return TextureData::ptr(new FileTextureData(fileHandle, preloadedPixmap, format, useMipMaps));
}

Pixmap* nix::LinuxGraphics::resolvePixmap(int width, int height, const gdx::Pixmap::Format& format, int pixType)
{
    switch(pixType) {
        case Pixmap::Gdx2d:
            return Gdx2DPixmap::newPixmap(width, height, Gdx2DPixmap::Format::toGdx2DPixmapFormat(format));
        case Pixmap::Svg:
            return new AggSvgPixmap(width, height);
    }
}

Pixmap* nix::LinuxGraphics::resolvePixmap(const gdx::Pixmap& other)
{
    switch(other.getType()) {
        case Pixmap::Gdx2d:
            return new Gdx2DPixmap((Gdx2DPixmap&)other);
    } 
}

Pixmap* nix::LinuxGraphics::resolvePixmap(const FileHandle::ptr& file)
{
    std::string extension = file->extension();
    
    if (extension == "png" || extension == "jpg" || extension == "tga" || extension == "bmp")
        return Gdx2DPixmap::newPixmapFromFile(file, 0);
    else if (extension == "svg") {
        return AggSvgPixmap::newFromFile(file);        
    } else {
        gdx_log_error("gdx","unsupported image format: " + extension);
    }
}

bool gdx::nix::LinuxGraphics::setupGLModes()
{
    std::string version =  (const char*) ::glGetString(GL_VERSION);

    if (!version.empty()) {

        int major = atoi((const char*) version.c_str());
        int minor = atoi((const char*) &version.c_str()[2]);

        if (false && major >= 2) {


        } else {
            if (major == 1 && minor < 5) {
                glCommon = gl10 = new GL10;
            } else {
                glCommon = gl10 = gl11 = new GL11;
            }
        }

        SDL_WM_SetCaption(this->title.c_str(), NULL);
        glCommon->glViewport(0, 0, width, height);

        return true;
    } else {
        std::cerr << "Failed to recover the GL_VERSION, aborting" << std::endl;
        return false;
    }
}

LinuxGraphics::~LinuxGraphics()
{
    SDL_Quit();
}
