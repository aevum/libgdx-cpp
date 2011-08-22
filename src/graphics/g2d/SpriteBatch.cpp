
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

using namespace gdx_cpp::graphics::g2d;

void SpriteBatch::createShader () {
    String vertexShader = "attribute vec4 " + ShaderProgram.POSITION_ATTRIBUTE + ";\n" //
                          + "attribute vec4 " + ShaderProgram.COLOR_ATTRIBUTE + ";\n" //
                          + "attribute vec2 " + ShaderProgram.TEXCOORD_ATTRIBUTE + "0;\n" //
                          + "uniform mat4 u_projectionViewMatrix;\n" //
                          + "varying vec4 v_color;\n" //
                          + "varying vec2 v_texCoords;\n" //
                          + "\n" //
                          + "void main()\n" //
                          + "{\n" //
                          + "   v_color = " + ShaderProgram.COLOR_ATTRIBUTE + ";\n" //
                          + "   v_texCoords = " + ShaderProgram.TEXCOORD_ATTRIBUTE + "0;\n" //
                          + "   gl_Position =  u_projectionViewMatrix * " + ShaderProgram.POSITION_ATTRIBUTE + ";\n" //
                          + "}\n";
    String fragmentShader = "#ifdef GL_ES\n" //
                            + "precision mediump float;\n" //
                            + "#endif\n" //
                            + "varying vec4 v_color;\n" //
                            + "varying vec2 v_texCoords;\n" //
                            + "uniform sampler2D u_texture;\n" //
                            + "void main()\n"//
                            + "{\n" //
                            + "  gl_FragColor = v_color * texture2D(u_texture, v_texCoords);\n" //
                            + "}";

    shader = new ShaderProgram(vertexShader, fragmentShader);
    if (shader.isCompiled() == false) throw new IllegalArgumentException("couldn't compile shader: " + shader.getLog());
}

void SpriteBatch::begin () {
    if (drawing) throw new IllegalStateException("you have to call SpriteBatch.end() first");
    renderCalls = 0;

    if (Gdx.graphics.isGL20Available() == false) {
        GL10 gl = Gdx.gl10;

        gl.glDepthMask(false);
        gl.glEnable(GL10.GL_TEXTURE_2D);

        gl.glMatrixMode(GL10.GL_PROJECTION);
        gl.glLoadMatrixf(projectionMatrix.val, 0);
        gl.glMatrixMode(GL10.GL_MODELVIEW);
        gl.glLoadMatrixf(transformMatrix.val, 0);
    } else {
        combinedMatrix.set(projectionMatrix).mul(transformMatrix);

        GL20 gl = Gdx.gl20;
        gl.glDepthMask(false);
        gl.glEnable(GL20.GL_TEXTURE_2D);

        if (customShader != null) {
            customShader.begin();
            customShader.setUniformMatrix("u_proj", projectionMatrix);
            customShader.setUniformMatrix("u_trans", transformMatrix);
            customShader.setUniformMatrix("u_projTrans", combinedMatrix);
            customShader.setUniformi("u_texture", 0);
        } else {
            shader.begin();
            shader.setUniformMatrix("u_projectionViewMatrix", combinedMatrix);
            shader.setUniformi("u_texture", 0);
        }
    }

    idx = 0;
    lastTexture = null;
    drawing = true;
}

void SpriteBatch::end () {
    if (!drawing) throw new IllegalStateException("SpriteBatch.begin must be called before end.");
    if (idx > 0) renderMesh();
    lastTexture = null;
    idx = 0;
    drawing = false;

    GLCommon gl = Gdx.gl;
    gl.glDepthMask(true);
    if (isBlendingEnabled()) gl.glDisable(GL10.GL_BLEND);
    gl.glDisable(GL10.GL_TEXTURE_2D);

    if (Gdx.graphics.isGL20Available()) {
        if (customShader != null)
            customShader.end();
        else
            shader.end();
    }
}

void SpriteBatch::setColor (const gdx_cpp::graphics::Color& tint) {
    color = tint.toFloatBits();
}

void SpriteBatch::setColor (float r,float g,float b,float a) {
    int intBits = (int)(255 * a) << 24 | (int)(255 * b) << 16 | (int)(255 * g) << 8 | (int)(255 * r);
    color = NumberUtils.intBitsToFloat(intBits & 0xfeffffff);
}

void SpriteBatch::setColor (float color) {
    this.color = color;
}

gdx_cpp::graphics::Color& SpriteBatch::getColor () {
    int intBits = NumberUtils.floatToRawIntBits(color);
    Color color = this.tempColor;
    color.r = (intBits & 0xff) / 255f;
    color.g = ((intBits >>> 8) & 0xff) / 255f;
    color.b = ((intBits >>> 16) & 0xff) / 255f;
    color.a = ((intBits >>> 24) & 0xff) / 255f;
    return color;
}

