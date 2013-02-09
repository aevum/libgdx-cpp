
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

#include <string>
#include <vector>

#include "BitmapFont.hpp"
#include "gdx-cpp/graphics/Color.hpp"
#include "gdx-cpp/graphics/g2d/SpriteBatch.hpp"
#include "gdx-cpp/utils/Disposable.hpp"

namespace gdx {

class SpriteBatch;

class BitmapFontCache: public Disposable {
friend class BitmapFont;
public:
    void setPosition (float x,float y);
    void translate (float xAmount,float yAmount);
    void setColor (float color);
    void setColor (const Color& tint);
    void setColor (float r,float g,float b,float a);
    void draw (SpriteBatch& spriteBatch);
    void draw (SpriteBatch& spriteBatch,float alphaModulation);
    Color& getColor ();
    BitmapFont::TextBounds& setText (const std::string& str, float x, float y);
    BitmapFont::TextBounds& setText (const std::string& str, float x, float y, int start, int end);
    BitmapFont::TextBounds& setMultiLineText (const std::string& str, float x, float y);
    BitmapFont::TextBounds& setMultiLineText (const std::string& str, float x, float y, float alignmentWidth, const gdx::BitmapFont::HAlignment& alignment);
    BitmapFont::TextBounds& setWrappedText (const std::string& str, float x, float y, float wrapWidth);
    BitmapFont::TextBounds& setWrappedText (const std::string& str, float x, float y, float wrapWidth, const gdx::BitmapFont::HAlignment& alignment);
    BitmapFont::TextBounds& getBounds ();
    float getX ();
    float getY ();
    BitmapFont* getFont ();
    void dispose ();
    void setUseIntegerPositions (bool use);
    bool usesIntegerPositions ();
    
    BitmapFontCache (BitmapFont* font,bool integer = true);

private:
    void reset (int glyphCount);
    float addToCache (const std::string& str, float x, float y, unsigned int start, unsigned int end);
    void addGlyph (BitmapFont::Glyph* glyph,float x,float y,float width,float height);
    BitmapFont* font;

    std::vector<float> vertices;
    
    int idx ;
    float color;
    Color tmpColor;
    BitmapFont::TextBounds textBounds;
    bool integer;
    float x,y;
};

} // namespace gdx

#endif // GDX_CPP_GRAPHICS_G2D_BITMAPFONTCACHE_HPP_
