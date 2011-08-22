
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

#include "FrameBuffer.hpp"

using namespace gdx_cpp::graphics::glutils;

void FrameBuffer::build () {
    colorTexture = new Texture(width, height, format);
    colorTexture.setFilter(TextureFilter.Linear, TextureFilter.Linear);
    colorTexture.setWrap(TextureWrap.ClampToEdge, TextureWrap.ClampToEdge);
    GL20 gl = Gdx.graphics.getGL20();

    ByteBuffer tmp = ByteBuffer.allocateDirect(4);
    tmp.order(ByteOrder.nativeOrder());
    IntBuffer handle = tmp.asIntBuffer();

    gl.glGenFramebuffers(1, handle);
    framebufferHandle = handle.get(0);

    if (hasDepth) {
        gl.glGenRenderbuffers(1, handle);
        depthbufferHandle = handle.get(0);
    }

    gl.glBindTexture(GL20.GL_TEXTURE_2D, colorTexture.getTextureObjectHandle());

    if (hasDepth) {
        gl.glBindRenderbuffer(GL20.GL_RENDERBUFFER, depthbufferHandle);
        gl.glRenderbufferStorage(GL20.GL_RENDERBUFFER, GL20.GL_DEPTH_COMPONENT16, colorTexture.getWidth(),
                                 colorTexture.getHeight());
    }

    gl.glBindFramebuffer(GL20.GL_FRAMEBUFFER, framebufferHandle);
    gl.glFramebufferTexture2D(GL20.GL_FRAMEBUFFER, GL20.GL_COLOR_ATTACHMENT0, GL20.GL_TEXTURE_2D,
                              colorTexture.getTextureObjectHandle(), 0);
    if (hasDepth) {
        gl.glFramebufferRenderbuffer(GL20.GL_FRAMEBUFFER, GL20.GL_DEPTH_ATTACHMENT, GL20.GL_RENDERBUFFER, depthbufferHandle);
    }
    int result = gl.glCheckFramebufferStatus(GL20.GL_FRAMEBUFFER);

    gl.glBindRenderbuffer(GL20.GL_RENDERBUFFER, 0);
    gl.glBindTexture(GL20.GL_TEXTURE_2D, 0);
    gl.glBindFramebuffer(GL20.GL_FRAMEBUFFER, 0);

    if (result != GL20.GL_FRAMEBUFFER_COMPLETE) {
        colorTexture.dispose();
        if (hasDepth) {
            handle.put(depthbufferHandle);
            handle.flip();
            gl.glDeleteRenderbuffers(1, handle);
        }

        colorTexture.dispose();
        handle.put(framebufferHandle);
        handle.flip();
        gl.glDeleteFramebuffers(1, handle);

        if (result == GL20.GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT)
            throw new IllegalStateException("frame buffer couldn't be constructed: incomplete attachment");
        if (result == GL20.GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS)
            throw new IllegalStateException("frame buffer couldn't be constructed: incomplete dimensions");
        if (result == GL20.GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT)
            throw new IllegalStateException("frame buffer couldn't be constructed: missing attachment");
    }
}

void FrameBuffer::dispose () {
    GL20 gl = Gdx.graphics.getGL20();

    ByteBuffer tmp = ByteBuffer.allocateDirect(4);
    tmp.order(ByteOrder.nativeOrder());
    IntBuffer handle = tmp.asIntBuffer();

    colorTexture.dispose();
    if (hasDepth) {
        handle.put(depthbufferHandle);
        handle.flip();
        gl.glDeleteRenderbuffers(1, handle);
    }

    handle.put(framebufferHandle);
    handle.flip();
    gl.glDeleteFramebuffers(1, handle);

    if (buffers.get(Gdx.app) != null) buffers.get(Gdx.app).remove(this);
}

void FrameBuffer::begin () {
    Gdx.graphics.getGL20().glViewport(0, 0, colorTexture.getWidth(), colorTexture.getHeight());
    Gdx.graphics.getGL20().glBindFramebuffer(GL20.GL_FRAMEBUFFER, framebufferHandle);
}

void FrameBuffer::end () {
    Gdx.graphics.getGL20().glViewport(0, 0, Gdx.graphics.getWidth(), Gdx.graphics.getHeight());
    Gdx.graphics.getGL20().glBindFramebuffer(GL20.GL_FRAMEBUFFER, 0);
}

void FrameBuffer::addManagedFrameBuffer (const gdx_cpp::Application& app,const FrameBuffer& frameBuffer) {
    List<FrameBuffer> managedResources = buffers.get(app);
    if (managedResources == null) managedResources = new ArrayList<FrameBuffer>();
    managedResources.add(frameBuffer);
    buffers.put(app, managedResources);
}

void FrameBuffer::invalidateAllFrameBuffers (const gdx_cpp::Application& app) {
    if (Gdx.graphics.getGL20() == null) return;

    List<FrameBuffer> bufferList = buffers.get(app);
    if (bufferList == null) return;
    for (int i = 0; i < bufferList.size(); i++) {
        bufferList.get(i).build();
    }
}

void FrameBuffer::clearAllFrameBuffers (const gdx_cpp::Application& app) {
    buffers.remove(app);
}

std::string& FrameBuffer::getManagedStatus () {
    StringBuilder builder = new StringBuilder();
    int i = 0;
    builder.append("Managed buffers/app: { ");
for (Application app : buffers.keySet()) {
        builder.append(buffers.get(app).size());
        builder.append(" ");
    }
    builder.append("}");
    return builder.toString();
}

gdx_cpp::graphics::Texture& FrameBuffer::getColorBufferTexture () {
    return colorTexture;
}

int FrameBuffer::getHeight () {
    return colorTexture.getHeight();
}

int FrameBuffer::getWidth () {
    return colorTexture.getWidth();
}

