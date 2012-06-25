
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

#include "ScreenUtils.hpp"

using namespace gdx::utils;

gdx::TextureRegion& ScreenUtils::getFrameBufferTexture () {
    final int w = Gdx.graphics.getWidth();
    final int h = Gdx.graphics.getHeight();
    return getFrameBufferTexture(0, 0, w, h);
}

gdx::TextureRegion& ScreenUtils::getFrameBufferTexture (int x,int y,int w,int h) {
    final int potW = MathUtils.nextPowerOfTwo(w);
    final int potH = MathUtils.nextPowerOfTwo(h);

    final Pixmap pixmap = new Pixmap(potW, potH, Format.RGBA8888);
    ByteBuffer pixels = pixmap.getPixels();
    Gdx.gl.glReadPixels(x, y, potW, potH, GL10.GL_RGBA, GL10.GL_UNSIGNED_BYTE, pixels);

    Texture texture = new Texture(pixmap);
    TextureRegion textureRegion = new TextureRegion(texture, 0, h, w, -h);
    pixmap.dispose();

    return textureRegion;
}

char* ScreenUtils::getFrameBufferPixels (bool flipY) {
    final int w = Gdx.graphics.getWidth();
    final int h = Gdx.graphics.getHeight();
    return getFrameBufferPixels(0, 0, w, h, flipY);
}

char* ScreenUtils::getFrameBufferPixels (int x,int y,int w,int h,bool flipY) {
    final ByteBuffer pixels = BufferUtils.newByteBuffer(w * h * 4);
    Gdx.gl.glReadPixels(x, y, w, h, GL10.GL_RGBA, GL10.GL_UNSIGNED_BYTE, pixels);
    final int numBytes = w * h * 4;
    byte[] lines = new byte[numBytes];
    if (flipY) {
        final int numBytesPerLine = w * 4;
        for (int i = 0; i < h; i++) {
            pixels.position((h - i - 1) * numBytesPerLine);
            pixels.get(lines, i * numBytesPerLine, numBytesPerLine);
        }
    } else {
        pixels.clear();
        pixels.get(lines);
    }
    return lines;

}

