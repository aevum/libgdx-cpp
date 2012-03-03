
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

#include "SpriteBatch.hpp"

#include <string.h>
#include <stdexcept>

#include "gdx-cpp/graphics/Mesh.hpp"
#include "gdx-cpp/graphics/VertexAttribute.hpp"
#include "gdx-cpp/graphics/GL20.hpp"
#include "gdx-cpp/Gdx.hpp"
#include "Sprite.hpp"
#include "gdx-cpp/utils/NumberUtils.hpp"
#include "gdx-cpp/math/MathUtils.hpp"
#include "gdx-cpp/graphics/g2d/TextureRegion.hpp"
#include "gdx-cpp/graphics/Mesh.hpp"
#include "gdx-cpp/graphics/glutils/ShaderProgram.hpp"

using namespace gdx_cpp::graphics::glutils;
using namespace gdx_cpp::graphics::g2d;
using namespace gdx_cpp::graphics;
using namespace gdx_cpp;

gdx_cpp::graphics::g2d::SpriteBatch::SpriteBatch(int size) :
        color(Color::WHITE.toFloatBits())
        , maxSpritesInBatch(0)
        , renderCalls(0)
        , tempColor(1,1,1,1)
        , blendSrcFunc(GL10::GL_SRC_ALPHA)
        , blendDstFunc(GL10::GL_ONE_MINUS_SRC_ALPHA)
        , blendingDisabled(false)
        , drawing(false)
        , currBufferIdx(0)
        , idx(0)
        , invTexWidth(0)
        , invTexHeight(0)
        , mesh(0)
        , shader(0)
        , customShader(0)
{

    std::vector<VertexAttribute> attributes;
    attributes.push_back(VertexAttribute(VertexAttributes::Usage::Position, 2,  ShaderProgram::POSITION_ATTRIBUTE));
    attributes.push_back(VertexAttribute(VertexAttributes::Usage::ColorPacked, 4,  ShaderProgram::COLOR_ATTRIBUTE));
    attributes.push_back(VertexAttribute(VertexAttributes::Usage::TextureCoordinates, 2,  ShaderProgram::TEXCOORD_ATTRIBUTE + "0"));

    this->buffers.push_back(new Mesh(Mesh::VertexDataType::VertexArray,
                                     false,
                                     size * 4,
                                     size * 6,
                                     attributes));

    projectionMatrix.setToOrtho2D(0, 0, Gdx::graphics->getWidth(), Gdx::graphics->getHeight());

    vertices = new float[size * Sprite::SPRITE_SIZE];
    verticesSize  = size * Sprite::SPRITE_SIZE;

    int len = size * 6;
    std::vector<short> indices(len);

    short j = 0;
    for (int i = 0; i < len; i += 6, j += 4) {
        indices[i + 0] = (j + 0);
        indices[i + 1] = (j + 1);
        indices[i + 2] = (j + 2);
        indices[i + 3] = (j + 2);
        indices[i + 4] = (j + 3);
        indices[i + 5] = (j + 0);
    }
    buffers[0]->setIndices(indices);
    mesh = buffers[0];

    if (Gdx::graphics->isGL20Available()) createShader();
}


void SpriteBatch::createShader () {
    std::string vertexShader = "attribute vec4 " + ShaderProgram::POSITION_ATTRIBUTE + ";\n"
                               "attribute vec4 " + ShaderProgram::COLOR_ATTRIBUTE + ";\n" //
                               "attribute vec2 " + ShaderProgram::TEXCOORD_ATTRIBUTE + "0;\n" //
                               "uniform mat4 u_projectionViewMatrix;\n" //
                               "varying vec4 v_color;\n" //
                               "varying vec2 v_texCoords;\n" //
                               "\n" //
                               "void main()\n" //
                               "{\n" //
                               "   v_color = " + ShaderProgram::COLOR_ATTRIBUTE + ";\n" //
                               "   v_texCoords = " + ShaderProgram::TEXCOORD_ATTRIBUTE + "0;\n" //
                               "   gl_Position =  u_projectionViewMatrix * " + ShaderProgram::POSITION_ATTRIBUTE + ";\n" //
                               "}\n";
    std::string fragmentShader = "#ifdef GL_ES\n" //
                                 "precision mediump float;\n" //
                                 "#endif\n" //
                                 "varying vec4 v_color;\n" //
                                 "varying vec2 v_texCoords;\n" //
                                 "uniform sampler2D u_texture;\n" //
                                 "void main()\n"//
                                 "{\n" //
                                 "  gl_FragColor = v_color * texture2D(u_texture, v_texCoords);\n" //
                                 "}";

    shader = new ShaderProgram(vertexShader, fragmentShader);
    if (shader->isCompiled() == false)
        throw std::runtime_error("couldn't compile shader: " + shader->getLog());
}

