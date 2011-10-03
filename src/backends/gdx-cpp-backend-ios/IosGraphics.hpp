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


#ifndef GDX_CPP_BACKENDS_IOS_IOSGRAPHICS_HPP
#define GDX_CPP_BACKENDS_IOS_IOSGRAPHICS_HPP

#include <gdx-cpp/Graphics.hpp>
#include <gdx-cpp/graphics/Pixmap.hpp>

namespace gdx_cpp {

namespace backends {

namespace ios {

class IosGraphics : public Graphics
{
public:
    IosGraphics();

    void initialize();
    bool isGL11Available ();
    bool isGL20Available ();
    graphics::GLCommon* getGLCommon ();
    graphics::GL10* getGL10 ();
    graphics::GL11* getGL11 ();
    graphics::GL20* getGL20 ();
    graphics::GLU* getGLU ();
    int getWidth ();
    int getHeight ();
    float getDeltaTime ();
    int getFramesPerSecond ();
    GraphicsType getType ();
    float getPpiX ();
    float getPpiY ();
    float getPpcX ();
    float getPpcY ();
    float getDensity ();
    bool supportsDisplayModeChange ();
    std::vector<DisplayMode>& getDisplayModes ();
    DisplayMode getDesktopDisplayMode ();
    bool setDisplayMode (DisplayMode displayMode);
    bool setDisplayMode (int width, int height, bool fullscreen);
    void setTitle (const std::string& title);
    void setIcon (gdx_cpp::graphics::Pixmap::ptr pixmap);
    void setVSync (bool vsync);
    BufferFormat getBufferFormat ();
    bool supportsExtension (const std::string& extension);
    void update();
    void updateTime();

    graphics::TextureData::ptr resolveTextureData(Files::fhandle_ptr fileHandle, graphics::Pixmap::ptr preloadedPixmap, const gdx_cpp::graphics::Pixmap::Format* format, bool useMipMaps);

    graphics::Pixmap* resolvePixmap(int width, int height, const gdx_cpp::graphics::Pixmap::Format& format, int pixType);
    graphics::Pixmap* resolvePixmap(const gdx_cpp::graphics::Pixmap& other);
    graphics::Pixmap* resolvePixmap(const gdx_cpp::Files::fhandle_ptr& file);
    
protected:
    bool vsync;    
    int window;
    int width, height;
    graphics::GL10* gl10;
    graphics::GL11* gl11;
    graphics::GL20* gl20;
    graphics::GLU* glu;
    graphics::GLCommon* glCommon;
    graphics::Pixmap::ptr iconPixmap;
    
    uint64_t lastTime;
    uint64_t frames;
    uint64_t frameStart;
    uint32_t fps;
    float deltaTime;
};

}

}

}

#endif // GDX_CPP_BACKENDS_ios_IosGRAPHICS_HPP
