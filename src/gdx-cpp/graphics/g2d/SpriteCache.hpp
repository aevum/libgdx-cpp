
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

#ifndef GDX_CPP_GRAPHICS_G2D_SPRITECACHE_HPP_
#define GDX_CPP_GRAPHICS_G2D_SPRITECACHE_HPP_

#include "gdx-cpp/utils/Disposable.hpp"
#include "Sprite.hpp"
#include "gdx-cpp/math/Matrix4.hpp"

namespace gdx_cpp {
namespace graphics {

class Mesh;

namespace glutils {
class ShaderProgram;
}

namespace g2d {

class SpriteCache: public gdx_cpp::utils::Disposable {
    struct Cache {
        int id;
        int offset;
        int maxCount;
        std::vector<Texture::ptr> textures;
        std::vector<int> counts;

        Cache (int id, int offset) {
            this->id = id;
            this->offset = offset;
        }
    };

    static glutils::ShaderProgram* createDefaultShader ();
public:
    SpriteCache(int size = 1000, bool useIndices = false, gdx_cpp::graphics::glutils::ShaderProgram* shader = createDefaultShader());

    void setColor (const gdx_cpp::graphics::Color& tint);
    void setColor (float r,float g,float b,float a);
    void setColor (float color);
    gdx_cpp::graphics::Color& getColor ();
    void beginCache ();
    void beginCache (unsigned int cacheID);
    int endCache ();
    void clear ();

    void add (const gdx_cpp::graphics::Texture::ptr texture, float* vertices, int size, int offset, int length) ;
    void add (gdx_cpp::graphics::Texture::ptr texture,float x,float y);
    void add (const gdx_cpp::graphics::Texture::ptr texture, float* vertices, int offset, int length);
    void add (gdx_cpp::graphics::g2d::TextureRegion& region, float x, float y, float width, float height);
    void add (const gdx_cpp::graphics::Texture::ptr texture,float x,float y,int srcWidth,int srcHeight,float u,float v,float u2,float v2,float color);
    void add (Texture::ptr texture,float x,float y,int srcX,int srcY,int srcWidth,int srcHeight);
    void add (Texture::ptr texture, float x, float y, float width, float height, int srcX, int srcY, int srcWidth, int srcHeight, bool flipX, bool flipY);
    void add (Texture::ptr texture, float x, float y, float originX, float originY, float width, float height, float scaleX, float scaleY, float rotation, int srcX, int srcY, int srcWidth, int srcHeight, bool flipX, bool flipY);
    void add (TextureRegion::ptr region, float x, float y);
    void add (TextureRegion::ptr region, float x, float y, float width, float height);
    void add (TextureRegion::ptr region,float x,float y,float originX,float originY,float width,float height,float scaleX,float scaleY,float rotation);
    void add (gdx_cpp::graphics::g2d::Sprite& sprite);
    void begin ();
    void end ();
    void draw (int cacheID);
    void draw (int cacheID,int offset,int length);
    void dispose ();
    gdx_cpp::math::Matrix4& getProjectionMatrix ();
    void setProjectionMatrix (const gdx_cpp::math::Matrix4& projection);
    gdx_cpp::math::Matrix4& getTransformMatrix ();
    void setTransformMatrix (const gdx_cpp::math::Matrix4& transform);
    void setShader (gdx_cpp::graphics::glutils::ShaderProgram* shader);

private:
    static float tempVertices[Sprite::VERTEX_SIZE * 6];

    Mesh* mesh;
    bool drawing;
    math::Matrix4 transformMatrix;
    math::Matrix4 projectionMatrix;
    std::vector<Cache*> caches;

    math::Matrix4 combinedMatrix;
    glutils::ShaderProgram* shader;

    Cache* currentCache;
    std::vector<Texture::ptr> textures;
    std::vector<int> counts;

    float color;
    Color tempColor;

    glutils::ShaderProgram* customShader;
};

} // namespace gdx_cpp
} // namespace graphics
} // namespace g2d

#endif // GDX_CPP_GRAPHICS_G2D_SPRITECACHE_HPP_
