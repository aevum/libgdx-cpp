
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

#ifndef GDX_CPP_SCENES_SCENE2D_UI_UTILS_SCISSORSTACK_HPP_
#define GDX_CPP_SCENES_SCENE2D_UI_UTILS_SCISSORSTACK_HPP_

namespace gdx_cpp {
namespace scenes {
namespace scene2d {
namespace ui {
namespace utils {

class ScissorStack {
public:
    static void pushScissors (const gdx_cpp::math::Rectangle& scissor);
    static void popScissors ();
    static void calculateScissors (const gdx_cpp::graphics::Camera& camera,const gdx_cpp::math::Matrix4& batchTransform,const gdx_cpp::math::Rectangle& area,const gdx_cpp::math::Rectangle& scissor);
    static gdx_cpp::math::Rectangle& getViewport ();
    static void toWindowCoordinates (const gdx_cpp::graphics::Camera& camera,const gdx_cpp::math::Matrix4& transformMatrix,const gdx_cpp::math::Vector2& point);

protected:


private:
    static void fix (const gdx_cpp::math::Rectangle& rect);
    static Array<Rectangle> scissors = new Array<Rectangle>();
};

} // namespace gdx_cpp
} // namespace scenes
} // namespace scene2d
} // namespace ui
} // namespace utils

#endif // GDX_CPP_SCENES_SCENE2D_UI_UTILS_SCISSORSTACK_HPP_
