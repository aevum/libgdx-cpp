
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

using namespace gdx_cpp::graphics::g2d;
using namespace gdx_cpp;

void BitmapFont::BitmapFontData::setGlyph (int ch, graphics::g2d::BitmapFont::Glyph* glyph) {
    Glyph* page = glyphs[ch / PAGE_SIZE];
    if (page == NULL) glyphs[ch / PAGE_SIZE] = page = new Glyph[PAGE_SIZE];
    page[ch & PAGE_SIZE - 1] = glyph;
}

BitmapFont::Glyph* BitmapFont::BitmapFontData::getFirstGlyph () {
    for (int i = 0; i < PAGES; ++i) {
            Glyph* page = glyphs[i];

            if (page == NULL) {
                continue;
            }
            
            for (int j = 0; j < PAGE_SIZE; ++j) {
                Glyph* glyph = page[j];

                if (glyph == NULL) {
                    continue;
                }
                return glyph;
        }
    }
    throw new std::runtime_error("No glyphs found!");
}

BitmapFont::Glyph* BitmapFont::BitmapFontData::getGlyph (char ch) {
    Glyph* page = glyphs[ch / PAGE_SIZE];
    
    if (page != NULL) return page[ch & PAGE_SIZE - 1];

    return NULL;
}

std::string BitmapFont::BitmapFontData::getImagePath () {
    return imagePath;
}

gdx_cpp::files::FileHandle& BitmapFont::BitmapFontData::getFontFile () {
    return fontFile;
}

void BitmapFont::load (const BitmapFontData& data) {
    float invTexWidth = 1.0f / region->getTexture()->getWidth();
    float invTexHeight = 1.0f / region->getTexture()->getHeight();
    float u = region->u;
    float v = region->v;

    for (int i = 0; i < PAGES; i++) {
        Glyph* page = data->glyphs[i];
        if (page == NULL)
            continue;
        for (int j = 0; j < PAGE_SIZE;++j) {
            Glyph* glyph = page[j];
            
            if (glyph == NULL)
                continue;
            
            glyph->u = u + glyph->srcX * invTexWidth;
            glyph->u2 = u + (glyph->srcX + glyph->width) * invTexWidth;
            
            if (data->flipped) {
                glyph->v = v + glyph->srcY * invTexHeight;
                glyph->v2 = v + (glyph->srcY + glyph->height) * invTexHeight;
            } else {
                glyph->v2 = v + glyph->srcY * invTexHeight;
                glyph->v = v + (glyph->srcY + glyph->height) * invTexHeight;
            }
        }
    }
}

BitmapFont::TextBounds& BitmapFont::draw (SpriteBatch& spriteBatch,const std::string& str,float x,float y) {
    return draw(spriteBatch, str, x, y, 0, str.length());
}

