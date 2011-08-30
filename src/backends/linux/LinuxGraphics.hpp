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
    virtual bool isGL11Available ();    
    virtual bool isGL20Available ();    
    virtual graphics::GLCommon* getGLCommon ();    
    virtual graphics::GL10* getGL10 ();    
    virtual graphics::GL11* getGL11 ();    
    virtual graphics::GL20* getGL20 ();    
    virtual graphics::GLU* getGLU ();    
    virtual int getWidth ();    
    virtual int getHeight ();    
    virtual float getDeltaTime ();    
    virtual int getFramesPerSecond ();    
    virtual GraphicsType getType ();    
    virtual float getPpiX ();   
    virtual float getPpiY ();    
    virtual float getPpcX ();    
    virtual float getPpcY ();    
    virtual float getDensity ();    
    virtual bool supportsDisplayModeChange ();    
    virtual std::vector<DisplayMode>& getDisplayModes ();    
    virtual DisplayMode getDesktopDisplayMode ();    
    virtual bool setDisplayMode (DisplayMode displayMode);    
    virtual bool setDisplayMode (int width, int height, bool fullscreen);    
    virtual void setTitle (const std::string& title);    
    virtual void setIcon (Pixmap& pixmap);    
    virtual void setVSync (bool vsync);    
    virtual BufferFormat getBufferFormat ();    
    virtual bool supportsExtension (const std::string& extension);
};

}

}

}

#endif // GDX_CPP_BACKENDS_NIX_LINUXGRAPHICS_HPP
