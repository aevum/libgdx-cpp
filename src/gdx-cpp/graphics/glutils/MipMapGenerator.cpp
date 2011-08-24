
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

#include "MipMapGenerator.hpp"

#include "gdx-cpp/graphics/Pixmap.hpp"
#include "gdx-cpp/graphics/GL20.hpp"
#include "gdx-cpp/graphics/GL10.hpp"
#include "gdx-cpp/Application.hpp"
#include "gdx-cpp/Gdx.hpp"

using namespace gdx_cpp;
using namespace gdx_cpp::graphics;
using namespace gdx_cpp::graphics::glutils;

bool MipMapGenerator::useHWMipMap = true;

void MipMapGenerator::setUseHardwareMipMap (bool useHWMipMap) {
    MipMapGenerator::useHWMipMap = useHWMipMap;
}

void MipMapGenerator::generateMipMap (gdx_cpp::graphics::Pixmap& pixmap,int textureWidth,int textureHeight,bool disposePixmap) {
    if (!useHWMipMap) {
        generateMipMapCPU(pixmap, textureWidth, textureHeight, disposePixmap);
        return;
    }

    if (gdx_cpp::Gdx::app.getType() == gdx_cpp::Application::Android) {
        if (gdx_cpp::Gdx::graphics.isGL20Available())
            generateMipMapGLES20(pixmap, disposePixmap);
        else
            generateMipMapCPU(pixmap, textureWidth, textureHeight, disposePixmap);
    } else {
        generateMipMapDesktop(pixmap, textureWidth, textureHeight, disposePixmap);
    }
}

void MipMapGenerator::generateMipMapGLES20 (gdx_cpp::graphics::Pixmap& pixmap,bool disposePixmap) {
    Gdx::gl->glTexImage2D(GL20::GL_TEXTURE_2D, 0, pixmap.getGLInternalFormat(), pixmap.getWidth(), pixmap.getHeight(), 0,
                        pixmap.getGLFormat(), pixmap.getGLType(), pixmap.getPixels());
    Gdx::gl20->glGenerateMipmap(GL20::GL_TEXTURE_2D);
    if (disposePixmap) pixmap.dispose();
}

void MipMapGenerator::generateMipMapDesktop (gdx_cpp::graphics::Pixmap& pixmap,int textureWidth,int textureHeight,bool disposePixmap) {
    if (Gdx::graphics.isGL20Available()
            && (Gdx::graphics.supportsExtension("GL_ARB_framebuffer_object") || Gdx::graphics
                .supportsExtension("GL_EXT_framebuffer_object"))) {
        Gdx::gl->glTexImage2D(GL20::GL_TEXTURE_2D, 0, pixmap.getGLInternalFormat(), pixmap.getWidth(), pixmap.getHeight(), 0,
                            pixmap.getGLFormat(), pixmap.getGLType(), pixmap.getPixels());
        Gdx::gl20->glGenerateMipmap(GL20::GL_TEXTURE_2D);
        if (disposePixmap) pixmap.dispose();
    } else if (Gdx::graphics.supportsExtension("GL_SGIS_generate_mipmap")) {
        if ((Gdx::gl20 == NULL) && textureWidth != textureHeight) {
            Gdx::app.error("MipMapGenerator.cpp") << "texture width and height must be square when using mipmapping in OpenGL ES 1.x";
        }
        
        Gdx::gl->glTexParameterf(GL20::GL_TEXTURE_2D, GLCommon::GL_GENERATE_MIPMAP, GL10::GL_TRUE);
        Gdx::gl->glTexImage2D(GL20::GL_TEXTURE_2D, 0, pixmap.getGLInternalFormat(), pixmap.getWidth(), pixmap.getHeight(), 0,
                            pixmap.getGLFormat(), pixmap.getGLType(), pixmap.getPixels());
        if (disposePixmap) pixmap.dispose();
    } else {
        generateMipMapCPU(pixmap, textureWidth, textureHeight, disposePixmap);
    }
}

void MipMapGenerator::generateMipMapCPU (Pixmap& pixmap,int textureWidth,int textureHeight,bool disposePixmap) {
    Gdx::gl->glTexImage2D(GL10::GL_TEXTURE_2D, 0, pixmap.getGLInternalFormat(), pixmap.getWidth(), pixmap.getHeight(), 0,
                        pixmap.getGLFormat(), pixmap.getGLType(), pixmap.getPixels());
    if ((Gdx::gl20 == NULL) && textureWidth != textureHeight) { 
        Gdx::app.error("MipMapGenerator.cpp") << "texture width and height must be square when using mipmapping.";
    }
    
    int width = pixmap.getWidth() / 2;
    int height = pixmap.getHeight() / 2;
    int level = 1;
    
    while (width > 0 && height > 0) {
        Pixmap tmp(width, height, pixmap.getFormat());
        tmp.drawPixmap(pixmap, 0, 0, pixmap.getWidth(), pixmap.getHeight(), 0, 0, width, height);
        if (level > 1 || disposePixmap) pixmap.dispose();
        pixmap = tmp;

        Gdx::gl->glTexImage2D(GL10::GL_TEXTURE_2D, level, pixmap.getGLInternalFormat(), pixmap.getWidth(), pixmap.getHeight(), 0,
                            pixmap.getGLFormat(), pixmap.getGLType(), pixmap.getPixels());

        width = pixmap.getWidth() / 2;
        height = pixmap.getHeight() / 2;
        level++;
    }
    pixmap.dispose();
}

