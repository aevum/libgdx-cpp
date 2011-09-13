
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
#include <vector>
#include "gdx-cpp/math/Vector2.hpp"
#include "Box2D.h"

using namespace gdx_cpp::physics::box2d;



PolygonShape::PolygonShape () {
    addr = newPolygonShape();
}

PolygonShape::PolygonShape (b2PolygonShape * _addr)
{
  addr = _addr;
}

b2PolygonShape* PolygonShape::newPolygonShape()
{
    b2PolygonShape* poly = new b2PolygonShape();
    return poly;
}

Shape::Type PolygonShape::getType () {
    return Shape::Polygon;
}

void PolygonShape::set (std::vector<gdx_cpp::math::Vector2>& vertices) {
    int size = vertices.size() * 2;
    float verts [size];
    for (int i = 0, j = 0; i < size; i += 2, j++) {
        verts[i] = vertices[j].x;
        verts[i + 1] = vertices[j].y;
    }
    int numVertices = size / 2;
    b2Vec2* verticesOut = new b2Vec2[numVertices];
    for ( int i = 0; i < numVertices; i++ )
    {
        verticesOut[i] = b2Vec2(verts[i<<1], verts[(i<<1)+1]);
    }
    static_cast<b2PolygonShape*>(addr)->Set( verticesOut, numVertices );
    delete verticesOut;

}

void PolygonShape::setAsBox (float hx,float hy) {
    static_cast<b2PolygonShape*>(addr)->SetAsBox(hx, hy);
}

void PolygonShape::setAsBox (float hx,float hy,const gdx_cpp::math::Vector2& center,float angle) {
    static_cast<b2PolygonShape*>(addr)->SetAsBox( hx, hy, b2Vec2( center.x, center.y), angle );
}

void PolygonShape::setAsEdge (const gdx_cpp::math::Vector2& v1,const gdx_cpp::math::Vector2& v2) {
    static_cast<b2PolygonShape*>(addr)->SetAsEdge(b2Vec2( v1.x, v1.y), b2Vec2(v2.x, v2.y));
}

int PolygonShape::getVertexCount () {
    return static_cast<b2PolygonShape*>(addr)->GetVertexCount();
}

void PolygonShape::getVertex (int index, gdx_cpp::math::Vector2& vertex) {
    b2Vec2 v = static_cast<b2PolygonShape*>(addr)->GetVertex( index );
    vertex.x = v.x;
    vertex.y = v.y;
}

