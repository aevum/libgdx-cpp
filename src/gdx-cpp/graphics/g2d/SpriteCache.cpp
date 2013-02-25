
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

#include "gdx-cpp/gl.hpp"
#include <string.h>
#include <array>
#include <memory>
#include <sstream>
#include <string>

#include "SpriteCache.hpp"
#include "gdx-cpp/Gdx.hpp"
#include "gdx-cpp/Graphics.hpp"
#include "gdx-cpp/Log.hpp"
#include "gdx-cpp/graphics/Color.hpp"
#include "gdx-cpp/graphics/GL10.hpp"
#include "gdx-cpp/graphics/GL20.hpp"
#include "gdx-cpp/graphics/Mesh.hpp"
#include "gdx-cpp/graphics/VertexAttribute.hpp"
#include "gdx-cpp/graphics/VertexAttributes.hpp"
#include "gdx-cpp/graphics/g2d/Sprite.hpp"
#include "gdx-cpp/graphics/glutils/ShaderProgram.hpp"
#include "gdx-cpp/math/MathUtils.hpp"
#include "gdx-cpp/utils/Buffer.hpp"
#include "gdx-cpp/utils/NumberUtils.hpp"

using namespace gdx;

float SpriteCache::tempVertices[Sprite::VERTEX_SIZE * 6];

ShaderProgram* SpriteCache::createDefaultShader () {
    if ( !graphics->isGL20Available() ) return NULL;
    std::string vertexShader = "attribute vec4 " + ShaderProgram::POSITION_ATTRIBUTE + ";\n" //
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

    ShaderProgram* shader = new ShaderProgram ( vertexShader, fragmentShader );
    if ( shader->isCompiled() == false )
        gdx_log_error("gdx", "Error compiling shader: %s", shader->getLog().c_str() );
    return shader;
}

SpriteCache::SpriteCache ( int size, bool useIndices, ShaderProgram* shader ) :
    mesh ( 0 ),
drawing ( false ),
shader ( shader ),
currentCache ( 0 ),
color ( Color::WHITE.toFloatBits() ),
tempColor ( 1,1,1,1 ),
customShader ( 0 ) {
    textures.reserve ( 8 );
    counts.reserve ( 8 );

    std::vector<VertexAttribute> attribute;
    attribute.push_back ( VertexAttribute ( VertexAttributes::Usage::Position, 2, ShaderProgram::POSITION_ATTRIBUTE ) );
    attribute.push_back ( VertexAttribute ( VertexAttributes::Usage::ColorPacked, 4, ShaderProgram::COLOR_ATTRIBUTE ) );
    attribute.push_back ( VertexAttribute ( VertexAttributes::Usage::TextureCoordinates, 2, ShaderProgram::TEXCOORD_ATTRIBUTE + "0" ) );

    mesh = new Mesh ( true, size * ( useIndices ? 4 : 6 ), useIndices ? size * 6 : 0, attribute );

    mesh->setAutoBind ( false );

    if ( useIndices ) {
        int length = size * 6;
        std::vector<short> indices ( length );
        short j = 0;
        for ( int i = 0; i < length; i += 6, j += 4 ) {
            indices[i + 0] = ( short ) j;
            indices[i + 1] = ( short ) ( j + 1 );
            indices[i + 2] = ( short ) ( j + 2 );
            indices[i + 3] = ( short ) ( j + 2 );
            indices[i + 4] = ( short ) ( j + 3 );
            indices[i + 5] = ( short ) j;
        }
        mesh->setIndices ( indices );
    }

    projectionMatrix.setToOrtho2D ( 0, 0, graphics->getWidth(), graphics->getHeight() );
}


void SpriteCache::setColor ( const Color& tint ) {
    color = tint.toFloatBits();
}

void SpriteCache::setColor ( float r, float g, float b, float a ) {
    int intBits = ( int ) ( 255 * a ) << 24 | ( int ) ( 255 * b ) << 16 | ( int ) ( 255 * g ) << 8 | ( int ) ( 255 * r );
    color = NumberUtils::intBitsToFloat ( intBits & 0xfeffffff );
}

void SpriteCache::setColor ( float color ) {
    this->color = color;
}