void SpriteBatch::begin () {
    if (drawing)
        throw new std::runtime_error("you have to call SpriteBatch.end() first");

    renderCalls = 0;
    Gdx::gl->glDepthMask(false);
    Gdx::gl->glEnable(GL10::GL_TEXTURE_2D);

    if (Gdx::graphics->isGL20Available()) {
        if (customShader != NULL)
            customShader->begin();
        else shader->begin();
    }
    
    setupMatrices();

    idx = 0;
    lastTexture = NULL;
    drawing = true;
}

void SpriteBatch::end () {
    if (!drawing)
        throw std::runtime_error("SpriteBatch.begin must be called before end.");
    if (idx > 0) renderMesh();
    lastTexture = NULL;
    idx = 0;
    drawing = false;

    GLCommon& gl = *Gdx::gl;
    gl.glDepthMask(true);
    if (isBlendingEnabled()) gl.glDisable(GL10::GL_BLEND);
    gl.glDisable(GL10::GL_TEXTURE_2D);

    if (Gdx::graphics->isGL20Available()) {
        if (customShader != NULL)
            customShader->end();
        else
            shader->end();
    }
}

void SpriteBatch::setColor (const gdx_cpp::graphics::Color& tint) {
    color = tint.toFloatBits();
}

void SpriteBatch::setColor (float r,float g,float b,float a) {
    int intBits = (int)(255 * a) << 24 | (int)(255 * b) << 16 | (int)(255 * g) << 8 | (int)(255 * r);
    color =  utils::NumberUtils::intBitsToFloat(intBits & 0xfeffffff);
}

void SpriteBatch::setColor (float color) {
    this->color = color;
}

gdx_cpp::graphics::Color& SpriteBatch::getColor () {
    int intBits = utils::NumberUtils::floatToRawIntBits(color);
    this->tempColor.r = (intBits & 0xff) / 255.0f;
    this->tempColor.g = (((unsigned int)intBits >> 8) & 0xff) / 255.0f;
    this->tempColor.b = (((unsigned int)intBits >> 16) & 0xff) / 255.0f;
    this->tempColor.a = (((unsigned int)intBits >> 24) & 0xff) / 255.0f;
    return this->tempColor;
}

void SpriteBatch::draw (const gdx_cpp::graphics::Texture& texture,float x,float y,float originX,float originY,float width,float height,float scaleX,float scaleY,float rotation,int srcX,int srcY,int srcWidth,int srcHeight,bool flipX,bool flipY) {
    if (!drawing)
        throw new std::runtime_error("SpriteBatch.begin must be called before draw.");

    if (&texture != lastTexture) {
        renderMesh();
        lastTexture = const_cast<Texture*>(&texture);
        invTexWidth = 1.0f / texture.getWidth();
        invTexHeight = 1.0f / texture.getHeight();
    } else if (idx == 20000) {
        renderMesh();
    }

    // bottom left and top right corner points relative to origin
    float worldOriginX = x + originX;
    float worldOriginY = y + originY;
    float fx = -originX;
    float fy = -originY;
    float fx2 = width - originX;
    float fy2 = height - originY;

    // scale
    if (scaleX != 1 || scaleY != 1) {
        fx *= scaleX;
        fy *= scaleY;
        fx2 *= scaleX;
        fy2 *= scaleY;
    }

    // construct corner points, start from top left and go counter clockwise
    float p1x = fx;
    float p1y = fy;
    float p2x = fx;
    float p2y = fy2;
    float p3x = fx2;
    float p3y = fy2;
    float p4x = fx2;
    float p4y = fy;

    float x1;
    float y1;
    float x2;
    float y2;
    float x3;
    float y3;
    float x4;
    float y4;

    // rotate
    if (rotation != 0) {
        float cos = math::utils::cosDeg(rotation);
        float sin = math::utils::sinDeg(rotation);

        x1 = cos * p1x - sin * p1y;
        y1 = sin * p1x + cos * p1y;

        x2 = cos * p2x - sin * p2y;
        y2 = sin * p2x + cos * p2y;

        x3 = cos * p3x - sin * p3y;
        y3 = sin * p3x + cos * p3y;

        x4 = x1 + (x3 - x2);
        y4 = y3 - (y2 - y1);
    } else {
        x1 = p1x;
        y1 = p1y;

        x2 = p2x;
        y2 = p2y;

        x3 = p3x;
        y3 = p3y;

        x4 = p4x;
        y4 = p4y;
    }

    x1 += worldOriginX;
    y1 += worldOriginY;
    x2 += worldOriginX;
    y2 += worldOriginY;
    x3 += worldOriginX;
    y3 += worldOriginY;
    x4 += worldOriginX;
    y4 += worldOriginY;

    float u = srcX * invTexWidth;
    float v = (srcY + srcHeight) * invTexHeight;
    float u2 = (srcX + srcWidth) * invTexWidth;
    float v2 = srcY * invTexHeight;

    if (flipX) {
        float tmp = u;
        u = u2;
        u2 = tmp;
    }

    if (flipY) {
        float tmp = v;
        v = v2;
        v2 = tmp;
    }

    vertices[idx++] = x1;
    vertices[idx++] = y1;
    vertices[idx++] = color;
    vertices[idx++] = u;
    vertices[idx++] = v;

    vertices[idx++] = x2;
    vertices[idx++] = y2;
    vertices[idx++] = color;
    vertices[idx++] = u;
    vertices[idx++] = v2;

    vertices[idx++] = x3;
    vertices[idx++] = y3;
    vertices[idx++] = color;
    vertices[idx++] = u2;
    vertices[idx++] = v2;

    vertices[idx++] = x4;
    vertices[idx++] = y4;
    vertices[idx++] = color;
    vertices[idx++] = u2;
    vertices[idx++] = v;
}

