
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

#include <stddef.h>
#include <memory>

#include "MipMapGenerator.hpp"
#include "gdx-cpp/Application.hpp"
#include "gdx-cpp/Gdx.hpp"
#include "gdx-cpp/Graphics.hpp"
#include "gdx-cpp/Log.hpp"
#include "gdx-cpp/graphics/Pixmap.hpp"
#include "gdx-cpp/graphics/GLCommon.hpp"

#include <gdx-cpp/graphics/GL20.hpp>
using namespace gdx;

bool MipMapGenerator::useHWMipMap = true;

void MipMapGenerator::setUseHardwareMipMap (bool useHWMipMap) {
    MipMapGenerator::useHWMipMap = useHWMipMap;
}

void MipMapGenerator::generateMipMap (Pixmap::ptr pixmap,int textureWidth,int textureHeight,bool disposePixmap) {
    if (!useHWMipMap) {
        generateMipMapCPU(pixmap, textureWidth, textureHeight, disposePixmap);
        return;
    }

    if (app->getType() == Application::Android) {
        if (graphics->isGL20Available())
            generateMipMapGLES20(pixmap, disposePixmap);
        else
            generateMipMapCPU(pixmap, textureWidth, textureHeight, disposePixmap);
    } else {
        generateMipMapDesktop(pixmap, textureWidth, textureHeight, disposePixmap);
    }
}

void MipMapGenerator::generateMipMapGLES20 (Pixmap::ptr pixmap,bool disposePixmap) {
    gl->glTexImage2D(GL10::GL_TEXTURE_2D, 0, pixmap->getGLInternalFormat(), pixmap->getWidth(), pixmap->getHeight(), 0,
                        pixmap->getGLFormat(), pixmap->getGLType(), pixmap->getPixels());
    gl20->glGenerateMipmap(GL10::GL_TEXTURE_2D);
    if (disposePixmap) pixmap->dispose();
}

void MipMapGenerator::generateMipMapDesktop (Pixmap::ptr pixmap,int textureWidth,int textureHeight,bool disposePixmap) {
    if (graphics->isGL20Available()
            && (graphics->supportsExtension("GL_ARB_framebuffer_object") || graphics
                ->supportsExtension("GL_EXT_framebuffer_object"))) {
        gl->glTexImage2D(GL10::GL_TEXTURE_2D, 0, pixmap->getGLInternalFormat(), pixmap->getWidth(), pixmap->getHeight(), 0,
                            pixmap->getGLFormat(), pixmap->getGLType(), pixmap->getPixels());
        gl20->glGenerateMipmap(GL10::GL_TEXTURE_2D);
        if (disposePixmap) pixmap->dispose();
    } else if (graphics->supportsExtension("GL_SGIS_generate_mipmap")) {
        if ((gl20 == NULL) && textureWidth != textureHeight) {
            gdx_log_error("gdx","texture width and height must be square when using mipmapping in OpenGL ES 1.x");
        }
        
        gl->glTexParameterf(GL10::GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL10::GL_TRUE);
        gl->glTexImage2D(GL10::GL_TEXTURE_2D, 0, pixmap->getGLInternalFormat(), pixmap->getWidth(), pixmap->getHeight(), 0,
                            pixmap->getGLFormat(), pixmap->getGLType(), pixmap->getPixels());
        if (disposePixmap) pixmap->dispose();
    } else {
        generateMipMapCPU(pixmap, textureWidth, textureHeight, disposePixmap);
    }
}

void MipMapGenerator::generateMipMapCPU (Pixmap::ptr pixmap,int textureWidth,int textureHeight,bool disposePixmap) {
    gl->glTexImage2D(GL10::GL_TEXTURE_2D, 0, pixmap->getGLInternalFormat(), pixmap->getWidth(), pixmap->getHeight(), 0,
                        pixmap->getGLFormat(), pixmap->getGLType(), pixmap->getPixels());
    if ((gl20 == NULL) && textureWidth != textureHeight) { 
        gdx_log_error("gdx","texture width and height must be square when using mipmapping.");
    }
    
    int width = pixmap->getWidth() / 2;
    int height = pixmap->getHeight() / 2;
    int level = 1;
    
    while (width > 0 && height > 0) {
        Pixmap::ptr tmp(Pixmap::newFromRect(width, height, pixmap->getFormat(), pixmap->getType()));
        tmp->drawPixmap(*pixmap, 0, 0, pixmap->getWidth(), pixmap->getHeight(), 0, 0, width, height);
        if (level > 1 || disposePixmap) pixmap->dispose();

        pixmap.swap(tmp);

        gl->glTexImage2D(GL10::GL_TEXTURE_2D, level, pixmap->getGLInternalFormat(), pixmap->getWidth(), pixmap->getHeight(), 0,
                            pixmap->getGLFormat(), pixmap->getGLType(), pixmap->getPixels());

        width = pixmap->getWidth() / 2;
        height = pixmap->getHeight() / 2;
        level++;
    }
    
    pixmap->dispose();
}

