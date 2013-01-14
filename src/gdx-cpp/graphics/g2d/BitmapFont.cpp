
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

#include "BitmapFont.hpp"

#include <stdexcept>
#include <string.h>

#include "gdx-cpp/utils/ArrayUtils.hpp"

#define LOG2_PAGE_SIZE 9
#define GDX_BITMAPFONT_PAGE_SIZE  (1 << LOG2_PAGE_SIZE)
#define GDX_BITMAPFONT_PAGES 0x10000 / GDX_BITMAPFONT_PAGE_SIZE

#define xChars "xeaonsrcumvwz"
#define capChars "MNBDCEFKAGHIJLOPTUVWXYZ"

using namespace gdx;

#define IS_IN_RANGE(c, f, l)    (((c) >= (f)) && ((c) <= (l)))

//function grabbed on http://stackoverflow.com/questions/2948308/how-do-i-read-utf-8-characters-via-a-pointer/2953960#2953960
ulong readNextChar (const char* p, unsigned int& index) 
{  
    // TODO: since UTF-8 is a variable-length
    // encoding, you should pass in the input
    // buffer's actual byte length so that you
    // can determine if a malformed UTF-8
    // sequence would exceed the end of the buffer...

    unsigned char c1, c2, *ptr = (unsigned char*) p;
    ulong uc = 0;
    int seqlen;
    // int datalen = ... available length of p ...;    

    /*
    if( datalen < 1 )
    {
        // malformed data, do something !!!
        return (u_long) -1;
    }
    */

    c1 = ptr[0];

    if( (c1 & 0x80) == 0 )
    {
        uc = (ulong) (c1 & 0x7F);
        seqlen = 1;
    }
    else if( (c1 & 0xE0) == 0xC0 )
    {
        uc = (ulong) (c1 & 0x1F);
        seqlen = 2;
    }
    else if( (c1 & 0xF0) == 0xE0 )
    {
        uc = (ulong) (c1 & 0x0F);
        seqlen = 3;
    }
    else if( (c1 & 0xF8) == 0xF0 )
    {
        uc = (ulong) (c1 & 0x07);
        seqlen = 4;
    }
    else
    {
        // malformed data, do something !!!
        return (ulong) -1;
    }

    /*
    if( seqlen > datalen )
    {
        // malformed data, do something !!!
        return (u_long) -1;
    }
    */

    for(int i = 1; i < seqlen; ++i)
    {
        c1 = ptr[i];

        if( (c1 & 0xC0) != 0x80 )
        {
            // malformed data, do something !!!
            return (ulong) -1;
        }
    }

    switch( seqlen )
    {
        case 2:
        {
            c1 = ptr[0];

            if( !IS_IN_RANGE(c1, 0xC2, 0xDF) )
            {
                // malformed data, do something !!!
                return (ulong) -1;
            }

            break;
        }

        case 3:
        {
            c1 = ptr[0];
            c2 = ptr[1];

            if( ((c1 == 0xE0) && !IS_IN_RANGE(c2, 0xA0, 0xBF)) ||
                ((c1 == 0xED) && !IS_IN_RANGE(c2, 0x80, 0x9F)) ||
                (!IS_IN_RANGE(c1, 0xE1, 0xEC) && !IS_IN_RANGE(c1, 0xEE, 0xEF)) )
            {
                // malformed data, do something !!!
                return (ulong) -1;
            }

            break;
        }

        case 4:
        {
            c1 = ptr[0];
            c2 = ptr[1];

            if( ((c1 == 0xF0) && !IS_IN_RANGE(c2, 0x90, 0xBF)) ||
                ((c1 == 0xF4) && !IS_IN_RANGE(c2, 0x80, 0x8F)) ||
                !IS_IN_RANGE(c1, 0xF1, 0xF3) )
            {
                // malformed data, do something !!!
                return (ulong) -1;
            }

            break;
        }
    }

    for(int i = 1; i < seqlen; ++i)
    {
        uc = ((uc << 6) | (ulong)(ptr[i] & 0x3F));
    }

    index += seqlen;
    return uc; 
}

