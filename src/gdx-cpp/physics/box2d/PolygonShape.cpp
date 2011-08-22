
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

#include "PolygonShape.hpp"

using namespace gdx_cpp::physics::box2d;

Type& PolygonShape::getType () {
    return Type.Polygon;
}

void PolygonShape::set () {
    float[] verts = new float[vertices.length * 2];
    for (int i = 0, j = 0; i < vertices.length * 2; i += 2, j++) {
        verts[i] = vertices[j].x;
        verts[i + 1] = vertices[j].y;
    }
    jniSet(addr, verts);
}

void PolygonShape::setAsBox (float hx,float hy) {
    jniSetAsBox(addr, hx, hy);
}

void PolygonShape::setAsBox (float hx,float hy,const gdx_cpp::math::Vector2& center,float angle) {
    jniSetAsBox(addr, hx, hy, center.x, center.y, angle);
}

void PolygonShape::setAsEdge (const gdx_cpp::math::Vector2& v1,const gdx_cpp::math::Vector2& v2) {
    jniSetAsEdge(addr, v1.x, v1.y, v2.x, v2.y);
}

int PolygonShape::getVertexCount () {
    return jniGetVertexCount(addr);
}

void PolygonShape::getVertex (int index,const gdx_cpp::math::Vector2& vertex) {
    jniGetVertex(addr, index, verts);
    vertex.x = verts[0];
    vertex.y = verts[1];
}

