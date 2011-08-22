
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

#ifndef GDX_CPP_GRAPHICS_G2D_SPRITE_HPP_
#define GDX_CPP_GRAPHICS_G2D_SPRITE_HPP_

namespace gdx_cpp {
namespace graphics {
namespace g2d {

class Sprite {
public:
    void set (const Sprite& sprite);
    void setBounds (float x,float y,float width,float height);
    void setSize (float width,float height);
    void setPosition (float x,float y);
    void translate (float xAmount,float yAmount);
    void setColor (const gdx_cpp::graphics::Color& tint);
    void setColor (float r,float g,float b,float a);
    void setOrigin (float originX,float originY);
    void setRotation (float degrees);
    void rotate (float degrees);
    void rotate90 (bool clockwise);
    void setScale (float scaleXY);
    void setScale (float scaleX,float scaleY);
    void scale (float amount);
    float* getVertices ();
    gdx_cpp::math::Rectangle& getBoundingRectangle ();
    void draw (const SpriteBatch& spriteBatch);
    void draw (const SpriteBatch& spriteBatch,float alphaModulation);
    float getX ();
    float getY ();
    float getWidth ();
    float getHeight ();
    float getOriginX ();
    float getOriginY ();
    float getRotation ();
    float getScaleX ();
    float getScaleY ();
    gdx_cpp::graphics::Color& getColor ();
    void setRegion (float u,float v,float u2,float v2);
    void setU (float u);
    void setV (float v);
    void setU2 (float u2);
    void setV2 (float v2);
    void flip (bool x,bool y);
    void scroll (float xAmount,float yAmount);

protected:


private:

};

} // namespace gdx_cpp
} // namespace graphics
} // namespace g2d

#endif // GDX_CPP_GRAPHICS_G2D_SPRITE_HPP_
