
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

#include "BitmapFontCache.hpp"

using namespace gdx;

void BitmapFontCache::setPosition (float x,float y) {
    translate(x - this->x, y - this->y);
}

void BitmapFontCache::translate (float xAmount,float yAmount) {
    if (xAmount == 0 && yAmount == 0) return;
    if (integer) {
        xAmount = (int)xAmount;
        yAmount = (int)yAmount;
    }
    x += xAmount;
    y += yAmount;
    
    for (int i = 0, n = idx; i < n; i += 5) {
        vertices[i] += xAmount;
        vertices[i + 1] += yAmount;
    }
}

void BitmapFontCache::setColor (float color) {
    if (color == this->color) return;
    this->color = color;
    
    for (int i = 2, n = idx; i < n; i += 5)
        vertices[i] = color;
}

void BitmapFontCache::setColor (const Color& tint) {
    float color = tint.toFloatBits();
    if (color == this->color) return;
    this->color = color;

    for (int i = 2, n = idx; i < n; i += 5)
        vertices[i] = color;
}

void BitmapFontCache::setColor (float r,float g,float b,float a) {
    int intBits = ((int)(255 * a) << 24) | ((int)(255 * b) << 16) | ((int)(255 * g) << 8) | ((int)(255 * r));
    float color = NumberUtils::intBitsToFloat((intBits & 0xfeffffff));
    if (color == this->color) return;
    this->color = color;

    for (int i = 2, n = idx; i < n; i += 5) {
        vertices[i] = color;
    }
}

void BitmapFontCache::draw (SpriteBatch& spriteBatch) {
    spriteBatch.draw(*font->getRegion().getTexture(), &vertices[0], vertices.size(), 0, idx);
}

void BitmapFontCache::draw (SpriteBatch& spriteBatch,float alphaModulation) {
    Color color = getColor();
    float oldAlpha = color.a;
    color.a *= alphaModulation;
    setColor(color);
    draw(spriteBatch);
    color.a = oldAlpha;
    setColor(color);
}

Color& BitmapFontCache::getColor () {
    float floatBits = color;
    int intBits = NumberUtils::floatToRawIntBits(color);
    
    tmpColor.r = (intBits & 0xff) / 255.f;
    tmpColor.g = ((intBits >> 8) & 0xff) / 255.f;
    tmpColor.b = ((intBits >> 16) & 0xff) / 255.f;
    tmpColor.a = ((intBits >> 24) & 0xff) / 255.f;
    return tmpColor;
}

void BitmapFontCache::reset (int glyphCount) {
    x = 0;
    y = 0;
    idx = 0;

    int vertexCount = glyphCount * 20;
    if (vertices.empty() || vertices.size() < vertexCount) vertices.resize(vertexCount);
}

float BitmapFontCache::addToCache (const std::string& str,float x,float y,int start,int end) {
    float startX = x;
    BitmapFont::Glyph* lastGlyph = NULL;
    if (font->data->scaleX == 1 && font->data->scaleY == 1) {
        while (start < end) {
            lastGlyph = font->data->getGlyph(str[start++]);
            if (lastGlyph != NULL) {
                addGlyph(lastGlyph, x + lastGlyph->xoffset, y + lastGlyph->yoffset, lastGlyph->width, lastGlyph->height);
                x += lastGlyph->xadvance;
                break;
            }
        }
        while (start < end) {
            char ch = str[start++];
            BitmapFont::Glyph* g = font->data->getGlyph(ch);
            if (g != NULL) {
                x += lastGlyph->getKerning(ch);
                lastGlyph = g;
                addGlyph(lastGlyph, x + g->xoffset, y + g->yoffset, g->width, g->height);
                x += g->xadvance;
            }
        }
    } else {
        float scaleX = font->data->scaleX, scaleY = font->data->scaleY;
        while (start < end) {
            lastGlyph = font->data->getGlyph(str[start++]);
            if (lastGlyph != NULL) {
                addGlyph(lastGlyph, //
                         x + lastGlyph->xoffset * scaleX, //
                         y + lastGlyph->yoffset * scaleY, //
                         lastGlyph->width * scaleX, //
                         lastGlyph->height * scaleY);
                x += lastGlyph->xadvance * scaleX;
                break;
            }
        }
        while (start < end) {
            char ch = str[start++];
            BitmapFont::Glyph* g = font->data->getGlyph(ch);
            if (g != NULL) {
                x += lastGlyph->getKerning(ch) * scaleX;
                lastGlyph = g;
                addGlyph(lastGlyph, //
                         x + g->xoffset * scaleX, //
                         y + g->yoffset * scaleY, //
                         g->width * scaleX, //
                         g->height * scaleY);
                x += g->xadvance * scaleX;
            }
        }
    }
    return x - startX;
}

