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


#include <EGL/eglplatform.h>
#include <GL/gl.h>
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

#include "LinuxGLU.hpp"
#include "LinuxGraphics.hpp"
#include "gdx-cpp/Log.hpp"
#include "gdx-cpp/graphics/GLCommon.hpp"
#include "gdx-cpp/graphics/Pixmap.hpp"

namespace gdx
{
class GLU;
}  // namespace gdx


using namespace gdx::nix;
using namespace gdx;

#define g_totalConfigsIn 10

EGLDisplay gdx::nix::LinuxGraphics::g_eglDisplay;
EGLContext gdx::nix::LinuxGraphics::g_eglContext;
EGLSurface gdx::nix::LinuxGraphics::g_eglSurface;

Display* gdx::nix::LinuxGraphics::x11Disp = NULL;

gdx::nix::LinuxGraphics::LinuxGraphics ( bool UseOpenGLES2 ) :
    vsync ( false ),
    title ( "GDX-CPP" ),
    window ( 0 ),
    width ( 0 ),
    height ( 0 ),
    gl10 ( 0 ),
    gl11 ( 0 ),
    gl20 ( 0 ),
    glu ( new LinuxGLU ),
    glCommon ( 0 ),
    iconPixmap ( 0 ),
    lastTime ( 0 ),
    frames ( 0 ),
    frameStart ( 0 ),
    deltaTime ( 0 ),
    isUseOpenGLES2 ( UseOpenGLES2 )
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
    gdx_log_error ( "gdx","not implemented yet" );
    return * ( BufferFormat* ) nullptr;
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
    gdx_log_error ( "gdx","not implemented yet" );
}

std::vector< gdx::Graphics::DisplayMode >& gdx::nix::LinuxGraphics::getDisplayModes()
{
    gdx_log_error ( "gdx","not implemented yet" );
}

int gdx::nix::LinuxGraphics::getFramesPerSecond()
{
    return this->fps;
}