void BitmapFont::BitmapFontData::setGlyph ( int ch, BitmapFont::Glyph::unique_ptr& glyph ) {
    auto& page = glyphs[ch / GDX_BITMAPFONT_PAGE_SIZE];

    if ( page.empty() ) {
        page.resize(GDX_BITMAPFONT_PAGE_SIZE);
    }

    page[ch & ( GDX_BITMAPFONT_PAGE_SIZE - 1 )].swap(glyph);
}

BitmapFont::Glyph* BitmapFont::BitmapFontData::getFirstGlyph () {
    for ( int i = 0; i < GDX_BITMAPFONT_PAGES; ++i ) {
        auto& page = glyphs[i];

        if ( page.empty() ) {
            continue;
        }

        for ( int j = 0; j < GDX_BITMAPFONT_PAGE_SIZE; ++j ) {
            auto& glyph = page[j];

            if ( glyph == nullptr ) {
                continue;
            }

            return glyph.get();
        }
    }

    gdx_log_error ("BitmapFontData::getFirstGlyph", "No glyphs found!" );
}

BitmapFont::Glyph* BitmapFont::BitmapFontData::getGlyph(unsigned int ch)
{
    auto& page = glyphs[ch / GDX_BITMAPFONT_PAGE_SIZE];

    if ( !page.empty() ) {
        return page[ch & ( GDX_BITMAPFONT_PAGE_SIZE - 1 )].get();
    }

    return nullptr;
}

unsigned int BitmapFont::BitmapFontData::getGlyph ( const std::string& str, unsigned int& pos, BitmapFont::Glyph*& result ) {
    result = nullptr;
    
    unsigned int ch = 0;
    if (isascii(str[pos])) {
        ch = str[pos];        
        pos++;
    } else if (pos + 1 < str.length()) { //we're handling utf-8
        ch = readNextChar(&str[pos], pos);        
    }
    
    auto& page = glyphs[ch / GDX_BITMAPFONT_PAGE_SIZE];

    if ( !page.empty() ) {
        result = page[ch & ( GDX_BITMAPFONT_PAGE_SIZE - 1 )].get();
    }

    return ch;
}

std::string BitmapFont::BitmapFontData::getImagePath () {
    return imagePath;
}

FileHandle::ptr BitmapFont::BitmapFontData::getFontFile () {
    return fontFile;
}

void BitmapFont::load ( BitmapFontData* data ) {
    float invTexWidth = 1.0f / region.getTexture()->getWidth();
    float invTexHeight = 1.0f / region.getTexture()->getHeight();
    float u = region.u;
    float v = region.v;

    for ( int i = 0; i < GDX_BITMAPFONT_PAGES; i++ ) {
        auto& page = data->glyphs[i];

        if ( page.empty() )
            continue;

        for ( int j = 0; j < GDX_BITMAPFONT_PAGE_SIZE; ++j ) {
            auto& glyph = page[j];

            if ( glyph == nullptr )
                continue;

            glyph->u = u + glyph->srcX * invTexWidth;
            glyph->u2 = u + ( glyph->srcX + glyph->width ) * invTexWidth;

            if ( data->flipped ) {
                glyph->v = v + glyph->srcY * invTexHeight;
                glyph->v2 = v + ( glyph->srcY + glyph->height ) * invTexHeight;
            } else {
                glyph->v2 = v + glyph->srcY * invTexHeight;
                glyph->v = v + ( glyph->srcY + glyph->height ) * invTexHeight;
            }
        }
    }
}

BitmapFont::TextBounds& BitmapFont::draw ( SpriteBatch& spriteBatch, const std::string& str, float x, float y ) {
    return draw ( spriteBatch, str, x, y, 0, str.length() );
}