void SpriteBatch::draw (const gdx_cpp::graphics::Texture& texture,float x,float y,float width,float height,int srcX,int srcY,int srcWidth,int srcHeight,bool flipX,bool flipY) {
    if (!drawing)
        throw std::runtime_error("SpriteBatch.begin must be called before draw.");

    if (&texture != lastTexture) {
        renderMesh();
        lastTexture = const_cast<Texture*>(&texture);
        invTexWidth = 1.0f / texture.getWidth();
        invTexHeight = 1.0f / texture.getHeight();
    } else if (idx == verticesSize) renderMesh();

    float u = srcX * invTexWidth;
    float v = (srcY + srcHeight) * invTexHeight;
    float u2 = (srcX + srcWidth) * invTexWidth;
    float v2 = srcY * invTexHeight;
    float fx2 = x + width;
    float fy2 = y + height;

    if (flipX) {
        float tmp = u;
        u = u2;
        u2 = tmp;
    }

    if (flipY) {
        float tmp = v;
        v = v2;
        v2 = tmp;
    }

    vertices[idx++] = x;
    vertices[idx++] = y;
    vertices[idx++] = color;
    vertices[idx++] = u;
    vertices[idx++] = v;

    vertices[idx++] = x;
    vertices[idx++] = fy2;
    vertices[idx++] = color;
    vertices[idx++] = u;
    vertices[idx++] = v2;

    vertices[idx++] = fx2;
    vertices[idx++] = fy2;
    vertices[idx++] = color;
    vertices[idx++] = u2;
    vertices[idx++] = v2;

    vertices[idx++] = fx2;
    vertices[idx++] = y;
    vertices[idx++] = color;
    vertices[idx++] = u2;
    vertices[idx++] = v;
}

void SpriteBatch::draw (const gdx_cpp::graphics::Texture& texture,float x,float y,int srcX,int srcY,int srcWidth,int srcHeight) {
    if (!drawing)
        throw std::runtime_error("SpriteBatch.begin must be called before draw.");

    if (&texture != lastTexture) {
        renderMesh();
        lastTexture = const_cast<Texture*>(&texture);
        invTexWidth = 1.0f / texture.getWidth();
        invTexHeight = 1.0f / texture.getHeight();
    } else if (idx == verticesSize) renderMesh();

    float u = srcX * invTexWidth;
    float v = (srcY + srcHeight) * invTexHeight;
    float u2 = (srcX + srcWidth) * invTexWidth;
    float v2 = srcY * invTexHeight;
    float fx2 = x + srcWidth;
    float fy2 = y + srcHeight;

    vertices[idx++] = x;
    vertices[idx++] = y;
    vertices[idx++] = color;
    vertices[idx++] = u;
    vertices[idx++] = v;

    vertices[idx++] = x;
    vertices[idx++] = fy2;
    vertices[idx++] = color;
    vertices[idx++] = u;
    vertices[idx++] = v2;

    vertices[idx++] = fx2;
    vertices[idx++] = fy2;
    vertices[idx++] = color;
    vertices[idx++] = u2;
    vertices[idx++] = v2;

    vertices[idx++] = fx2;
    vertices[idx++] = y;
    vertices[idx++] = color;
    vertices[idx++] = u2;
    vertices[idx++] = v;
}

