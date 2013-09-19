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


#ifndef GDX_CPP_BACKENDS_NIX_LINUXGRAPHICS_HPP
#define GDX_CPP_BACKENDS_NIX_LINUXGRAPHICS_HPP

#include <EGL/egl.h>
#include <SDL/SDL.h>
#include <X11/Xlib.h>
#include <gdx-cpp/Graphics.hpp>
#include <gdx-cpp/graphics/Pixmap.hpp>
#include <stdint.h>
#include <string>
#include <vector>

#include "gdx-cpp/files/FileHandle.hpp"
#include "gdx-cpp/graphics/TextureData.hpp"

namespace gdx {
class GL10;
class GL11;
class GL20;
class GLCommon;
class GLU;
}  // namespace gdx

namespace gdx {

namespace nix {

class LinuxGraphics : public Graphics
{
static EGLDisplay g_eglDisplay;
static EGLContext g_eglContext;
static EGLSurface g_eglSurface;

static Display* x11Disp;
public:
    LinuxGraphics(bool isUseOpenGLES2);

    virtual void initialize();
    bool isGL11Available () override;
    bool isGL20Available () override;
    GLCommon* getGLCommon () override;
    GL10* getGL10 () override;
    GL11* getGL11 () override;
    GL20* getGL20 () override;
    GLU* getGLU () override;
    int getWidth () override;
    int getHeight () override;
    float getDeltaTime () override;
    int getFramesPerSecond () override;
    GraphicsType getType () override;
    float getPpiX () override;
    float getPpiY () override;
    float getPpcX () override;
    float getPpcY () override;
    float getDensity () override;
    bool supportsDisplayModeChange () override;
    std::vector<DisplayMode>& getDisplayModes () override;
    DisplayMode getDesktopDisplayMode () override;
    bool setDisplayMode (DisplayMode displayMode) override;
    bool setDisplayMode (int width, int height, bool fullscreen) override;
    void setTitle (const std::string& title) override;
    void setIcon (gdx::Pixmap::ptr pixmap) override;
    void setVSync (bool vsync) override;
    BufferFormat getBufferFormat () override;
    bool supportsExtension (const std::string& extension) override;
    virtual void update();
    void updateTime();

    TextureData::ptr resolveTextureData(const FileHandle::ptr& fileHandle, Pixmap::ptr preloadedPixmap, const gdx::Pixmap::Format* format, bool useMipMaps) override;

    Pixmap* resolvePixmap(int width, int height, const gdx::Pixmap::Format& format, Pixmap::PixmapType pixType) override;
    Pixmap* resolvePixmap(const gdx::Pixmap& other) override;
    Pixmap* resolvePixmap(const gdx::FileHandle::ptr& file) override;

    virtual ~LinuxGraphics();
    
protected:
    virtual bool setupGLModes();
    bool vsync;    
    std::string title;
    int window;
    int width, height;
    GL10* gl10;
    GL11* gl11;
    GL20* gl20;
    GLU* glu;
    GLCommon* glCommon;
    Pixmap::ptr iconPixmap;
    
    uint64_t lastTime;
    uint64_t frames;
    uint64_t frameStart;
    uint32_t fps;
    float deltaTime;
    bool isUseOpenGLES2;
};

}

}

#endif // GDX_CPP_BACKENDS_NIX_LINUXGRAPHICS_HPP