BitmapFont::TextBounds& BitmapFont::draw ( SpriteBatch& spriteBatch, const std::string& str, float x, float y, unsigned int start, unsigned int end ) {
    float batchColor = spriteBatch.color;
    spriteBatch.setColor ( color );
    Texture::ptr texture = region.getTexture();
    y += data->ascent;
    float startX = x;

    Glyph* lastGlyph = nullptr;

    if ( data->scaleX == 1 && data->scaleY == 1 ) {
        if ( integer ) {
            y = ( int ) y;
            x = ( int ) x;
        }

        while ( start < end ) {            
            data->getGlyph ( str, start, lastGlyph );
            if ( lastGlyph != NULL ) {
                spriteBatch.draw ( *texture, //
                                   x + lastGlyph->xoffset, y + lastGlyph->yoffset, //
                                   lastGlyph->width, lastGlyph->height, //
                                   lastGlyph->u, lastGlyph->v, lastGlyph->u2, lastGlyph->v2 );
                x += lastGlyph->xadvance;
                break;
            }
        }
        while ( start < end ) {
            Glyph* g = nullptr;
            unsigned int ch = data->getGlyph ( str, start, g);
            
            if ( g == nullptr ) {
                continue;
            }
            x += lastGlyph->getKerning ( ch );
            if ( integer ) x = ( int ) x;
            lastGlyph = g;
            spriteBatch.draw ( *texture, //
                               x + lastGlyph->xoffset, y + lastGlyph->yoffset, //
                               lastGlyph->width, lastGlyph->height, //
                               lastGlyph->u, lastGlyph->v, lastGlyph->u2, lastGlyph->v2 );
            x += g->xadvance;
        }
    } else {
        float scaleX = this->data->scaleX, scaleY = this->data->scaleY;
        while ( start < end ) {            
            data->getGlyph ( str, start , lastGlyph);
            if ( lastGlyph != nullptr ) {
                if ( !integer ) {
                    spriteBatch.draw ( *texture, //
                                       x + lastGlyph->xoffset * scaleX, //
                                       y + lastGlyph->yoffset * scaleY, //
                                       lastGlyph->width * scaleX, //
                                       lastGlyph->height * scaleY, //
                                       lastGlyph->u, lastGlyph->v, lastGlyph->u2, lastGlyph->v2 );
                } else {
                    spriteBatch.draw ( *texture, //
                                       ( int ) ( x + lastGlyph->xoffset * scaleX ), //
                                       ( int ) ( y + lastGlyph->yoffset * scaleY ), //
                                       ( int ) ( lastGlyph->width * scaleX ), //
                                       ( int ) ( lastGlyph->height * scaleY ), //
                                       lastGlyph->u, lastGlyph->v, lastGlyph->u2, lastGlyph->v2 );
                }
                x += lastGlyph->xadvance * scaleX;
                break;
            }
        }
        while ( start < end ) {
            Glyph* g = nullptr;
            unsigned int ch = data->getGlyph ( str, start, g);            
            if ( g == nullptr ) {
                continue;
            }
            x += lastGlyph->getKerning ( ch ) * scaleX;
            lastGlyph = g;
            if ( !integer ) {
                spriteBatch.draw ( *texture, //
                                   x + lastGlyph->xoffset * scaleX, //
                                   y + lastGlyph->yoffset * scaleY, //
                                   lastGlyph->width * scaleX, //
                                   lastGlyph->height * scaleY, //
                                   lastGlyph->u, lastGlyph->v, lastGlyph->u2, lastGlyph->v2 );
            } else {
                spriteBatch.draw ( *texture, //
                                   ( int ) ( x + lastGlyph->xoffset * scaleX ), //
                                   ( int ) ( y + lastGlyph->yoffset * scaleY ), //
                                   ( int ) ( lastGlyph->width * scaleX ), //
                                   ( int ) ( lastGlyph->height * scaleY ), //
                                   lastGlyph->u, lastGlyph->v, lastGlyph->u2, lastGlyph->v2 );
            }
            x += g->xadvance * scaleX;
        }
    }
    spriteBatch.setColor ( batchColor );

    textBounds.width = x - startX;
    textBounds.height = data->capHeight;

    return textBounds;
}

BitmapFont::TextBounds& BitmapFont::drawMultiLine ( SpriteBatch& spriteBatch,const std::string& str,float x,float y ) {
    return drawMultiLine ( spriteBatch, str, x, y, 0, HAlignment::HALIGNMENT_LEFT );
}

