
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

#include "ShaderProgram.hpp"
#include "gdx-cpp/graphics/GL20.hpp"
#include "gdx-cpp/Gdx.hpp"
#include "gdx-cpp/Application.hpp"
#include <tr1/unordered_map>
#include <stdexcept>
#include "gdx-cpp/math/Matrix3.hpp"
#include "gdx-cpp/math/Matrix4.hpp"
#include <set>
#include <sstream>

using namespace gdx_cpp::graphics;
using namespace gdx_cpp::graphics::glutils;
using namespace gdx_cpp;

const std::string ShaderProgram::POSITION_ATTRIBUTE = "a_position";
const std::string ShaderProgram::NORMAL_ATTRIBUTE = "a_normal";
const std::string ShaderProgram::COLOR_ATTRIBUTE = "a_color";
const std::string ShaderProgram::TEXCOORD_ATTRIBUTE = "a_texCoord";
const std::string ShaderProgram::TANGENT_ATTRIBUTE = "a_tangent";
const std::string ShaderProgram::BINORMAL_ATTRIBUTE = "a_binormal";

std::tr1::unordered_map <gdx_cpp::Application *, std::set<ShaderProgram *> * > shaders();


std::string log;
bool isCompiledVar;

// const std::tr1::unordered_map <std::string, int> * ShaderProgram::uniforms = new std::tr1::unordered_map <std::string, int>();
// const std::tr1::unordered_map <std::string, int> * ShaderProgram::uniformTypes = new std::tr1::unordered_map <std::string, int>();

std::vector<std::string> uniformNames;

// const std::tr1::unordered_map <std::string, int> * ShaderProgram::attributes = new std::tr1::unordered_map <std::string, int>();
// const std::tr1::unordered_map <std::string, int> * ShaderProgram::attributeTypes = new std::tr1::unordered_map <std::string, int>();

bool ShaderProgram::pedantic = true;

void ShaderProgram::compileShaders (const std::string& vertexShader,const std::string& fragmentShader) {
    vertexShaderHandle = loadShader(GL20::GL_VERTEX_SHADER, vertexShader);
    fragmentShaderHandle = loadShader(GL20::GL_FRAGMENT_SHADER, fragmentShader);

    if (vertexShaderHandle == -1 || fragmentShaderHandle == -1) {
        isCompiledVar = false;
        return;
    }

    program = linkProgram();
    if (program == -1) {
        isCompiledVar = false;
        return;
    }

    isCompiledVar = true;
}

int ShaderProgram::loadShader (int type,const std::string& source) {
    gdx_cpp::graphics::GL20 * gl = gdx_cpp::Gdx::graphics->getGL20();
    //TODO BUFERRRRRRRRRRRRRrrs
//     ByteBuffer tmp = ByteBuffer.allocateDirect(4);
//     tmp.order(ByteOrder.nativeOrder());
//     IntBuffer intbuf = tmp.asIntBuffer();

    int shader = gl->glCreateShader(type);
    if (shader == 0) return -1;

    gl->glShaderSource(shader, source);
    gl->glCompileShader(shader);
//     gl->glGetShaderiv(shader, gdx_cpp::graphics::GL20.GL_COMPILE_STATUS, intbuf);
//
//     int compiled = intbuf.get(0);
//     if (compiled == 0) {
//         gl->glGetShaderiv(shader, GL20.GL_INFO_LOG_LENGTH, intbuf);
//         int infoLogLength = intbuf.get(0);
//         if (infoLogLength > 1) {
//             String infoLog = gl->glGetShaderInfoLog(shader);
//             log += infoLog;
//         }
//         return -1;
//     }

    return shader;
}

int ShaderProgram::linkProgram () {
    gdx_cpp::graphics::GL20 *gl = gdx_cpp::Gdx::graphics->getGL20();
    int program = gl->glCreateProgram();
    if (program == 0) return -1;

    gl->glAttachShader(program, vertexShaderHandle);
    gl->glAttachShader(program, fragmentShaderHandle);
    gl->glLinkProgram(program);

//     ByteBuffer tmp = ByteBuffer.allocateDirect(4);
//     tmp.order(ByteOrder.nativeOrder());
//     IntBuffer intbuf = tmp.asIntBuffer();
//
//     gl->glGetProgramiv(program, gdx_cpp::graphics::GL20.GL_LINK_STATUS, intbuf);
//     int linked = intbuf.get(0);
//     if (linked == 0) {
//         return -1;
//     }

    return program;
}