void SpriteBatch::draw (const gdx_cpp::graphics::Texture& texture,float x,float y,float width,float height,float u,float v,float u2,float v2) {
    if (!drawing)
        throw std::runtime_error("SpriteBatch.begin must be called before draw.");

    if (&texture != lastTexture) {
        renderMesh();
        lastTexture = const_cast<Texture*>(&texture);
        invTexWidth = 1.0f / texture.getWidth();
        invTexHeight = 1.0f / texture.getHeight();
    } else if (idx == verticesSize) renderMesh();

    float fx2 = x + width;
    float fy2 = y + height;

    vertices[idx++] = x;
    vertices[idx++] = y;
    vertices[idx++] = color;
    vertices[idx++] = u;
    vertices[idx++] = v;

    vertices[idx++] = x;
    vertices[idx++] = fy2;
    vertices[idx++] = color;
    vertices[idx++] = u;
    vertices[idx++] = v2;

    vertices[idx++] = fx2;
    vertices[idx++] = fy2;
    vertices[idx++] = color;
    vertices[idx++] = u2;
    vertices[idx++] = v2;

    vertices[idx++] = fx2;
    vertices[idx++] = y;
    vertices[idx++] = color;
    vertices[idx++] = u2;
    vertices[idx++] = v;
}

void SpriteBatch::draw (const gdx_cpp::graphics::Texture& texture,float x,float y) {
    if (!drawing)
        throw std::runtime_error("SpriteBatch.begin must be called before draw.");

    if (&texture != lastTexture) {
        renderMesh();
        lastTexture = const_cast<Texture*>(&texture);
        invTexWidth = 1.0f / texture.getWidth();
        invTexHeight = 1.0f / texture.getHeight();
    } else if (idx == verticesSize) renderMesh();

    float fx2 = x + texture.getWidth();
    float fy2 = y + texture.getHeight();

    vertices[idx++] = x;
    vertices[idx++] = y;
    vertices[idx++] = color;
    vertices[idx++] = 0;
    vertices[idx++] = 1;

    vertices[idx++] = x;
    vertices[idx++] = fy2;
    vertices[idx++] = color;
    vertices[idx++] = 0;
    vertices[idx++] = 0;

    vertices[idx++] = fx2;
    vertices[idx++] = fy2;
    vertices[idx++] = color;
    vertices[idx++] = 1;
    vertices[idx++] = 0;

    vertices[idx++] = fx2;
    vertices[idx++] = y;
    vertices[idx++] = color;
    vertices[idx++] = 1;
    vertices[idx++] = 1;
}

void SpriteBatch::draw (const gdx_cpp::graphics::Texture& texture,float x,float y,float width,float height) {
    if (!drawing)
        throw std::runtime_error("SpriteBatch.begin must be called before draw.");

    if (&texture != lastTexture) {
        renderMesh();
        lastTexture = const_cast<Texture*>(&texture);
        invTexWidth = 1.0f / texture.getWidth();
        invTexHeight = 1.0f / texture.getHeight();
    } else if (idx == verticesSize) //
        renderMesh();

    float fx2 = x + width;
    float fy2 = y + height;
    float u = 0;
    float v = 1;
    float u2 = 1;
    float v2 = 0;

    vertices[idx++] = x;
    vertices[idx++] = y;
    vertices[idx++] = color;
    vertices[idx++] = u;
    vertices[idx++] = v;

    vertices[idx++] = x;
    vertices[idx++] = fy2;
    vertices[idx++] = color;
    vertices[idx++] = u;
    vertices[idx++] = v2;

    vertices[idx++] = fx2;
    vertices[idx++] = fy2;
    vertices[idx++] = color;
    vertices[idx++] = u2;
    vertices[idx++] = v2;

    vertices[idx++] = fx2;
    vertices[idx++] = y;
    vertices[idx++] = color;
    vertices[idx++] = u2;
    vertices[idx++] = v;
}