void BitmapFontCache::addGlyph (BitmapFont::Glyph* glyph, float x, float y, float width, float height) {
    float x2 = x + width;
    float y2 = y + height;
    float u = glyph->u;
    float u2 = glyph->u2;
    float v = glyph->v;
    float v2 = glyph->v2;

    if (integer) {
        x = (int)x;
        y = (int)y;
        x2 = (int)x2;
        y2 = (int)y2;
    }

    vertices[idx++] = x;
    vertices[idx++] = y;
    vertices[idx++] = color;
    vertices[idx++] = u;
    vertices[idx++] = v;

    vertices[idx++] = x;
    vertices[idx++] = y2;
    vertices[idx++] = color;
    vertices[idx++] = u;
    vertices[idx++] = v2;

    vertices[idx++] = x2;
    vertices[idx++] = y2;
    vertices[idx++] = color;
    vertices[idx++] = u2;
    vertices[idx++] = v2;

    vertices[idx++] = x2;
    vertices[idx++] = y;
    vertices[idx++] = color;
    vertices[idx++] = u2;
    vertices[idx++] = v;
}

BitmapFont::TextBounds& BitmapFontCache::setText (const std::string& str,float x,float y) {
    return setText(str, x, y, 0, str.length());
}

BitmapFont::TextBounds& BitmapFontCache::setText (const std::string& str,float x,float y,int start,int end) {
    reset(end - start);
    y += font->data->ascent;
    textBounds.width = addToCache(str, x, y, start, end);
    textBounds.height = font->data->capHeight;
    return textBounds;
}

BitmapFont::TextBounds& BitmapFontCache::setMultiLineText (const std::string& str,float x,float y) {
    return setMultiLineText(str, x, y, 0, BitmapFont::HAlignment::HALIGNMENT_LEFT);
}

BitmapFont::TextBounds& BitmapFontCache::setMultiLineText (const std::string& str,float x,float y,float alignmentWidth,const BitmapFont::HAlignment& alignment) {
    int length = str.length();
    reset(length);

    y += font->data->ascent;
    float down = font->data->down;

    float maxWidth = 0;
    int start = 0;
    int numLines = 0;
    while (start < length) {
        int lineEnd = BitmapFont::indexOf(str, '\n', start);
        float xOffset = 0;
        if (alignment != BitmapFont::HAlignment::HALIGNMENT_LEFT) {
            float lineWidth = font->getBounds(str, start, lineEnd).width;
            xOffset = alignmentWidth - lineWidth;
            if (alignment == BitmapFont::HAlignment::HALIGNMENT_CENTER) xOffset /= 2;
        }
        float lineWidth = addToCache(str, x + xOffset, y, start, lineEnd);
        maxWidth = std::max(maxWidth, lineWidth);
        start = lineEnd + 1;
        y += down;
        numLines++;
    }
    textBounds.width = maxWidth;
    textBounds.height = font->data->capHeight + (numLines - 1) * font->data->lineHeight;
    return textBounds;
}

BitmapFont::TextBounds& BitmapFontCache::setWrappedText (const std::string& str,float x,float y,float wrapWidth) {
    return setWrappedText(str, x, y, wrapWidth, BitmapFont::HAlignment::HALIGNMENT_LEFT);
}

BitmapFont::TextBounds& BitmapFontCache::setWrappedText (const std::string& str,float x,float y,float wrapWidth,const BitmapFont::HAlignment& alignment) {
    int length = str.length();
    reset(length);

    y += font->data->ascent;
    float down = font->data->down;

    float maxWidth = 0;
    int start = 0;
    int numLines = 0;
    while (start < length) {
        int lineEnd = start + font->computeVisibleGlyphs(str, start, BitmapFont::indexOf(str, '\n', start), wrapWidth);
        if (lineEnd < length) {
            while (lineEnd > start) {
                char ch = str[lineEnd];
                if (ch == ' ' || ch == '\n') break;
                lineEnd--;
            }
        }
        if (lineEnd == start) lineEnd++;
        float xOffset = 0;
        if (alignment != BitmapFont::HAlignment::HALIGNMENT_LEFT) {
            float lineWidth = font->getBounds(str, start, lineEnd).width;
            xOffset = wrapWidth - lineWidth;
            if (alignment == BitmapFont::HAlignment::HALIGNMENT_CENTER) xOffset /= 2;
        }
        float lineWidth = addToCache(str, x + xOffset, y, start, lineEnd);
        maxWidth = std::max(maxWidth, lineWidth);
        start = lineEnd + 1;
        y += down;
        numLines++;
    }
    textBounds.width = maxWidth;
    textBounds.height = font->data->capHeight + (numLines - 1) * font->data->lineHeight;
    return textBounds;
}

BitmapFont::TextBounds& BitmapFontCache::getBounds () {
    return textBounds;
}

float BitmapFontCache::getX () {
    return x;
}

float BitmapFontCache::getY () {
    return y;
}

BitmapFont* BitmapFontCache::getFont () {
    return font;
}

void BitmapFontCache::dispose () {
    font->dispose();
}

void BitmapFontCache::setUseIntegerPositions (bool use) {
    this->integer = use;
}

bool BitmapFontCache::usesIntegerPositions () {
    return integer;
}

BitmapFontCache::BitmapFontCache (BitmapFont* font, bool integer)
: font(font),
idx(0),
color(Color::WHITE.toFloatBits()),
tmpColor(Color::WHITE),
integer(integer),
x(0),
y(0)
{
}

