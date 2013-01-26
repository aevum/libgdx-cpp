
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

#include <stddef.h>
#include <memory>
#include <ostream>
#include <unordered_map>
#include <utility>

#include "FrameBuffer.hpp"
#include "gdx-cpp/gl.hpp"
#include "gdx-cpp/Gdx.hpp"
#include "gdx-cpp/Graphics.hpp"
#include "gdx-cpp/Log.hpp"
#include "gdx-cpp/graphics/GL20.hpp"

namespace gdx {
class Application;
}  // namespace gdx

using namespace gdx;

FrameBuffer::buffer_map FrameBuffer::buffers;

void FrameBuffer::build () {
    colorTexture = Texture::ptr(new Texture(width, height, format, Pixmap::PixmapType::PixmapType_Gdx2d));
    colorTexture->setFilter(Texture::TextureFilter::Linear, Texture::TextureFilter::Linear);
    colorTexture->setWrap(Texture::TextureWrap::ClampToEdge, Texture::TextureWrap::ClampToEdge);

    GL20& gl = *gl20;

    int handle;
    gl.glGenFramebuffers(1, (unsigned int*) &handle);
    framebufferHandle = handle;

    if (hasDepth) {
        gl.glGenRenderbuffers(1, (unsigned int*)&handle);
        depthbufferHandle = handle;
    }

    gl.glBindTexture(GL_TEXTURE_2D, colorTexture->getTextureObjectHandle());

    if (hasDepth) {
        gl.glBindRenderbuffer(GL_RENDERBUFFER, depthbufferHandle);
        gl.glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, colorTexture->getWidth(),
                                 colorTexture->getHeight());
    }

    gl.glBindFramebuffer(GL_FRAMEBUFFER, framebufferHandle);
    gl.glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                              colorTexture->getTextureObjectHandle(), 0);
    if (hasDepth) {
        gl.glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthbufferHandle);
    }
    int result = gl.glCheckFramebufferStatus(GL_FRAMEBUFFER);

    gl.glBindRenderbuffer(GL_RENDERBUFFER, 0);
    gl.glBindTexture(GL_TEXTURE_2D, 0);
    gl.glBindFramebuffer(GL_FRAMEBUFFER, 0);

    if (result != GL_FRAMEBUFFER_COMPLETE) {
        colorTexture.reset();
        if (hasDepth) {
            handle = depthbufferHandle;
            gl.glDeleteRenderbuffers(1, (const unsigned int*) &handle);
        }

        handle = framebufferHandle;
        
        gl.glDeleteFramebuffers(1, (const unsigned int*) &handle);

        if (result == GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT)
            gdx_log_error("gdx","frame buffer couldn't be constructed: incomplete attachment");        
        if (result == GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT)
            gdx_log_error("gdx","frame buffer couldn't be constructed: missing attachment");
    }
}

void FrameBuffer::dispose () {
    GL20& gl = *gl20;

    int handle = 0;

    colorTexture.reset();
    if (hasDepth) {
        handle = depthbufferHandle;
        gl.glDeleteRenderbuffers(1, (const unsigned int*) &handle);
    }

    handle = framebufferHandle;
    
    gl.glDeleteFramebuffers(1, (const unsigned int*) &handle);

    if (buffers.count(app) > 0) buffers[app].erase(this);
}

void FrameBuffer::begin () {
    gl20->glViewport(0, 0, colorTexture->getWidth(), colorTexture->getHeight());
    gl20->glBindFramebuffer(GL_FRAMEBUFFER, framebufferHandle);
}

void FrameBuffer::end () {
    gl20->glViewport(0, 0, graphics->getWidth(), graphics->getHeight());
    gl20->glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::addManagedFrameBuffer (Application* app,
                                         FrameBuffer* frameBuffer) {
    buffers[app].insert(frameBuffer);
}

void FrameBuffer::invalidateAllFrameBuffers (Application* app) {
    if (gl20 == NULL) return;

    buffer_map::value_type::second_type::iterator it = buffers[app].begin();
    buffer_map::value_type::second_type::iterator end = buffers[app].end();
       
    for (; it != end; ++it) {
        (*it)->build();
    }
}

void FrameBuffer::clearAllFrameBuffers (Application* app) {
    buffer_map::value_type::second_type::iterator it = buffers[app].begin();
    buffer_map::value_type::second_type::iterator end = buffers[app].end();

    for (; it != end; it++) {
        delete *it;
    }
    
    buffers.erase(app);
}

std::string FrameBuffer::getManagedStatus () {
    std::stringstream builder;
    builder << "Managed buffers/app: { ";

    buffer_map::iterator it = buffers.begin();
    buffer_map::iterator end = buffers.end();
    
    for (; it != end; ++it) {
        builder << buffers[it->first].size();
        builder << " ";
    }
    
    builder << "}";
    return builder.str();
}

Texture::ptr FrameBuffer::getColorBufferTexture () {
    return colorTexture;
}

int FrameBuffer::getHeight () {
    return colorTexture->getHeight();
}

int FrameBuffer::getWidth () {
    return colorTexture->getWidth();
}

FrameBuffer::FrameBuffer(const Pixmap::Format& format, int width, int height, bool hasDepth)
 :
 width(width),
height(height),
hasDepth(hasDepth),
format(format) {
    build();
    addManagedFrameBuffer(app, this);
}