BitmapFont::TextBounds& BitmapFont::drawMultiLine ( SpriteBatch& spriteBatch, const std::string& str, float x, float y, float alignmentWidth, const BitmapFont::HAlignment& alignment ) {
    float batchColor = spriteBatch.color;
    float down = this->data->down;
    int start = 0;
    int numLines = 0;
    int length = str.length();
    float maxWidth = 0;
    while ( start < length ) {
        int lineEnd = indexOf ( str, '\n', start );
        float xOffset = 0;
        if ( alignment != HAlignment::HALIGNMENT_LEFT ) {
            float lineWidth = getBounds ( str, start, lineEnd ).width;
            xOffset = alignmentWidth - lineWidth;
            if ( alignment == HAlignment::HALIGNMENT_CENTER ) xOffset = xOffset / 2;
        }
        float lineWidth = draw ( spriteBatch, str, x + xOffset, y, start, lineEnd ).width;
        maxWidth = std::max ( maxWidth, lineWidth );
        start = lineEnd + 1;
        y += down;
        numLines++;
    }
    spriteBatch.setColor ( batchColor );

    textBounds.width = maxWidth;
    textBounds.height = data->capHeight + ( numLines - 1 ) * data->lineHeight;
    return textBounds;
}

BitmapFont::TextBounds& BitmapFont::drawWrapped ( SpriteBatch& spriteBatch, const std::string& str, float x, float y, float wrapWidth ) {
    return drawWrapped ( spriteBatch, str, x, y, wrapWidth, HAlignment::HALIGNMENT_LEFT );
}

BitmapFont::TextBounds& BitmapFont::drawWrapped ( SpriteBatch& spriteBatch, const std::string& str, float x, float y, float wrapWidth, const BitmapFont::HAlignment& alignment ) {
    float batchColor = spriteBatch.color;
    float down = this->data->down;
    int start = 0;
    int numLines = 0;
    int length = str.length();
    float maxWidth = 0;
    while ( start < length ) {
        int lineEnd = start + computeVisibleGlyphs ( str, start, indexOf ( str, '\n', start ), wrapWidth );
        int nextLineStart;
        if ( lineEnd < length ) {
            int originalLineEnd = lineEnd;
            while ( lineEnd > start ) {
                unsigned int ch = str[lineEnd];
                if ( ch == ' ' || ch == '\n' ) break;
                lineEnd--;
            }
            if ( lineEnd == start ) {
                lineEnd = originalLineEnd;
                if ( lineEnd == start ) lineEnd++;
                nextLineStart = lineEnd;
            } else
                nextLineStart = lineEnd + 1; // Eat space or newline.
        } else {
            if ( lineEnd == start ) lineEnd++;
            nextLineStart = length;
        }
        float xOffset = 0;
        if ( alignment != HAlignment::HALIGNMENT_LEFT ) {
            float lineWidth = getBounds ( str, start, lineEnd ).width;
            xOffset = wrapWidth - lineWidth;
            if ( alignment ==  HAlignment::HALIGNMENT_CENTER ) xOffset /= 2;
        }
        float lineWidth = draw ( spriteBatch, str, x + xOffset, y, start, lineEnd ).width;
        maxWidth = std::max ( maxWidth, lineWidth );
        start = nextLineStart;
        y += down;
        numLines++;
    }
    spriteBatch.setColor ( batchColor );
    textBounds.width = maxWidth;
    textBounds.height = data->capHeight + ( numLines - 1 ) * data->lineHeight;
    return textBounds;
}

BitmapFont::TextBounds& BitmapFont::getBounds ( const std::string& str ) {
    return getBounds ( str, 0, str.length() );
}

BitmapFont::TextBounds& BitmapFont::getBounds ( const std::string& str, unsigned int start, unsigned  int end ) {
    float width = 0;
    Glyph* lastGlyph = NULL;
    while ( start < end ) {
        data->getGlyph ( str, start, lastGlyph );
        if ( lastGlyph != NULL ) {
            width = lastGlyph->xadvance;
            break;
        }
    }
    while ( start < end ) {
        Glyph* g = nullptr;         
        unsigned int ch = data->getGlyph ( str, start, g );
        if ( g != NULL ) {
            width += lastGlyph->getKerning ( ch );
            lastGlyph = g;
            width += g->xadvance;
        }
    }
    textBounds.width = width * data->scaleX;
    textBounds.height = data->capHeight;
    return textBounds;
}

BitmapFont::TextBounds& BitmapFont::getMultiLineBounds ( const std::string& str ) {
    int start = 0;
    float maxWidth = 0;
    int numLines = 0;
    int length = str.length();
    while ( start < length ) {
        int lineEnd = indexOf ( str, '\n', start );
        float lineWidth = getBounds ( str, start, lineEnd ).width;
        maxWidth = std::max ( maxWidth, lineWidth );
        start = lineEnd + 1;
        numLines++;
    }
    textBounds.width = maxWidth;
    textBounds.height = data->capHeight + ( numLines - 1 ) * data->lineHeight;
    return textBounds;
}

