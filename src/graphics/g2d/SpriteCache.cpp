
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

#include "SpriteCache.hpp"

using namespace gdx_cpp::graphics::g2d;

void SpriteCache::setColor (const gdx_cpp::graphics::Color& tint) {
    color = tint.toFloatBits();
}

void SpriteCache::setColor (float r,float g,float b,float a) {
    int intBits = (int)(255 * a) << 24 | (int)(255 * b) << 16 | (int)(255 * g) << 8 | (int)(255 * r);
    color = NumberUtils.intBitsToFloat(intBits & 0xfeffffff);
}

void SpriteCache::setColor (float color) {
    this.color = color;
}

gdx_cpp::graphics::Color& SpriteCache::getColor () {
    int intBits = NumberUtils.floatToRawIntBits(color);
    Color color = this.tempColor;
    color.r = (intBits & 0xff) / 255f;
    color.g = ((intBits >>> 8) & 0xff) / 255f;
    color.b = ((intBits >>> 16) & 0xff) / 255f;
    color.a = ((intBits >>> 24) & 0xff) / 255f;
    return color;
}

void SpriteCache::beginCache () {
    if (currentCache != null) throw new IllegalStateException("endCache must be called before begin.");
    int verticesPerImage = mesh.getNumIndices() > 0 ? 4 : 6;
    currentCache = new Cache(caches.size(), mesh.getNumVertices() / verticesPerImage * 6);
    caches.add(currentCache);
    mesh.getVerticesBuffer().compact();
}

void SpriteCache::beginCache (int cacheID) {
    if (currentCache != null) throw new IllegalStateException("endCache must be called before begin.");
    if (cacheID == caches.size() - 1) {
        caches.remove(cacheID);
        beginCache();
        return;
    }
    currentCache = caches.get(cacheID);
    mesh.getVerticesBuffer().position(currentCache.offset);
}

int SpriteCache::endCache () {
    if (currentCache == null) throw new IllegalStateException("beginCache must be called before endCache.");

    Cache cache = currentCache;
    int cacheCount = mesh.getVerticesBuffer().position() - cache.offset;
    if (cache.textures == null) {
        // New cache.
        cache.maxCount = cacheCount;
        cache.textures = textures.toArray(new Texture[textures.size()]);
        cache.counts = new int[counts.size()];
        for (int i = 0, n = counts.size(); i < n; i++)
            cache.counts[i] = counts.get(i);

        mesh.getVerticesBuffer().flip();
    } else {
        // Redefine existing cache.
        if (cacheCount > cache.maxCount) {
            throw new GdxRuntimeException(
                "If a cache is not the last created, it cannot be redefined with more entries than when it was first created: "
                + cacheCount + " (" + cache.maxCount + " max)");
        }

        if (cache.textures.length < textures.size()) cache.textures = new Texture[textures.size()];
        for (int i = 0, n = textures.size(); i < n; i++)
            cache.textures[i] = textures.get(i);

        if (cache.counts.length < counts.size()) cache.counts = new int[counts.size()];
        for (int i = 0, n = counts.size(); i < n; i++)
            cache.counts[i] = counts.get(i);

        FloatBuffer vertices = mesh.getVerticesBuffer();
        vertices.position(0);
        Cache lastCache = caches.get(caches.size() - 1);
        vertices.limit(lastCache.offset + lastCache.maxCount);
    }

    currentCache = null;
    textures.clear();
    counts.clear();

    return cache.id;
}

void SpriteCache::clear () {
    caches.clear();
    mesh.getVerticesBuffer().clear().flip();
}

void SpriteCache::add (const gdx_cpp::graphics::Texture& texture,int offset,int length) {
    if (currentCache == null) throw new IllegalStateException("beginCache must be called before add.");

    int verticesPerImage = mesh.getNumIndices() > 0 ? 4 : 6;
    int count = length / (verticesPerImage * VERTEX_SIZE) * 6;
    int lastIndex = textures.size() - 1;
    if (lastIndex < 0 || textures.get(lastIndex) != texture) {
        textures.add(texture);
        counts.add(count);
    } else
        counts.set(lastIndex, counts.get(lastIndex) + count);

    mesh.getVerticesBuffer().put(vertices, offset, length);
}

void SpriteCache::add (const gdx_cpp::graphics::Texture& texture,float x,float y) {
    final float fx2 = x + texture.getWidth();
    final float fy2 = y + texture.getHeight();

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

    if (mesh.getNumIndices() > 0) {
        tempVertices[15] = fx2;
        tempVertices[16] = y;
        tempVertices[17] = color;
        tempVertices[18] = 1;
        tempVertices[19] = 1;
        add(texture, tempVertices, 0, 20);
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
        add(texture, tempVertices, 0, 30);
    }
}

