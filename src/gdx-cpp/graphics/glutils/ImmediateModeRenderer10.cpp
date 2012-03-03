
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

#include "ImmediateModeRenderer10.hpp"
#include "gdx-cpp/graphics/GL10.hpp"
#include "gdx-cpp/Gdx.hpp"
#include "gdx-cpp/math/Matrix4.hpp"
#include "gdx-cpp/math/Vector3.hpp"

using namespace gdx_cpp::graphics::glutils;


ImmediateModeRenderer10::ImmediateModeRenderer10 (int maxVertices) :
primitiveType(false), idxPos(0), idxCols(0), idxNors(0), idxTexCoords(0),
hasCols(false), hasNors(false), hasTexCoords(false), maxVertices(maxVertices)
{
    this->positions = new float[3 * maxVertices];
    this->positionsBuffer = allocateBuffer(3 * maxVertices);
    this->colors = new float[4 * maxVertices];
    this->colorsBuffer = allocateBuffer(4 * maxVertices);
    this->normals = new float[3 * maxVertices];
    this->normalsBuffer = allocateBuffer(3 * maxVertices);
    this->texCoords = new float[2 * maxVertices];
    this->texCoordsBuffer = allocateBuffer(2 * maxVertices);
}

ImmediateModeRenderer10::~ImmediateModeRenderer10 ()
{
    delete [] this->positions;
    delete [] this->colors;
    delete [] this->normals;
    delete [] this->texCoords;
}

gdx_cpp::utils::float_buffer ImmediateModeRenderer10::allocateBuffer (int numFloats) {
    gdx_cpp::utils::byte_buffer buffer(numFloats * 4);
//     buffer->order(ByteOrder.nativeOrder());
    return buffer.convert<float>();
}

void ImmediateModeRenderer10::begin (gdx_cpp::math::Matrix4& projModelView,int primitiveType) {
    gdx_cpp::graphics::GL10 * gl = gdx_cpp::Gdx::gl10;
    gl->glMatrixMode(gdx_cpp::graphics::GL10::GL_PROJECTION);
    gl->glLoadMatrixf(projModelView.val);
    gl->glMatrixMode(gdx_cpp::graphics::GL10::GL_MODELVIEW);
    gl->glLoadIdentity();
    begin(primitiveType);
}

void ImmediateModeRenderer10::begin (int primitiveType) {
    this->primitiveType = primitiveType;
    numVertices = 0;
    idxPos = 0;
    idxCols = 0;
    idxNors = 0;
    idxTexCoords = 0;
    hasCols = false;
    hasNors = false;
    hasTexCoords = false;
}

void ImmediateModeRenderer10::color (float r,float g,float b,float a) {
    colors[idxCols] = r;
    colors[idxCols + 1] = g;
    colors[idxCols + 2] = b;
    colors[idxCols + 3] = a;
    hasCols = true;
}

void ImmediateModeRenderer10::normal (float x,float y,float z) {
    normals[idxNors] = x;
    normals[idxNors + 1] = y;
    normals[idxNors + 2] = z;
    hasNors = true;
}

void ImmediateModeRenderer10::texCoord (float u,float v) {
    texCoords[idxTexCoords] = u;
    texCoords[idxTexCoords + 1] = v;
    hasTexCoords = true;
}

void ImmediateModeRenderer10::vertex (float x,float y,float z) {
    positions[idxPos++] = x;
    positions[idxPos++] = y;
    positions[idxPos++] = z;

    if (hasCols) idxCols += 4;
    if (hasNors) idxNors += 3;
    if (hasTexCoords) idxTexCoords += 2;
    numVertices++;
}

int ImmediateModeRenderer10::getNumVertices () {
    return idxPos / 3;
}

void ImmediateModeRenderer10::end () {
    if (idxPos == 0) return;

    gdx_cpp::graphics::GL10 * gl = gdx_cpp::Gdx::gl10;
    gl->glEnableClientState(gdx_cpp::graphics::GL10::GL_VERTEX_ARRAY);
    positionsBuffer.clear();
    positionsBuffer.copy<float>(positions, idxPos, 0);
    gl->glVertexPointer(3, gdx_cpp::graphics::GL10::GL_FLOAT, 0, positionsBuffer);

    if (hasCols) {
        gl->glEnableClientState(gdx_cpp::graphics::GL10::GL_COLOR_ARRAY);
        colorsBuffer.clear();
        colorsBuffer.copy<float>(colors, idxCols, 0);
        gl->glColorPointer(4, gdx_cpp::graphics::GL10::GL_FLOAT, 0, colorsBuffer);
    }

    if (hasNors) {
        gl->glEnableClientState(gdx_cpp::graphics::GL10::GL_NORMAL_ARRAY);
        normalsBuffer.clear();
        normalsBuffer.copy<float>(normals, idxNors, 0);
        gl->glNormalPointer(gdx_cpp::graphics::GL10::GL_FLOAT, 0, normalsBuffer);
    }

    if (hasTexCoords) {
        gl->glClientActiveTexture(gdx_cpp::graphics::GL10::GL_TEXTURE0);
        gl->glEnableClientState(gdx_cpp::graphics::GL10::GL_TEXTURE_COORD_ARRAY);
        texCoordsBuffer.clear();
        texCoordsBuffer.copy<float>(texCoords, idxTexCoords, 0);
        gl->glTexCoordPointer(2, gdx_cpp::graphics::GL10::GL_FLOAT, 0, texCoordsBuffer);
    }

    gl->glDrawArrays(primitiveType, 0, idxPos / 3);

    if (hasCols) gl->glDisableClientState(gdx_cpp::graphics::GL10::GL_COLOR_ARRAY);
    if (hasNors) gl->glDisableClientState(gdx_cpp::graphics::GL10::GL_NORMAL_ARRAY);
    if (hasTexCoords) gl->glDisableClientState(gdx_cpp::graphics::GL10::GL_TEXTURE_COORD_ARRAY);
}

void ImmediateModeRenderer10::vertex (const gdx_cpp::math::Vector3& point) {
    vertex(point.x, point.y, point.z);
}

int gdx_cpp::graphics::glutils::ImmediateModeRenderer10::getMaxVertices()
{
    return maxVertices; 
}

void gdx_cpp::graphics::glutils::ImmediateModeRenderer10::dispose()
{

}