Color& SpriteCache::getColor () {
    int intBits = NumberUtils::floatToRawIntBits ( color );
    tempColor.r = ( intBits & 0xff ) / 255.0f;
    tempColor.g = ( ( ( unsigned int ) intBits >> 8 ) & 0xff ) / 255.0f;
    tempColor.b = ( ( ( unsigned int ) intBits >> 16 ) & 0xff ) / 255.0f;
    tempColor.a = ( ( ( unsigned int ) intBits >> 24 ) & 0xff ) / 255.0f;
    return tempColor;
}

void SpriteCache::beginCache () {
    if ( currentCache != NULL )
        gdx_log_error("gdx", "endCache must be called before begin." );

    int verticesPerImage = mesh->getNumIndices() > 0 ? 4 : 6;
    currentCache = new Cache ( caches.size(), mesh->getVerticesBuffer().limit() );
    caches.push_back ( currentCache );
    mesh->getVerticesBuffer().compact();
}

void SpriteCache::beginCache ( unsigned int cacheID ) {
    if ( currentCache != NULL )
        gdx_log_error("gdx", "endCache must be called before begin." );

    if ( cacheID == caches.size() - 1 ) {
        Cache* oldCache = caches[cacheID];
        caches.erase ( caches.begin() + cacheID );
        mesh->getVerticesBuffer().limit ( oldCache->offset );
        beginCache();
        return;
    }
    currentCache = caches[cacheID];
    mesh->getVerticesBuffer().position ( currentCache->offset );
}

int SpriteCache::endCache () {
    if ( currentCache == NULL )
        gdx_log_error("gdx", "beginCache must be called before endCache." );

    int cacheCount = mesh->getVerticesBuffer().position() - currentCache->offset;
    if ( currentCache->textures.size() == 0 ) {
        // New cache.
        currentCache->maxCount = cacheCount;
        currentCache->textures = textures;
        currentCache->counts = counts;
        mesh->getVerticesBuffer().flip();
    } else {
        // Redefine existing cache.
        if ( cacheCount > currentCache->maxCount ) {
            std::stringstream ss;
            ss << "If a cache is not the last created, it cannot be redefined with more entries than when it was first created: "
               << cacheCount << " (" << currentCache->maxCount  << " max)";
            gdx_log_error("gdx", ss.str().c_str() );
        }

        if ( currentCache->textures.size() < textures.size() ) {
            currentCache->textures.resize ( textures.size() );
        }

        for ( int i = 0, n = textures.size(); i < n; i++ )
            currentCache->textures[i] = textures[i];

        if ( currentCache->counts.size() < counts.size() ) currentCache->counts.resize ( counts.size() );
        for ( int i = 0, n = counts.size(); i < n; i++ )
            currentCache->counts[i] = counts[i];

        float_buffer& vertices = mesh->getVerticesBuffer();
        vertices.position ( 0 );
        Cache* lastCache = caches[caches.size() - 1];
        vertices.limit ( lastCache->offset + lastCache->maxCount );
    }

    Cache* cache = currentCache;
    currentCache = NULL;
    textures.clear();
    counts.clear();

    return cache->id;
}

void SpriteCache::clear () {
    for ( int i = 0; i < caches.size(); ++i ) {
        delete caches[i];
    }
    caches.clear();
    mesh->getVerticesBuffer().clear().flip();
}

void SpriteCache::add ( const Texture::ptr& texture, float x, float y ) {
    float fx2 = x + texture->getWidth();
    float fy2 = y + texture->getHeight();

    tempVertices[0] = x;
    tempVertices[1] = y;
    tempVertices[2] = color;
    tempVertices[3] = 0;
    tempVertices[4] = 1;

    tempVertices[5] = x;
    tempVertices[6] = fy2;
    tempVertices[7] = color;
    tempVertices[8] = 0;
    tempVertices[9] = 0;

    tempVertices[10] = fx2;
    tempVertices[11] = fy2;
    tempVertices[12] = color;
    tempVertices[13] = 1;
    tempVertices[14] = 0;

    if ( mesh->getNumIndices() > 0 ) {
        tempVertices[15] = fx2;
        tempVertices[16] = y;
        tempVertices[17] = color;
        tempVertices[18] = 1;
        tempVertices[19] = 1;
        add ( texture, tempVertices, 30, 0, 20 );
    } else {
        tempVertices[15] = fx2;
        tempVertices[16] = fy2;
        tempVertices[17] = color;
        tempVertices[18] = 1;
        tempVertices[19] = 0;

        tempVertices[20] = fx2;
        tempVertices[21] = y;
        tempVertices[22] = color;
        tempVertices[23] = 1;
        tempVertices[24] = 1;

        tempVertices[25] = x;
        tempVertices[26] = y;
        tempVertices[27] = color;
        tempVertices[28] = 0;
        tempVertices[29] = 1;
        add ( texture, tempVertices, 30, 0, 30 );
    }
}

