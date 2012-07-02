
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

namespace gdx {
class BitmapFontCache;

class BitmapFont: public Disposable {
    friend class BitmapFontCache;
protected:
    static const int LOG2_PAGE_SIZE = 9;
    static const int PAGE_SIZE = 1 << LOG2_PAGE_SIZE;
    static const int PAGES = 0x10000 / PAGE_SIZE;

public:
    typedef ref_ptr_maker<BitmapFont>::shared_ptr_def ptr;

    enum HAlignment {
        HALIGNMENT_LEFT, HALIGNMENT_CENTER, HALIGNMENT_RIGHT
    };

    struct Glyph {
        int srcX;
        int srcY;
        int width, height;
        float u, v, u2, v2;
        int xoffset, yoffset;
        int xadvance;
        char** kerning;

        int getKerning (char ch);
        void setKerning (int ch, int value);

        Glyph();
        ~Glyph();
    };

    class BitmapFontData {
        friend class BitmapFont;
        friend class BitmapFontCache;
    protected:
        std::string imagePath;
        FileHandle::ptr fontFile;
        bool flipped;
        float lineHeight;
        float capHeight;
        float ascent;
        float descent;
        float down;
        float scaleX , scaleY;

        Glyph*** glyphs;

        float spaceWidth;
        float xHeight;

    public:
        ~BitmapFontData();

        BitmapFontData (FileHandle::ptr fontFile, bool flip);
        Glyph* getGlyph (char ch);
        std::string getImagePath ();
        FileHandle::ptr getFontFile ();

    private:
        void setGlyph (int ch,Glyph* glyph);
        Glyph* getFirstGlyph ();
    };

    struct TextBounds {
        float width;
        float height;

        TextBounds () ;

        TextBounds (const TextBounds& bounds) {
            set(bounds);
        }

        void set (const TextBounds& bounds) ;
    };


    TextBounds& draw (SpriteBatch& spriteBatch, const std::string& str, float x, float y);
    TextBounds& draw (SpriteBatch& spriteBatch, const std::string& str, float x, float y, int start, int end);
    TextBounds& drawMultiLine (SpriteBatch& spriteBatch, const std::string& str, float x, float y);
    TextBounds& drawMultiLine (SpriteBatch& spriteBatch, const std::string& str, float x, float y, float alignmentWidth, int alignment);
    TextBounds& drawWrapped (SpriteBatch& spriteBatch, const std::string& str, float x, float y, float wrapWidth);
    TextBounds& drawWrapped (SpriteBatch& spriteBatch, const std::string& str, float x, float y, float wrapWidth, const BitmapFont::HAlignment& alignment);
    TextBounds& getBounds (const std::string& str);
    TextBounds& getBounds (const std::string& str,int start,int end);
    TextBounds& getMultiLineBounds (const std::string& str);
    TextBounds& getWrappedBounds (const std::string& str,float wrapWidth);

    void computeGlyphAdvancesAndPositions (const std::string& str, std::vector< float >& glyphAdvances, std::vector< float >& glyphPositions);
    int computeVisibleGlyphs (const std::string& str,int start,int end,float availableWidth);

    void setColor (float color);
    void setColor (const Color& tint);
    void setColor (float r,float g,float b,float a);

    Color getColor ();
    void setScale (float scaleX,float scaleY);
    void setScale (float scaleXY);
    void scale (float amount);
    float getScaleX ();
    float getScaleY ();
    TextureRegion::ptr getRegion ();
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

    static BitmapFont* fromFiles (FileHandle::ptr fontFile,
                                  FileHandle::ptr imageFile = null_shared_ptr(),
                                  bool flip = false,
                                  bool integer = true);

    static int indexOf (const std::string& text, char ch, int start) {
        int n = text.length();
        for (; start < n; start++)
            if (text[start] == ch) return start;
        return n;
    }

protected:

    BitmapFont (BitmapFontData* data, TextureRegion::ptr region, bool integer);

    static const char xChars[];
    static const char capChars[];

    TextureRegion::ptr region;
    TextBounds textBounds;
    float color;
    Color tempColor;
    bool flipped;
    bool integer;
    BitmapFontData* data;

private:
    void load (BitmapFontData* data);
};

} // namespace gdx

#endif // GDX_CPP_GRAPHICS_G2D_BITMAPFONT_HPP_
