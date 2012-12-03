
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

#ifndef GDX_CPP_GRAPHICS_G2D_NINEPATCH_HPP_
#define GDX_CPP_GRAPHICS_G2D_NINEPATCH_HPP_

#include "gdx-cpp/graphics/g2d/TextureRegion.hpp"
#include "gdx-cpp/graphics/Texture.hpp"

#include <array>

namespace gdx {
class Texture;

class SpriteBatch;
class TextureRegion;

class NinePatch {
public:
    typedef ref_ptr_maker < NinePatch >::shared_ptr_t ptr;
    
    enum class Sides {
        TOP_LEFT = 0,
        TOP_CENTER,
        TOP_RIGHT,
        MIDDLE_LEFT,
        MIDDLE_CENTER,
        MIDDLE_RIGHT,
        BOTTOM_LEFT,
        BOTTOM_CENTER,
        BOTTOM_RIGHT
    };
        
    NinePatch (const Texture::ptr& texture, int left, int right, int top, int bottom);
    NinePatch (TextureRegion texture, int left, int right, int top, int bottom);
    NinePatch (std::array<TextureRegion ,9 >& _patches);
    NinePatch(TextureRegion region);
    
    void draw (gdx::SpriteBatch& batch, float x, float y, float width, float height);
    float getLeftWidth ();
    float getRightWidth ();
    float getTopHeight ();
    float getBottomHeight ();
    float getTotalHeight ();
    float getTotalWidth ();

    std::array<TextureRegion, 9 > getPatches();

private:
    std::array<TextureRegion, 9 > patches;
    void initialize(TextureRegion region, int left, int right, int top, int bottom);
    void checkValidity ();
    NinePatch();
};

} // namespace gdx

#endif // GDX_CPP_GRAPHICS_G2D_NINEPATCH_HPP_
