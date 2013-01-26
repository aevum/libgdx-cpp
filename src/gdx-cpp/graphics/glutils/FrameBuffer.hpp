
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

#ifndef GDX_CPP_GRAPHICS_GLUTILS_FRAMEBUFFER_HPP_
#define GDX_CPP_GRAPHICS_GLUTILS_FRAMEBUFFER_HPP_

#include <set>
#include <string>

#include "gdx-cpp/graphics/Pixmap.hpp"
#include "gdx-cpp/graphics/Texture.hpp"
#include "gdx-cpp/internal/memory"
#include "gdx-cpp/internal/unordered_map"
#include "gdx-cpp/utils/Disposable.hpp"

namespace gdx {

class Application;

class FrameBuffer:
    public Disposable {
public:
    typedef ref_ptr_maker<FrameBuffer>::shared_ptr_t ptr;
    
    FrameBuffer (const Pixmap::Format& format, int width, int height, bool hasDepth) ;
    
    void dispose ();
    void begin ();
    void end ();
    static void invalidateAllFrameBuffers (Application* app);
    static void clearAllFrameBuffers (Application* app);
    std::string getManagedStatus ();
    Texture::ptr getColorBufferTexture ();
    int getHeight ();
    int getWidth ();

private:
    typedef gdx_unordered_map<Application*, std::set < FrameBuffer* > > buffer_map;
    static buffer_map buffers;
    void build ();
    void addManagedFrameBuffer (Application* app, FrameBuffer* frameBuffer);
    Texture::ptr colorTexture;  
    int framebufferHandle;
    int depthbufferHandle;
    int width;
    int height;
    bool hasDepth;
    Pixmap::Format format;
};

} // namespace gdx

#endif // GDX_CPP_GRAPHICS_GLUTILS_FRAMEBUFFER_HPP_