BitmapFont::TextBounds& BitmapFont::getWrappedBounds ( const std::string& str, float wrapWidth ) {
    int start = 0;
    int numLines = 0;
    int length = str.length();
    float maxWidth = 0;
    while ( start < length ) {
        int lineEnd = start + computeVisibleGlyphs ( str, start, indexOf ( str, '\n', start ), wrapWidth );
        int nextLineStart;
        if ( lineEnd < length ) {
            int originalLineEnd = lineEnd;
            while ( lineEnd > start ) {
                unsigned int ch = str[lineEnd];
                if ( ch == ' ' || ch == '\n' ) break;
                lineEnd--;
            }
            if ( lineEnd == start ) {
                lineEnd = originalLineEnd;
                if ( lineEnd == start ) lineEnd++;
                nextLineStart = lineEnd;
            } else
                nextLineStart = lineEnd + 1; // Eat space or newline.
        } else {
            if ( lineEnd == start ) lineEnd++;
            nextLineStart = length;
        }
        float lineWidth = getBounds ( str, start, lineEnd ).width;
        maxWidth = std::max ( maxWidth, lineWidth );
        start = nextLineStart;
        numLines++;
    }
    textBounds.width = maxWidth;
    textBounds.height = data->capHeight + ( numLines - 1 ) * (data->lineHeight * data->scaleY);
    return textBounds;
}

void BitmapFont::computeGlyphAdvancesAndPositions ( const std::string& str,
        std::vector<float>& glyphAdvances,
        std::vector<float>& glyphPositions ) {
    glyphAdvances.clear();
    glyphPositions.clear();
    
    unsigned int index = 0;
    unsigned int end = str.length();
    
    float width = 0;
    Glyph* lastGlyph = NULL;

    if ( data->scaleX == 1 ) {
        for ( ; index < end;) {
            Glyph* g = nullptr;            
            unsigned int ch = data->getGlyph ( str , index, g  );
            if ( g != NULL ) {
                if ( lastGlyph != NULL ) width += lastGlyph->getKerning ( ch );
                lastGlyph = g;
                glyphAdvances.push_back ( g->xadvance );
                glyphPositions.push_back ( width );
                width += g->xadvance;
            }
        }
        glyphAdvances.push_back ( 0 );
        glyphPositions.push_back ( width );
    } else {
        float scaleX = this->data->scaleX;
        for ( ; index < end; ) {
            Glyph* g = nullptr;            
            unsigned int ch = data->getGlyph ( str , index, g  );
            if ( g != NULL ) {
                if ( lastGlyph != NULL ) {
                    width += lastGlyph->getKerning ( ch ) * scaleX;
                }
                lastGlyph = g;
                glyphAdvances.push_back ( g->xadvance * scaleX );
                glyphPositions.push_back ( width );
                width += g->xadvance;
            }
        }
        glyphAdvances.push_back ( 0 );
        glyphPositions.push_back ( width );
    }
}

int BitmapFont::computeVisibleGlyphs ( const std::string& str, unsigned int start, unsigned int end, float availableWidth ) {
    unsigned int index = start;
    float width = 0;
    Glyph* lastGlyph = NULL;
    if ( data->scaleX == 1 ) {
        for ( ; index < end; ) {
            Glyph* g = nullptr;            
            unsigned int ch = data->getGlyph ( str , index, g  );
            if ( g != NULL ) {
                if ( lastGlyph != NULL ) width += lastGlyph->getKerning ( ch );
                lastGlyph = g;
                if ( width + g->xadvance > availableWidth ) break;
                width += g->xadvance;
            }
        }
    } else {
        float scaleX = this->data->scaleX;
        for ( ; index < end; ) {
            Glyph* g = nullptr;            
            unsigned int ch = data->getGlyph ( str , index, g  );
            if ( g != NULL ) {
                if ( lastGlyph != NULL ) width += lastGlyph->getKerning ( ch ) * scaleX;
                lastGlyph = g;
                if ((width + g->xadvance * scaleX) - availableWidth > 0.000001f ) break;
                width += g->xadvance * scaleX;
            }
        }
    }
    return index - start;
}

