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

namespace gdx_cpp {

class Graphics {
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

        stlport::string toString () {
            return width + "x" + height + ", bpp: " + bitsPerPixel + ", hz: " + refreshRate;
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

        String toString () {
            return "r: " + r + ", g: " + g + ", b: " + b + ", a: " + a + ", depth: " + depth + ", stencil: " + stencil
                   + ", num samples: " + samples + ", coverage sampling: " + coverageSampling;
        }
    };

    /** Returns whether OpenGL ES 1.1 is available. If it is you can get an instance of {@link GL11} via {@link #getGL11()} to
     * access OpenGL ES 1.1 functionality. This also implies that {@link #getGL10()} will return an instance.
     *
     * @return whether OpenGL ES 1.1 is available */
    virtual bool isGL11Available () = 0;

    /** Returns whether OpenGL ES 2.0 is available. If it is you can get an instance of {@link GL20} via {@link #getGL20()} to
     * access OpenGL ES 2.0 functionality. Note that this functionality will only be available if you instructed the
     * {@link Application} instance to use OpenGL ES 2.0!
     *
     * @return whether OpenGL ES 2.0 is available */
    virtual bool isGL20Available () = 0;

    /** @return a {@link GLCommon} instance */
    virtual GLCommon getGLCommon () = 0;

    /** @return the {@link GL10} instance or null if not supported */
    virtual GL10 getGL10 () = 0;

    /** @return the {@link GL11} instance or null if not supported */
    virtual GL11 getGL11 () = 0;

    /** @return the {@link GL20} instance or null if not supported */
    virtual GL20 getGL20 () = 0;

    /** @return the {@link GLU} instance */
    virtual GLU getGLU () = 0;

    /** @return the width in pixels of the display surface */
    virtual int getWidth () = 0;

    /** @return the height in pixels of the display surface */
    virtual int getHeight () = 0;

    /** @return the time span between the current frame and the last frame in seconds */
    virtual float getDeltaTime () = 0;

    /** @return the average number of frames per second */
    virtual int getFramesPerSecond () = 0;

    /** @return the {@link GraphicsType} of this Graphics instance */
    virtual GraphicsType getType () = 0;

    /** @return the pixels per inch on the x-axis */
    virtual float getPpiX () = 0;

    /** @return the pixels per inch on the y-axis */
    virtual float getPpiY () = 0;

    /** @return the pixels per centimeter on the x-axis */
    virtual float getPpcX () = 0;

    /** @return the pixels per centimeter on the y-axis. */
    virtual float getPpcY () = 0;

    /** This is a scaling factor for the Density Independent Pixel unit, following the same conventions as
     * android.util.DisplayMetrics#density, where one DIP is one pixel on an approximately 160 dpi screen. Thus on a 160dpi screen
     * this density value will be 1; on a 120 dpi screen it would be .75; etc.
     *
     * @return the logical density of the Display. */
    virtual float getDensity () = 0;

    /** Whether the given backend supports a display mode change via calling {@link Graphics#setDisplayMode(DisplayMode)}
     *
     * @return whether display mode changes are supported or not. */
    virtual bool supportsDisplayModeChange () = 0;

    /** @return the supported fullscreen {@link DisplayMode}. */
    virtual DisplayMode[] getDisplayModes () = 0;

    /** @return the display mode of the primary graphics adapter. */
    virtual DisplayMode getDesktopDisplayMode () = 0;

    /** Sets the current {@link DisplayMode}. Returns false in case the operation failed. Not all backends support this methods. See
     * {@link Graphics#supportsDisplayModeChange()}.
     *
     * @param displayMode the display mode.
     * @return whether the operation succeeded. */
    virtual bool setDisplayMode (DisplayMode displayMode) = 0;

    /** Tries to set the display mode width the given width and height in pixels. Will always succeed if fullscreen is set to false,
     * in which case the application will be run in windowed mode. Use {@link Graphics#getDisplayModes()} to get a list of
     * supported fullscreen modes.
     *
     * @param width the width in pixels
     * @param height the height in pixels
     * @param fullscreen whether to use fullscreen rendering or not */
    virtual bool setDisplayMode (int width, int height, bool fullscreen) = 0;

    /** Sets the title of the window. Ignored on Android.
     *
     * @param title the title. */
    virtual void setTitle (String title) = 0;

    /** Sets the icon of the window. Ignored on Android.
     *
     * @param pixmap */
    virtual void setIcon (Pixmap pixmap) = 0;

    /** Enable/Disable vsynching. This is a best-effort attempt which might not work on all platforms.
     *
     * @param vsync vsync enabled or not. */
    virtual void setVSync (bool vsync) = 0;

    /** @return the format of the color, depth and stencil buffer in a {@link BufferFormat} instance */
    virtual BufferFormat getBufferFormat () = 0;

    /** @param extension the extension name
     * @return whether the extension is supported */
    virtual bool supportsExtension (String extension) = 0;

    // /**
    // * Opens the first back facing video camera. Only one camera
    // * can be opened at any given time.
    // * @param width the width of the image to be taken in pixels.
    // * @param height the height of the image to be taken in pixels.
    // * @param portrait whether the camera should be opened in portrait mode or
    // not (landscape otherwise)
    // * @return true if this succeeded, false otherwise.
    // */
    // public bool openCamera(int width, int height, bool portrait);
    //
    // /**
    // * @return true in case a new camera frame arrived since the last call to
    // {@link #getCameraFrame()}.
    // */
    // public bool hasNewCameraFrame();
    //
    // /**
    // * Returns a {@link TextureRegion} containing the latest frame of the
    // currently opened camera. Will
    // * throw a GdxRuntimeException in case the camera is not opened.
    // * @return a TextureRegion containing the camera snapshot.
    // */
    // public TextureRegion getCameraFrame();
    //
    // /**
    // * Saves the latest frame of the currently opened camera to the given
    // {@link ByteBuffer}. The pixels are stored
    // * in RGB565 format. The provided ByteBuffer must be able to store 2 *
    // cameraWidth * cameraHeight bytes. The ByteBuffer <b>must</b>
    // * be a direct ByteBuffer. The method will write pixels starting from the
    // ByteBuffer's current position.
    // * @param pixels the direct ByteBuffer to store the pixels in.
    // */
    // public void getCameraFrame(ByteBuffer pixels);
    //
    // /**
    // * Closes the camera. Has no effect in case the camera has not been
    // opened.
    // */
    // public void closeCamera();
};

}

#endif // GDX_CPP_GRAPHICS_H
