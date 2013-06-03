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


#include <GL/gl.h>

#define SDL_VIDEO_DRIVER_X11

#include <SDL/SDL.h>
#include <SDL/SDL_stdinc.h>
#include <SDL/SDL_syswm.h>
#include <SDL/SDL_version.h>
#include <SDL/SDL_video.h>

#include <gdx-cpp/Gdx.hpp>
#include <gdx-cpp/Graphics.hpp>
#include <gdx-cpp/graphics/GL10.hpp>
#include <gdx-cpp/graphics/GL11.hpp>
#include <gdx-cpp/graphics/GL20.hpp>
#include <gdx-cpp/graphics/g2d/Gdx2DPixmap.hpp>
#include <gdx-cpp/graphics/g2d/svg/AggSvgPixmap.hpp>
#include <gdx-cpp/graphics/glutils/FileTextureData.hpp>
#include <gdx-cpp/graphics/Pixmap.hpp>
#include <gdx-cpp/implementation/System.hpp>
#include <stdlib.h>
#include <iostream>
#include <memory>

#include "EmscriptenGLU.hpp"
#include "EmscriptenGraphics.hpp"
#include "gdx-cpp/Log.hpp"
#include "gdx-cpp/graphics/GLCommon.hpp"
#include <gdx-cpp/gl.hpp>
#include "gdx-cpp/graphics/Pixmap.hpp"

#define g_totalConfigsIn 10

namespace gdx
{
class GLU;
}  // namespace gdx


using namespace gdx::scripten;
using namespace gdx;

EGLDisplay gdx::scripten::EmscriptenGraphics::g_eglDisplay;
EGLContext gdx::scripten::EmscriptenGraphics::g_eglContext;
EGLSurface gdx::scripten::EmscriptenGraphics::g_eglSurface;

Display* gdx::scripten::EmscriptenGraphics::x11Disp = NULL;

gdx::scripten::EmscriptenGraphics::EmscriptenGraphics ( bool UseOpenGLES2 ) :
    vsync ( false ),
    title ( "GDX-CPP" ),
    window ( 0 ),
    width ( 0 ),
    height ( 0 ),
    gl10 ( 0 ),
    gl11 ( 0 ),
    gl20 ( 0 ),
    glu ( new EmscriptenGLU ),
    glCommon ( 0 ),
    iconPixmap ( 0 ),
    lastTime ( 0 ),
    frames ( 0 ),
    frameStart ( 0 ),
    deltaTime ( 0 ),
    isUseOpenGLES2 ( UseOpenGLES2 )
{
}

gdx::GL10* gdx::scripten::EmscriptenGraphics::getGL10()
{
    return gl10;
}

gdx::GL11* gdx::scripten::EmscriptenGraphics::getGL11()
{
    return gl11;
}

gdx::GL20* gdx::scripten::EmscriptenGraphics::getGL20()
{
    return gl20;
}

gdx::GLU* gdx::scripten::EmscriptenGraphics::getGLU()
{
    return glu;
}

gdx::Graphics::BufferFormat gdx::scripten::EmscriptenGraphics::getBufferFormat()
{
    gdx_log_error ( "gdx","not implemented yet" );
    return * ( BufferFormat* ) nullptr;
}

float gdx::scripten::EmscriptenGraphics::getDeltaTime()
{
    return deltaTime;
}

float gdx::scripten::EmscriptenGraphics::getDensity()
{
    return 0;
}

gdx::Graphics::DisplayMode gdx::scripten::EmscriptenGraphics::getDesktopDisplayMode()
{
    gdx_log_error ( "gdx","not implemented yet" );
}

std::vector< gdx::Graphics::DisplayMode >& gdx::scripten::EmscriptenGraphics::getDisplayModes()
{
    gdx_log_error ( "gdx","not implemented yet" );
}

int gdx::scripten::EmscriptenGraphics::getFramesPerSecond()
{
    return this->fps;
}

gdx::GLCommon* gdx::scripten::EmscriptenGraphics::getGLCommon()
{
    return glCommon;
}

int gdx::scripten::EmscriptenGraphics::getHeight()
{
    return this->height;
}

float gdx::scripten::EmscriptenGraphics::getPpcX()
{
    return 0;
}

float gdx::scripten::EmscriptenGraphics::getPpcY()
{
    return 0;
}

float gdx::scripten::EmscriptenGraphics::getPpiX()
{
    return 0;
}

float gdx::scripten::EmscriptenGraphics::getPpiY()
{
    return 0;
}

void gdx::scripten::EmscriptenGraphics::updateTime()
{
    uint64_t time = system->nanoTime();

    deltaTime = ( time - lastTime ) / 1000000000.0f;
    lastTime = time;

    if ( time - frameStart >= 1000000000 ) {
        fps = frames;
        frames = 0;
        frameStart = time;
    }
    frames++;
}

gdx::Graphics::GraphicsType gdx::scripten::EmscriptenGraphics::getType()
{
    return gdx::Graphics::SdlGL;
}

int gdx::scripten::EmscriptenGraphics::getWidth()
{
    return this->width;
}

bool gdx::scripten::EmscriptenGraphics::isGL11Available()
{
    return gl11 != NULL;
}

bool gdx::scripten::EmscriptenGraphics::isGL20Available()
{
    return gl20 != NULL;
}

bool gdx::scripten::EmscriptenGraphics::setDisplayMode ( gdx::Graphics::DisplayMode displayMode )
{
    if ( !supportsDisplayModeChange() ) {
        return false;
    }
    return true;
}

