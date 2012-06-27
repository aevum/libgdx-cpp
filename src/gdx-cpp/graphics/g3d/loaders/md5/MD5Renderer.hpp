
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

#ifndef GDX_CPP_GRAPHICS_G3D_LOADERS_MD5_MD5RENDERER_HPP_
#define GDX_CPP_GRAPHICS_G3D_LOADERS_MD5_MD5RENDERER_HPP_

namespace gdx {
namespace graphics {
namespace g3d {
namespace loaders {
namespace md5 {

class MD5Renderer: public gdx::Disposable {
public:
    gdx::BoundingBox& getBBox ();
    float* getVertices (int idx);
    short* getIndices (int idx);
    gdx::Mesh& getMesh ();
    void setSkeleton (const MD5Joints& skeleton);
    void setUseJni (bool useJni);
    void calculateNormals (const MD5Joints& bindPoseSkeleton);
    void render ();
    void render ();
    void dispose ();
    bool isJniUsed ();

protected:


private:
    MD5Model model;
    Mesh mesh;
    short[][] indices;
    float[][] vertices;
};

} // namespace gdx
} // namespace graphics
} // namespace g3d
} // namespace loaders
} // namespace md5

#endif // GDX_CPP_GRAPHICS_G3D_LOADERS_MD5_MD5RENDERER_HPP_