std::string ShaderProgram::getLog () {
    if (isCompiledVar) {
        gdx_cpp::Gdx::gl20->glGetProgramiv(program, gdx_cpp::graphics::GL20::GL_INFO_LOG_LENGTH, &intbuf);
        int infoLogLength = intbuf;//.get(0);
        if (infoLogLength > 1) log = gdx_cpp::Gdx::gl20->glGetProgramInfoLog(program);
        return log;
    } else {
        return log;
    }
}

bool ShaderProgram::isCompiled () {
    return isCompiledVar;
}

int ShaderProgram::fetchAttributeLocation (const std::string& name) {
    gdx_cpp::graphics::GL20 * gl = gdx_cpp::Gdx::graphics->getGL20();
    int location;
    if (attributes.count(name) == 0)
    {
        location = gl->glGetAttribLocation(program, name);
        if (location != -1) attributes[name] = location;
    } else
    {
        location = attributes[name];
    }
    return location;
}

int ShaderProgram::fetchUniformLocation (std::string& name) {
    gdx_cpp::graphics::GL20 * gl = gdx_cpp::Gdx::graphics->getGL20();
    int location;
    if (uniforms.count(name) == 0) {
        location = gl->glGetUniformLocation(program, name);
        if (location == -1 && pedantic)throw std::runtime_error("no uniform with name '" + name + "' in shader");
        uniforms[name] = location;
    }else
    {
        location = uniforms[name];
    }
    return location;
}

void ShaderProgram::setUniformi (std::string& name,int value) {
    gdx_cpp::graphics::GL20 * gl = gdx_cpp::Gdx::graphics->getGL20();
    checkManaged();
    int location = fetchUniformLocation(name);
    gl->glUniform1i(location, value);
}

void ShaderProgram::setUniformi (std::string& name,int value1,int value2) {
    gdx_cpp::graphics::GL20 * gl = gdx_cpp::Gdx::graphics->getGL20();
    checkManaged();
    int location = fetchUniformLocation(name);
    gl->glUniform2i(location, value1, value2);
}

void ShaderProgram::setUniformi (std::string& name,int value1,int value2,int value3) {
    gdx_cpp::graphics::GL20 * gl = gdx_cpp::Gdx::graphics->getGL20();
    checkManaged();
    int location = fetchUniformLocation(name);
    gl->glUniform3i(location, value1, value2, value3);
}

void ShaderProgram::setUniformi (std::string& name,int value1,int value2,int value3,int value4) {
    gdx_cpp::graphics::GL20 * gl = gdx_cpp::Gdx::graphics->getGL20();
    checkManaged();
    int location = fetchUniformLocation(name);
    gl->glUniform4i(location, value1, value2, value3, value4);
}

void ShaderProgram::setUniformf (std::string& name,float value) {
    gdx_cpp::graphics::GL20 * gl = gdx_cpp::Gdx::graphics->getGL20();
    checkManaged();
    int location = fetchUniformLocation(name);
    gl->glUniform1f(location, value);
}

void ShaderProgram::setUniformf (std::string& name,float value1,float value2) {
    gdx_cpp::graphics::GL20 * gl = gdx_cpp::Gdx::graphics->getGL20();
    checkManaged();
    int location = fetchUniformLocation(name);
    gl->glUniform2f(location, value1, value2);
}

void ShaderProgram::setUniformf (std::string& name,float value1,float value2,float value3) {
    gdx_cpp::graphics::GL20 * gl = gdx_cpp::Gdx::graphics->getGL20();
    checkManaged();
    int location = fetchUniformLocation(name);
    gl->glUniform3f(location, value1, value2, value3);
}

void ShaderProgram::setUniformf (std::string& name,float value1,float value2,float value3,float value4) {
    gdx_cpp::graphics::GL20 * gl = gdx_cpp::Gdx::graphics->getGL20();
    checkManaged();
    int location = fetchUniformLocation(name);
    gl->glUniform4f(location, value1, value2, value3, value4);
}

void ShaderProgram::setUniform1fv (std::string& name, float * values, int offset,int length) {
    gdx_cpp::graphics::GL20 * gl = gdx_cpp::Gdx::graphics->getGL20();
    checkManaged();
    int location = fetchUniformLocation(name);
    ensureBufferCapacity(length << 2);
    floatBuffer.clear();
    floatBuffer.copy(values, length, offset);
    gl->glUniform1fv(location, length, floatBuffer);
}

void ShaderProgram::setUniform2fv (std::string& name, float * values, int offset,int length) {
    gdx_cpp::graphics::GL20 * gl = gdx_cpp::Gdx::graphics->getGL20();
    checkManaged();
    int location = fetchUniformLocation(name);
    ensureBufferCapacity(length << 2);
    floatBuffer.clear();
    floatBuffer.copy(values, length, offset);
    gl->glUniform2fv(location, length / 2, floatBuffer);
}

