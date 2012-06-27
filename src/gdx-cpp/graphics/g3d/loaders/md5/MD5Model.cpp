
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

#include "MD5Model.hpp"

using namespace gdx::g3d::md5;

int MD5Model::getNumVertices () {
    int numVertices = 0;

    for (int i = 0; i < meshes.length; i++)
        numVertices += meshes[i].numVertices;

    return numVertices;
}

int MD5Model::getNumTriangles () {
    int numTriangles = 0;

    for (int i = 0; i < meshes.length; i++)
        numTriangles += meshes[i].numTriangles;

    return numTriangles;
}

void MD5Model::read (const DataInputStream& in) throws IOException {
    numJoints = in.readInt();
    baseSkeleton = new MD5Joints();
    baseSkeleton.read(in);
    int numMeshes = in.readInt();
    meshes = new MD5Mesh[numMeshes];
    for (int i = 0; i < numMeshes; i++) {
        meshes[i] = new MD5Mesh();
        meshes[i].read(in);
    }
}

void MD5Model::write (const DataOutputStream& out) throws IOException {
    out.writeInt(numJoints);
    baseSkeleton.write(out);
    out.writeInt(meshes.length);
    for (int i = 0; i < meshes.length; i++) {
        meshes[i].write(out);
    }
}

