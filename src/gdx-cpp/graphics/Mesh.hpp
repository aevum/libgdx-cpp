
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

#include <list>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

#include "VertexAttribute.hpp"
#include "VertexAttributes.hpp"
#include "gdx-cpp/Application.hpp"
#include "gdx-cpp/internal/memory"
#include "gdx-cpp/internal/unordered_map"
#include "gdx-cpp/utils/Buffer.hpp"
#include "gdx-cpp/utils/Disposable.hpp"
#include "gdx-cpp/math/collision/BoundingBox.hpp"

namespace gdx {

//class BoundingBox;
class IndexData;
class ShaderProgram;
class VertexData;
class Application;
class VertexAttribute;
class VertexAttributes;

class Mesh: public Disposable {
public:
    typedef ref_ptr_maker<Mesh>::shared_ptr_t ptr;
    
    struct VertexDataType {
        static const int VertexArray = 0;
        static const int VertexBufferObject = 1;
        static const int VertexBufferObjectSubData = 2;
    };

    Mesh (int type, bool isStatic, int maxVertices, int maxIndices, const std::vector< VertexAttribute >& attributes) ;
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
    void bind (ShaderProgram& shader);
    void unbind (ShaderProgram& shader);
    void render (int primitiveType);
    void render (int primitiveType,int offset,int count);
    void render (ShaderProgram& shader, int primitiveType);
    void render (ShaderProgram& shader, int primitiveType, int offset, int count);
    void dispose ();
    VertexAttribute* const getVertexAttribute (int usage);
    VertexAttributes& getVertexAttributes ();
    float_buffer& getVerticesBuffer ();
    void calculateBoundingBox (BoundingBox& bbox);
    short_buffer& getIndicesBuffer ();
    static void invalidateAllMeshes (Application* app);
    static void clearAllMeshes (Application* app);
    std::string getManagedStatus ();
    void scale (float scaleX,float scaleY,float scaleZ);

    static bool forceVBO;

    ~Mesh();
    
protected:
    VertexData* vertices;
    IndexData* indices;
    bool autoBind;
    bool isVertexArray;
    bool disposed;
private:
    typedef gdx_unordered_map<Application*, std::set<Mesh*> > MeshMap;
    static MeshMap meshes;
    static void addManagedMesh (Application* app, Mesh* mesh);
    
};

} // namespace gdx

#endif // GDX_CPP_GRAPHICS_MESH_HPP_