void gdx::scripten::EmscriptenGraphics::setIcon ( gdx::Pixmap::ptr pixmap )
{
    this->iconPixmap = pixmap;
}

void gdx::scripten::EmscriptenGraphics::setTitle ( const std::string& title )
{
    this->title = title;
}

void gdx::scripten::EmscriptenGraphics::setVSync ( bool vsync )
{
    this->vsync = true;
}

bool gdx::scripten::EmscriptenGraphics::supportsDisplayModeChange()
{
    return false;
}

bool gdx::scripten::EmscriptenGraphics::supportsExtension ( const std::string& extension )
{
    return gdx::gl->glGetString ( GL_EXTENSIONS ).find ( extension ) != std::string::npos;
}

void gdx::scripten::EmscriptenGraphics::initialize()
{
    if ( SDL_Init ( SDL_INIT_VIDEO ) < 0 ) {
        gdx_log_error ( "gdx","Failed to initialize SDL video" );
    }
}

bool gdx::scripten::EmscriptenGraphics::setDisplayMode ( int width, int height, bool fullscreen )
{
    this->lastTime = system->nanoTime();
    this->width = width;
    this->height = height;
    const SDL_VideoInfo* info = SDL_GetVideoInfo();

    Uint32 flags = SDL_OPENGL | SDL_HWSURFACE;
    if ( fullscreen ) {
        flags |= SDL_FULLSCREEN;
    }   

    SDL_GL_SetAttribute ( SDL_GL_RED_SIZE, 8 );
    SDL_GL_SetAttribute ( SDL_GL_GREEN_SIZE, 8 );
    SDL_GL_SetAttribute ( SDL_GL_BLUE_SIZE, 8 );
    SDL_GL_SetAttribute ( SDL_GL_DEPTH_SIZE, 16 );
    SDL_GL_SetAttribute ( SDL_GL_BUFFER_SIZE, 32 );
    SDL_GL_SetAttribute ( SDL_GL_DOUBLEBUFFER, 1 );

    if ( !SDL_SetVideoMode ( width, height, info->vfmt->BitsPerPixel, flags ) ) {
        gdx_log_error ( "gdx","Failed to initialize SDL video" );
        return false;
    }
    
    
    return setupGLModes();
}

void gdx::scripten::EmscriptenGraphics::update()
{
    SDL_GL_SwapBuffers();
}

TextureData::ptr scripten::EmscriptenGraphics::resolveTextureData ( const FileHandle::ptr& fileHandle,
        Pixmap::ptr preloadedPixmap,
        const gdx::Pixmap::Format* format,
        bool useMipMaps )
{
    return TextureData::ptr ( new FileTextureData ( fileHandle, preloadedPixmap, format, useMipMaps ) );
}

gdx::Pixmap* scripten::EmscriptenGraphics::resolvePixmap ( int width, int height, const gdx::Pixmap::Format& format, Pixmap::PixmapType pixType )
{
    switch ( pixType ) {
    case Pixmap::PixmapType::PixmapType_Gdx2d:
        return Gdx2DPixmap::newPixmap ( width, height, Gdx2DPixmap::Format::toGdx2DPixmapFormat ( format ) );
    case Pixmap::PixmapType::PixmapType_Svg:
        return new AggSvgPixmap ( width, height );
    }

    return nullptr;
}

gdx::Pixmap* scripten::EmscriptenGraphics::resolvePixmap ( const gdx::Pixmap& other )
{
    switch ( other.getType() ) {
    case Pixmap::PixmapType::PixmapType_Gdx2d:
        return new Gdx2DPixmap ( ( Gdx2DPixmap& ) other );
    case gdx::Pixmap::PixmapType::PixmapType_Svg:
        gdx_log_error ( "gdx", "Cannot copy a Svg pixmap" );
    }

    return nullptr;
}

gdx::Pixmap* scripten::EmscriptenGraphics::resolvePixmap ( const FileHandle::ptr& file )
{
    std::string extension = file->extension();

    if ( extension == "png" || extension == "jpg" || extension == "tga" || extension == "bmp" ) {
        return Gdx2DPixmap::newPixmapFromFile ( file, 0 );
    } else if ( extension == "svg" ) {
        return AggSvgPixmap::newFromFile ( file );
    } else {
        gdx_log_error ( "gdx","unsupported image format: %s", extension.c_str() );
    }
}

bool gdx::scripten::EmscriptenGraphics::setupGLModes()
{
    if ( isUseOpenGLES2 ) {
        gdx_log_debug("graphics", "set gl mode to ES2");
        gl20 = new GL20;
        glCommon = gl20;
        if ( glCommon == NULL ) {
            gdx_log_error ( "gdx", "error init gl" );
        }

    } else {
        const char* ver = ( const char* ) ::glGetString ( gdx::GL::VERSION );
        if ( ver == nullptr ) {
            gdx_log_error ( "gdx", "error init gl" );
            return false;
        }
        
        std::string version ( ver );

        if ( !version.empty() ) {
            int major = atoi ( ( const char* ) version.c_str() );
            int minor = atoi ( ( const char* ) &version.c_str() [2] );
            if ( major == 1 && minor < 5 ) {
                glCommon = gl10 = new GL10;
            } else {
                glCommon = gl10 = gl11 = new GL11;
            }
        } else {
            std::cerr << "Failed to recover the GL_VERSION, aborting" << std::endl;
            return false;
        }
    }

    SDL_WM_SetCaption ( this->title.c_str(), NULL );
    glCommon->glViewport ( 0, 0, width, height );

    return true;
}

EmscriptenGraphics::~EmscriptenGraphics()
{
    SDL_Quit();
}