void ShaderProgram::setUniform3fv (std::string& name,float * values, int offset,int length) {
    gdx_cpp::graphics::GL20 * gl = gdx_cpp::Gdx::graphics->getGL20();
    checkManaged();
    int location = fetchUniformLocation(name);
    ensureBufferCapacity(length << 2);
    floatBuffer.clear();
    floatBuffer.copy(values, length, offset);
    gl->glUniform3fv(location, length / 3, floatBuffer);
}

void ShaderProgram::setUniform4fv (std::string& name,float * values, int offset,int length) {
    gdx_cpp::graphics::GL20 * gl = gdx_cpp::Gdx::graphics->getGL20();
    checkManaged();
    int location = fetchUniformLocation(name);
    ensureBufferCapacity(length << 2);
    floatBuffer.clear();
    floatBuffer.copy(values, length, offset);
    gl->glUniform4fv(location, length / 4, floatBuffer);
}

void ShaderProgram::setUniformMatrix (std::string& name,const gdx_cpp::math::Matrix4& matrix) {
    setUniformMatrix(name, matrix, false);
}

void ShaderProgram::setUniformMatrix (std::string& name,const gdx_cpp::math::Matrix4& matrix,bool transpose) {
    gdx_cpp::graphics::GL20 * gl = gdx_cpp::Gdx::graphics->getGL20();
    checkManaged();
    int location = fetchUniformLocation(name);
    this->matrix.clear();

    this->matrix.copy(matrix.val, matrix.length, 0);
    gl->glUniformMatrix4fv(location, 1, transpose, this->matrix);
}

void ShaderProgram::setUniformMatrix (std::string& name, gdx_cpp::math::Matrix3& matrix) {
    setUniformMatrix(name, matrix, false);
}

void ShaderProgram::setUniformMatrix (std::string& name, gdx_cpp::math::Matrix3& matrix,bool transpose) {
    gdx_cpp::graphics::GL20 * gl = gdx_cpp::Gdx::graphics->getGL20();
    checkManaged();
    int location = fetchUniformLocation(name);
    float * vals = matrix.getValues();
    this->matrix.clear();
    this->matrix.copy(vals, matrix.length, 0);
    gl->glUniformMatrix3fv(location, 1, transpose, this->matrix);
}

void ShaderProgram::setVertexAttribute (std::string& name,int size,int type,bool normalize,int stride, gdx_cpp::utils::buffer<float>* buffer) {
    gdx_cpp::graphics::GL20 * gl = gdx_cpp::Gdx::graphics->getGL20();
    checkManaged();
    int location = fetchAttributeLocation(name);
    gl->glVertexAttribPointer(location, size, type, normalize, stride, buffer);
}

void ShaderProgram::setVertexAttribute (std::string& name,int size,int type,bool normalize,int stride,int offset) {
    gdx_cpp::graphics::GL20 * gl = gdx_cpp::Gdx::graphics->getGL20();
    checkManaged();
    int location = fetchAttributeLocation(name);
    if (location == -1) return;
    gl->glVertexAttribPointer(location, size, type, normalize, stride, offset);
}

void ShaderProgram::begin () {
    gdx_cpp::graphics::GL20 * gl = gdx_cpp::Gdx::graphics->getGL20();
    checkManaged();
    gl->glUseProgram(program);
}

void ShaderProgram::end () {
    gdx_cpp::graphics::GL20 * gl = gdx_cpp::Gdx::graphics->getGL20();
    gl->glUseProgram(0);
}

void ShaderProgram::dispose () {
    gdx_cpp::graphics::GL20 * gl = gdx_cpp::Gdx::graphics->getGL20();
    gl->glUseProgram(0);
    gl->glDeleteShader(vertexShaderHandle);
    gl->glDeleteShader(fragmentShaderHandle);
    gl->glDeleteProgram(program);
    if (shaders.count(Gdx::app) > 0) shaders[Gdx::app]->erase(this);
}

void ShaderProgram::disableVertexAttribute (std::string& name) {
    gdx_cpp::graphics::GL20 * gl = gdx_cpp::Gdx::graphics->getGL20();
    checkManaged();
    int location = fetchAttributeLocation(name);
    if (location == -1) return;
    gl->glDisableVertexAttribArray(location);
}

void ShaderProgram::enableVertexAttribute (std::string& name) {
    gdx_cpp::graphics::GL20 * gl = gdx_cpp::Gdx::graphics->getGL20();
    checkManaged();
    int location = fetchAttributeLocation(name);
    if (location == -1) return;
    gl->glEnableVertexAttribArray(location);
}

