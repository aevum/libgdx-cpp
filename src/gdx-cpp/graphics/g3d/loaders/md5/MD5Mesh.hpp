
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

#ifndef GDX_CPP_GRAPHICS_G3D_LOADERS_MD5_MD5MESH_HPP_
#define GDX_CPP_GRAPHICS_G3D_LOADERS_MD5_MD5MESH_HPP_

namespace gdx_cpp {
namespace graphics {
namespace g3d {
namespace loaders {
namespace md5 {

class MD5Mesh {
public:
    float* createVertexArray ();
    float* createVertexArray (int stride);
    short* getIndices ();
    void calculateVerticesN (const MD5Joints& skeleton,const gdx_cpp::math::collision::BoundingBox& bbox);
    void calculateVertices (const MD5Joints& skeleton,const gdx_cpp::math::collision::BoundingBox& bbox);
    static void calculateVerticesN (const MD5Joints& skeleton,float vertices,int vstride,int wstride,const gdx_cpp::math::collision::BoundingBox& bbox);
    static void calculateVertices (const MD5Joints& skeleton,float vertices,int vstride,int wstride,const gdx_cpp::math::collision::BoundingBox& bbox);
    void calculateVerticesJni (const MD5Joints& skeleton);
    void calculateNormalsBind (const MD5Joints& bindPoseSkeleton);
    static void calculateNormalsBind (const MD5Joints& skeleton,float vertices,const short& indices,float verts,int vstride,int wstride);
    void read (const DataInputStream& in);
    void write (const DataOutputStream& out);

protected:


private:
    static gdx_cpp::math::Vector3& calcNor (const gdx_cpp::math::Vector3& v1,const gdx_cpp::math::Vector3& v2,const gdx_cpp::math::Vector3& v3);
};

} // namespace gdx_cpp
} // namespace graphics
} // namespace g3d
} // namespace loaders
} // namespace md5

#endif // GDX_CPP_GRAPHICS_G3D_LOADERS_MD5_MD5MESH_HPP_
