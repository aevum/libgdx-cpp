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

#include <gdx-cpp/Graphics.hpp>

namespace gdx_cpp {

namespace backends {

namespace nix {

class LinuxGraphics : public Graphics
{
public:
    LinuxGraphics();
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
    void setIcon (Pixmap& pixmap);
    void setVSync (bool vsync);
    BufferFormat getBufferFormat ();
    bool supportsExtension (const std::string& extension);

protected:
    graphics::GL10* gl10;
    graphics::GL11* gl11;
    graphics::GL20* gl20;
    graphics::GLU* glu;
};

}

}

}

#endif // GDX_CPP_BACKENDS_NIX_LINUXGRAPHICS_HPP
