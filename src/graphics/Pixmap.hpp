
/*
    Copyright 2011 Aevum Software aevum @ aevumlab.com

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.

    @author Victor Vicente de Carvalho victor.carvalho@aevumlab.com
    @author Ozires Bortolon de Faria ozires@aevumlab.com
*/

#ifndef GDX_CPP_GRAPHICS_PIXMAP_HPP_
#define GDX_CPP_GRAPHICS_PIXMAP_HPP_

namespace gdx_cpp {
namespace graphics {

class Pixmap: public gdx_cpp::utils::Disposable {
public:
    static void setBlending (const Blending& blending);
    static void setFilter (const Filter& filter);
    void setColor (float r,float g,float b,float a);
    void setColor (const Color& color);
    void fill ();
    void setStrokeWidth (int width);
    void drawLine (int x,int y,int x2,int y2);
    void drawRectangle (int x,int y,int width,int height);
    void drawPixmap (const Pixmap& pixmap,int x,int y,int srcx,int srcy,int srcWidth,int srcHeight);
    void drawPixmap (const Pixmap& pixmap,int srcx,int srcy,int srcWidth,int srcHeight,int dstx,int dsty,int dstWidth,int dstHeight);
    void fillRectangle (int x,int y,int width,int height);
    void drawCircle (int x,int y,int radius);
    void fillCircle (int x,int y,int radius);
    int getPixel (int x,int y);
    int getWidth ();
    int getHeight ();
    void dispose ();
    void drawPixel (int x,int y);
    int getGLFormat ();
    int getGLInternalFormat ();
    int getGLType ();
    ByteBuffer& getPixels ();
    Format& getFormat ();
    static Blending& getBlending ();

protected:


private:

};

} // namespace gdx_cpp
} // namespace graphics

#endif // GDX_CPP_GRAPHICS_PIXMAP_HPP_