void SpriteBatch::draw (const gdx_cpp::graphics::Texture& texture,const std::vector<float>& spriteVertices, int offset,int length) {
    if (!drawing)
        throw std::runtime_error("SpriteBatch.begin must be called before draw.");

    if (&texture != lastTexture) {
        renderMesh();
        lastTexture = const_cast<Texture*>(&texture);
        invTexWidth = 1.0f / texture.getWidth();
        invTexHeight = 1.0f / texture.getHeight();
    } else if (idx + length >= verticesSize) renderMesh();


    memcpy(&vertices[idx], &spriteVertices[offset], sizeof(float) * length);
    idx += length;
}

void SpriteBatch::draw (const TextureRegion& region,float x,float y) {
    draw(region, x, y, std::abs(region.getRegionWidth()), std::abs(region.getRegionHeight()));
}

void SpriteBatch::draw (const TextureRegion& region,float x,float y,float width,float height) {
    if (!drawing)
        throw std::runtime_error("SpriteBatch.begin must be called before draw.");

    Texture::ptr texture = region.getTexture();
    if (texture.get() != lastTexture) {
        renderMesh();
        lastTexture = texture.get();
        invTexWidth = 1.0f / texture->getWidth();
        invTexHeight = 1.0f / texture->getHeight();
    } else if (idx == verticesSize) //
        renderMesh();

    float fx2 = x + width;
    float fy2 = y + height;
    float u = region.u;
    float v = region.v2;
    float u2 = region.u2;
    float v2 = region.v;

    utils::float_buffer& buffer = mesh->getVerticesBuffer();
    buffer.limit(buffer.position() + 20);

    vertices[idx++] = x;
    vertices[idx++] = y;
    vertices[idx++] = color;
    vertices[idx++] = u;
    vertices[idx++] = v;

    vertices[idx++] = x;
    vertices[idx++] = fy2;
    vertices[idx++] = color;
    vertices[idx++] = u;
    vertices[idx++] = v2;

    vertices[idx++] = fx2;
    vertices[idx++] = fy2;
    vertices[idx++] = color;
    vertices[idx++] = u2;
    vertices[idx++] = v2;

    vertices[idx++] = fx2;
    vertices[idx++] = y;
    vertices[idx++] = color;
    vertices[idx++] = u2;
    vertices[idx++] = v;
}

void SpriteBatch::draw (const TextureRegion& region,float x,float y,float originX,float originY,float width,float height,float scaleX,float scaleY,float rotation) {
    if (!drawing)
        throw std::runtime_error("SpriteBatch.begin must be called before draw.");

    Texture::ptr texture = region.getTexture();
    if (texture.get() != lastTexture) {
        renderMesh();
        lastTexture = texture.get();
        invTexWidth = 1.0f / texture->getWidth();
        invTexHeight = 1.0f / texture->getHeight();
    } else if (idx == verticesSize) //
        renderMesh();

    // bottom left and top right corner points relative to origin
    float worldOriginX = x + originX;
    float worldOriginY = y + originY;
    float fx = -originX;
    float fy = -originY;
    float fx2 = width - originX;
    float fy2 = height - originY;

    // scale
    if (scaleX != 1 || scaleY != 1) {
        fx *= scaleX;
        fy *= scaleY;
        fx2 *= scaleX;
        fy2 *= scaleY;
    }

    // construct corner points, start from top left and go counter clockwise
    float p1x = fx;
    float p1y = fy;
    float p2x = fx;
    float p2y = fy2;
    float p3x = fx2;
    float p3y = fy2;
    float p4x = fx2;
    float p4y = fy;

    float x1;
    float y1;
    float x2;
    float y2;
    float x3;
    float y3;
    float x4;
    float y4;

    // rotate
    if (rotation != 0) {
        float cos = math::utils::cosDeg(rotation);
        float sin = math::utils::sinDeg(rotation);

        x1 = cos * p1x - sin * p1y;
        y1 = sin * p1x + cos * p1y;

        x2 = cos * p2x - sin * p2y;
        y2 = sin * p2x + cos * p2y;

        x3 = cos * p3x - sin * p3y;
        y3 = sin * p3x + cos * p3y;

        x4 = x1 + (x3 - x2);
        y4 = y3 - (y2 - y1);
    } else {
        x1 = p1x;
        y1 = p1y;

        x2 = p2x;
        y2 = p2y;

        x3 = p3x;
        y3 = p3y;

        x4 = p4x;
        y4 = p4y;
    }

    x1 += worldOriginX;
    y1 += worldOriginY;
    x2 += worldOriginX;
    y2 += worldOriginY;
    x3 += worldOriginX;
    y3 += worldOriginY;
    x4 += worldOriginX;
    y4 += worldOriginY;

    float u = region.u;
    float v = region.v2;
    float u2 = region.u2;
    float v2 = region.v;

    vertices[idx++] = x1;
    vertices[idx++] = y1;
    vertices[idx++] = color;
    vertices[idx++] = u;
    vertices[idx++] = v;

    vertices[idx++] = x2;
    vertices[idx++] = y2;
    vertices[idx++] = color;
    vertices[idx++] = u;
    vertices[idx++] = v2;

    vertices[idx++] = x3;
    vertices[idx++] = y3;
    vertices[idx++] = color;
    vertices[idx++] = u2;
    vertices[idx++] = v2;

    vertices[idx++] = x4;
    vertices[idx++] = y4;
    vertices[idx++] = color;
    vertices[idx++] = u2;
    vertices[idx++] = v;
}

