
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

#include "ImmediateModeRenderer20.hpp"
#include "gdx-cpp/graphics/VertexAttribute.hpp"
#include "gdx-cpp/graphics/Color.hpp"
#include "gdx-cpp/utils/StringConvertion.hpp"

using namespace gdx;

std::vector< VertexAttribute > ImmediateModeRenderer20::buildVertexAttributes (bool hasNormals, bool hasColor, int numTexCoords) {
    std::vector<VertexAttribute> attribs;
    attribs.push_back(VertexAttribute(VertexAttributes::Usage::Position, 3, ShaderProgram::POSITION_ATTRIBUTE));

    if (hasNormals) {
        attribs.push_back(VertexAttribute(VertexAttributes::Usage::Normal, 3, ShaderProgram::NORMAL_ATTRIBUTE));
    }
    
    if (hasColor) {
        attribs.push_back(VertexAttribute(VertexAttributes::Usage::ColorPacked, 4, ShaderProgram::COLOR_ATTRIBUTE));
    }
    
    for (int i = 0; i < numTexCoords; i++) {
        attribs.push_back(VertexAttribute(VertexAttributes::Usage::TextureCoordinates, 2, ShaderProgram::TEXCOORD_ATTRIBUTE + to_string(i)));
    }
        
    return attribs;
}

std::string ImmediateModeRenderer20::createVertexShader (bool hasNormals, bool hasColors, int numTexCoords) {
    std::stringstream shader;
    shader << "attribute vec4 " + ShaderProgram::POSITION_ATTRIBUTE + ";\n"
           << (hasNormals ? "attribute vec3 " + ShaderProgram::NORMAL_ATTRIBUTE + ";\n" : "")
           << (hasColors ? "attribute vec4 " + ShaderProgram::COLOR_ATTRIBUTE + ";\n" : "");

    for (int i = 0; i < numTexCoords; i++) {
        shader << "attribute vec2 " + ShaderProgram::TEXCOORD_ATTRIBUTE << i << ";\n";
    }

    shader << "uniform mat4 u_projModelView;\n";
    shader << (hasColors ? "varying vec4 v_col;\n" : "");

    for (int i = 0; i < numTexCoords; i++) {
        shader << "varying vec2 v_tex" << i + ";\n";
    }

    shader << "void main() {\n" << "   gl_Position = u_projModelView * " << ShaderProgram::POSITION_ATTRIBUTE << ";\n"
           << (hasColors ? "   v_col = " + ShaderProgram::COLOR_ATTRIBUTE + ";\n" : "");

    for (int i = 0; i < numTexCoords; i++) {
        shader << "   v_tex" << i  << " = " + ShaderProgram::TEXCOORD_ATTRIBUTE <<  i << ";\n";
    }

    shader << "}\n";

    return shader.str();
}

std::string ImmediateModeRenderer20::createFragmentShader (bool hasNormals,bool hasColors,int numTexCoords) {
    std::stringstream shader;
    shader << "#ifdef GL_ES\nprecision highp float;\n#endif\n";

    if (hasColors) {
        shader << "varying vec4 v_col;\n";
    }
    for (int i = 0; i < numTexCoords; i++) {
        shader << "varying vec2 v_tex" << i << ";\n";
        shader << "uniform sampler2D u_sampler" <<  i << ";\n";
    }

    shader << "void main() {\n" << " gl_FragColor = " << (hasColors ? "v_col" : "vec4(1, 1, 1, 1)");

    if (numTexCoords > 0) {
        shader << " * ";
    }

    for (int i = 0; i < numTexCoords; i++) {
        if (i == numTexCoords - 1) {
            shader << " texture2D(u_sampler" << i << ",  v_tex" << i << ")";
        } else {
            shader << " texture2D(u_sampler" << i << ",  v_tex" << i << ") *";
        }
    }

    shader << ";\n}";

    return shader.str();
}

void ImmediateModeRenderer20::begin (Matrix4& projModelView, int primitiveType ) {
    this->customShader = NULL;
    
    this->projModelView.set(projModelView);
    this->primitiveType = primitiveType;
}

