
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

#include <vector>

#include "Sprite.hpp"
#include "gdx-cpp/graphics/Color.hpp"
#include "gdx-cpp/graphics/Texture.hpp"
#include "gdx-cpp/graphics/g2d/TextureRegion.hpp"
#include "gdx-cpp/math/Matrix4.hpp"
#include "gdx-cpp/utils/Disposable.hpp"

namespace gdx {
class Mesh;
class ShaderProgram;

class SpriteCache: public Disposable {
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

    static ShaderProgram* createDefaultShader ();
public:
    SpriteCache(int size = 1000, bool useIndices = false, ShaderProgram* shader = createDefaultShader());

    void setColor (const Color& tint);
    void setColor (float r,float g,float b,float a);
    void setColor (float color);
    Color& getColor ();
    void beginCache ();
    void beginCache (unsigned int cacheID);
    int endCache ();
    void clear ();

    void add (const Texture::ptr& texture, const float* vertices, int size, int offset, int length) ;
    void add (const Texture::ptr& texture, float x,float y);
    void add (const Texture::ptr& texture, const float* vertices, int offset, int length);
    void add (const Texture::ptr& texture, float x,float y,int srcWidth,int srcHeight,float u,float v,float u2,float v2,float color);
    void add (const Texture::ptr& texture, float x,float y,int srcX,int srcY,int srcWidth,int srcHeight);
    void add (const Texture::ptr& texture, float x, float y, float width, float height, int srcX, int srcY, int srcWidth, int srcHeight, bool flipX, bool flipY);
    void add (const Texture::ptr& texture, float x, float y, float originX, float originY, float width, float height, float scaleX, float scaleY, float rotation, int srcX, int srcY, int srcWidth, int srcHeight, bool flipX, bool flipY);
    
    void add (const TextureRegion& region, float x, float y, float width, float height);
    void add (const TextureRegion& region, float x, float y);
    void add (const TextureRegion& region,float x,float y,float originX,float originY,float width,float height,float scaleX,float scaleY,float rotation);
    void add ( gdx::Sprite& sprite );
    void begin ();
    void end ();
    void draw (int cacheID);
    void draw (int cacheID,int offset,int length);
    void dispose ();
    Matrix4& getProjectionMatrix ();
    void setProjectionMatrix (const Matrix4& projection);
    Matrix4& getTransformMatrix ();
    void setTransformMatrix (const Matrix4& transform);
    void setShader (ShaderProgram* shader);

    void disposeCache(int cacheID);
private:
    SpriteCache(const SpriteCache& other);
    SpriteCache& operator = (const SpriteCache& other);
    
    static float tempVertices[Sprite::VERTEX_SIZE * 6];

    Mesh* mesh;
    bool drawing;
    Matrix4 transformMatrix;
    Matrix4 projectionMatrix;
    std::vector<Cache*> caches;

    Matrix4 combinedMatrix;
    ShaderProgram* shader;

    Cache* currentCache;
    std::vector<Texture::ptr> textures;
    std::vector<int> counts;

    float color;
    Color tempColor;

    ShaderProgram* customShader;
};

} // namespace gdx
#endif // GDX_CPP_GRAPHICS_G2D_SPRITECACHE_HPP_
