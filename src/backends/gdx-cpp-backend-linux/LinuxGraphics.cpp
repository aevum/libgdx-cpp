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

using namespace gdx_cpp::backends::nix;
using namespace gdx_cpp::graphics;
using namespace gdx_cpp;

gdx_cpp::backends::nix::LinuxGraphics::LinuxGraphics() :
gl10(0)
,gl11(0)
,gl20(0)
,glu(new LinuxGLU)
,glCommon(0)
,deltaTime(0)
,lastTime(0)
,frameStart(0)
,frames(0)
,vsync(false)
,title("GDX-CPP")
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
    throw std::runtime_error("not implemented yet");
}

float gdx_cpp::backends::nix::LinuxGraphics::getDeltaTime()
{
    return deltaTime;
}

float gdx_cpp::backends::nix::LinuxGraphics::getDensity()
{
    return 0;
}

gdx_cpp::Graphics::DisplayMode gdx_cpp::backends::nix::LinuxGraphics::getDesktopDisplayMode()
{
    throw std::runtime_error("not implemented yet");
}

std::vector< gdx_cpp::Graphics::DisplayMode >& gdx_cpp::backends::nix::LinuxGraphics::getDisplayModes()
{
    throw std::runtime_error("not implemented yet");
}

int gdx_cpp::backends::nix::LinuxGraphics::getFramesPerSecond()
{
    return this->fps;
}

gdx_cpp::graphics::GLCommon* gdx_cpp::backends::nix::LinuxGraphics::getGLCommon()
{
    return gl10;
}

int gdx_cpp::backends::nix::LinuxGraphics::getHeight()
{
    return this->height;
}

float gdx_cpp::backends::nix::LinuxGraphics::getPpcX()
{
    return 0;
}

float gdx_cpp::backends::nix::LinuxGraphics::getPpcY()
{
    return 0;
}

float gdx_cpp::backends::nix::LinuxGraphics::getPpiX()
{
    return 0;
}

float gdx_cpp::backends::nix::LinuxGraphics::getPpiY()
{
    return 0;
}

void gdx_cpp::backends::nix::LinuxGraphics::updateTime()
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

gdx_cpp::Graphics::GraphicsType gdx_cpp::backends::nix::LinuxGraphics::getType()
{
    return gdx_cpp::Graphics::SdlGL;
}

int gdx_cpp::backends::nix::LinuxGraphics::getWidth()
{
    return this->width;
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
    return true;
}

void gdx_cpp::backends::nix::LinuxGraphics::setIcon(gdx_cpp::graphics::Pixmap::ptr pixmap)
{
    this->iconPixmap = pixmap;
}

void gdx_cpp::backends::nix::LinuxGraphics::setTitle(const std::string& title)
{
    this->title = title;
}

void gdx_cpp::backends::nix::LinuxGraphics::setVSync(bool vsync)
{
    this->vsync = true;
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
    this->lastTime = Gdx::system->nanoTime();
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
        throw std::runtime_error("Failed to initialize SDL video");
    }

    return setupGLModes();
}

void gdx_cpp::backends::nix::LinuxGraphics::update()
{
    SDL_GL_SwapBuffers();
}

TextureData::ptr backends::nix::LinuxGraphics::resolveTextureData(files::FileHandle::ptr fileHandle,
                                                                  Pixmap::ptr preloadedPixmap,
                                                                  const gdx_cpp::graphics::Pixmap::Format* format,
                                                                  bool useMipMaps)
{
    return TextureData::ptr(new glutils::FileTextureData(fileHandle, preloadedPixmap, format, useMipMaps));
}

Pixmap* backends::nix::LinuxGraphics::resolvePixmap(int width, int height, const gdx_cpp::graphics::Pixmap::Format& format, int pixType)
{
    switch(pixType) {
        case Pixmap::Gdx2d:
            return g2d::Gdx2DPixmap::newPixmap(width, height, g2d::Gdx2DPixmap::Format::toGdx2DPixmapFormat(format));
        case Pixmap::Svg:
            return new g2d::svg::AggSvgPixmap(width, height);
    }
}

Pixmap* backends::nix::LinuxGraphics::resolvePixmap(const gdx_cpp::graphics::Pixmap& other)
{
    switch(other.getType()) {
        case Pixmap::Gdx2d:
            return new g2d::Gdx2DPixmap((g2d::Gdx2DPixmap&)other);
    } 
}

Pixmap* backends::nix::LinuxGraphics::resolvePixmap(const files::FileHandle::ptr& file)
{
    std::string extension = file->extension();
    
    if (extension == "png" || extension == "jpg" || extension == "tga" || extension == "bmp")
        return g2d::Gdx2DPixmap::newPixmapFromFile(file, 0);
    else if (extension == "svg") {
        return g2d::svg::AggSvgPixmap::newFromFile(file);        
    } else {
        throw std::runtime_error("unsupported image format: " + extension);
    }
}

bool gdx_cpp::backends::nix::LinuxGraphics::setupGLModes()
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
