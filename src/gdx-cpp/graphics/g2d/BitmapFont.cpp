
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

using namespace gdx_cpp::graphics::g2d;

void BitmapFont::setGlyph (int ch,const Glyph& glyph) {
    Glyph[] page = glyphs[ch / PAGE_SIZE];
    if (page == null) glyphs[ch / PAGE_SIZE] = page = new Glyph[PAGE_SIZE];
    page[ch & PAGE_SIZE - 1] = glyph;
}

Glyph& BitmapFont::getFirstGlyph () {
for (Glyph[] page : this.glyphs) {
        if (page == null) continue;
for (Glyph glyph : page) {
            if (glyph == null) continue;
            return glyph;
        }
    }
    throw new GdxRuntimeException("No glyphs found!");
}

Glyph& BitmapFont::getGlyph (char ch) {
    Glyph[] page = glyphs[ch / PAGE_SIZE];
    if (page != null) return page[ch & PAGE_SIZE - 1];
    return null;
}

std::string& BitmapFont::getImageFile () {
    return imgFile;
}

void BitmapFont::load (const BitmapFontData& data) {
    float invTexWidth = 1.0f / region.getTexture().getWidth();
    float invTexHeight = 1.0f / region.getTexture().getHeight();
    float u = region.u;
    float v = region.v;

for (Glyph[] page : data.glyphs) {
        if (page == null) continue;
for (Glyph glyph : page) {
            if (glyph == null) continue;
            glyph.u = u + glyph.srcX * invTexWidth;
            glyph.u2 = u + (glyph.srcX + glyph.width) * invTexWidth;
            if (data.flipped) {
                glyph.v = v + glyph.srcY * invTexHeight;
                glyph.v2 = v + (glyph.srcY + glyph.height) * invTexHeight;
            } else {
                glyph.v2 = v + glyph.srcY * invTexHeight;
                glyph.v = v + (glyph.srcY + glyph.height) * invTexHeight;
            }
        }
    }
}

TextBounds& BitmapFont::draw (const SpriteBatch& spriteBatch,const CharSequence& str,float x,float y) {
    return draw(spriteBatch, str, x, y, 0, str.length());
}