void SpriteCache::add (const gdx_cpp::graphics::Texture& texture,float x,float y,int srcWidth,int srcHeight,float u,float v,float u2,float v2,float color) {
    final float fx2 = x + srcWidth;
    final float fy2 = y + srcHeight;

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

    if (mesh.getNumIndices() > 0) {
        tempVertices[15] = fx2;
        tempVertices[16] = y;
        tempVertices[17] = color;
        tempVertices[18] = u2;
        tempVertices[19] = v;
        add(texture, tempVertices, 0, 20);
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
        add(texture, tempVertices, 0, 30);
    }
}

void SpriteCache::add (const gdx_cpp::graphics::Texture& texture,float x,float y,int srcX,int srcY,int srcWidth,int srcHeight) {
    float invTexWidth = 1.0f / texture.getWidth();
    float invTexHeight = 1.0f / texture.getHeight();
    final float u = srcX * invTexWidth;
    final float v = (srcY + srcHeight) * invTexHeight;
    final float u2 = (srcX + srcWidth) * invTexWidth;
    final float v2 = srcY * invTexHeight;
    final float fx2 = x + srcWidth;
    final float fy2 = y + srcHeight;

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

    if (mesh.getNumIndices() > 0) {
        tempVertices[15] = fx2;
        tempVertices[16] = y;
        tempVertices[17] = color;
        tempVertices[18] = u2;
        tempVertices[19] = v;
        add(texture, tempVertices, 0, 20);
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
        add(texture, tempVertices, 0, 30);
    }
}

void SpriteCache::add (const gdx_cpp::graphics::Texture& texture,float x,float y,float width,float height,int srcX,int srcY,int srcWidth,int srcHeight,bool flipX,bool flipY) {

    float invTexWidth = 1.0f / texture.getWidth();
    float invTexHeight = 1.0f / texture.getHeight();
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

    if (mesh.getNumIndices() > 0) {
        tempVertices[15] = fx2;
        tempVertices[16] = y;
        tempVertices[17] = color;
        tempVertices[18] = u2;
        tempVertices[19] = v;
        add(texture, tempVertices, 0, 20);
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
        add(texture, tempVertices, 0, 30);
    }
}

void SpriteCache::add (const gdx_cpp::graphics::Texture& texture,float x,float y,float originX,float originY,float width,float height,float scaleX,float scaleY,float rotation,int srcX,int srcY,int srcWidth,int srcHeight,bool flipX,bool flipY) {

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

    float invTexWidth = 1.0f / texture.getWidth();
    float invTexHeight = 1.0f / texture.getHeight();
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

    if (mesh.getNumIndices() > 0) {
        tempVertices[15] = x4;
        tempVertices[16] = y4;
        tempVertices[17] = color;
        tempVertices[18] = u2;
        tempVertices[19] = v;
        add(texture, tempVertices, 0, 20);
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
        add(texture, tempVertices, 0, 30);
    }
}

void SpriteCache::add (const TextureRegion& region,float x,float y) {
    add(region, x, y, region.getRegionWidth(), region.getRegionHeight());
}

void SpriteCache::add (const TextureRegion& region,float x,float y,float width,float height) {
    final float fx2 = x + width;
    final float fy2 = y + height;
    final float u = region.u;
    final float v = region.v2;
    final float u2 = region.u2;
    final float v2 = region.v;

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

    if (mesh.getNumIndices() > 0) {
        tempVertices[15] = fx2;
        tempVertices[16] = y;
        tempVertices[17] = color;
        tempVertices[18] = u2;
        tempVertices[19] = v;
        add(region.texture, tempVertices, 0, 20);
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
        add(region.texture, tempVertices, 0, 30);
    }
}

void SpriteCache::add (const TextureRegion& region,float x,float y,float originX,float originY,float width,float height,float scaleX,float scaleY,float rotation) {

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

    if (mesh.getNumIndices() > 0) {
        tempVertices[15] = x4;
        tempVertices[16] = y4;
        tempVertices[17] = color;
        tempVertices[18] = u2;
        tempVertices[19] = v;
        add(region.texture, tempVertices, 0, 20);
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
        add(region.texture, tempVertices, 0, 30);
    }
}

void SpriteCache::add (const Sprite& sprite) {
    if (mesh.getNumIndices() > 0) {
        add(sprite.getTexture(), sprite.getVertices(), 0, SPRITE_SIZE);
        return;
    }

    float[] spriteVertices = sprite.getVertices();
    System.arraycopy(spriteVertices, 0, tempVertices, 0, 3 * VERTEX_SIZE); // temp0,1,2=sprite0,1,2
    System.arraycopy(spriteVertices, 2 * VERTEX_SIZE, tempVertices, 3 * VERTEX_SIZE, VERTEX_SIZE); // temp3=sprite2
    System.arraycopy(spriteVertices, 3 * VERTEX_SIZE, tempVertices, 4 * VERTEX_SIZE, VERTEX_SIZE); // temp4=sprite3
    System.arraycopy(spriteVertices, 0, tempVertices, 5 * VERTEX_SIZE, VERTEX_SIZE); // temp5=sprite0
    add(sprite.getTexture(), tempVertices, 0, 30);
}