void SpriteBatch::draw (const TextureRegion& region,float x,float y,float originX,float originY,float width,float height,float scaleX,float scaleY,float rotation,bool clockwise) {
    if (!drawing)
        throw std::runtime_error("SpriteBatch.begin must be called before draw.");

    Texture::ptr texture = region.getTexture();
    if (texture.get() != lastTexture) {
        renderMesh();
        lastTexture = texture.get();
        invTexWidth = 1.0f / texture->getWidth();
        invTexHeight = 1.0f / texture->getHeight();
    } else if (idx == verticesSize) {
        renderMesh();
    }

    // bottom left and top right corner points relative to origin
    float worldOriginX = x + originX;
    float worldOriginY = y + originY;
    float fx = -originX;
    float fy = -originY;
    float fx2 = width - originX;
    float fy2 = height - originY;

    // scale
    if (scaleX != 1 || scaleY != 1) {
        fx *= scaleX;
        fy *= scaleY;
        fx2 *= scaleX;
        fy2 *= scaleY;
    }

    // construct corner points, start from top left and go counter clockwise
    float p1x = fx;
    float p1y = fy;
    float p2x = fx;
    float p2y = fy2;
    float p3x = fx2;
    float p3y = fy2;
    float p4x = fx2;
    float p4y = fy;

    float x1;
    float y1;
    float x2;
    float y2;
    float x3;
    float y3;
    float x4;
    float y4;

    // rotate
    if (rotation != 0) {
        float cos = math::utils::cosDeg(rotation);
        float sin = math::utils::sinDeg(rotation);

        x1 = cos * p1x - sin * p1y;
        y1 = sin * p1x + cos * p1y;

        x2 = cos * p2x - sin * p2y;
        y2 = sin * p2x + cos * p2y;

        x3 = cos * p3x - sin * p3y;
        y3 = sin * p3x + cos * p3y;

        x4 = x1 + (x3 - x2);
        y4 = y3 - (y2 - y1);
    } else {
        x1 = p1x;
        y1 = p1y;

        x2 = p2x;
        y2 = p2y;

        x3 = p3x;
        y3 = p3y;

        x4 = p4x;
        y4 = p4y;
    }

    x1 += worldOriginX;
    y1 += worldOriginY;
    x2 += worldOriginX;
    y2 += worldOriginY;
    x3 += worldOriginX;
    y3 += worldOriginY;
    x4 += worldOriginX;
    y4 += worldOriginY;

    float u1, v1, u2, v2, u3, v3, u4, v4;
    if (clockwise) {
        u1 = region.u2;
        v1 = region.v2;
        u2 = region.u;
        v2 = region.v2;
        u3 = region.u;
        v3 = region.v;
        u4 = region.u2;
        v4 = region.v;
    } else {
        u1 = region.u;
        v1 = region.v;
        u2 = region.u2;
        v2 = region.v;
        u3 = region.u2;
        v3 = region.v2;
        u4 = region.u;
        v4 = region.v2;
    }

    vertices[idx++] = x1;
    vertices[idx++] = y1;
    vertices[idx++] = color;
    vertices[idx++] = u1;
    vertices[idx++] = v1;

    vertices[idx++] = x2;
    vertices[idx++] = y2;
    vertices[idx++] = color;
    vertices[idx++] = u2;
    vertices[idx++] = v2;

    vertices[idx++] = x3;
    vertices[idx++] = y3;
    vertices[idx++] = color;
    vertices[idx++] = u3;
    vertices[idx++] = v3;

    vertices[idx++] = x4;
    vertices[idx++] = y4;
    vertices[idx++] = color;
    vertices[idx++] = u4;
    vertices[idx++] = v4;
}