TextBounds& BitmapFont::draw (const SpriteBatch& spriteBatch,const CharSequence& str,float x,float y,int start,int end) {
    float batchColor = spriteBatch.color;
    spriteBatch.setColor(color);
    final Texture texture = region.getTexture();
    y += data.ascent;
    float startX = x;
    Glyph lastGlyph = null;
    if (data.scaleX == 1 && data.scaleY == 1) {
        while (start < end) {
            lastGlyph = data.getGlyph(str.charAt(start++));
            if (lastGlyph != null) {
                if (!integer) {
                    spriteBatch.draw(texture, //
                                     x + lastGlyph.xoffset, y + lastGlyph.yoffset, //
                                     lastGlyph.width, lastGlyph.height, //
                                     lastGlyph.u, lastGlyph.v, lastGlyph.u2, lastGlyph.v2);
                } else {
                    spriteBatch.draw(texture, //
                                     (int)x + lastGlyph.xoffset, (int)y + lastGlyph.yoffset, //
                                     lastGlyph.width, lastGlyph.height, //
                                     lastGlyph.u, lastGlyph.v, lastGlyph.u2, lastGlyph.v2);
                }
                x += lastGlyph.xadvance;
                break;
            }
        }
        while (start < end) {
            char ch = str.charAt(start++);
            Glyph g = data.getGlyph(ch);
            if (g == null) continue;
            x += lastGlyph.getKerning(ch);
            lastGlyph = g;
            if (!integer) {
                spriteBatch.draw(texture, //
                                 x + lastGlyph.xoffset, y + lastGlyph.yoffset, //
                                 lastGlyph.width, lastGlyph.height, //
                                 lastGlyph.u, lastGlyph.v, lastGlyph.u2, lastGlyph.v2);
            } else {
                spriteBatch.draw(texture, //
                                 (int)x + lastGlyph.xoffset, (int)y + lastGlyph.yoffset, //
                                 lastGlyph.width, lastGlyph.height, //
                                 lastGlyph.u, lastGlyph.v, lastGlyph.u2, lastGlyph.v2);
            }
            x += g.xadvance;
        }
    } else {
        float scaleX = this.data.scaleX, scaleY = this.data.scaleY;
        while (start < end) {
            lastGlyph = data.getGlyph(str.charAt(start++));
            if (lastGlyph != null) {
                if (!integer) {
                    spriteBatch.draw(texture, //
                                     x + lastGlyph.xoffset * scaleX, //
                                     y + lastGlyph.yoffset * scaleY, //
                                     lastGlyph.width * scaleX, //
                                     lastGlyph.height * scaleY, //
                                     lastGlyph.u, lastGlyph.v, lastGlyph.u2, lastGlyph.v2);
                } else {
                    spriteBatch.draw(texture, //
                                     (int)(x + lastGlyph.xoffset * scaleX), //
                                     (int)(y + lastGlyph.yoffset * scaleY), //
                                     (int)(lastGlyph.width * scaleX), //
                                     (int)(lastGlyph.height * scaleY), //
                                     lastGlyph.u, lastGlyph.v, lastGlyph.u2, lastGlyph.v2);
                }
                x += lastGlyph.xadvance * scaleX;
                break;
            }
        }
        while (start < end) {
            char ch = str.charAt(start++);
            Glyph g = data.getGlyph(ch);
            if (g == null) continue;
            x += lastGlyph.getKerning(ch) * scaleX;
            lastGlyph = g;
            if (!integer) {
                spriteBatch.draw(texture, //
                                 x + lastGlyph.xoffset * scaleX, //
                                 y + lastGlyph.yoffset * scaleY, //
                                 lastGlyph.width * scaleX, //
                                 lastGlyph.height * scaleY, //
                                 lastGlyph.u, lastGlyph.v, lastGlyph.u2, lastGlyph.v2);
            } else {
                spriteBatch.draw(texture, //
                                 (int)(x + lastGlyph.xoffset * scaleX), //
                                 (int)(y + lastGlyph.yoffset * scaleY), //
                                 (int)(lastGlyph.width * scaleX), //
                                 (int)(lastGlyph.height * scaleY), //
                                 lastGlyph.u, lastGlyph.v, lastGlyph.u2, lastGlyph.v2);
            }
            x += g.xadvance * scaleX;
        }
    }
    spriteBatch.setColor(batchColor);
    textBounds.width = x - startX;
    textBounds.height = data.capHeight;
    return textBounds;
}

TextBounds& BitmapFont::drawMultiLine (const SpriteBatch& spriteBatch,const CharSequence& str,float x,float y) {
    return drawMultiLine(spriteBatch, str, x, y, 0, HAlignment.LEFT);
}

TextBounds& BitmapFont::drawMultiLine (const SpriteBatch& spriteBatch,const CharSequence& str,float x,float y,float alignmentWidth,const HAlignment& alignment) {
    float batchColor = spriteBatch.color;
    float down = this.data.down;
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
        maxWidth = Math.max(maxWidth, lineWidth);
        start = lineEnd + 1;
        y += down;
        numLines++;
    }
    spriteBatch.setColor(batchColor);

    textBounds.width = maxWidth;
    textBounds.height = data.capHeight + (numLines - 1) * data.lineHeight;
    return textBounds;
}

TextBounds& BitmapFont::drawWrapped (const SpriteBatch& spriteBatch,const CharSequence& str,float x,float y,float wrapWidth) {
    return drawWrapped(spriteBatch, str, x, y, wrapWidth, HAlignment.LEFT);
}

TextBounds& BitmapFont::drawWrapped (const SpriteBatch& spriteBatch,const CharSequence& str,float x,float y,float wrapWidth,const HAlignment& alignment) {
    float batchColor = spriteBatch.color;
    float down = this.data.down;
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
                char ch = str.charAt(lineEnd);
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
        maxWidth = Math.max(maxWidth, lineWidth);
        start = nextLineStart;
        y += down;
        numLines++;
    }
    spriteBatch.setColor(batchColor);
    textBounds.width = maxWidth;
    textBounds.height = data.capHeight + (numLines - 1) * data.lineHeight;
    return textBounds;
}

