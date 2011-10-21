
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

#ifndef GDX_CPP_SCENES_SCENE2D_ACTORS_IMAGE_HPP_
#define GDX_CPP_SCENES_SCENE2D_ACTORS_IMAGE_HPP_

namespace gdx_cpp {
namespace scenes {
namespace scene2d {
namespace actors {

class Image: public gdx_cpp::scenes::scene2d::Actor {
public:
    void draw (const gdx_cpp::graphics::g2d::SpriteBatch& batch,float parentAlpha);
    bool touchDown (float x,float y,int pointer);
    void touchUp (float x,float y,int pointer);
    void touchDragged (float x,float y,int pointer);
    gdx_cpp::scenes::scene2d::Actor& hit (float x,float y);
    Image (const std::string& name);
    Image (const std::string& name,const gdx_cpp::graphics::Texture& texture);
    Image (const std::string& name,const gdx_cpp::graphics::g2d::TextureRegion& region);
    TextureRegion region = null;

protected:


private:

};

} // namespace gdx_cpp
} // namespace scenes
} // namespace scene2d
} // namespace actors

#endif // GDX_CPP_SCENES_SCENE2D_ACTORS_IMAGE_HPP_