void SpriteCache::add ( const Texture::ptr& texture, float x, float y, int srcWidth, int srcHeight, float u, float v, float u2, float v2, float color ) {
    float fx2 = x + srcWidth;
    float fy2 = y + srcHeight;

    tempVertices[0] = x;
    tempVertices[1] = y;
    tempVertices[2] = color;
    tempVertices[3] = u;
    tempVertices[4] = v;

    tempVertices[5] = x;
    tempVertices[6] = fy2;
    tempVertices[7] = color;
    tempVertices[8] = u;
    tempVertices[9] = v2;

    tempVertices[10] = fx2;
    tempVertices[11] = fy2;
    tempVertices[12] = color;
    tempVertices[13] = u2;
    tempVertices[14] = v2;

    if ( mesh->getNumIndices() > 0 ) {
        tempVertices[15] = fx2;
        tempVertices[16] = y;
        tempVertices[17] = color;
        tempVertices[18] = u2;
        tempVertices[19] = v;
        add ( texture, tempVertices, 30, 0, 20 );
    } else {
        tempVertices[15] = fx2;
        tempVertices[16] = fy2;
        tempVertices[17] = color;
        tempVertices[18] = u2;
        tempVertices[19] = v2;

        tempVertices[20] = fx2;
        tempVertices[21] = y;
        tempVertices[22] = color;
        tempVertices[23] = u2;
        tempVertices[24] = v;

        tempVertices[25] = x;
        tempVertices[26] = y;
        tempVertices[27] = color;
        tempVertices[28] = u;
        tempVertices[29] = v;
        add ( texture, tempVertices, 30, 0, 30 );
    }
}

void SpriteCache::add ( const Texture::ptr& texture, float x, float y, int srcX, int srcY, int srcWidth, int srcHeight ) {
    float invTexWidth = 1.0f / texture->getWidth();
    float invTexHeight = 1.0f / texture->getHeight();
    float u = srcX * invTexWidth;
    float v = ( srcY + srcHeight ) * invTexHeight;
    float u2 = ( srcX + srcWidth ) * invTexWidth;
    float v2 = srcY * invTexHeight;
    float fx2 = x + srcWidth;
    float fy2 = y + srcHeight;

    tempVertices[0] = x;
    tempVertices[1] = y;
    tempVertices[2] = color;
    tempVertices[3] = u;
    tempVertices[4] = v;

    tempVertices[5] = x;
    tempVertices[6] = fy2;
    tempVertices[7] = color;
    tempVertices[8] = u;
    tempVertices[9] = v2;

    tempVertices[10] = fx2;
    tempVertices[11] = fy2;
    tempVertices[12] = color;
    tempVertices[13] = u2;
    tempVertices[14] = v2;

    if ( mesh->getNumIndices() > 0 ) {
        tempVertices[15] = fx2;
        tempVertices[16] = y;
        tempVertices[17] = color;
        tempVertices[18] = u2;
        tempVertices[19] = v;
        add ( texture, tempVertices, 30, 0, 20 );
    } else {
        tempVertices[15] = fx2;
        tempVertices[16] = fy2;
        tempVertices[17] = color;
        tempVertices[18] = u2;
        tempVertices[19] = v2;

        tempVertices[20] = fx2;
        tempVertices[21] = y;
        tempVertices[22] = color;
        tempVertices[23] = u2;
        tempVertices[24] = v;

        tempVertices[25] = x;
        tempVertices[26] = y;
        tempVertices[27] = color;
        tempVertices[28] = u;
        tempVertices[29] = v;
        add ( texture, tempVertices, 30, 0, 30 );
    }
}