BitmapFont::TextBounds& BitmapFont::draw (SpriteBatch& spriteBatch,const std::string& str,float x,float y,int start,int end) {
    float batchColor = spriteBatch.color;
    spriteBatch.setColor(color);
    graphics::Texture::ptr texture = region->getTexture();
    y += data->ascent;
    float startX = x;

    Glyph* lastGlyph = NULL;
    
    if (data->scaleX == 1 && data->scaleY == 1) {
        if (integer) {
            y = (int)y;
            x = (int)x;
        }
        
        while (start < end) {
            lastGlyph = data->getGlyph(str[start++]);
            if (lastGlyph != NULL) {
                spriteBatch.draw(*texture, //
                                 x + lastGlyph->xoffset, y + lastGlyph->yoffset, //
                                 lastGlyph->width, lastGlyph->height, //
                                 lastGlyph->u, lastGlyph->v, lastGlyph->u2, lastGlyph->v2);
                x += lastGlyph->xadvance;
                break;
            }
        }
        while (start < end) {
            char ch = str[start++];
            Glyph* g = data->getGlyph(ch);
            if (g == NULL) {
                continue;
            }
            x += lastGlyph->getKerning(ch);
            if (integer) x = (int)x;
            lastGlyph = g;
            spriteBatch.draw(*texture, //
                             x + lastGlyph->xoffset, y + lastGlyph->yoffset, //
                             lastGlyph->width, lastGlyph->height, //
                             lastGlyph->u, lastGlyph->v, lastGlyph->u2, lastGlyph->v2);
            x += g->xadvance;
        }
    } else {
        float scaleX = this->data->scaleX, scaleY = this->data->scaleY;
        while (start < end) {
            lastGlyph = data->getGlyph(str[start++]);
            if (lastGlyph != NULL) {
                if (!integer) {
                    spriteBatch.draw(*texture, //
                                     x + lastGlyph->xoffset * scaleX, //
                                     y + lastGlyph->yoffset * scaleY, //
                                     lastGlyph->width * scaleX, //
                                     lastGlyph->height * scaleY, //
                                     lastGlyph->u, lastGlyph->v, lastGlyph->u2, lastGlyph->v2);
                } else {
                    spriteBatch.draw(*texture, //
                                     (int)(x + lastGlyph->xoffset * scaleX), //
                                     (int)(y + lastGlyph->yoffset * scaleY), //
                                     (int)(lastGlyph->width * scaleX), //
                                     (int)(lastGlyph->height * scaleY), //
                                     lastGlyph->u, lastGlyph->v, lastGlyph->u2, lastGlyph->v2);
                }
                x += lastGlyph->xadvance * scaleX;
                break;
            }
        }
        while (start < end) {
            char ch = str[start++];
            Glyph* g = data->getGlyph(ch);
            if (g == NULL) {
                continue;
            }
            x += lastGlyph->getKerning(ch) * scaleX;
            lastGlyph = g;
            if (!integer) {
                spriteBatch.draw(*texture, //
                                 x + lastGlyph->xoffset * scaleX, //
                                 y + lastGlyph->yoffset * scaleY, //
                                 lastGlyph->width * scaleX, //
                                 lastGlyph->height * scaleY, //
                                 lastGlyph->u, lastGlyph->v, lastGlyph->u2, lastGlyph->v2);
            } else {
                spriteBatch.draw(*texture, //
                                 (int)(x + lastGlyph->xoffset * scaleX), //
                                 (int)(y + lastGlyph->yoffset * scaleY), //
                                 (int)(lastGlyph->width * scaleX), //
                                 (int)(lastGlyph->height * scaleY), //
                                 lastGlyph->u, lastGlyph->v, lastGlyph->u2, lastGlyph->v2);
            }
            x += g->xadvance * scaleX;
        }
    }
    spriteBatch.setColor(batchColor);
    
    textBounds.width = x - startX;
    textBounds.height = data->capHeight;

    return textBounds;
}

BitmapFont::TextBounds& BitmapFont::drawMultiLine (SpriteBatch& spriteBatch,const std::string& str,float x,float y) {
    return drawMultiLine(spriteBatch, str, x, y, 0, HAlignment.LEFT);
}

BitmapFont::TextBounds& BitmapFont::drawMultiLine (SpriteBatch& spriteBatch,const std::string& str,float x,float y,float alignmentWidth,const HAlignment& alignment) {
    float batchColor = spriteBatch.color;
    float down = this->data->down;
    int start = 0;
    int numLines = 0;
    int length = str.length();
    float maxWidth = 0;
    while (start < length) {
        int lineEnd = indexOf(str, '\n', start);
        float xOffset = 0;
        if (alignment != HAlignment.LEFT) {
            float lineWidth = getBounds(str, start, lineEnd).width;
            xOffset = alignmentWidth - lineWidth;
            if (alignment == HAlignment.CENTER) xOffset = xOffset / 2;
        }
        float lineWidth = draw(spriteBatch, str, x + xOffset, y, start, lineEnd).width;
        maxWidth = std::max(maxWidth, lineWidth);
        start = lineEnd + 1;
        y += down;
        numLines++;
    }
    spriteBatch.setColor(batchColor);

    textBounds.width = maxWidth;
    textBounds.height = data->capHeight + (numLines - 1) * data->lineHeight;
    return textBounds;
}

BitmapFont::TextBounds& BitmapFont::drawWrapped (const SpriteBatch& spriteBatch,const std::string& str,float x,float y,float wrapWidth) {
    return drawWrapped(spriteBatch, str, x, y, wrapWidth, HAlignment.LEFT);
}