void SpriteBatch::flush () {
    renderMesh();
}

void SpriteBatch::renderMesh () {
    if (idx == 0) return;

    renderCalls++;
    int spritesInBatch = idx / 20;
    if (spritesInBatch > maxSpritesInBatch) maxSpritesInBatch = spritesInBatch;

    lastTexture->bind();

    mesh->setVertices(vertices, idx);

    if (Gdx::graphics->isGL20Available()) {
        if (blendingDisabled) {
            Gdx::gl20->glDisable(GL20::GL_BLEND);
        } else {
            GL20& gl20 = *Gdx::gl20;
            gl20.glEnable(GL20::GL_BLEND);
            gl20.glBlendFunc(blendSrcFunc, blendDstFunc);
        }

        if (customShader != NULL)
            mesh->render(*customShader, GL10::GL_TRIANGLES, 0, spritesInBatch * 6);
        else
            mesh->render(*shader, GL10::GL_TRIANGLES, 0, spritesInBatch * 6);
    } else {
        if (blendingDisabled) {
            Gdx::gl10->glDisable(GL10::GL_BLEND);
        } else {
            GL10& gl10 = *Gdx::gl10;
            gl10.glEnable(GL10::GL_BLEND);
            gl10.glBlendFunc(blendSrcFunc, blendDstFunc);
        }
        mesh->render(GL10::GL_TRIANGLES, 0, spritesInBatch * 6);
    }

    idx = 0;
    currBufferIdx++;
    if (currBufferIdx == buffers.size()) currBufferIdx = 0;
    mesh = buffers[currBufferIdx];
}

void SpriteBatch::disableBlending () {
    renderMesh();
    blendingDisabled = true;
}

void SpriteBatch::enableBlending () {
    renderMesh();
    blendingDisabled = false;
}

void SpriteBatch::setBlendFunction (int srcFunc,int dstFunc) {
    renderMesh();
    blendSrcFunc = srcFunc;
    blendDstFunc = dstFunc;
}

void SpriteBatch::dispose () {
    for (int i = 0; i < buffers.size(); i++) {
        buffers[i]->dispose();
    }
    if (shader != NULL)
        shader->dispose();
}

math::Matrix4& SpriteBatch::getProjectionMatrix () {
    return projectionMatrix;
}

const gdx_cpp::math::Matrix4& SpriteBatch::getTransformMatrix () {
    return transformMatrix;
}

void SpriteBatch::setProjectionMatrix (const gdx_cpp::math::Matrix4& projection) {
    if (drawing)
        throw std::runtime_error("Can't set the matrix within begin()/end() block");

    projectionMatrix.set(projection);
}

void SpriteBatch::setTransformMatrix (const gdx_cpp::math::Matrix4& transform) {
    if (drawing)
        throw std::runtime_error("Can't set the matrix within begin()/end() block");

    transformMatrix.set(transform);
}

void SpriteBatch::setShader (gdx_cpp::graphics::glutils::ShaderProgram* shader) {
    customShader = shader;
}

bool SpriteBatch::isBlendingEnabled () {
    return !blendingDisabled;
}

