
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

    static const unsigned LOG2_PAGE_SIZE = 9;
    static const unsigned GDX_BITMAPFONT_PAGE_SIZE  = 1 << LOG2_PAGE_SIZE;
    static const unsigned GDX_BITMAPFONT_PAGES = 0x10000 / GDX_BITMAPFONT_PAGE_SIZE;
   
public:
    typedef ref_ptr_maker<BitmapFont>::shared_ptr_t ptr;
    
    enum class HAlignment {
        HALIGNMENT_LEFT, HALIGNMENT_CENTER, HALIGNMENT_RIGHT
    };

    struct Glyph {
        typedef ref_ptr_maker<Glyph>::unique_ptr_t unique_ptr;
        
        int srcX;
        int srcY;
        int width, height;
        float u, v, u2, v2;
        int xoffset, yoffset;
        int xadvance;
        
        typedef std::unique_ptr< std::array< std::vector<unsigned int>, GDX_BITMAPFONT_PAGES> > kerning_t;
        kerning_t kerning;

        int getKerning (unsigned int ch);
        void setKerning (unsigned int ch, unsigned int value);

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

        std::array< std::vector< Glyph::unique_ptr >, GDX_BITMAPFONT_PAGES > glyphs;

        float spaceWidth;
        float xHeight;

    public:
        ~BitmapFontData();

        BitmapFontData (FileHandle::ptr fontFile, bool flip);
        
        unsigned int getGlyph (const std::string& str, unsigned int& pos, Glyph*& result);

        std::string getImagePath ();
        FileHandle::ptr getFontFile ();
        float getFontSize() const;

    protected:
        Glyph* getGlyph( unsigned int ch );
        
    private:
        void setGlyph (int ch, BitmapFont::Glyph::unique_ptr& glyph);
        Glyph* getFirstGlyph ();
        float fontSize;
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
    TextBounds& draw (gdx::SpriteBatch& spriteBatch, const std::string& str, float x, float y, unsigned int start, unsigned int end);
    TextBounds& drawMultiLine (SpriteBatch& spriteBatch, const std::string& str, float x, float y);
    TextBounds& drawMultiLine (SpriteBatch& spriteBatch, const std::string& str, float x, float y, float alignmentWidth, const BitmapFont::HAlignment& alignment);
    TextBounds& drawWrapped (SpriteBatch& spriteBatch, const std::string& str, float x, float y, float wrapWidth);
    TextBounds& drawWrapped (SpriteBatch& spriteBatch, const std::string& str, float x, float y, float wrapWidth, const BitmapFont::HAlignment& alignment);
    TextBounds& getBounds (const std::string& str);
    TextBounds& getBounds (const std::string& str, unsigned int start, unsigned int end);
    TextBounds& getMultiLineBounds (const std::string& str);
    TextBounds& getWrappedBounds (const std::string& str,float wrapWidth);

    void computeGlyphAdvancesAndPositions (const std::string& str, std::vector< float >& glyphAdvances, std::vector< float >& glyphPositions);
    int computeVisibleGlyphs (const std::string& str, unsigned int start, unsigned int end, float availableWidth);

    void setColor (float color);
    void setColor (const Color& tint);
    void setColor (float r,float g,float b,float a);

    Color getColor ();
    void setScale (float scaleX,float scaleY);
    void setScale (float scaleXY);
    void scale (float amount);
    float getScaleX ();
    float getScaleY ();
    const TextureRegion& getRegion ();
    float getLineHeight ();
    float getSpaceWidth ();
    float getXHeight ();
    float getCapHeight ();
    float getAscent ();
    float getDescent ();
    bool isFlipped ();
    void dispose ();
    void setFixedWidthGlyphs (const std::string& glyphs);
    bool containsCharacter (unsigned int character);
    void setUseIntegerPositions (bool use);
    bool usesIntegerPositions ();
    
    
    BitmapFontData* getData ();

    static std::unique_ptr<BitmapFont> fromFiles (FileHandle::ptr fontFile,
                                  FileHandle::ptr imageFile = nullptr,
                                  bool flip = false,
                                  bool integer = true,
                                  bool generateMipmaps = false);

    static int indexOf (const std::string& text, wchar_t ch, int start) {
        int n = text.length();
        for (; start < n; start++)
            if (text[start] == ch) return start;
        return n;
    }

protected:

    BitmapFont ( gdx::BitmapFont::BitmapFontData* p_data, gdx::TextureRegion p_region, bool p_integer );

    TextureRegion region;
    TextBounds textBounds;
    float color;
    Color tempColor;
    bool flipped;
    bool integer;
    BitmapFontData* data;
    int fontSize;
    
private:
    void load (BitmapFontData* data);
};

} // namespace gdx

#endif // GDX_CPP_GRAPHICS_G2D_BITMAPFONT_HPP_