BitmapFont::TextBounds& BitmapFont::drawWrapped (const SpriteBatch& spriteBatch,const std::string& str,float x,float y,float wrapWidth,const HAlignment& alignment) {
    float batchColor = spriteBatch.color;
    float down = this->data->down;
    int start = 0;
    int numLines = 0;
    int length = str.length();
    float maxWidth = 0;
    while (start < length) {
        int lineEnd = start + computeVisibleGlyphs(str, start, indexOf(str, '\n', start), wrapWidth);
        int nextLineStart;
        if (lineEnd < length) {
            int originalLineEnd = lineEnd;
            while (lineEnd > start) {
                char ch = str[lineEnd];
                if (ch == ' ' || ch == '\n') break;
                lineEnd--;
            }
            if (lineEnd == start) {
                lineEnd = originalLineEnd;
                if (lineEnd == start) lineEnd++;
                nextLineStart = lineEnd;
            } else
                nextLineStart = lineEnd + 1; // Eat space or newline.
        } else {
            if (lineEnd == start) lineEnd++;
            nextLineStart = length;
        }
        float xOffset = 0;
        if (alignment != HAlignment.LEFT) {
            float lineWidth = getBounds(str, start, lineEnd).width;
            xOffset = wrapWidth - lineWidth;
            if (alignment == HAlignment.CENTER) xOffset /= 2;
        }
        float lineWidth = draw(spriteBatch, str, x + xOffset, y, start, lineEnd).width;
        maxWidth = std::max(maxWidth, lineWidth);
        start = nextLineStart;
        y += down;
        numLines++;
    }
    spriteBatch.setColor(batchColor);
    textBounds.width = maxWidth;
    textBounds.height = data->capHeight + (numLines - 1) * data->lineHeight;
    return textBounds;
}

BitmapFont::TextBounds& BitmapFont::getBounds (const std::string& str) {
    return getBounds(str, 0, str.length());
}

BitmapFont::TextBounds& BitmapFont::getBounds (const std::string& str,int start,int end) {
    int width = 0;
    Glyph* lastGlyph = NULL;
    while (start < end) {
        lastGlyph = data->getGlyph(str[start++]);
        if (lastGlyph != NULL) {
            width = lastGlyph->xadvance;
            break;
        }
    }
    while (start < end) {
        char ch = str[start++];
        Glyph* g = data->getGlyph(ch);
        if (g != NULL) {
            width += lastGlyph->getKerning(ch);
            lastGlyph = g;
            width += g->xadvance;
        }
    }
    textBounds.width = width * data->scaleX;
    textBounds.height = data->capHeight;
    return textBounds;
}

BitmapFont::TextBounds& BitmapFont::getMultiLineBounds (const std::string& str) {
    int start = 0;
    float maxWidth = 0;
    int numLines = 0;
    int length = str.length();
    while (start < length) {
        int lineEnd = indexOf(str, '\n', start);
        float lineWidth = getBounds(str, start, lineEnd).width;
        maxWidth = std::max(maxWidth, lineWidth);
        start = lineEnd + 1;
        numLines++;
    }
    textBounds.width = maxWidth;
    textBounds.height = data->capHeight + (numLines - 1) * data->lineHeight;
    return textBounds;
}

BitmapFont::TextBounds& BitmapFont::getWrappedBounds (const std::string& str,float wrapWidth) {
    int start = 0;
    int numLines = 0;
    int length = str.length();
    float maxWidth = 0;
    while (start < length) {
        int lineEnd = start + computeVisibleGlyphs(str, start, indexOf(str, '\n', start), wrapWidth);
        int nextLineStart;
        if (lineEnd < length) {
            int originalLineEnd = lineEnd;
            while (lineEnd > start) {
                char ch = str[lineEnd];
                if (ch == ' ' || ch == '\n') break;
                lineEnd--;
            }
            if (lineEnd == start) {
                lineEnd = originalLineEnd;
                if (lineEnd == start) lineEnd++;
                nextLineStart = lineEnd;
            } else
                nextLineStart = lineEnd + 1; // Eat space or newline.
        } else {
            if (lineEnd == start) lineEnd++;
            nextLineStart = length;
        }
        float lineWidth = getBounds(str, start, lineEnd).width;
        maxWidth = std::max(maxWidth, lineWidth);
        start = nextLineStart;
        numLines++;
    }
    textBounds.width = maxWidth;
    textBounds.height = data->capHeight + (numLines - 1) * data->lineHeight;
    return textBounds;
}