void BitmapFont::setColor ( float color ) {
    this->color = color;
}

void BitmapFont::setColor ( const Color& tint ) {
    this->color = tint.toFloatBits();
}

void BitmapFont::setColor ( float r,float g,float b,float a ) {
    int intBits = ( int ) ( 255 * a ) << 24 | ( int ) ( 255 * b ) << 16 | ( int ) ( 255 * g ) << 8 | ( int ) ( 255 * r );
    color = NumberUtils::intBitsToFloat ( ( intBits & 0xfeffffff ) );
}

Color BitmapFont::getColor () {
    int intBits = NumberUtils::floatToRawIntBits ( color );
    Color color = this->tempColor;
    color.r = ( intBits & 0xff ) / 255.f;
    color.g = ( ( intBits >> 8 ) & 0xff ) / 255.f;
    color.b = ( ( intBits >> 16 ) & 0xff ) / 255.f;
    color.a = ( ( intBits >> 24 ) & 0xff ) / 255.f;

    return color;
}

void BitmapFont::setScale ( float scaleX,float scaleY ) {
    data->spaceWidth = data->spaceWidth / this->data->scaleX * scaleX;
    data->xHeight = data->xHeight / this->data->scaleY * scaleY;
    data->capHeight = data->capHeight / this->data->scaleY * scaleY;
    data->ascent = data->ascent / this->data->scaleY * scaleY;
    data->descent = data->descent / this->data->scaleY * scaleY;
    data->down = data->down / this->data->scaleY * scaleY;
    data->scaleX = scaleX;
    data->scaleY = scaleY;
}

void BitmapFont::setScale ( float scaleXY ) {
    setScale ( scaleXY, scaleXY );
}

void BitmapFont::scale ( float amount ) {
    setScale ( data->scaleX + amount, data->scaleY + amount );
}

float BitmapFont::getScaleX () {
    return data->scaleX;
}

float BitmapFont::getScaleY () {
    return data->scaleY;
}

const TextureRegion& BitmapFont::getRegion () {
    return region;
}

float BitmapFont::getLineHeight () {
    return data->lineHeight;
}

float BitmapFont::getSpaceWidth () {
    return data->spaceWidth;
}

float BitmapFont::getXHeight () {
    return data->xHeight;
}

float BitmapFont::getCapHeight () {
    return data->capHeight;
}

float BitmapFont::getAscent () {
    return data->ascent;
}

float BitmapFont::getDescent () {
    return data->descent;
}

bool BitmapFont::isFlipped () {
    return flipped;
}

void BitmapFont::dispose () {
//     region.getTexture()->dispose();
}

void BitmapFont::setFixedWidthGlyphs ( const std::string& glyphs ) {
    int maxAdvance = 0;
    for ( unsigned int index = 0, end = glyphs.length(); index < end; ) {
        Glyph* g = nullptr;
        data->getGlyph ( glyphs, index, g );
        if ( g != NULL && g->xadvance > maxAdvance ) maxAdvance = g->xadvance;
    }
    for ( unsigned int index = 0, end = glyphs.length(); index < end; ) {
        Glyph* g = nullptr;
        data->getGlyph ( glyphs, index, g );
        if ( g == nullptr )
            continue;
        g->xoffset += ( maxAdvance - g->xadvance ) / 2;
        g->xadvance = maxAdvance;
        g->kerning.release();
    }
}

bool BitmapFont::containsCharacter ( unsigned int character ) {
    return data->getGlyph ( character ) != NULL;
}

void BitmapFont::setUseIntegerPositions ( bool use ) {
    this->integer = use;
}

bool BitmapFont::usesIntegerPositions () {
    return integer;
}

BitmapFont::BitmapFontData* BitmapFont::getData () {
    return data;
}

float BitmapFont::BitmapFontData::getFontSize() const
{
    return fontSize;
}

BitmapFont::BitmapFont ( BitmapFont::BitmapFontData* p_data, TextureRegion p_region, bool p_integer )
    : region ( p_region ),
color ( Color::WHITE.toFloatBits() ),
tempColor ( 1,1,1,1 ),
flipped ( p_data->flipped ),
integer ( p_integer ),
data ( p_data ) {
    if ( !region.isValid() ) {
        region = TextureRegion::newFromTexture ( Texture::newFromFile ( files->internal ( data->imagePath ), NULL, false ) );
    }
    load ( data );
}

