
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

#include<vector>

namespace gdx_cpp {
namespace graphics {
  
class Texture;

namespace g2d {

class SpriteBatch;
class TextureRegion;

class NinePatch {
public:

    const static int TOP_LEFT = 0;
    const static int TOP_CENTER = 1;
    const static int TOP_RIGHT = 2;
    const static int MIDDLE_LEFT = 3;
    const static int MIDDLE_CENTER = 4;
    const static int MIDDLE_RIGHT = 5;
    const static int BOTTOM_LEFT = 6;
    const static int BOTTOM_CENTER = 7;
    const static int BOTTOM_RIGHT = 8;

    NinePatch (Texture::ptr texture, int left, int right, int top, int bottom);
    NinePatch (TextureRegion::ptr texture, int left, int right, int top, int bottom);
    NinePatch (std::vector< TextureRegion::ptr >& _patches);
    
    void draw (gdx_cpp::graphics::g2d::SpriteBatch& batch, float x, float y, float width, float height);
    float getLeftWidth ();
    float getRightWidth ();
    float getTopHeight ();
    float getBottomHeight ();
    float getTotalHeight ();
    float getTotalWidth ();

protected:
    std::vector<TextureRegion::ptr> patches;
    
private:
    void initialize(TextureRegion::ptr region, int left, int right, int top, int bottom);
    void checkValidity ();
};

} // namespace gdx_cpp
} // namespace graphics
} // namespace g2d

#endif // GDX_CPP_GRAPHICS_G2D_NINEPATCH_HPP_
