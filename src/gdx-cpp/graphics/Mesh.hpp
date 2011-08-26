
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

#include "gdx-cpp/utils/Disposable.hpp"

#include <tr1/unordered_map.h>
#include <list>
#include <Application.hpp>

#include "VertexAttribute.hpp"
#include "VertexAttributes.hpp"

namespace gdx_cpp {
namespace graphics {

namespace glutils {
    class VertexData;
    class IndexData;
}

class Mesh: public gdx_cpp::utils::Disposable {
public:

    class VertexDataType {
        enum {
            VertexArray, VertexBufferObject, VertexBufferObjectSubData,
        };
    };

    Mesh (bool isStatic, int maxVertices, int maxIndices, std::vector<VertexAttribute> attributes);
    
    void setVertices ();
    void setVertices (int offset,int count);
    void getVertices ();
    void setIndices ();
    void setIndices (int offset,int count);
    void getIndices ();
    int getNumIndices ();
    int getNumVertices ();
    int getMaxVertices ();
    int getMaxIndices ();
    int getVertexSize ();
    void setAutoBind (bool autoBind);
    void bind ();
    void unbind ();
    void bind (const gdx_cpp::graphics::glutils::ShaderProgram& shader);
    void unbind (const gdx_cpp::graphics::glutils::ShaderProgram& shader);
    void render (int primitiveType);
    void render (int primitiveType,int offset,int count);
    void render (const gdx_cpp::graphics::glutils::ShaderProgram& shader,int primitiveType);
    void render (const gdx_cpp::graphics::glutils::ShaderProgram& shader,int primitiveType,int offset,int count);
    void dispose ();
    VertexAttribute& getVertexAttribute (int usage);
    VertexAttributes& getVertexAttributes ();
    std::vector<float> getVerticesBuffer ();
    gdx_cpp::math::collision::BoundingBox& calculateBoundingBox ();
    void calculateBoundingBox (const gdx_cpp::math::collision::BoundingBox& bbox);
    ShortBuffer& getIndicesBuffer ();
    static void invalidateAllMeshes (const gdx_cpp::Application& app);
    static void clearAllMeshes (const gdx_cpp::Application& app);
    static std::string& getManagedStatus ();
    void scale (float scaleX,float scaleY,float scaleZ);

    static bool forceVBO;
    
protected:
    static std::tr1::unordered_map<gdx_cpp::Application*, std::list<Mesh*> > meshes;
    glutils::VertexData* vertices;
    glutils::IndexData* indices;
    bool autoBind = true;
    bool isVertexArray;
    
    int refCount = 0;
    
private:
    static void addManagedMesh (const gdx_cpp::Application& app, Mesh* mesh);
    
};

} // namespace gdx_cpp
} // namespace graphics

#endif // GDX_CPP_GRAPHICS_MESH_HPP_