TextBounds& BitmapFont::getBounds (const CharSequence& str) {
    return getBounds(str, 0, str.length());
}

TextBounds& BitmapFont::getBounds (const CharSequence& str,int start,int end) {
    int width = 0;
    Glyph lastGlyph = null;
    while (start < end) {
        lastGlyph = data.getGlyph(str.charAt(start++));
        if (lastGlyph != null) {
            width = lastGlyph.xadvance;
            break;
        }
    }
    while (start < end) {
        char ch = str.charAt(start++);
        Glyph g = data.getGlyph(ch);
        if (g != null) {
            width += lastGlyph.getKerning(ch);
            lastGlyph = g;
            width += g.xadvance;
        }
    }
    textBounds.width = width * data.scaleX;
    textBounds.height = data.capHeight;
    return textBounds;
}

TextBounds& BitmapFont::getMultiLineBounds (const CharSequence& str) {
    int start = 0;
    float maxWidth = 0;
    int numLines = 0;
    int length = str.length();
    while (start < length) {
        int lineEnd = indexOf(str, '\n', start);
        float lineWidth = getBounds(str, start, lineEnd).width;
        maxWidth = Math.max(maxWidth, lineWidth);
        start = lineEnd + 1;
        numLines++;
    }
    textBounds.width = maxWidth;
    textBounds.height = data.capHeight + (numLines - 1) * data.lineHeight;
    return textBounds;
}

TextBounds& BitmapFont::getWrappedBounds (const CharSequence& str,float wrapWidth) {
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
                char ch = str.charAt(lineEnd);
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
        maxWidth = Math.max(maxWidth, lineWidth);
        start = nextLineStart;
        numLines++;
    }
    textBounds.width = maxWidth;
    textBounds.height = data.capHeight + (numLines - 1) * data.lineHeight;
    return textBounds;
}

void BitmapFont::computeGlyphAdvancesAndPositions (const CharSequence& str,const gdx_cpp::utils::FloatArray& glyphAdvances,const gdx_cpp::utils::FloatArray& glyphPositions) {
    glyphAdvances.clear();
    glyphPositions.clear();
    int index = 0;
    int end = str.length();
    int width = 0;
    Glyph lastGlyph = null;
    if (data.scaleX == 1) {
        for (; index < end; index++) {
            char ch = str.charAt(index);
            Glyph g = data.getGlyph(ch);
            if (g != null) {
                if (lastGlyph != null) width += lastGlyph.getKerning(ch);
                lastGlyph = g;
                glyphAdvances.add(g.xadvance);
                glyphPositions.add(width);
                width += g.xadvance;
            }
        }
        glyphAdvances.add(0);
        glyphPositions.add(width);
    } else {
        float scaleX = this.data.scaleX;
        for (; index < end; index++) {
            char ch = str.charAt(index);
            Glyph g = data.getGlyph(ch);
            if (g != null) {
                if (lastGlyph != null) width += lastGlyph.getKerning(ch) * scaleX;
                lastGlyph = g;
                glyphAdvances.add(g.xadvance * scaleX);
                glyphPositions.add(width);
                width += g.xadvance;
            }
        }
        glyphAdvances.add(0);
        glyphPositions.add(width);
    }
}