gdx::GLCommon* gdx::nix::LinuxGraphics::getGLCommon()
{
    return glCommon;
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

    deltaTime = ( time - lastTime ) / 1000000000.0f;
    lastTime = time;

    if ( time - frameStart >= 1000000000 ) {
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

bool gdx::nix::LinuxGraphics::setDisplayMode ( gdx::Graphics::DisplayMode displayMode )
{
    if ( !supportsDisplayModeChange() ) {
        return false;
    }
    return true;
}

void gdx::nix::LinuxGraphics::setIcon ( gdx::Pixmap::ptr pixmap )
{
    this->iconPixmap = pixmap;
}

void gdx::nix::LinuxGraphics::setTitle ( const std::string& title )
{
    this->title = title;
}

void gdx::nix::LinuxGraphics::setVSync ( bool vsync )
{
    this->vsync = true;
}

bool gdx::nix::LinuxGraphics::supportsDisplayModeChange()
{
    return false;
}

bool gdx::nix::LinuxGraphics::supportsExtension ( const std::string& extension )
{
    return gdx::gl->glGetString ( GL_EXTENSIONS ).find ( extension ) != std::string::npos;
}

void gdx::nix::LinuxGraphics::initialize()
{
    if ( SDL_Init ( SDL_INIT_VIDEO ) < 0 ) {
        gdx_log_error ( "gdx","Failed to initialize SDL video" );
    }
}

bool gdx::nix::LinuxGraphics::setDisplayMode ( int width, int height, bool fullscreen )
{
    this->lastTime = system->nanoTime();
    this->width = width;
    this->height = height;
    const SDL_VideoInfo* info = SDL_GetVideoInfo();

    Uint32 flags = SDL_OPENGL | SDL_HWSURFACE;
    if ( fullscreen ) {
        flags |= SDL_FULLSCREEN;
    }

    if ( isUseOpenGLES2 ) {
        x11Disp        = NULL;
        g_eglSurface   = 0;
        g_eglContext   = 0;
        g_eglDisplay   = 0;

        x11Disp        = XOpenDisplay ( 0 );
        if ( !x11Disp ) {
            gdx_log_error ( "WINDOW", "Failed to open X display" );
            return false;
        }

        g_eglDisplay = eglGetDisplay ( ( EGLNativeDisplayType ) x11Disp );
        if ( g_eglDisplay == EGL_NO_DISPLAY ) {
            gdx_log_error ( "WINDOW", "Failed to get EGL display" );
            return false;
        }

        if ( !eglInitialize ( g_eglDisplay, NULL, NULL ) ) {
            gdx_log_error ( "WINDOW", "Failed to initialize EGL" );
            return false;
        }

        uint8_t rgb[4];
        switch ( info->vfmt->BitsPerPixel ) {
        case 8:
            rgb[0] = 2;
            rgb[1] = 3;
            rgb[2] = 3;
            rgb[3] = 8;
            break;
        case 15:
        case 16:
            rgb[0] = 5;
            rgb[1] = 5;
            rgb[2] = 5;
            rgb[3] = 16;
            break;
        default:
            rgb[0] = 8;
            rgb[1] = 8;
            rgb[2] = 8;
            rgb[3] = 24;
            break;
        }

        if ( !SDL_SetVideoMode ( width, height, info->vfmt->BitsPerPixel, flags ) ) {
            gdx_log_error ( "gdx","Failed to initialize SDL video" );
            return false;
        }

        static EGLint s_configAttribs[] = {
            EGL_RED_SIZE,           0,
            EGL_GREEN_SIZE,         0,
            EGL_BLUE_SIZE,          0,
            EGL_DEPTH_SIZE,         0,
            EGL_SURFACE_TYPE,       EGL_WINDOW_BIT,
            EGL_RENDERABLE_TYPE,    EGL_OPENGL_ES2_BIT,
            EGL_NONE
        };

        s_configAttribs[1] = rgb[0];
        s_configAttribs[3] = rgb[1];
        s_configAttribs[5] = rgb[2];
        s_configAttribs[7] = rgb[3];

        EGLint numConfigsOut = 0;

        EGLConfig g_allConfigs[g_totalConfigsIn];
        EGLConfig g_eglConfig;

        /* Choose configuration */
        if ( eglChooseConfig ( g_eglDisplay, s_configAttribs, g_allConfigs, g_totalConfigsIn, &numConfigsOut ) != EGL_TRUE
                || numConfigsOut == 0 ) {
            gdx_log_error ( "WINDOW", "Could not find suitable EGL configuration" );
            return false;
        }

        /* Bind GLES API */
        g_eglConfig = g_allConfigs[0];
        eglBindAPI ( EGL_OPENGL_ES_API );

        EGLint contextParams[] = {EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE};

        /* Create EGL Context */
        g_eglContext = eglCreateContext ( g_eglDisplay, g_eglConfig, EGL_NO_CONTEXT, contextParams );
        if ( g_eglContext == EGL_NO_CONTEXT ) {
            gdx_log_error ( "WINDOW", "Failed to create EGL context" );
            return false;
        }

        /* Get window manager information */
        SDL_SysWMinfo sysInfo;
        SDL_VERSION ( &sysInfo.version );
        if ( SDL_GetWMInfo ( &sysInfo ) <= 0 ) {
            gdx_log_error ( "WINDOW", "SDL_GetWMInfo failed" );
            return false;
        }

        /* Create surface */
        g_eglSurface = eglCreateWindowSurface ( g_eglDisplay, g_eglConfig, ( EGLNativeWindowType ) sysInfo.info.x11.window, NULL );
        if ( g_eglSurface == EGL_NO_SURFACE ) {
            gdx_log_error ( "WINDOW", "Failed to create EGL surface" );
            return false;
        }

        /* Make EGL current */
        if ( eglMakeCurrent ( g_eglDisplay, g_eglSurface, g_eglSurface, g_eglContext ) == EGL_FALSE ) {
            gdx_log_error ( "WINDOW", "Failed to make EGL current" );
            return false;
        }
    } else {

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
    }

    return setupGLModes();
}

void gdx::nix::LinuxGraphics::update()
{
    if ( isUseOpenGLES2 ) {
        eglSwapBuffers ( g_eglDisplay, g_eglSurface );
    } else {
        SDL_GL_SwapBuffers();
    }
}

TextureData::ptr nix::LinuxGraphics::resolveTextureData ( const FileHandle::ptr& fileHandle,
        Pixmap::ptr preloadedPixmap,
        const gdx::Pixmap::Format* format,
        bool useMipMaps )
{
    return TextureData::ptr ( new FileTextureData ( fileHandle, preloadedPixmap, format, useMipMaps ) );
}

gdx::Pixmap* nix::LinuxGraphics::resolvePixmap ( int width, int height, const gdx::Pixmap::Format& format, Pixmap::PixmapType pixType )
{
    switch ( pixType ) {
    case Pixmap::PixmapType::PixmapType_Gdx2d:
        return Gdx2DPixmap::newPixmap ( width, height, Gdx2DPixmap::Format::toGdx2DPixmapFormat ( format ) );
    case Pixmap::PixmapType::PixmapType_Svg:
        return new AggSvgPixmap ( width, height );
    }
    
    return nullptr;
}

gdx::Pixmap* nix::LinuxGraphics::resolvePixmap ( const gdx::Pixmap& other )
{
    switch ( other.getType() ) {
    case Pixmap::PixmapType::PixmapType_Gdx2d:
        return new Gdx2DPixmap ( ( Gdx2DPixmap& ) other );
    case gdx::Pixmap::PixmapType::PixmapType_Svg:
        gdx_log_error ( "gdx", "Cannot copy a Svg pixmap" );
    }

    return nullptr;
}

gdx::Pixmap* nix::LinuxGraphics::resolvePixmap ( const FileHandle::ptr& file )
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

bool gdx::nix::LinuxGraphics::setupGLModes()
{
    if ( isUseOpenGLES2 ) {
        gl20 = new GL20;
        glCommon = gl20;
        std::string version = ( const char* ) ::glGetString ( GL_VERSION );
        std::cerr << version;
        if ( glCommon == NULL ) {
            gdx_log_error ( "gdx", "error init gl" );
        }

    } else {
        std::string version = ( const char* ) ::glGetString ( GL_VERSION );

        if ( !version.empty() ) {

            int major = atoi ( ( const char* ) version.c_str() );
            int minor = atoi ( ( const char* ) &version.c_str() [2] );
            std::cerr << version;
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

LinuxGraphics::~LinuxGraphics()
{
    if ( isUseOpenGLES2 ) {
        if ( g_eglDisplay ) {
            eglMakeCurrent ( g_eglDisplay, NULL, NULL, EGL_NO_CONTEXT );
            if ( g_eglContext ) {
                eglDestroyContext ( g_eglDisplay, g_eglContext );
            }
            if ( g_eglSurface ) {
                eglDestroySurface ( g_eglDisplay, g_eglSurface );
            }
            eglTerminate ( g_eglDisplay );

            g_eglSurface = 0;
            g_eglContext = 0;
            g_eglDisplay = 0;
        }

        if ( x11Disp ) {
            XCloseDisplay ( x11Disp );
        }
        x11Disp = NULL;
    } else {
        SDL_Quit();
    }
}
