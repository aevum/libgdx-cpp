
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

#ifndef GDX_CPP_GRAPHICS_G2D_BITMAPFONTCACHE_HPP_
#define GDX_CPP_GRAPHICS_G2D_BITMAPFONTCACHE_HPP_

#include "gdx-cpp/utils/Disposable.hpp"
#include "gdx-cpp/graphics/g2d/SpriteBatch.hpp"
#include "gdx-cpp/graphics/Color.hpp"

#include "BitmapFont.hpp"

namespace gdx_cpp {
namespace graphics {
namespace g2d {

class BitmapFontCache: public gdx_cpp::utils::Disposable {
friend class BitmapFont;
public:
    void setPosition (float x,float y);
    void translate (float xAmount,float yAmount);
    void setColor (float color);
    void setColor (const gdx_cpp::graphics::Color& tint);
    void setColor (float r,float g,float b,float a);
    void draw (SpriteBatch& spriteBatch);
    void draw (SpriteBatch& spriteBatch,float alphaModulation);
    gdx_cpp::graphics::Color& getColor ();
    gdx_cpp::graphics::g2d::BitmapFont::TextBounds& setText (const std::string& str,float x,float y);
    gdx_cpp::graphics::g2d::BitmapFont::TextBounds& setText (const std::string& str,float x,float y,int start,int end);
    gdx_cpp::graphics::g2d::BitmapFont::TextBounds& setMultiLineText (const std::string& str,float x,float y);
    gdx_cpp::graphics::g2d::BitmapFont::TextBounds& setMultiLineText (const std::string& str,float x,float y,float alignmentWidth,const gdx_cpp::graphics::g2d::BitmapFont::HAlignment& alignment);
    gdx_cpp::graphics::g2d::BitmapFont::TextBounds& setWrappedText (const std::string& str,float x,float y,float wrapWidth);
    gdx_cpp::graphics::g2d::BitmapFont::TextBounds& setWrappedText (const std::string& str,float x,float y,float wrapWidth,const gdx_cpp::graphics::g2d::BitmapFont::HAlignment& alignment);
    gdx_cpp::graphics::g2d::BitmapFont::TextBounds& getBounds ();
    float getX ();
    float getY ();
    BitmapFont* getFont ();
    void dispose ();
    void setUseIntegerPositions (bool use);
    bool usesIntegerPositions ();
    
    BitmapFontCache (BitmapFont* font,bool integer = true);

private:
    void reset (int glyphCount);
    float addToCache (const std::string& str,float x,float y,int start,int end);
    void addGlyph (gdx_cpp::graphics::g2d::BitmapFont::Glyph* glyph,float x,float y,float width,float height);
    BitmapFont* font;

    std::vector<float> vertices;
    
    int idx ;
    float color;
    Color tmpColor;
    BitmapFont::TextBounds textBounds;
    bool integer;
    float x,y;
};

} // namespace gdx_cpp
} // namespace graphics
} // namespace g2d

#endif // GDX_CPP_GRAPHICS_G2D_BITMAPFONTCACHE_HPP_