std::unique_ptr< BitmapFont > BitmapFont::fromFiles ( FileHandle::ptr fontFile, FileHandle::ptr imageFile, bool flip, bool integer, bool generateMipmaps ) {
    BitmapFontData* data = new BitmapFontData ( fontFile, flip );
    
    TextureRegion region;
    if (!imageFile) {
        region = TextureRegion::newFromTexture ( Texture::newFromFile ( gdx::files->internal(data->imagePath) , NULL, generateMipmaps ) );
    } else {
        region = TextureRegion::newFromTexture ( Texture::newFromFile ( imageFile , NULL, generateMipmaps ) );
    }

    return std::unique_ptr<BitmapFont>(new BitmapFont ( data, region, integer ));
}

BitmapFont::BitmapFontData::BitmapFontData ( FileHandle::ptr fontFile, bool flip )
    : fontFile ( fontFile ),
flipped ( flip ),
capHeight ( 1 ),
ascent ( 0 ),
descent ( 0 ),
down ( 0 ),
scaleX ( 1 ),
scaleY ( 1 ),
spaceWidth ( 0 ),
xHeight ( 1 ),
fontSize(0) {
    std::vector <char> n_buffer;
    
    {
        FileHandle::buffer_ptr buffer;
        int readed = fontFile->readBytes ( buffer );
        n_buffer.resize ( readed + 1);
        memcpy ( &n_buffer[0], buffer.get(), readed );
        n_buffer.back() = 0;
    }

    char* line_r = NULL;

    try {
        char* line = strtok_r ( &n_buffer[0], "\n", &line_r );
        
        strtok ( line, " " );
        strtok ( NULL, " " );        
        
        if ( sscanf ( strtok ( NULL, " " ), "size=%f", &fontSize ) != 1 ) {
            gdx_log_error("gdx", "Invalid font file: %s", fontFile->toString().c_str() );
        }
        
        if ( ( line = strtok_r ( NULL, "\n", &line_r ) ) == NULL ) {
            gdx_log_error("gdx", "Invalid font file: %s", fontFile->toString().c_str() );
        }

        char* common = strtok ( line, " " );

        if ( sscanf ( strtok ( NULL, " " ), "lineHeight=%f", &lineHeight ) != 1 ) {
            gdx_log_error("gdx", "Invalid font file: %s", fontFile->toString().c_str() );
        }

        int baseLine = 0;
        if ( sscanf ( strtok ( NULL, " " ), "base=%d", &baseLine ) != 1 ) {
            gdx_log_error("gdx", "Invalid font file: %s", fontFile->toString().c_str() );
        }

        if ( ( line = strtok_r ( NULL, "\n", &line_r ) ) == NULL ) {
            gdx_log_error("gdx", "Invalid font file: %s", fontFile->toString().c_str() );
        }

        strtok ( line, " " );
        strtok ( NULL, " " );

        char file[1024];
        if ( sscanf ( strtok ( NULL, " " ), "file=%s", file ) < 0 ) {
            gdx_log_error("gdx", "Invalid font file: %s", fontFile->toString().c_str() );
        }

        //removing the quotes (") from start and end of the string
        char unquoted[1024];
        strncpy ( unquoted, file + 1, strlen ( file ) - 2 );
        unquoted[strlen ( file ) - 2] = 0;

        imagePath = unquoted;
        descent = 0;

        while ( true ) {
            line = strtok_r ( NULL, "\n", &line_r );

            if ( line == NULL ) {
                break;
            }

            if ( strstr ( line, "kernings " ) != NULL ) break;
            if ( strstr ( line, "char " ) == NULL ) continue;

            Glyph::unique_ptr glyph = std::unique_ptr<Glyph>(new Glyph());

            int ch = 0;

            if ( sscanf ( line, "char id=%d x=%d y=%d width=%d height=%d xoffset=%d yoffset=%d xadvance=%d page=%*s chnl=%*s",
                          &ch, &glyph->srcX, &glyph->srcY, &glyph->width, &glyph->height, &glyph->xoffset, &glyph->yoffset, &glyph->xadvance ) != 8 ) {

                gdx_log_error("gdx", "Invalid font file: %s", fontFile->toString().c_str() );
            }

            if ( ch <= 0xffff ) {
                if ( !flip ) {
                    glyph->yoffset = - ( glyph->height + glyph->yoffset );
                }

                descent = std::min ( ( float ) ( baseLine + glyph->yoffset ), descent );                
                setGlyph ( ch, glyph );
            }            
        }

        while ( true ) {
            line = strtok_r ( NULL, "\n", &line_r );
            if ( line == NULL ) {
                break;
            }

            if ( strstr ( line, "kerning " ) == NULL ) break;

            unsigned int first = 0, second = 0, amount = 0;

            if ( sscanf ( line, "kerning first=%d second=%d amount=%d", &first, &second, &amount ) != 3 ) {
                gdx_log_error("gdx", "Invalid font file: %s", fontFile->toString().c_str() );
            }

            if ( first < 0 || first > 0xffff || second < 0 || second > 0xffff )
                continue;

            Glyph* glyph = getGlyph ( first );
            glyph->setKerning ( second, amount );
        }

        Glyph* spaceGlyph = getGlyph ( ' ' );
        
        if ( spaceGlyph == nullptr ) {
            spaceGlyph = new Glyph();
            Glyph* xadvanceGlyph = getGlyph ( 'l' );
            if ( xadvanceGlyph == nullptr ) xadvanceGlyph = getFirstGlyph();
            spaceGlyph->xadvance = xadvanceGlyph->xadvance;
            auto uptr = std::unique_ptr<Glyph>(spaceGlyph);
            setGlyph ( ' ', uptr);
        }

        spaceWidth = spaceGlyph != nullptr ? spaceGlyph->xadvance + spaceGlyph->width : 1;

        Glyph* xGlyph = NULL;
        for ( int i = 0; i < array_size ( xChars ); i++ ) {
            xGlyph = getGlyph ( xChars[i] );
            if ( xGlyph != NULL ) break;
        }

        if ( xGlyph == NULL ) xGlyph = getFirstGlyph();
        xHeight = xGlyph->height;

        Glyph* capGlyph = NULL;
        for ( int i = 0; i < array_size ( capChars ); i++ ) {
            capGlyph = getGlyph ( capChars[i] );
            if ( capGlyph != NULL ) break;
        }
        if ( xGlyph == NULL ) xGlyph = getFirstGlyph();
        capHeight = capGlyph->height;

        ascent = baseLine - capHeight;
        down = -lineHeight;
        if ( flip ) {
            ascent = -ascent;
            down = -down;
        }
    } catch ( std::exception e ) {
       gdx_log_debug ( "BitmapFont", "Constructor exception: %s", e.what() );
        gdx_log_error("gdx", "Error loading font file: %s", fontFile->name().c_str() );
    }
}

