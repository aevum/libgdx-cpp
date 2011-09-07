
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

#ifndef GDX_CPP_GRAPHICS_MESH_HPP_
#define GDX_CPP_GRAPHICS_MESH_HPP_

#include <tr1/unordered_map>
#include <list>

#include "gdx-cpp/utils/Disposable.hpp"
#include "gdx-cpp/utils/Buffer.hpp"
#include "gdx-cpp/Application.hpp"
#include "VertexAttribute.hpp"
#include "VertexAttributes.hpp"
#include <set>


namespace gdx_cpp {
namespace math {
namespace collision {

class BoundingBox;
class BoundingBox;
}
}

namespace graphics {

namespace glutils {
    class VertexData;
    class IndexData;
    class ShaderProgram;
}

class Mesh: public gdx_cpp::utils::Disposable {
public:

    struct VertexDataType {
        static const int VertexArray = 0;
        static const int VertexBufferObject = 1;
        static const int VertexBufferObjectSubData = 2;
    };

    Mesh (int type, bool isStatic, int maxVertices, int maxIndices, const std::vector< gdx_cpp::graphics::VertexAttribute >& attributes) ;
    Mesh (bool isStatic, int maxVertices, int maxIndices, const std::vector<VertexAttribute>& attributes);


    
    void setVertices(const float* length, int size);    
    void setVertices (const std::vector< float >& vertices);
    void setVertices (const std::vector< float >& vertices, int offset, int count);
    void getVertices (std::vector< float >& vertices);
    void setIndices (std::vector< short int >& indices);
    void setIndices (std::vector< short int >& indices, int offset, int count);
    void getIndices (std::vector< short int >& indices);
    unsigned int getNumIndices ();
    unsigned int getNumVertices ();
    int getMaxVertices ();
    int getMaxIndices ();
    int getVertexSize ();
    void setAutoBind (bool autoBind);
    void bind ();
    void unbind ();
    void bind (gdx_cpp::graphics::glutils::ShaderProgram& shader);
    void unbind (gdx_cpp::graphics::glutils::ShaderProgram& shader);
    void render (int primitiveType);
    void render (int primitiveType,int offset,int count);
    void render (gdx_cpp::graphics::glutils::ShaderProgram& shader, int primitiveType);
    void render (gdx_cpp::graphics::glutils::ShaderProgram& shader, int primitiveType, int offset, int count);
    void dispose ();
    VertexAttribute& getVertexAttribute (int usage);
    VertexAttributes& getVertexAttributes ();
    utils::float_buffer& getVerticesBuffer ();
    void calculateBoundingBox (gdx_cpp::math::collision::BoundingBox& bbox);
    utils::short_buffer& getIndicesBuffer ();
    static void invalidateAllMeshes (gdx_cpp::Application* app);
    static void clearAllMeshes (gdx_cpp::Application* app);
    std::string getManagedStatus ();
    void scale (float scaleX,float scaleY,float scaleZ);

    static bool forceVBO;
    
protected:
    glutils::VertexData* vertices;
    glutils::IndexData* indices;
    bool autoBind;
    bool isVertexArray;
    
    int refCount;
    
private:
    typedef std::tr1::unordered_map<gdx_cpp::Application*, std::set<Mesh*> > MeshMap;
    static MeshMap meshes;
    static void addManagedMesh (gdx_cpp::Application* app, gdx_cpp::graphics::Mesh* mesh);
    
};

} // namespace gdx_cpp
} // namespace graphics

#endif // GDX_CPP_GRAPHICS_MESH_HPP_