void SpriteCache::add ( const Texture::ptr& texture,float x,float y,float width,float height,int srcX,int srcY,int srcWidth,int srcHeight,bool flipX,bool flipY ) {

    float invTexWidth = 1.0f / texture->getWidth();
    float invTexHeight = 1.0f / texture->getHeight();
    float u = srcX * invTexWidth;
    float v = ( srcY + srcHeight ) * invTexHeight;
    float u2 = ( srcX + srcWidth ) * invTexWidth;
    float v2 = srcY * invTexHeight;
    float fx2 = x + width;
    float fy2 = y + height;

    if ( flipX ) {
        float tmp = u;
        u = u2;
        u2 = tmp;
    }
    if ( flipY ) {
        float tmp = v;
        v = v2;
        v2 = tmp;
    }

    tempVertices[0] = x;
    tempVertices[1] = y;
    tempVertices[2] = color;
    tempVertices[3] = u;
    tempVertices[4] = v;

    tempVertices[5] = x;
    tempVertices[6] = fy2;
    tempVertices[7] = color;
    tempVertices[8] = u;
    tempVertices[9] = v2;

    tempVertices[10] = fx2;
    tempVertices[11] = fy2;
    tempVertices[12] = color;
    tempVertices[13] = u2;
    tempVertices[14] = v2;

    if ( mesh->getNumIndices() > 0 ) {
        tempVertices[15] = fx2;
        tempVertices[16] = y;
        tempVertices[17] = color;
        tempVertices[18] = u2;
        tempVertices[19] = v;
        add ( texture, tempVertices, 30, 0, 20 );
    } else {
        tempVertices[15] = fx2;
        tempVertices[16] = fy2;
        tempVertices[17] = color;
        tempVertices[18] = u2;
        tempVertices[19] = v2;

        tempVertices[20] = fx2;
        tempVertices[21] = y;
        tempVertices[22] = color;
        tempVertices[23] = u2;
        tempVertices[24] = v;

        tempVertices[25] = x;
        tempVertices[26] = y;
        tempVertices[27] = color;
        tempVertices[28] = u;
        tempVertices[29] = v;
        add ( texture, tempVertices, 30, 0, 30 );
    }
}

