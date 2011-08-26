
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

#ifndef GDX_CPP_GRAPHICS_G2D_SPRITEBATCH_HPP_
#define GDX_CPP_GRAPHICS_G2D_SPRITEBATCH_HPP_

#include "gdx-cpp/graphics/Texture.hpp"

namespace gdx_cpp {
namespace graphics {
namespace g2d {

class SpriteBatch: public gdx_cpp::utils::Disposable {
public:
    void begin ();
    void end ();
    void setColor (const gdx_cpp::graphics::Color& tint);
    void setColor (float r,float g,float b,float a);
    void setColor (float color);
    gdx_cpp::graphics::Color& getColor ();
    void draw (const gdx_cpp::graphics::Texture& texture,float x,float y,float originX,float originY,float width,float height,float scaleX,float scaleY,float rotation,int srcX,int srcY,int srcWidth,int srcHeight,bool flipX,bool flipY);
    void draw (const gdx_cpp::graphics::Texture& texture,float x,float y,float width,float height,int srcX,int srcY,int srcWidth,int srcHeight,bool flipX,bool flipY);
    void draw (const gdx_cpp::graphics::Texture& texture,float x,float y,int srcX,int srcY,int srcWidth,int srcHeight);
    void draw (const gdx_cpp::graphics::Texture& texture,float x,float y,float width,float height,float u,float v,float u2,float v2);
    void draw (const gdx_cpp::graphics::Texture& texture,float x,float y);
    void draw (const gdx_cpp::graphics::Texture& texture,float x,float y,float width,float height);
    void draw (const gdx_cpp::graphics::Texture& texture,int offset,int length);
    void draw (const TextureRegion& region,float x,float y);
    void draw (const TextureRegion& region,float x,float y,float width,float height);
    void draw (const TextureRegion& region,float x,float y,float originX,float originY,float width,float height,float scaleX,float scaleY,float rotation);
    void draw (const TextureRegion& region,float x,float y,float originX,float originY,float width,float height,float scaleX,float scaleY,float rotation,bool clockwise);
    void flush ();
    void disableBlending ();
    void enableBlending ();
    void setBlendFunction (int srcFunc,int dstFunc);
    void dispose ();
    gdx_cpp::math::Matrix4& getProjectionMatrix ();
    gdx_cpp::math::Matrix4& getTransformMatrix ();
    void setProjectionMatrix (const gdx_cpp::math::Matrix4& projection);
    void setTransformMatrix (const gdx_cpp::math::Matrix4& transform);
    void setShader (const gdx_cpp::graphics::glutils::ShaderProgram& shader);
    bool isBlendingEnabled ();

protected:


private:
    void createShader ();
    void renderMesh ();
    float vertices*;

    Mesh mesh;
    Mesh buffers*;
    
    Texture::ptr lastTexture = null;
    private float invTexWidth = 0;
    private float invTexHeight = 0;
    
    private int idx = 0;
    private int currBufferIdx = 0;
    private float[] vertices;
    
    private final Matrix4 transformMatrix = new Matrix4();
    private final Matrix4 projectionMatrix = new Matrix4();
    private final Matrix4 combinedMatrix = new Matrix4();
    
    private boolean drawing = false;
    
    private boolean blendingDisabled = false;
    private int blendSrcFunc = GL11.GL_SRC_ALPHA;
    private int blendDstFunc = GL11.GL_ONE_MINUS_SRC_ALPHA;
    
    private ShaderProgram shader;
    
    float color = Color.WHITE.toFloatBits();
    private Color tempColor = new Color(1, 1, 1, 1);
    
    /** number of render calls **/
    public int renderCalls = 0;
    
    /** the maximum number of sprites rendered in one batch so far **/
    public int maxSpritesInBatch = 0;
    private ShaderProgram customShader = null;
};

} // namespace gdx_cpp
} // namespace graphics
} // namespace g2d

#endif // GDX_CPP_GRAPHICS_G2D_SPRITEBATCH_HPP_
