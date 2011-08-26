
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

#ifndef GDX_CPP_GRAPHICS_COLOR_HPP_
#define GDX_CPP_GRAPHICS_COLOR_HPP_

#include <string>

namespace gdx_cpp {
namespace graphics {

class Color {
public:
    static const Color WHITE;
    static const Color BLACK;
    static const Color RED;
    static const Color GREEN;
    static const Color BLUE;

    float r, g, b, a;

    Color (float r, float g, float b, float a) ;
    Color (const gdx_cpp::graphics::Color& color) ;
    Color& set (const Color& color);
    Color& mul (const Color& color);
    Color& mul (float value);
    Color& add (const Color& color);
    Color& sub (const Color& color);
    void clamp ();
    void set (float r,float g,float b,float a);
    bool equals (const gdx_cpp::graphics::Color& o);
    int hashCode ();
    const std::string toString ();
    static float toFloatBits (int r,int g,int b,int a);
    static int toIntBits (int r,int g,int b,int a);
    float toFloatBits () const;
    int toIntBits () const;
    static float toFloatBits (float r,float g,float b,float a);
    static int alpha (float alpha);
    static int luminanceAlpha (float luminance,float alpha);
    static int rgb565 (float r,float g,float b);
    static int rgba4444 (float r,float g,float b,float a);
    static int rgb888 (float r,float g,float b);
    static int rgba8888 (float r,float g,float b,float a);

protected:


private:

};

} // namespace gdx_cpp
} // namespace graphics

#endif // GDX_CPP_GRAPHICS_COLOR_HPP_