void BitmapFont::computeGlyphAdvancesAndPositions (const std::string& str,
                                                   std::vector<float>& glyphAdvances,
                                                   std::vector<float>& glyphPositions) {
    glyphAdvances.clear();
    glyphPositions.clear();
    int index = 0;
    int end = str.length();
    int width = 0;
    Glyph* lastGlyph = NULL;
    
    if (data->scaleX == 1) {
        for (; index < end; index++) {
            char ch = str[index];
            Glyph* g = data->getGlyph(ch);
            if (g != NULL) {
                if (lastGlyph != NULL) width += lastGlyph->getKerning(ch);
                lastGlyph = g;
                glyphAdvances.push_back(g->xadvance);
                glyphPositions.push_back(width);
                width += g->xadvance;
            }
        }
        glyphAdvances.push_back(0);
        glyphPositions.push_back(width);
    } else {
        float scaleX = this->data->scaleX;
        for (; index < end; index++) {
            char ch = str[index];
            Glyph g = data->getGlyph(ch);
            if (g != NULL) {
                if (lastGlyph != NULL) {
                    width += lastGlyph->getKerning(ch) * scaleX;
                }
                lastGlyph = g;
                glyphAdvances.push_back(g.xadvance * scaleX);
                glyphPositions.push_back(width);
                width += g.xadvance;
            }
        }
        glyphAdvances.push_back(0);
        glyphPositions.push_back(width);
    }
}

int BitmapFont::computeVisibleGlyphs (const std::string& str, int start, int end, float availableWidth) {
    int index = start;
    int width = 0;
    Glyph* lastGlyph = NULL;
    if (data->scaleX == 1) {
        for (; index < end; index++) {
            char ch = str[index];
            Glyph g = data->getGlyph(ch);
            if (g != NULL) {
                if (lastGlyph != NULL) width += lastGlyph->getKerning(ch);
                lastGlyph = g;
                if (width + g.xadvance > availableWidth) break;
                width += g.xadvance;
            }
        }
    } else {
        float scaleX = this->data->scaleX;
        for (; index < end; index++) {
            char ch = str[index];
            Glyph* g = data->getGlyph(ch);
            if (g != NULL) {
                if (lastGlyph != NULL) width += lastGlyph->getKerning(ch) * scaleX;
                lastGlyph = g;
                if (width + g->xadvance * scaleX > availableWidth) break;
                width += g->xadvance * scaleX;
            }
        }
    }
    return index - start;
}

void BitmapFont::setColor (float color) {
    this->color = color;
}

void BitmapFont::setColor (const gdx_cpp::graphics::Color& tint) {
    this->color = tint.toFloatBits();
}

void BitmapFont::setColor (float r,float g,float b,float a) {
    int intBits = (int)(255 * a) << 24 | (int)(255 * b) << 16 | (int)(255 * g) << 8 | (int)(255 * r);
    color = gdx_cpp::utils::NumberUtils::intBitsToFloat((intBits & 0xfeffffff));
}

gdx_cpp::graphics::Color BitmapFont::getColor () {
    int intBits = gdx_cpp::utils::NumberUtils::floatToRawIntBits(color);
    graphics::Color color = this->tempColor;
    color.r = (intBits & 0xff) / 255.f;
    color.g = ((intBits >>> 8) & 0xff) / 255.f;
    color.b = ((intBits >>> 16) & 0xff) / 255.f;
    color.a = ((intBits >>> 24) & 0xff) / 255.f;

    return color;
}

void BitmapFont::setScale (float scaleX,float scaleY) {
    data->spaceWidth = data->spaceWidth / this->data->scaleX * scaleX;
    data->xHeight = data->xHeight / this->data->scaleY * scaleY;
    data->capHeight = data->capHeight / this->data->scaleY * scaleY;
    data->ascent = data->ascent / this->data->scaleY * scaleY;
    data->descent = data->descent / this->data->scaleY * scaleY;
    data->down = data->down / this->data->scaleY * scaleY;
    data->scaleX = scaleX;
    data->scaleY = scaleY;
}

void BitmapFont::setScale (float scaleXY) {
    setScale(scaleXY, scaleXY);
}

void BitmapFont::scale (float amount) {
    setScale(data->scaleX + amount, data->scaleY + amount);
}

float BitmapFont::getScaleX () {
    return data->scaleX;
}

float BitmapFont::getScaleY () {
    return data->scaleY;
}

TextureRegion& BitmapFont::getRegion () {
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
    region->getTexture()->dispose();
}

