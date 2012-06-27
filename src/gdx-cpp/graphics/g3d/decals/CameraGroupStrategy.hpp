
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

#ifndef GDX_CPP_GRAPHICS_G3D_DECALS_CAMERAGROUPSTRATEGY_HPP_
#define GDX_CPP_GRAPHICS_G3D_DECALS_CAMERAGROUPSTRATEGY_HPP_

namespace gdx {
namespace graphics {
namespace g3d {
namespace decals {

class CameraGroupStrategy {
public:
    int compare (const Decal& o1,const Decal& o2);
    void setCamera (const gdx::Camera& camera);
    gdx::Camera& getCamera ();
    int decideGroup (const Decal& decal);
    void beforeGroup (int group,gdx::ArrayDecal>& contents);
    void afterGroup (int group);
    void beforeGroups ();
    void afterGroups ();
    gdx::ShaderProgram& getGroupShader (int group);

protected:
    gdx::ArrayDecal>& newObject ();

private:
    void createDefaultShader ();
};

} // namespace gdx
} // namespace graphics
} // namespace g3d
} // namespace decals

#endif // GDX_CPP_GRAPHICS_G3D_DECALS_CAMERAGROUPSTRATEGY_HPP_
