
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

using namespace gdx_cpp::graphics::glutils;

FloatBuffer& ImmediateModeRenderer10::allocateBuffer (int numFloats) {
    ByteBuffer buffer = ByteBuffer.allocateDirect(numFloats * 4);
    buffer.order(ByteOrder.nativeOrder());
    return buffer.asFloatBuffer();
}

void ImmediateModeRenderer10::begin (const gdx_cpp::math::Matrix4& projModelView,int primitiveType) {
    GL10 gl = Gdx.gl10;
    gl.glMatrixMode(GL10.GL_PROJECTION);
    gl.glLoadMatrixf(projModelView.val, 0);
    gl.glMatrixMode(GL10.GL_MODELVIEW);
    gl.glLoadIdentity();
    begin(primitiveType);
}

void ImmediateModeRenderer10::begin (int primitiveType) {
    this.primitiveType = primitiveType;
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
}

int ImmediateModeRenderer10::getNumVertices () {
    return idxPos / 3;
}

void ImmediateModeRenderer10::end () {
    if (idxPos == 0) return;

    GL10 gl = Gdx.gl10;
    gl.glEnableClientState(GL10.GL_VERTEX_ARRAY);
    positionsBuffer.clear();
    BufferUtils.copy(positions, positionsBuffer, idxPos, 0);
    gl.glVertexPointer(3, GL10.GL_FLOAT, 0, positionsBuffer);

    if (hasCols) {
        gl.glEnableClientState(GL10.GL_COLOR_ARRAY);
        colorsBuffer.clear();
        BufferUtils.copy(colors, colorsBuffer, idxCols, 0);
        gl.glColorPointer(4, GL10.GL_FLOAT, 0, colorsBuffer);
    }

    if (hasNors) {
        gl.glEnableClientState(GL10.GL_NORMAL_ARRAY);
        normalsBuffer.clear();
        BufferUtils.copy(normals, normalsBuffer, idxNors, 0);
        gl.glNormalPointer(GL10.GL_FLOAT, 0, normalsBuffer);
    }

    if (hasTexCoords) {
        gl.glClientActiveTexture(GL10.GL_TEXTURE0);
        gl.glEnableClientState(GL10.GL_TEXTURE_COORD_ARRAY);
        texCoordsBuffer.clear();
        BufferUtils.copy(texCoords, texCoordsBuffer, idxTexCoords, 0);
        gl.glTexCoordPointer(2, GL10.GL_FLOAT, 0, texCoordsBuffer);
    }

    gl.glDrawArrays(primitiveType, 0, idxPos / 3);

    if (hasCols) gl.glDisableClientState(GL10.GL_COLOR_ARRAY);
    if (hasNors) gl.glDisableClientState(GL10.GL_NORMAL_ARRAY);
    if (hasTexCoords) gl.glDisableClientState(GL10.GL_TEXTURE_COORD_ARRAY);
}

void ImmediateModeRenderer10::vertex (const gdx_cpp::math::Vector3& point) {
    vertex(point.x, point.y, point.z);
}