void BitmapFont::setFixedWidthGlyphs (const std::string& glyphs) {
    int maxAdvance = 0;
    for (int index = 0, end = glyphs.length(); index < end; index++) {
        Glyph* g = data->getGlyph(glyphs[index]);
        if (g != NULL && g->xadvance > maxAdvance) maxAdvance = g->xadvance;
    }
    for (int index = 0, end = glyphs.length(); index < end; index++) {
        Glyph* g = data->getGlyph(glyphs[index]);
        if (g == NULL)
            continue;
        g->xoffset += (maxAdvance - g.xadvance) / 2;
        g->xadvance = maxAdvance;
        g->kerning = NULL;
    }
}

bool BitmapFont::containsCharacter (char character) {
    return data->getGlyph(character) != NULL;
}

void BitmapFont::setUseIntegerPositions (bool use) {
    this->integer = use;
}

bool BitmapFont::usesIntegerPositions () {
    return integer;
}

BitmapFont::BitmapFontData* BitmapFont::getData () {
    return data;
}

void BitmapFont::TextBounds::set (const TextBounds& bounds) {
    width = bounds.width;
    height = bounds.height;
}

BitmapFont::BitmapFont (graphics::g2d::BitmapFont::BitmapFontData* p_data, graphics::g2d::TextureRegion::ptr p_region, bool p_integer)
: data(p_data),
region(p_region),
integer(p_integer),
flipped(p_data->flipped)
{
    if (region == NULL) {
        region = TextureRegion::nemFromTexture(graphics::Texture::fromFile(Gdx::files->internal(data->imagePath)), false);
    }
    load(data);
}

BitmapFont* BitmapFont::fromFiles(files::FileHandle::ptr fontFile, files::FileHandle::ptr imageFile, bool flip, bool integer)
{
    BitmapFontData* data = new BitmapFontData(fontFile, flip);
    graphics::g2d::TextureRegion::ptr region = graphics::g2d::TextureRegion::nemFromTexture(graphics::Texture::fromFile(imageFile, false));

    return new BitmapFont(data, region, integer);
}

