
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
#include "gdx-cpp/graphics/Color.hpp"
#include "gdx-cpp/math/Matrix4.hpp"

namespace gdx_cpp {
namespace graphics {

class Mesh;
namespace glutils {
    class ShaderProgram;
}

namespace g2d {

class TextureRegion;


class SpriteBatch: public gdx_cpp::utils::Disposable {
public:
    SpriteBatch(int size = 1000);
    SpriteBatch (int size, int buffers) ;

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
    void draw (const gdx_cpp::graphics::Texture& texture, const std::vector< float >& spriteVertices, int offset, int length);
    void draw (const TextureRegion& region,float x,float y);
    void draw (const TextureRegion& region,float x,float y,float width,float height);
    void draw (const TextureRegion& region,float x,float y,float originX,float originY,float width,float height,float scaleX,float scaleY,float rotation);
    void draw (const TextureRegion& region,float x,float y,float originX,float originY,float width,float height,float scaleX,float scaleY,float rotation,bool clockwise);
    void flush ();
    void disableBlending ();
    void enableBlending ();
    void setBlendFunction (int srcFunc,int dstFunc);
    void dispose ();
    const gdx_cpp::math::Matrix4& getProjectionMatrix ();
    const gdx_cpp::math::Matrix4& getTransformMatrix ();
    void setProjectionMatrix (const gdx_cpp::math::Matrix4& projection);
    void setTransformMatrix (const gdx_cpp::math::Matrix4& transform);
    void setShader (gdx_cpp::graphics::glutils::ShaderProgram* shader);
    bool isBlendingEnabled ();

    int renderCalls;
    int maxSpritesInBatch;

    virtual ~SpriteBatch();
    
protected:
    float color;
private:
    void createShader ();
    void renderMesh ();
    std::vector<float> vertices;

    Mesh* mesh;
    std::vector<Mesh*> buffers;
    
    Texture* lastTexture;
    float invTexWidth;
    float invTexHeight;
    
    int idx;
    int currBufferIdx;
    
    math::Matrix4 transformMatrix;
    math::Matrix4 projectionMatrix;
    math::Matrix4 combinedMatrix;
    
    bool drawing;
    
    bool blendingDisabled ;
    int blendSrcFunc;
    int blendDstFunc;
    
    glutils::ShaderProgram *shader;
    Color tempColor;
    
    glutils::ShaderProgram* customShader;
};

} // namespace gdx_cpp
} // namespace graphics
} // namespace g2d

#endif // GDX_CPP_GRAPHICS_G2D_SPRITEBATCH_HPP_