void SpriteCache::add ( const Texture::ptr& texture,float x,float y,float originX,float originY,float width,float height,float scaleX,float scaleY,float rotation,int srcX,int srcY,int srcWidth,int srcHeight,bool flipX,bool flipY ) {

    // bottom left and top right corner points relative to origin
    float worldOriginX = x + originX;
    float worldOriginY = y + originY;
    float fx = -originX;
    float fy = -originY;
    float fx2 = width - originX;
    float fy2 = height - originY;

    // scale
    if ( scaleX != 1 || scaleY != 1 ) {
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
    if ( rotation != 0 ) {
        float cos = cosDeg ( rotation );
        float sin = sinDeg ( rotation );

        x1 = cos * p1x - sin * p1y;
        y1 = sin * p1x + cos * p1y;

        x2 = cos * p2x - sin * p2y;
        y2 = sin * p2x + cos * p2y;

        x3 = cos * p3x - sin * p3y;
        y3 = sin * p3x + cos * p3y;

        x4 = x1 + ( x3 - x2 );
        y4 = y3 - ( y2 - y1 );
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

    float invTexWidth = 1.0f / texture->getWidth();
    float invTexHeight = 1.0f / texture->getHeight();
    float u = srcX * invTexWidth;
    float v = ( srcY + srcHeight ) * invTexHeight;
    float u2 = ( srcX + srcWidth ) * invTexWidth;
    float v2 = srcY * invTexHeight;

    if ( flipX ) {
        float tmp = u;
        u = u2;
        u2 = tmp;
    }

    if ( flipY ) {
        float tmp = v;
        v = v2;
        v2 = tmp;
    }

    tempVertices[0] = x1;
    tempVertices[1] = y1;
    tempVertices[2] = color;
    tempVertices[3] = u;
    tempVertices[4] = v;

    tempVertices[5] = x2;
    tempVertices[6] = y2;
    tempVertices[7] = color;
    tempVertices[8] = u;
    tempVertices[9] = v2;

    tempVertices[10] = x3;
    tempVertices[11] = y3;
    tempVertices[12] = color;
    tempVertices[13] = u2;
    tempVertices[14] = v2;

    if ( mesh->getNumIndices() > 0 ) {
        tempVertices[15] = x4;
        tempVertices[16] = y4;
        tempVertices[17] = color;
        tempVertices[18] = u2;
        tempVertices[19] = v;
        add ( texture, tempVertices, 30, 0, 20 );
    } else {
        tempVertices[15] = x3;
        tempVertices[16] = y3;
        tempVertices[17] = color;
        tempVertices[18] = u2;
        tempVertices[19] = v2;

        tempVertices[20] = x4;
        tempVertices[21] = y4;
        tempVertices[22] = color;
        tempVertices[23] = u2;
        tempVertices[24] = v;

        tempVertices[25] = x1;
        tempVertices[26] = y1;
        tempVertices[27] = color;
        tempVertices[28] = u;
        tempVertices[29] = v;
        add ( texture, tempVertices, 30, 0, 30 );
    }
}

void SpriteCache::add (const TextureRegion& region,float x,float y ) {
    add ( region, x, y, region.getRegionWidth(), region.getRegionHeight() );
}

void SpriteCache::add ( const TextureRegion& region,float x,float y,float width,float height ) {
    float fx2 = x + width;
    float fy2 = y + height;
    float u = region.u;
    float v = region.v2;
    float u2 = region.u2;
    float v2 = region.v;

    tempVertices[0] = x;
    tempVertices[1] = y;
    tempVertices[2] = color;
    tempVertices[3] = u;
    tempVertices[4] = v;

    tempVertices[5] = x;
    tempVertices[6] = fy2;
    tempVertices[7] = color;
    tempVertices[8] = u;
    tempVertices[9] = v2;

    tempVertices[10] = fx2;
    tempVertices[11] = fy2;
    tempVertices[12] = color;
    tempVertices[13] = u2;
    tempVertices[14] = v2;

    if ( mesh->getNumIndices() > 0 ) {
        tempVertices[15] = fx2;
        tempVertices[16] = y;
        tempVertices[17] = color;
        tempVertices[18] = u2;
        tempVertices[19] = v;
        add ( region.getTexture(), tempVertices, 30, 0, 20 );
    } else {
        tempVertices[15] = fx2;
        tempVertices[16] = fy2;
        tempVertices[17] = color;
        tempVertices[18] = u2;
        tempVertices[19] = v2;

        tempVertices[20] = fx2;
        tempVertices[21] = y;
        tempVertices[22] = color;
        tempVertices[23] = u2;
        tempVertices[24] = v;

        tempVertices[25] = x;
        tempVertices[26] = y;
        tempVertices[27] = color;
        tempVertices[28] = u;
        tempVertices[29] = v;
        add ( region.getTexture(), tempVertices, 30, 0, 30 );
    }
}

void SpriteCache::add ( const TextureRegion& region, float x, float y, float originX, float originY, float width, float height, float scaleX, float scaleY, float rotation ) {

    // bottom left and top right corner points relative to origin
    float worldOriginX = x + originX;
    float worldOriginY = y + originY;
    float fx = -originX;
    float fy = -originY;
    float fx2 = width - originX;
    float fy2 = height - originY;

    // scale
    if ( scaleX != 1 || scaleY != 1 ) {
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
    if ( rotation != 0 ) {
        float cos = cosDeg ( rotation );
        float sin = sinDeg ( rotation );

        x1 = cos * p1x - sin * p1y;
        y1 = sin * p1x + cos * p1y;

        x2 = cos * p2x - sin * p2y;
        y2 = sin * p2x + cos * p2y;

        x3 = cos * p3x - sin * p3y;
        y3 = sin * p3x + cos * p3y;

        x4 = x1 + ( x3 - x2 );
        y4 = y3 - ( y2 - y1 );
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

    tempVertices[0] = x1;
    tempVertices[1] = y1;
    tempVertices[2] = color;
    tempVertices[3] = u;
    tempVertices[4] = v;

    tempVertices[5] = x2;
    tempVertices[6] = y2;
    tempVertices[7] = color;
    tempVertices[8] = u;
    tempVertices[9] = v2;

    tempVertices[10] = x3;
    tempVertices[11] = y3;
    tempVertices[12] = color;
    tempVertices[13] = u2;
    tempVertices[14] = v2;

    if ( mesh->getNumIndices() > 0 ) {
        tempVertices[15] = x4;
        tempVertices[16] = y4;
        tempVertices[17] = color;
        tempVertices[18] = u2;
        tempVertices[19] = v;
        add ( region.getTexture(), tempVertices, 30, 0, 20 );
    } else {
        tempVertices[15] = x3;
        tempVertices[16] = y3;
        tempVertices[17] = color;
        tempVertices[18] = u2;
        tempVertices[19] = v2;

        tempVertices[20] = x4;
        tempVertices[21] = y4;
        tempVertices[22] = color;
        tempVertices[23] = u2;
        tempVertices[24] = v;

        tempVertices[25] = x1;
        tempVertices[26] = y1;
        tempVertices[27] = color;
        tempVertices[28] = u;
        tempVertices[29] = v;
        add ( region.getTexture(), tempVertices, Sprite::SPRITE_SIZE, 0, 30 );
    }
}

void SpriteCache::add ( Sprite& sprite ) {
    if ( mesh->getNumIndices() > 0 ) {
        add ( sprite.getTexture(), sprite.getVertices().data(), Sprite::SPRITE_SIZE, 0, Sprite::SPRITE_SIZE );
        return;
    }

    const auto& spriteVertices = sprite.getVertices();

    memcpy ( tempVertices, &spriteVertices[0], sizeof ( float ) * 3 * Sprite::VERTEX_SIZE );
    memcpy ( &tempVertices[3 * Sprite::VERTEX_SIZE], &spriteVertices[2 * Sprite::VERTEX_SIZE], sizeof ( float ) * Sprite::VERTEX_SIZE );
    memcpy ( &tempVertices[4 * Sprite::VERTEX_SIZE], &spriteVertices[3 * Sprite::VERTEX_SIZE],  sizeof ( float ) * Sprite::VERTEX_SIZE );
    memcpy ( &tempVertices[5 * Sprite::VERTEX_SIZE], &spriteVertices[0], sizeof ( float ) * Sprite::VERTEX_SIZE );

    add ( sprite.getTexture(), tempVertices, 30, 0, 30 );
}

void SpriteCache::begin () {
    if ( drawing )
        gdx_log_error("gdx", "end must be called before begin." );

    if ( graphics->isGL20Available() == false ) {
        GL10& gl = *gl10;
        gl.glDepthMask ( false );
        gl.glEnable(GL10::GL_TEXTURE_2D);

        gl.glMatrixMode(GL10::GL_PROJECTION);
        gl.glLoadMatrixf( projectionMatrix.val);
        gl.glMatrixMode(GL10::GL_MODELVIEW);
        gl.glLoadMatrixf ( transformMatrix.val );

        mesh->bind();
    } else {
        combinedMatrix.set ( projectionMatrix ).mul ( transformMatrix );

        GL20& gl = *gl20;
        gl.glDepthMask ( false );
        gl.glEnable(GL10::GL_TEXTURE_2D );

        if ( customShader != NULL ) {
            customShader->begin();
            customShader->setUniformMatrix ( "u_proj", projectionMatrix );
            customShader->setUniformMatrix ( "u_trans", transformMatrix );
            customShader->setUniformMatrix ( "u_projTrans", combinedMatrix );
            customShader->setUniformi ( "u_texture", 0 );
        } else {
            shader->begin();
            shader->setUniformMatrix ( "u_projectionViewMatrix", combinedMatrix );
            shader->setUniformi ( "u_texture", 0 );
        }

        mesh->bind ( *shader );
    }
    drawing = true;
}

void SpriteCache::end () {
    if ( !drawing )
        gdx_log_error("gdx", "begin must be called before end." );

    drawing = false;

    if ( graphics->isGL20Available() == false ) {
        GL10& gl = *gl10;
        gl.glDepthMask ( true );
        gl.glDisable ( GL10::GL_TEXTURE_2D );
        mesh->unbind();
    } else {
        shader->end();
        GL20& gl = *gl20;
        gl.glDepthMask ( true );
        gl.glDisable ( GL10::GL_TEXTURE_2D );
        mesh->unbind ( *shader );
    }
}

void SpriteCache::draw ( int cacheID ) {
    if ( !drawing )
        gdx_log_error("gdx", "SpriteCache.begin must be called before draw." );

    Cache* cache = caches[cacheID];

    int verticesPerImage = mesh->getNumIndices() > 0 ? 4 : 6;
    int offset = cache->offset  / ( verticesPerImage * Sprite::VERTEX_SIZE ) * 6;

    std::vector<Texture::ptr>& textures = cache->textures;
    std::vector<int>& counts = cache->counts;

    if ( graphics->isGL20Available() ) {
        for ( int i = 0, n = textures.size(); i < n; i++ ) {
            int count = counts[i];
            textures[i]->bind();
            if ( customShader != NULL )
                mesh->render ( *customShader, GL10::GL_TRIANGLES, offset, count );
            else
                mesh->render ( *shader, GL10::GL_TRIANGLES, offset, count );
            offset += count;
        }
    } else {
        for ( int i = 0, n = textures.size(); i < n; i++ ) {
            int count = counts[i];
            textures[i]->bind();

            mesh->render ( GL10::GL_TRIANGLES, offset, count );
            offset += count;
        }
    }
}

void SpriteCache::draw ( int cacheID,int offset,int length ) {
    if ( !drawing )
        gdx_log_error("gdx", "SpriteCache.begin must be called before draw." );

    Cache* cache = caches[cacheID];
    offset = offset * 6 + cache->offset;
    length *= 6;
    std::vector<Texture::ptr>& textures = cache->textures;
    std::vector<int>& counts = cache->counts;
    if ( graphics->isGL20Available() ) {
        for ( int i = 0, n = textures.size(); i < n; i++ ) {
            textures[i]->bind();
            int count = counts[i];
            if ( count > length ) {
                i = n;
                count = length;
            } else
                length -= count;
            if ( customShader != NULL )
                mesh->render ( *customShader, GL10::GL_TRIANGLES, offset, count );
            else
                mesh->render ( *shader, GL10::GL_TRIANGLES, offset, count );
            offset += count;
        }
    } else {
        for ( int i = 0, n = textures.size(); i < n; i++ ) {
            textures[i]->bind();
            int count = counts[i];
            if ( count > length ) {
                i = n;
                count = length;
            } else
                length -= count;
            mesh->render ( GL10::GL_TRIANGLES, offset, count );
            offset += count;
        }
    }
}

void SpriteCache::dispose () {
    mesh->dispose();
    if ( shader != NULL ) shader->dispose();
}

Matrix4& SpriteCache::getProjectionMatrix () {
    return projectionMatrix;
}

void SpriteCache::setProjectionMatrix ( const Matrix4& projection ) {
    if ( drawing )
        gdx_log_error("gdx", "Can't set the matrix within begin/end." );
    projectionMatrix.set ( projection );
}

Matrix4& SpriteCache::getTransformMatrix () {
    return transformMatrix;
}

void SpriteCache::setTransformMatrix ( const Matrix4& transform ) {
    if ( drawing )
        gdx_log_error("gdx", "Can't set the matrix within begin/end." );
    transformMatrix.set ( transform );
}

void SpriteCache::setShader ( ShaderProgram* shader ) {
    customShader = shader;
}

void SpriteCache::add ( const Texture::ptr& texture, const float* vertices, int size, int offset, int length ) {
    if ( currentCache == NULL )
        gdx_log_error("gdx", "beginCache must be called before add." );

    int verticesPerImage = mesh->getNumIndices() > 0 ? 4 : 6;
    int count = length / ( verticesPerImage * Sprite::VERTEX_SIZE ) * 6;
    int lastIndex = textures.size() - 1;

    if ( lastIndex < 0 || textures[lastIndex] != texture ) {
        textures.push_back ( texture );
        counts.push_back ( count );
    } else
        counts[lastIndex] = counts[lastIndex] + count;

    float_buffer& buffer = mesh->getVerticesBuffer();
    if (buffer.capacity() - (buffer.position() + size) < 0) {
        int pos = -1;
        for (int i=0; i<caches.size(); i++) {
            if (caches[i] != NULL) {
                if (pos == -1) {
                    pos = caches[i]->offset;
                }
                caches[i]->offset -= pos;
            }
        }
        buffer.position(pos);
        buffer.compact();
         
    }
    buffer.put ( &vertices[0], size, offset, length );
}

void SpriteCache::disposeCache ( int cacheID ) {
    for ( int i = 0; i < caches.size(); ++i ) {
        if ( caches[i] != NULL && caches[i]->id == cacheID ) {
            delete caches[i];
            caches[i] = NULL;
            break;
        }
    }
}
