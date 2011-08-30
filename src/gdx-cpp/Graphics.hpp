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


#ifndef GDX_CPP_GRAPHICS_H
#define GDX_CPP_GRAPHICS_H

#include <string>
#include <sstream>
#include <vector>

namespace gdx_cpp {

namespace graphics {
class GLCommon;
class GL10;
class GL11;
class GL20;
class GLU;
}
class Pixmap;

class Graphics {
public:
    /** Enumeration describing different types of {@link Graphics} implementations.
     *
     * @author mzechner */
    enum GraphicsType {
        AndroidGL, GtkGL, IOsGL
    };

    /** Class describing a fullscreen display mode
     *
     * @author mzechner */
    class DisplayMode {
    public:
        int width;
        int height;
        int refreshRate;
        int bitsPerPixel;

        std::string toString () {
            std::stringstream ss;
            ss << width << "x" << height << ", bpp: " << bitsPerPixel << ", hz: " << refreshRate;
            return ss.str();
        }

    protected:
        DisplayMode (int width, int height, int refreshRate, int bitsPerPixel) {
            this->width = width;
            this->height = height;
            this->refreshRate = refreshRate;
            this->bitsPerPixel = bitsPerPixel;
        }
    };

    /** Class describing the bits per pixel, depth buffer precision, stencil precision and number of MSAA samples. */
    class BufferFormat {
        /** number of bits per color channel **/
    public:
        int r, g, b, a;
        /** number of bits for depth and stencil buffer **/
        int depth, stencil;
        /** number of samples for MSAA **/
        int samples;
        /** whether coverage sampling anti-aliasing is used. in that case you have to clear the coverage buffer as well! */
        bool coverageSampling;

        BufferFormat (int r, int g, int b, int a, int depth, int stencil, int samples, bool coverageSampling) {
            this->r = r;
            this->g = g;
            this->b = b;
            this->a = a;
            this->depth = depth;
            this->stencil = stencil;
            this->samples = samples;
            this->coverageSampling = coverageSampling;
        }

        std::string toString () {
            std::stringstream ss;
            ss << "r: " << r << ", g: " << g << ", b: " << b << ", a: " << a << ", depth: " << depth << ", stencil: " << stencil
            << ", num samples: " << samples << ", coverage sampling: " << coverageSampling;
            return ss.str();
        }
    };

    virtual bool isGL11Available () = 0;

    virtual bool isGL20Available () = 0;

    virtual graphics::GLCommon* getGLCommon () = 0;

    virtual graphics::GL10* getGL10 () = 0;

    virtual graphics::GL11* getGL11 () = 0;

    virtual graphics::GL20* getGL20 () = 0;

    virtual graphics::GLU* getGLU () = 0;

    virtual int getWidth () = 0;

    virtual int getHeight () = 0;

    virtual float getDeltaTime () = 0;

    virtual int getFramesPerSecond () = 0;

    virtual GraphicsType getType () = 0;

    virtual float getPpiX () = 0;

    virtual float getPpiY () = 0;

    virtual float getPpcX () = 0;

    virtual float getPpcY () = 0;

    virtual float getDensity () = 0;

    virtual bool supportsDisplayModeChange () = 0;

    virtual std::vector<DisplayMode>& getDisplayModes () = 0;

    virtual DisplayMode getDesktopDisplayMode () = 0;

    virtual bool setDisplayMode (DisplayMode displayMode) = 0;

    virtual bool setDisplayMode (int width, int height, bool fullscreen) = 0;

    virtual void setTitle (const std::string& title) = 0;

    virtual void setIcon (Pixmap& pixmap) = 0;

    virtual void setVSync (bool vsync) = 0;

    virtual BufferFormat getBufferFormat () = 0;

    virtual bool supportsExtension (const std::string& extension) = 0;
};

}

#endif // GDX_CPP_GRAPHICS_H