void SpriteBatch::draw (const gdx_cpp::graphics::Texture& texture,float x,float y,float originX,float originY,float width,float height,float scaleX,float scaleY,float rotation,int srcX,int srcY,int srcWidth,int srcHeight,bool flipX,bool flipY) {
    if (!drawing) throw new IllegalStateException("SpriteBatch.begin must be called before draw.");

    if (texture != lastTexture) {
        renderMesh();
        lastTexture = texture;
        invTexWidth = 1.0f / texture.getWidth();
        invTexHeight = 1.0f / texture.getHeight();
    } else if (idx == vertices.length) renderMesh();

    // bottom left and top right corner points relative to origin
    final float worldOriginX = x + originX;
    final float worldOriginY = y + originY;
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
    final float p1x = fx;
    final float p1y = fy;
    final float p2x = fx;
    final float p2y = fy2;
    final float p3x = fx2;
    final float p3y = fy2;
    final float p4x = fx2;
    final float p4y = fy;

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
        final float cos = MathUtils.cosDeg(rotation);
        final float sin = MathUtils.sinDeg(rotation);

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
    if (!drawing) throw new IllegalStateException("SpriteBatch.begin must be called before draw.");

    if (texture != lastTexture) {
        renderMesh();
        lastTexture = texture;
        invTexWidth = 1.0f / texture.getWidth();
        invTexHeight = 1.0f / texture.getHeight();
    } else if (idx == vertices.length) renderMesh();

    float u = srcX * invTexWidth;
    float v = (srcY + srcHeight) * invTexHeight;
    float u2 = (srcX + srcWidth) * invTexWidth;
    float v2 = srcY * invTexHeight;
    final float fx2 = x + width;
    final float fy2 = y + height;

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
    if (!drawing) throw new IllegalStateException("SpriteBatch.begin must be called before draw.");

    if (texture != lastTexture) {
        renderMesh();
        lastTexture = texture;
        invTexWidth = 1.0f / texture.getWidth();
        invTexHeight = 1.0f / texture.getHeight();
    } else if (idx == vertices.length) renderMesh();

    final float u = srcX * invTexWidth;
    final float v = (srcY + srcHeight) * invTexHeight;
    final float u2 = (srcX + srcWidth) * invTexWidth;
    final float v2 = srcY * invTexHeight;
    final float fx2 = x + srcWidth;
    final float fy2 = y + srcHeight;

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
    if (!drawing) throw new IllegalStateException("SpriteBatch.begin must be called before draw.");

    if (texture != lastTexture) {
        renderMesh();
        lastTexture = texture;
        invTexWidth = 1.0f / texture.getWidth();
        invTexHeight = 1.0f / texture.getHeight();
    } else if (idx == vertices.length) renderMesh();

    final float fx2 = x + width;
    final float fy2 = y + height;

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
    if (!drawing) throw new IllegalStateException("SpriteBatch.begin must be called before draw.");

    if (texture != lastTexture) {
        renderMesh();
        lastTexture = texture;
        invTexWidth = 1.0f / texture.getWidth();
        invTexHeight = 1.0f / texture.getHeight();
    } else if (idx == vertices.length) renderMesh();

    final float fx2 = x + texture.getWidth();
    final float fy2 = y + texture.getHeight();

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
    if (!drawing) throw new IllegalStateException("SpriteBatch.begin must be called before draw.");

    if (texture != lastTexture) {
        renderMesh();
        lastTexture = texture;
        invTexWidth = 1f / texture.getWidth();
        invTexHeight = 1f / texture.getHeight();
    } else if (idx == vertices.length) //
        renderMesh();

    final float fx2 = x + width;
    final float fy2 = y + height;
    final float u = 0;
    final float v = 1;
    final float u2 = 1;
    final float v2 = 0;

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

void SpriteBatch::draw (const gdx_cpp::graphics::Texture& texture,int offset,int length) {
    if (!drawing) throw new IllegalStateException("SpriteBatch.begin must be called before draw.");

    if (texture != lastTexture) {
        renderMesh();
        lastTexture = texture;
        invTexWidth = 1.0f / texture.getWidth();
        invTexHeight = 1.0f / texture.getHeight();
    } else if (idx + length >= vertices.length) renderMesh();

    System.arraycopy(spriteVertices, offset, vertices, idx, length);
    idx += length;
}

void SpriteBatch::draw (const TextureRegion& region,float x,float y) {
    draw(region, x, y, Math.abs(region.getRegionWidth()), Math.abs(region.getRegionHeight()));
}

void SpriteBatch::draw (const TextureRegion& region,float x,float y,float width,float height) {
    if (!drawing) throw new IllegalStateException("SpriteBatch.begin must be called before draw.");

    Texture texture = region.texture;
    if (texture != lastTexture) {
        renderMesh();
        lastTexture = texture;
        invTexWidth = 1f / texture.getWidth();
        invTexHeight = 1f / texture.getHeight();
    } else if (idx == vertices.length) //
        renderMesh();

    final float fx2 = x + width;
    final float fy2 = y + height;
    final float u = region.u;
    final float v = region.v2;
    final float u2 = region.u2;
    final float v2 = region.v;

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
    if (!drawing) throw new IllegalStateException("SpriteBatch.begin must be called before draw.");

    Texture texture = region.texture;
    if (texture != lastTexture) {
        renderMesh();
        lastTexture = texture;
        invTexWidth = 1f / texture.getWidth();
        invTexHeight = 1f / texture.getHeight();
    } else if (idx == vertices.length) //
        renderMesh();

    // bottom left and top right corner points relative to origin
    final float worldOriginX = x + originX;
    final float worldOriginY = y + originY;
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
    final float p1x = fx;
    final float p1y = fy;
    final float p2x = fx;
    final float p2y = fy2;
    final float p3x = fx2;
    final float p3y = fy2;
    final float p4x = fx2;
    final float p4y = fy;

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
        final float cos = MathUtils.cosDeg(rotation);
        final float sin = MathUtils.sinDeg(rotation);

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

    final float u = region.u;
    final float v = region.v2;
    final float u2 = region.u2;
    final float v2 = region.v;

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
    if (!drawing) throw new IllegalStateException("SpriteBatch.begin must be called before draw.");

    Texture texture = region.texture;
    if (texture != lastTexture) {
        renderMesh();
        lastTexture = texture;
        invTexWidth = 1f / texture.getWidth();
        invTexHeight = 1f / texture.getHeight();
    } else if (idx == vertices.length) //
        renderMesh();

    // bottom left and top right corner points relative to origin
    final float worldOriginX = x + originX;
    final float worldOriginY = y + originY;
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
    final float p1x = fx;
    final float p1y = fy;
    final float p2x = fx;
    final float p2y = fy2;
    final float p3x = fx2;
    final float p3y = fy2;
    final float p4x = fx2;
    final float p4y = fy;

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
        final float cos = MathUtils.cosDeg(rotation);
        final float sin = MathUtils.sinDeg(rotation);

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

    lastTexture.bind();
    mesh.setVertices(vertices, 0, idx);

    if (Gdx.graphics.isGL20Available()) {
        if (blendingDisabled) {
            Gdx.gl20.glDisable(GL20.GL_BLEND);
        } else {
            GL20 gl20 = Gdx.gl20;
            gl20.glEnable(GL20.GL_BLEND);
            gl20.glBlendFunc(blendSrcFunc, blendDstFunc);
        }

        if (customShader != null)
            mesh.render(customShader, GL10.GL_TRIANGLES, 0, spritesInBatch * 6);
        else
            mesh.render(shader, GL10.GL_TRIANGLES, 0, spritesInBatch * 6);
    } else {
        if (blendingDisabled) {
            Gdx.gl10.glDisable(GL10.GL_BLEND);
        } else {
            GL10 gl10 = Gdx.gl10;
            gl10.glEnable(GL10.GL_BLEND);
            gl10.glBlendFunc(blendSrcFunc, blendDstFunc);
        }
        mesh.render(GL10.GL_TRIANGLES, 0, spritesInBatch * 6);
    }

    idx = 0;
    currBufferIdx++;
    if (currBufferIdx == buffers.length) currBufferIdx = 0;
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
    for (int i = 0; i < buffers.length; i++)
        buffers[i].dispose();
    if (shader != null) shader.dispose();
}

gdx_cpp::math::Matrix4& SpriteBatch::getProjectionMatrix () {
    return projectionMatrix;
}

gdx_cpp::math::Matrix4& SpriteBatch::getTransformMatrix () {
    return transformMatrix;
}

void SpriteBatch::setProjectionMatrix (const gdx_cpp::math::Matrix4& projection) {
    if (drawing) throw new GdxRuntimeException("Can't set the matrix within begin()/end() block");

    projectionMatrix.set(projection);
}

void SpriteBatch::setTransformMatrix (const gdx_cpp::math::Matrix4& transform) {
    if (drawing) throw new GdxRuntimeException("Can't set the matrix within begin()/end() block");

    transformMatrix.set(transform);
}

void SpriteBatch::setShader (const gdx_cpp::graphics::glutils::ShaderProgram& shader) {
    customShader = shader;
}

bool SpriteBatch::isBlendingEnabled () {
    return !blendingDisabled;
}

