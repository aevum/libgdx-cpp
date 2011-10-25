
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
#include "gdx-cpp/graphics/g2d/TextureRegion.hpp"
#include "gdx-cpp/files/FileHandle.hpp"
#include "gdx-cpp/graphics/g2d/SpriteBatch.hpp"
#include "gdx-cpp/utils/NumberUtils.hpp"

#include <string>

namespace gdx_cpp {
namespace graphics {
namespace g2d {

class BitmapFont: public gdx_cpp::utils::Disposable {
protected:
    static int LOG2_PAGE_SIZE = 9;
    static int PAGE_SIZE = 1 << LOG2_PAGE_SIZE;
    static int PAGES = 0x10000 / PAGE_SIZE;
    
public:
    enum HAlignment {
        LEFT, CENTER, RIGHT
    };
    
    class Glyph {
    public:
        int srcX;
        int srcY;

    protected:
        int width, height;
        float u, v, u2, v2;
        int xoffset, yoffset;
        int xadvance;
        char** kerning;
        
        int getKerning (char ch);        
        void setKerning (int ch, int value);
    };
    
    class BitmapFontData {
    protected:
        std::string imagePath;
        files::FileHandle::ptr fontFile;
        bool flipped;
        float lineHeight;
        float capHeight = 1;
        float ascent;
        float descent;
        float down;
        float scaleX = 1, scaleY = 1;

        Glyph** glyphs;
        
        float spaceWidth;
        float xHeight = 1;

    public:
        BitmapFontData (gdx_cpp::files::FileHandle::ptr fontFile, boolean flip);
        Glyph* getGlyph (char ch);
        std::string getImagePath ();
        gdx_cpp::files::FileHandle& getFontFile ();

    private:
        void setGlyph (int ch,Glyph* glyph);
        Glyph& getFirstGlyph ();
    };

    struct TextBounds {
        float width;
        float height;
        
        TextBounds () ;
        
        TextBounds (TextBounds bounds) {
            set(bounds);
        }
        
        void set (TextBounds bounds) ;
    };


    TextBounds& draw (gdx_cpp::graphics::g2d::SpriteBatch& spriteBatch, const std::string& str, float x, float y);
    TextBounds& draw (gdx_cpp::graphics::g2d::SpriteBatch& spriteBatch, const std::string& str, float x, float y, int start, int end);
    TextBounds& drawMultiLine (gdx_cpp::graphics::g2d::SpriteBatch& spriteBatch, const std::string& str, float x, float y);
    TextBounds& drawMultiLine (gdx_cpp::graphics::g2d::SpriteBatch& spriteBatch, const std::string& str, float x, float y, float alignmentWidth, const gdx_cpp::graphics::g2d::BitmapFont::HAlignment& alignment);
    TextBounds& drawWrapped (const graphics::g2d::SpriteBatch& spriteBatch,const CharSequence& str,float x,float y,float wrapWidth);
    TextBounds& drawWrapped (const graphics::g2d::SpriteBatch& spriteBatch,const CharSequence& str,float x,float y,float wrapWidth,const HAlignment& alignment);
    TextBounds& getBounds (const std::string& str);
    TextBounds& getBounds (const std::string& str,int start,int end);
    TextBounds& getMultiLineBounds (const std::string& str);
    TextBounds& getWrappedBounds (const std::string& str,float wrapWidth);

    void computeGlyphAdvancesAndPositions (const std::string& str, std::vector< float >& glyphAdvances, std::vector< float >& glyphPositions);
    int computeVisibleGlyphs (const std::string& str,int start,int end,float availableWidth);

    void setColor (float color);
    void setColor (const gdx_cpp::graphics::Color& tint);
    void setColor (float r,float g,float b,float a);

    Color getColor ();
    void setScale (float scaleX,float scaleY);
    void setScale (float scaleXY);
    void scale (float amount);
    float getScaleX ();
    float getScaleY ();
    TextureRegion::ptr& getRegion ();
    float getLineHeight ();
    float getSpaceWidth ();
    float getXHeight ();
    float getCapHeight ();
    float getAscent ();
    float getDescent ();
    bool isFlipped ();
    void dispose ();
    void setFixedWidthGlyphs (const std::string& glyphs);
    bool containsCharacter (char character);
    void setUseIntegerPositions (bool use);
    bool usesIntegerPositions ();
    BitmapFontData* getData ();

    static BitmapFont* fromFiles (gdx_cpp::files::FileHandle::ptr fontFile,
                      gdx_cpp::files::FileHandle::ptr imageFile = null_shared_ptr(),
                      bool flip = false,
                      bool integer = true);


protected:
    int indexOf (const std::string& text, char ch, int start) {
        int n = text.length();
        for (; start < n; start++)
            if (text[start] == ch) return start;
        return n;
    }
    
    BitmapFont (BitmapFontData* data, TextureRegion::ptr region, bool integer);
    
    static char xChars[] = {'x', 'e', 'a', 'o', 'n', 's', 'r', 'c', 'u', 'm', 'v', 'w', 'z'};

    graphics::g2d::TextureRegion::ptr region;
    TextBounds textBounds;
    float color = graphics::Color::WHITE.toFloatBits();
    Color tempColor = new Color(1, 1, 1, 1);
    bool flipped;
    bool integer = true;
    BitmapFontData* data;
    
private:    
    void load (const BitmapFontData& data);
};

} // namespace gdx_cpp
} // namespace graphics
} // namespace g2d

#endif // GDX_CPP_GRAPHICS_G2D_BITMAPFONT_HPP_