void SpriteCache::begin () {
    if (drawing) throw new IllegalStateException("end must be called before begin.");

    if (Gdx.graphics.isGL20Available() == false) {
        GL10 gl = Gdx.gl10;
        gl.glDepthMask(false);
        gl.glEnable(GL10.GL_TEXTURE_2D);

        gl.glMatrixMode(GL10.GL_PROJECTION);
        gl.glLoadMatrixf(projectionMatrix.val, 0);
        gl.glMatrixMode(GL10.GL_MODELVIEW);
        gl.glLoadMatrixf(transformMatrix.val, 0);

        mesh.bind();
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

        mesh.bind(shader);
    }
    drawing = true;
}

void SpriteCache::end () {
    if (!drawing) throw new IllegalStateException("begin must be called before end.");
    drawing = false;

    if (Gdx.graphics.isGL20Available() == false) {
        GL10 gl = Gdx.gl10;
        gl.glDepthMask(true);
        gl.glDisable(GL10.GL_TEXTURE_2D);
        mesh.unbind();
    } else {
        shader.end();
        GL20 gl = Gdx.gl20;
        gl.glDepthMask(true);
        gl.glDisable(GL20.GL_TEXTURE_2D);
        mesh.unbind(shader);
    }
}

void SpriteCache::draw (int cacheID) {
    if (!drawing) throw new IllegalStateException("SpriteCache.begin must be called before draw.");

    Cache cache = caches.get(cacheID);
    int offset = cache.offset;
    Texture[] textures = cache.textures;
    int[] counts = cache.counts;
    if (Gdx.graphics.isGL20Available()) {
        for (int i = 0, n = textures.length; i < n; i++) {
            int count = counts[i];
            textures[i].bind();
            if (customShader != null)
                mesh.render(customShader, GL10.GL_TRIANGLES, offset, count);
            else
                mesh.render(shader, GL10.GL_TRIANGLES, offset, count);
            offset += count;
        }
    } else {
        for (int i = 0, n = textures.length; i < n; i++) {
            int count = counts[i];
            textures[i].bind();
            mesh.render(GL10.GL_TRIANGLES, offset, count);
            offset += count;
        }
    }
}

void SpriteCache::draw (int cacheID,int offset,int length) {
    if (!drawing) throw new IllegalStateException("SpriteCache.begin must be called before draw.");

    Cache cache = caches.get(cacheID);
    offset = offset * 6 + cache.offset;
    length *= 6;
    Texture[] textures = cache.textures;
    int[] counts = cache.counts;
    if (Gdx.graphics.isGL20Available()) {
        for (int i = 0, n = textures.length; i < n; i++) {
            textures[i].bind();
            int count = counts[i];
            if (count > length) {
                i = n;
                count = length;
            } else
                length -= count;
            if (customShader != null)
                mesh.render(customShader, GL10.GL_TRIANGLES, offset, count);
            else
                mesh.render(shader, GL10.GL_TRIANGLES, offset, count);
            offset += count;
        }
    } else {
        for (int i = 0, n = textures.length; i < n; i++) {
            textures[i].bind();
            int count = counts[i];
            if (count > length) {
                i = n;
                count = length;
            } else
                length -= count;
            mesh.render(GL10.GL_TRIANGLES, offset, count);
            offset += count;
        }
    }
}

void SpriteCache::dispose () {
    mesh.dispose();
    if (shader != null) shader.dispose();
}

gdx_cpp::math::Matrix4& SpriteCache::getProjectionMatrix () {
    return projectionMatrix;
}

void SpriteCache::setProjectionMatrix (const gdx_cpp::math::Matrix4& projection) {
    if (drawing) throw new IllegalStateException("Can't set the matrix within begin/end.");
    projectionMatrix.set(projection);
}

gdx_cpp::math::Matrix4& SpriteCache::getTransformMatrix () {
    return transformMatrix;
}

void SpriteCache::setTransformMatrix (const gdx_cpp::math::Matrix4& transform) {
    if (drawing) throw new IllegalStateException("Can't set the matrix within begin/end.");
    transformMatrix.set(transform);
}

void SpriteCache::setShader (const gdx_cpp::graphics::glutils::ShaderProgram& shader) {
    customShader = shader;
}