BitmapFont::BitmapFontData::BitmapFontData(files::FileHandle::ptr fontFile, bool flip)
 : fontFile(fontFile),
 flipped(flip)
{
    this->fontFile = fontFile;
    this->flipped = flip;

    files::FileHandle::char_ptr buffer;
    int len = fontFile->readBytes(buffer);
    char* line_r = NULL;
    
    try {
        char* line = strtok_r(buffer.get(), '\n', &line_r);
        line = strtok_r(NULL, '\n', &line_r);
        
        if (line == NULL) {
            throw std::runtime_error("Invalid font file: " + fontFile->toString());
        }

        char* common = strtok(line, ' ');
        common = strtok(NULL, ' ');
        
        if (sscanf(common, "lineHeight=%d", &lineHeight) != 1) {
            throw std::runtime_error("Invalid font file: " + fontFile->toString());
        }
        
        common = strtok(NULL, ' ');

        int baseLine = 0;
        if (sscanf(common, "base=%d", &baseLine) != 1) {
            throw std::runtime_error("Invalid font file: " + fontFile->toString());
        }

        if ((line = strtok_r(NULL, '\n', &line_r)) == NULL) {
            throw std::runtime_error("Invalid font file: " + fontFile->toString());
        }

        common = strtok(line, ' ');
        common = strtok(NULL, ' ');

        char file[1024];
        if (sscanf(common, "file=%s", &file) < 0) {
            throw std::runtime_error("Invalid font file: " + fontFile->toString());
        }

        imagePath = fontFile->parent().child(file).path();        
        descent = 0;

        while (true) {
            line = strtok_r(NULL, '\n', line_r);
            
            if (line == NULL) {
                break;
            }
            
            if (strpbrk(line, "kernings ") != NULL) break;
            if (strpbrk(line, "char ") == NULL) continue;

            Glyph* glyph = new Glyph();

            common = strtok(line, " =");
            strtok(NULL, " =");
            strtok(NULL, " =");
                        
            int ch = 0;
            if (sscanf(strtok(NULL, " ="), "%d", &ch) != 1) {
                throw std::runtime_error("Invalid font file: " + fontFile->toString());
            }
            
            if (ch <= "\uffff")
                setGlyph(ch, glyph);
            else
                continue;
            
            strtok(NULL, " =");
            if (sscanf(strtok(NULL, " ="), "%d", &glyph->srcX) != 1) {
                throw std::runtime_error("Invalid font file: " + fontFile->toString());
            }

            strtok(NULL, " =");            
            if (sscanf(strtok(NULL, " ="), "%d", &glyph->srcY) != 1) {
                throw std::runtime_error("Invalid font file: " + fontFile->toString());
            }

            strtok(NULL, " =");
            if (sscanf(strtok(NULL, " ="), "%d", &glyph->width) != 1) {
                throw std::runtime_error("Invalid font file: " + fontFile->toString());
            }

            strtok(NULL, " =");
            if (sscanf(strtok(NULL, " ="), "%d", &glyph->height) != 1) {
                throw std::runtime_error("Invalid font file: " + fontFile->toString());
            }

            strtok(NULL, " =");
            if (sscanf(strtok(NULL, " ="), "%d", &glyph->xoffset) != 1) {
                throw std::runtime_error("Invalid font file: " + fontFile->toString());
            }

            strtok(NULL, " =");

            if (sscanf(strtok(NULL, " ="), "%d", &glyph->yoffset) != 1) {
                throw std::runtime_error("Invalid font file: " + fontFile->toString());
            }
            
            if (!flip) {
                glyph->yoffset = -(glyph->height + glyph->yoffset);
            }
          
            strtok(NULL, " =");
            if (sscanf(strtok(NULL, " ="), "%d", &glyph->xadvance) != 1) {
                throw std::runtime_error("Invalid font file: " + fontFile->toString());
            }
            
            descent = std::min(baseLine + glyph->yoffset, descent);
        }

        while (true) {
            line = strtok_r(NULL, '\n', &line_r);
            if (line == NULL) {
                break;
            }
            
            if (strpbrk(line, "kerning ") == NULL) break;

            int first = 0, second = 0, amount = 0;

            if (sscanf(line, "kerning first=%d second=%d amount=%d", &first, &second, &amount) != 3) {
                throw std::runtime_error("Invalid font file: " + fontFile->toString());
            }

            if (first < 0 || first > "\uffff" || second < 0 || second > "\uffff")
                continue;
            
            Glyph* glyph = getGlyph((char)first);
            glyph->setKerning(second, amount);
        }

        Glyph* spaceGlyph = getGlyph(' ');
        if (spaceGlyph == NULL) {
            spaceGlyph = new Glyph();
            Glyph* xadvanceGlyph = getGlyph('l');
            if (xadvanceGlyph == NULL) xadvanceGlyph = getFirstGlyph();
            spaceGlyph->xadvance = xadvanceGlyph->xadvance;
            setGlyph(' ', spaceGlyph);
        }
        spaceWidth = spaceGlyph != NULL ? spaceGlyph->xadvance + spaceGlyph->width : 1;

        Glyph* xGlyph = NULL;
        for (int i = 0; i < utils::array_size(xChars); i++) {
            xGlyph = getGlyph(xChars[i]);
            if (xGlyph != NULL) break;
        }

        if (xGlyph == NULL) xGlyph = getFirstGlyph();
        xHeight = xGlyph->height;

        Glyph* capGlyph = NULL;
        for (int i = 0; i < utils::array_size(capChars); i++) {
            capGlyph = getGlyph(capChars[i]);
            if (capGlyph != NULL) break;
        }
        if (xGlyph == NULL) xGlyph = getFirstGlyph();
        capHeight = capGlyph->height;

        ascent = baseLine - capHeight;
        down = -lineHeight;
        if (flip) {
            ascent = -ascent;
            down = -down;
        }
    } catch (std::exception e) {
        throw std::runtime_error("Error loading font file: " + fontFile->name());
    }
}

void BitmapFont::TextBounds::set(BitmapFont::TextBounds bounds) {
    width = bounds.width;
    height = bounds.height;
}

BitmapFont::TextBounds::TextBounds() {
}

void BitmapFont::Glyph::setKerning(int ch, int value) {
    if (kerning == NULL) {
        kerning = new char[PAGES];
        memset(kerning, 0, PAGES);
    }
    
    char* page = kerning[ch >> LOG2_PAGE_SIZE];

    if (page == NULL) {
        kerning[ch >> LOG2_PAGE_SIZE] = page = new char[PAGE_SIZE];
    }
    
    page[ch & PAGE_SIZE - 1] = (char) value;
}

int BitmapFont::Glyph::getKerning(char ch) {
    if (kerning != NULL) {
        char* page = kerning[ch >> LOG2_PAGE_SIZE];
        if (page != NULL) {
            return page[ch & PAGE_SIZE - 1];
        }
    }
    
    return 0;
}