void ShaderProgram::checkManaged () {
    if (invalidated) {
        compileShaders(vertexShaderSource, fragmentShaderSource);
        invalidated = false;
    }
}

void ShaderProgram::addManagedShader (gdx_cpp::Application* app, ShaderProgram* shaderProgram) {
    std::set<ShaderProgram *> *  managedResources;

    if (shaders.count(app) > 0)
    {
      managedResources =  shaders[app];
    }
    else
    {
      managedResources =  new std::set<ShaderProgram *>;
      shaders[app] = managedResources;
    }
    managedResources->insert(shaderProgram);
}

void ShaderProgram::invalidateAllShaderPrograms (gdx_cpp::Application* app) {
    if (gdx_cpp::Gdx::graphics->getGL20() == NULL) return;

    if (shaders.count(app) > 0) return;

    std::set<ShaderProgram *> * shaderList = shaders[app];

    std::set<ShaderProgram *>::iterator it;
    for ( it=shaderList->begin() ; it != shaderList->end(); it++ )
    {
       (**it).invalidated = true;
       (*it)->checkManaged();
    }
}

void ShaderProgram::clearAllShaderPrograms (gdx_cpp::Application* app) {
    shaders.erase(app);
}

std::string ShaderProgram::getManagedStatus () {
    std::stringstream builder;
    int i = 0;
    builder << "Managed shaders/app: { ";
    std::tr1::unordered_map<gdx_cpp::Application *, std::set<ShaderProgram *> * >::iterator it;
    for (it = shaders.begin(); it != shaders.end(); ++it) {
        builder << it->second->size();
        builder << " ";
    }
    builder << "}";
    return builder.str();
}

void ShaderProgram::setAttributef (std::string& name,float value1,float value2,float value3,float value4) {
    gdx_cpp::graphics::GL20 * gl = gdx_cpp::Gdx::graphics->getGL20();
    int location = fetchAttributeLocation(name);
    gl->glVertexAttrib4f(location, value1, value2, value3, value4);
}

void ShaderProgram::ensureBufferCapacity (int numBytes) {
    if (buffer ==NULL || buffer.capacity() != numBytes) {
        buffer = gdx_cpp::utils::byte_buffer(numBytes);
        floatBuffer = buffer.convert<float>();
        intBuffer = buffer.convert<int>();
    }
}

void ShaderProgram::fetchUniforms () {
    params=0;
    gdx_cpp::Gdx::gl20->glGetProgramiv(program, gdx_cpp::graphics::GL20::GL_ACTIVE_UNIFORMS, &params);
    int numUniforms = params;

    uniformNames.reserve(numUniforms);

    for (int i = 0; i < numUniforms; i++) {
        params=256;
        type=0;
        std::string name =  Gdx::gl20->glGetActiveUniform(program, i, &params, (char *) &type);
        int location = Gdx::gl20->glGetUniformLocation(program, name);
        uniforms[name] =  location;
        uniformTypes[name] = type;
        uniformNames[i] = name;
    }
}

void ShaderProgram::fetchAttributes () {
    params = 0;
    Gdx::gl20->glGetProgramiv(program, GL20::GL_ACTIVE_ATTRIBUTES, &params);
    int numAttributes = params;

    attributeNames.reserve(numAttributes);

    for (int i = 0; i < numAttributes; i++) {
        params = 256;
        type = 0;
        std::string name = Gdx::gl20->glGetActiveAttrib(program, i, &params, (char*) &type);
        int location = Gdx::gl20->glGetAttribLocation(program, name);
        attributes[name] = location;
        attributeTypes[name] = type;
        attributeNames[i] = name;
    }
}

bool ShaderProgram::hasAttribute (const std::string& name) {
    return attributes.count(name) > 0;
}

int ShaderProgram::getAttributeType (const std::string& name) {
    return attributes[name];
}

int ShaderProgram::getAttributeLocation (const std::string& name) {
    if (attributes.count(name) == 0)
        return -1;
    else
        return attributes[name];
}

bool ShaderProgram::hasUniform (const std::string& name) {
    return uniforms.count(name) > 0;
}

int ShaderProgram::getUniformType (const std::string& name) {
    return attributes[name];
}

int ShaderProgram::getUniformLocation (const std::string& name) {
    if (uniforms.count(name) == 0)
        return -1;
    else
        return uniforms[name];
}

std::vector<std::string>& ShaderProgram::getAttributes () {
    return attributeNames;
}

std::vector<std::string>& ShaderProgram::getUniforms () {
  return uniformNames;
}

