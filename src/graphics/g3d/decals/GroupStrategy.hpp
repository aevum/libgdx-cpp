
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

#ifndef GDX_CPP_GRAPHICS_G3D_DECALS_GROUPSTRATEGY_HPP_
#define GDX_CPP_GRAPHICS_G3D_DECALS_GROUPSTRATEGY_HPP_

namespace gdx_cpp {
namespace graphics {
namespace g3d {
namespace decals {

class GroupStrategy {
public:
    virtual   gdx_cpp::graphics::glutils::ShaderProgram& getGroupShader (int group) = 0;
    virtual   int decideGroup (const Decal& decal) = 0;
    virtual   void beforeGroup (int group,gdx_cpp::utils::ArrayDecal>& contents) = 0;
    virtual   void afterGroup (int group) = 0;
    virtual   void beforeGroups () = 0;
    virtual   void afterGroups () = 0;

protected:


private:

};

} // namespace gdx_cpp
} // namespace graphics
} // namespace g3d
} // namespace decals

#endif // GDX_CPP_GRAPHICS_G3D_DECALS_GROUPSTRATEGY_HPP_
