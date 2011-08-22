
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

#ifndef GDX_CPP_GRAPHICS_G2D_GDX2DPIXMAP_HPP_
#define GDX_CPP_GRAPHICS_G2D_GDX2DPIXMAP_HPP_

namespace gdx_cpp {
namespace graphics {
namespace g2d {

class Gdx2DPixmap: public gdx_cpp::utils::Disposable {
public:
    void dispose ();
    void clear (int color);
    void setPixel (int x,int y,int color);
    int getPixel (int x,int y);
    void drawLine (int x,int y,int x2,int y2,int color);
    void drawRect (int x,int y,int width,int height,int color);
    void drawCircle (int x,int y,int radius,int color);
    void fillRect (int x,int y,int width,int height,int color);
    void fillCircle (int x,int y,int radius,int color);
    void drawPixmap (const Gdx2DPixmap& src,int srcX,int srcY,int dstX,int dstY,int width,int height);
    void drawPixmap (const Gdx2DPixmap& src,int srcX,int srcY,int srcWidth,int srcHeight,int dstX,int dstY,int dstWidth,int dstHeight);
    static Gdx2DPixmap& newPixmap (const InputStream& in,int requestedFormat);
    static Gdx2DPixmap& newPixmap (int width,int height,int format);
    ByteBuffer& getPixels ();
    int getHeight ();
    int getWidth ();
    int getFormat ();
    int getGLInternalFormat ();
    int getGLFormat ();
    int getGLType ();
    std::string& getFormatString ();

protected:


private:

};

} // namespace gdx_cpp
} // namespace graphics
} // namespace g2d

#endif // GDX_CPP_GRAPHICS_G2D_GDX2DPIXMAP_HPP_