int BitmapFont::computeVisibleGlyphs (const CharSequence& str,int start,int end,float availableWidth) {
    int index = start;
    int width = 0;
    Glyph lastGlyph = null;
    if (data.scaleX == 1) {
        for (; index < end; index++) {
            char ch = str.charAt(index);
            Glyph g = data.getGlyph(ch);
            if (g != null) {
                if (lastGlyph != null) width += lastGlyph.getKerning(ch);
                lastGlyph = g;
                if (width + g.width + g.xoffset > availableWidth) break;
                width += g.xadvance;
            }
        }
    } else {
        float scaleX = this.data.scaleX;
        for (; index < end; index++) {
            char ch = str.charAt(index);
            Glyph g = data.getGlyph(ch);
            if (g != null) {
                if (lastGlyph != null) width += lastGlyph.getKerning(ch) * scaleX;
                lastGlyph = g;
                if (width + (g.width + g.xoffset) * scaleX > availableWidth) break;
                width += g.xadvance * scaleX;
            }
        }
    }
    return index - start;
}

void BitmapFont::setColor (const gdx_cpp::graphics::Color& tint) {
    this.color = tint.toFloatBits();
}

void BitmapFont::setColor (float r,float g,float b,float a) {
    int intBits = (int)(255 * a) << 24 | (int)(255 * b) << 16 | (int)(255 * g) << 8 | (int)(255 * r);
    color = NumberUtils.intBitsToFloat((intBits & 0xfeffffff));
}

gdx_cpp::graphics::Color& BitmapFont::getColor () {
    int intBits = NumberUtils.floatToRawIntBits(color);
    Color color = this.tempColor;
    color.r = (intBits & 0xff) / 255f;
    color.g = ((intBits >>> 8) & 0xff) / 255f;
    color.b = ((intBits >>> 16) & 0xff) / 255f;
    color.a = ((intBits >>> 24) & 0xff) / 255f;
    return color;
}

void BitmapFont::setScale (float scaleX,float scaleY) {
    data.spaceWidth = data.spaceWidth / this.data.scaleX * scaleX;
    data.xHeight = data.xHeight / this.data.scaleY * scaleY;
    data.capHeight = data.capHeight / this.data.scaleY * scaleY;
    data.ascent = data.ascent / this.data.scaleY * scaleY;
    data.descent = data.descent / this.data.scaleY * scaleY;
    data.down = data.down / this.data.scaleY * scaleY;
    data.scaleX = scaleX;
    data.scaleY = scaleY;
}

void BitmapFont::setScale (float scaleXY) {
    setScale(scaleXY, scaleXY);
}

void BitmapFont::scale (float amount) {
    setScale(data.scaleX + amount, data.scaleY + amount);
}

float BitmapFont::getScaleX () {
    return data.scaleX;
}

float BitmapFont::getScaleY () {
    return data.scaleY;
}

TextureRegion& BitmapFont::getRegion () {
    return region;
}

float BitmapFont::getLineHeight () {
    return data.lineHeight;
}

float BitmapFont::getSpaceWidth () {
    return data.spaceWidth;
}

float BitmapFont::getXHeight () {
    return data.xHeight;
}

float BitmapFont::getCapHeight () {
    return data.capHeight;
}

float BitmapFont::getAscent () {
    return data.ascent;
}

float BitmapFont::getDescent () {
    return data.descent;
}

bool BitmapFont::isFlipped () {
    return flipped;
}

void BitmapFont::dispose () {
    region.getTexture().dispose();
}

void BitmapFont::setFixedWidthGlyphs (const CharSequence& glyphs) {
    int maxAdvance = 0;
    for (int index = 0, end = glyphs.length(); index < end; index++) {
        Glyph g = data.getGlyph(glyphs.charAt(index));
        if (g != null && g.xadvance > maxAdvance) maxAdvance = g.xadvance;
    }
    for (int index = 0, end = glyphs.length(); index < end; index++) {
        Glyph g = data.getGlyph(glyphs.charAt(index));
        if (g == null) continue;
        g.xoffset += (maxAdvance - g.xadvance) / 2;
        g.xadvance = maxAdvance;
        g.kerning = null;
    }
}

void BitmapFont::set (const TextBounds& bounds) {
    width = bounds.width;
    height = bounds.height;
}

bool BitmapFont::containsCharacter (char character) {
    return data.getGlyph(character) != null;
}

void BitmapFont::setUseIntegerPositions (bool use) {
    this.integer = use;
}

bool BitmapFont::usesIntegerPositions () {
    return integer;
}

