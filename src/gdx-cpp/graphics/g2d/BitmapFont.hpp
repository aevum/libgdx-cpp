
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

#ifndef GDX_CPP_GRAPHICS_G2D_BITMAPFONT_HPP_
#define GDX_CPP_GRAPHICS_G2D_BITMAPFONT_HPP_

#include "gdx-cpp/utils/Disposable.hpp"

namespace gdx_cpp {
namespace graphics {
namespace g2d {

class BitmapFont: public gdx_cpp::utils::Disposable {
public:
    class Glyph {


    };
    
    Glyph& getGlyph (char ch);
    std::string& getImageFile ();
    TextBounds& draw (const SpriteBatch& spriteBatch,const CharSequence& str,float x,float y);
    TextBounds& draw (const SpriteBatch& spriteBatch,const CharSequence& str,float x,float y,int start,int end);
    TextBounds& drawMultiLine (const SpriteBatch& spriteBatch,const CharSequence& str,float x,float y);
    TextBounds& drawMultiLine (const SpriteBatch& spriteBatch,const CharSequence& str,float x,float y,float alignmentWidth,const HAlignment& alignment);
    TextBounds& drawWrapped (const SpriteBatch& spriteBatch,const CharSequence& str,float x,float y,float wrapWidth);
    TextBounds& drawWrapped (const SpriteBatch& spriteBatch,const CharSequence& str,float x,float y,float wrapWidth,const HAlignment& alignment);
    TextBounds& getBounds (const CharSequence& str);
    TextBounds& getBounds (const CharSequence& str,int start,int end);
    TextBounds& getMultiLineBounds (const CharSequence& str);
    TextBounds& getWrappedBounds (const CharSequence& str,float wrapWidth);
    void computeGlyphAdvancesAndPositions (const CharSequence& str,const gdx_cpp::utils::FloatArray& glyphAdvances,const gdx_cpp::utils::FloatArray& glyphPositions);
    int computeVisibleGlyphs (const CharSequence& str,int start,int end,float availableWidth);
    void setColor (const gdx_cpp::graphics::Color& tint);
    void setColor (float r,float g,float b,float a);
    gdx_cpp::graphics::Color& getColor ();
    void setScale (float scaleX,float scaleY);
    void setScale (float scaleXY);
    void scale (float amount);
    float getScaleX ();
    float getScaleY ();
    TextureRegion& getRegion ();
    float getLineHeight ();
    float getSpaceWidth ();
    float getXHeight ();
    float getCapHeight ();
    float getAscent ();
    float getDescent ();
    bool isFlipped ();
    void dispose ();
    void setFixedWidthGlyphs (const CharSequence& glyphs);
    void set (const TextBounds& bounds);
    bool containsCharacter (char character);
    void setUseIntegerPositions (bool use);
    bool usesIntegerPositions ();

protected:


private:
    void setGlyph (int ch,const Glyph& glyph);
    Glyph& getFirstGlyph ();
    void load (const BitmapFontData& data);
};

} // namespace gdx_cpp
} // namespace graphics
} // namespace g2d

#endif // GDX_CPP_GRAPHICS_G2D_BITMAPFONT_HPP_