void BitmapFont::TextBounds::set ( const BitmapFont::TextBounds& bounds ) {
    width = bounds.width;
    height = bounds.height;
}

BitmapFont::TextBounds::TextBounds() : width ( 0 ),
height ( 0 ) {
}

void BitmapFont::Glyph::setKerning ( unsigned int ch, unsigned int value ) {
    if ( kerning == nullptr ) {
        kerning = kerning_t(new kerning_t::element_type);
    }

    auto& page = (*kerning)[ch >> LOG2_PAGE_SIZE];

    if ( page.empty() ) {
        page.resize(GDX_BITMAPFONT_PAGE_SIZE);
    }

    page[ch & ( GDX_BITMAPFONT_PAGE_SIZE - 1 )] = value;
}

int BitmapFont::Glyph::getKerning ( unsigned int ch ) {
    if ( kerning != nullptr ) {
        auto& page = (*kerning)[ch >> LOG2_PAGE_SIZE];
        if ( page.empty() ) {
            return page[ch & ( GDX_BITMAPFONT_PAGE_SIZE - 1 )];
        }
    }

    return 0;
}

BitmapFont::BitmapFontData::~BitmapFontData() {
}

BitmapFont::Glyph::~Glyph() {
}

BitmapFont::Glyph::Glyph() : srcX ( 0 ),
srcY ( 0 ),
width ( 0 ),
height ( 0 ),
u ( 0 ),
v ( 0 ),
u2 ( 0 ),
v2 ( 0 ),
xoffset ( 0 ),
yoffset ( 0 ),
xadvance ( 0 ) {
}