SpriteBatch::SpriteBatch(int size, int buffers) :
        color(Color::WHITE.toFloatBits())
        , maxSpritesInBatch(0)
        , renderCalls(0)
        , tempColor(1,1,1,1)
        , blendSrcFunc(GL10::GL_SRC_ALPHA)
        , blendDstFunc(GL10::GL_ONE_MINUS_SRC_ALPHA)
        , blendingDisabled(false)
        , drawing(false)
        , currBufferIdx(0)
        , idx(0)
        , invTexWidth(0)
        , invTexHeight(0)
        , mesh(0)
        , shader(0)
        , customShader(0)
{
    this->buffers.reserve(buffers);

    std::vector<VertexAttribute> attributes;
    attributes.push_back(VertexAttribute(VertexAttributes::Usage::Position, 2, ShaderProgram::POSITION_ATTRIBUTE));
    attributes.push_back(VertexAttribute(VertexAttributes::Usage::ColorPacked, 4, ShaderProgram::COLOR_ATTRIBUTE));
    attributes.push_back(VertexAttribute(VertexAttributes::Usage::TextureCoordinates, 2, ShaderProgram::TEXCOORD_ATTRIBUTE + "0"));

    for (int i = 0; i < buffers; i++) {
        this->buffers[i] = new Mesh(false, size * 4, size * 6, attributes);
    }

    projectionMatrix.setToOrtho2D(0, 0, Gdx::graphics->getWidth(), Gdx::graphics->getHeight());

    vertices = new float[size * Sprite::SPRITE_SIZE];
    verticesSize  = size * Sprite::SPRITE_SIZE;

    int len = size * 6;
    std::vector<short> indices(len);
    short j = 0;

    for (int i = 0; i < len; i += 6, j += 4) {
        indices[i + 0] = (short)(j + 0);
        indices[i + 1] = (short)(j + 1);
        indices[i + 2] = (short)(j + 2);
        indices[i + 3] = (short)(j + 2);
        indices[i + 4] = (short)(j + 3);
        indices[i + 5] = (short)(j + 0);
    }

    for (int i = 0; i < buffers; i++) {
        this->buffers[i]->setIndices(indices);
    }
    mesh = this->buffers[0];

    if (Gdx::graphics->isGL20Available()) createShader();
}


SpriteBatch::~SpriteBatch()
{
    if (shader) {
        shader->dispose();
        delete shader;
    }

    if (customShader) {
        customShader->dispose();
        delete customShader;
    }

    for (unsigned int i = 0; i < buffers.size(); ++i) {
        buffers[i]->dispose();
        delete buffers[i];
    }

    delete [] vertices;
}

void SpriteBatch::draw(const Texture& texture, float* const spriteVertices, int size, int offset, int length) {
    if (!drawing)
        throw std::runtime_error("SpriteBatch.begin must be called before draw.");

    if (&texture != lastTexture) {
        renderMesh();
        lastTexture = const_cast<Texture*>(&texture);
        invTexWidth = 1.0f / texture.getWidth();
        invTexHeight = 1.0f / texture.getHeight();
    } else if (idx + length >= verticesSize ) renderMesh();

    int remainingVertices = verticesSize - idx;

    if (remainingVertices == 0) {
        renderMesh();
        remainingVertices = verticesSize;
    }

    int vertexCount = std::min(remainingVertices, length - offset);

    memcpy(&vertices[idx], &spriteVertices[offset], sizeof(float) * vertexCount);

    offset += vertexCount;
    idx += vertexCount;

    while (offset < length) {
        renderMesh();
        vertexCount =  std::min(verticesSize, length - offset);
        memcpy(&vertices[0], &spriteVertices[offset], sizeof(float) * vertexCount);
        offset += vertexCount;
        idx += vertexCount;
    }
}

void SpriteBatch::setupMatrices()
{
    if (!Gdx::graphics->isGL20Available()) {
        GL10& gl = *Gdx::gl10;
        gl.glMatrixMode(GL10::GL_PROJECTION);
        gl.glLoadMatrixf(projectionMatrix.val);
        gl.glMatrixMode(GL10::GL_MODELVIEW);
        gl.glLoadMatrixf(transformMatrix.val);
    } else {
        combinedMatrix.set(projectionMatrix).mul(transformMatrix);
        if (customShader != NULL) {
            customShader->setUniformMatrix("u_proj", projectionMatrix);
            customShader->setUniformMatrix("u_trans", transformMatrix);
            customShader->setUniformMatrix("u_projTrans", combinedMatrix);
            customShader->setUniformi("u_texture", 0);
        } else {
            shader->setUniformMatrix("u_projectionViewMatrix", combinedMatrix);
            shader->setUniformi("u_texture", 0);
        }
    }
}

void SpriteBatch::setTransformMatrix(math::Matrix4& transform)
{
    if (drawing) {
        flush();
    }
    
    transformMatrix.set(transform);

    if (drawing) {
        setupMatrices();
    }
}

void SpriteBatch::setProjectionMatrix(math::Matrix4& projection)
{
    if (drawing) {
        flush();
    }

    projectionMatrix.set(projection);

    if (drawing) {
        setupMatrices();
    }
}





