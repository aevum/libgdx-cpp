
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

#ifndef GDX_CPP_SCENES_SCENE2D_UI_IMAGE_HPP_
#define GDX_CPP_SCENES_SCENE2D_UI_IMAGE_HPP_

namespace gdx_cpp {
namespace scenes {
namespace scene2d {
namespace ui {

class Image {
public:
    void layout ();
    void draw (const gdx_cpp::graphics::g2d::SpriteBatch& batch,float parentAlpha);
    void setRegion (const gdx_cpp::graphics::g2d::TextureRegion& region);
    void setPatch (const gdx_cpp::graphics::g2d::NinePatch& patch);
    float getMinWidth ();
    float getMinHeight ();
    float getPrefWidth ();
    float getPrefHeight ();
    bool touchDown (float x,float y,int pointer);
    void touchUp (float x,float y,int pointer);
    void touchDragged (float x,float y,int pointer);
    Image (const gdx_cpp::graphics::g2d::TextureRegion& region);
    Image (const gdx_cpp::graphics::g2d::TextureRegion& region,const Scaling& scaling);
    Image (const gdx_cpp::graphics::g2d::TextureRegion& region,const Scaling& scaling,int align);
    Image (const gdx_cpp::graphics::g2d::TextureRegion& region,const Scaling& scaling,const std::string& name);
    Image (const gdx_cpp::graphics::g2d::TextureRegion& region,const Scaling& scaling,int align,const std::string& name);
    Image (const gdx_cpp::graphics::g2d::NinePatch& patch);
    Image (const gdx_cpp::graphics::g2d::NinePatch& patch,const Scaling& scaling);
    Image (const gdx_cpp::graphics::g2d::NinePatch& patch,const Scaling& scaling,int align);
    Image (const gdx_cpp::graphics::g2d::NinePatch& patch,const Scaling& scaling,const std::string& name);
    Image (const gdx_cpp::graphics::g2d::NinePatch& patch,const Scaling& scaling,int align,const std::string& name);

protected:


private:
    TextureRegion region ;
    NinePatch patch ;
    Scaling scaling ;
    int align = Align.CENTER;
};

} // namespace gdx_cpp
} // namespace scenes
} // namespace scene2d
} // namespace ui

#endif // GDX_CPP_SCENES_SCENE2D_UI_IMAGE_HPP_
