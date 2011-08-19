
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

#ifndef GDX_CPP_GRAPHICS_G3D_DECALS_DECAL_HPP_
#define GDX_CPP_GRAPHICS_G3D_DECALS_DECAL_HPP_

namespace gdx_cpp {
namespace graphics {
namespace g3d {
namespace decals {

class Decal {
public:
    void setColor (float r,float g,float b,float a);
    void rotateX (float angle);
    void rotateY (float angle);
    void rotateZ (float angle);
    void setRotation (const gdx_cpp::math::Vector3& dir,const gdx_cpp::math::Vector3& up);
    gdx_cpp::math::Quaternion& getRotation ();
    void translateX (float units);
    void setX (float x);
    float getX ();
    void translateY (float units);
    void setY (float y);
    float getY ();
    void translateZ (float units);
    void setZ (float z);
    float getZ ();
    void translate (float x,float y,float z);
    void setPosition (float x,float y,float z);
    gdx_cpp::math::Vector3& getPosition ();
    void setScaleX (float scale);
    float getScaleX ();
    void setScaleY (float scale);
    float getScaleY ();
    void setScale (float scaleX,float scaleY);
    void setScale (float scale);
    void setWidth (float width);
    float getWidth ();
    void setHeight (float height);
    float getHeight ();
    void setDimensions (float width,float height);
    float* getVertices ();
    void setTextureRegion (const gdx_cpp::graphics::g2d::TextureRegion& textureRegion);
    void setBlending (int srcBlendFactor,int dstBlendFactor);
    static Decal& newDecal (const gdx_cpp::graphics::g2d::TextureRegion& textureRegion);
    static Decal& newDecal (const gdx_cpp::graphics::g2d::TextureRegion& textureRegion,bool hasTransparency);
    static Decal& newDecal (float width,float height,const gdx_cpp::graphics::g2d::TextureRegion& textureRegion);
    static Decal& newDecal (float width,float height,const gdx_cpp::graphics::g2d::TextureRegion& textureRegion,bool hasTransparency);
    static Decal& newDecal (float width,float height,const gdx_cpp::graphics::g2d::TextureRegion& textureRegion,int srcBlendFactor,int dstBlendFactor);

protected:
    void update ();
    void transformVertices ();
    void resetVertices ();
    void updateUVs ();
    DecalMaterial& getMaterial ();

private:

};

} // namespace gdx_cpp
} // namespace graphics
} // namespace g3d
} // namespace decals

#endif // GDX_CPP_GRAPHICS_G3D_DECALS_DECAL_HPP_