void ImmediateModeRenderer20::begin (ShaderProgram* shader,int primitiveType) {
    this->customShader = shader;
    this->primitiveType = primitiveType;
}

void ImmediateModeRenderer20::color (float r,float g,float b,float a) {
    vertices[vertexIdx + colorOffset] = Color::toFloatBits(r, g, b, a);
}

void ImmediateModeRenderer20::texCoord (float u,float v) {
    int idx = vertexIdx + texCoordOffset;
    vertices[idx] = u;
    vertices[idx + 1] = v;
    numSetTexCoords += 2;
}

void ImmediateModeRenderer20::normal (float x,float y,float z) {
    int idx = vertexIdx + normalOffset;
    vertices[idx] = x;
    vertices[idx + 1] = y;
    vertices[idx + 2] = z;
}

void ImmediateModeRenderer20::vertex (float x,float y,float z) {
    int idx = vertexIdx;
    vertices[idx] = x;
    vertices[idx + 1] = y;
    vertices[idx + 2] = z;

    numSetTexCoords = 0;
    vertexIdx += vertexSize;
    numVertices++;
}

void ImmediateModeRenderer20::end () {
    if (customShader != NULL) {
        customShader->begin();
        mesh.setVertices(vertices, vertexIdx);
        mesh.render(*customShader, primitiveType);
        customShader->end();
    } else {
        defaultShader->begin();
        defaultShader->setUniformMatrix("u_projModelView", projModelView);
        for (int i = 0; i < numTexCoords; i++) {
            defaultShader->setUniformi("u_sampler" + i, i);
        }
        mesh.setVertices(vertices, vertexIdx);
        mesh.render(*defaultShader, primitiveType);
        defaultShader->end();
    }

    numSetTexCoords = 0;
    vertexIdx = 0;
    numVertices = 0;
}

int ImmediateModeRenderer20::getNumVertices () {
    return numVertices;
}

int ImmediateModeRenderer20::getMaxVertices () {
    return maxVertices;
}

void ImmediateModeRenderer20::dispose () {
    if(defaultShader != NULL) defaultShader->dispose();
    mesh.dispose();
}

ImmediateModeRenderer20::ImmediateModeRenderer20 (bool hasNormals,bool hasColors,int numTexCoords, int maxVertices)
: primitiveType(0),
maxVertices(maxVertices),
attribs(buildVertexAttributes(hasNormals, hasColors, numTexCoords)),
mesh(false, maxVertices, 0, attribs),
vertexShader(createVertexShader(hasNormals, hasColors, numTexCoords)),
fragmentShader(createFragmentShader(hasNormals, hasColors, numTexCoords)),
defaultShader(new ShaderProgram(vertexShader, fragmentShader)),
numTexCoords(numTexCoords),
vertexIdx(0),
numSetTexCoords(0),
numVertices(0),
vertexSize(0),
normalOffset(0),
colorOffset(0),
texCoordOffset(0)
{
    if (!defaultShader->isCompiled())
        throw std::runtime_error("Couldn't compile immediate mode default shader!\n" + defaultShader->getLog());

    vertices = new float[maxVertices * (mesh.getVertexAttributes().vertexSize / 4)];
    vertexSize = mesh.getVertexAttributes().vertexSize / 4;
    normalOffset = mesh.getVertexAttribute(VertexAttributes::Usage::Normal) != NULL ? mesh.getVertexAttribute(VertexAttributes::Usage::Normal)->offset / 4 : 0;
    colorOffset = mesh.getVertexAttribute(VertexAttributes::Usage::ColorPacked) != NULL ? mesh.getVertexAttribute(VertexAttributes::Usage::ColorPacked)->offset / 4
                  : 0;
                  texCoordOffset = mesh.getVertexAttribute(VertexAttributes::Usage::TextureCoordinates) != NULL ? mesh
                  .getVertexAttribute(VertexAttributes::Usage::TextureCoordinates)->offset / 4 : 0;
}

