
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

namespace gdx_cpp {
namespace graphics {
namespace glutils {

class FrameBuffer: public gdx_cpp::utils::Disposable {
public:
    void dispose ();
    void begin ();
    void end ();
    static void invalidateAllFrameBuffers (const gdx_cpp::Application& app);
    static void clearAllFrameBuffers (const gdx_cpp::Application& app);
    static std::string& getManagedStatus ();
    gdx_cpp::graphics::Texture& getColorBufferTexture ();
    int getHeight ();
    int getWidth ();

protected:


private:
    void build ();
    void addManagedFrameBuffer (const gdx_cpp::Application& app,const FrameBuffer& frameBuffer);
    int width;
    int height;
    boolean hasDepth;
    Pixmap.Format format;
};

} // namespace gdx_cpp
} // namespace graphics
} // namespace glutils

#endif // GDX_CPP_GRAPHICS_GLUTILS_FRAMEBUFFER_HPP_
