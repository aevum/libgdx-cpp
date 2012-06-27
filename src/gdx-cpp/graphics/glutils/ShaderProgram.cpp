
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
#include "gdx-cpp/Graphics.hpp"
#include "gdx-cpp/Application.hpp"
#include <tr1/unordered_map>
#include <stdexcept>
#include "gdx-cpp/math/Matrix3.hpp"
#include "gdx-cpp/math/Matrix4.hpp"
#include <set>
#include <sstream>

using namespace gdx;

const std::string ShaderProgram::POSITION_ATTRIBUTE = "a_position";
const std::string ShaderProgram::NORMAL_ATTRIBUTE = "a_normal";
const std::string ShaderProgram::COLOR_ATTRIBUTE = "a_color";
const std::string ShaderProgram::TEXCOORD_ATTRIBUTE = "a_texCoord";
const std::string ShaderProgram::TANGENT_ATTRIBUTE = "a_tangent";
const std::string ShaderProgram::BINORMAL_ATTRIBUTE = "a_binormal";

std::tr1::unordered_map <Application *, std::set<ShaderProgram *> * > ShaderProgram::shaders;

bool ShaderProgram::pedantic = true;
int ShaderProgram::intbuf = 0;


ShaderProgram::ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader)
: params(0), type (0),
  isCompiledVar(false), program(0), vertexShaderHandle(0),
  fragmentShaderHandle(0), invalidated(false), refCount(0), matrix(16)
{
    compileShaders(vertexShader, fragmentShader);
    if (isCompiled()) {
        fetchAttributes();
        fetchUniforms();
        addManagedShader(app, this);
    }
}

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
    GL20 * gl = graphics->getGL20();
    //TODO BUFERRRRRRRRRRRRRrrs
//     ByteBuffer tmp = ByteBuffer.allocateDirect(4);
//     tmp.order(ByteOrder.nativeOrder());
//     IntBuffer intbuf = tmp.asIntBuffer();

    int shader = gl->glCreateShader(type);
    if (shader == 0) return -1;

    gl->glShaderSource(shader, source);
    gl->glCompileShader(shader);
//     gl->glGetShaderiv(shader, GL20.GL_COMPILE_STATUS, intbuf);
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
    GL20 *gl = graphics->getGL20();
    int program = gl->glCreateProgram();
    if (program == 0) return -1;

    gl->glAttachShader(program, vertexShaderHandle);
    gl->glAttachShader(program, fragmentShaderHandle);
    gl->glLinkProgram(program);

//     ByteBuffer tmp = ByteBuffer.allocateDirect(4);
//     tmp.order(ByteOrder.nativeOrder());
//     IntBuffer intbuf = tmp.asIntBuffer();
//
//     gl->glGetProgramiv(program, GL20.GL_LINK_STATUS, intbuf);
//     int linked = intbuf.get(0);
//     if (linked == 0) {
//         return -1;
//     }

    return program;
}

std::string ShaderProgram::getLog () {
    if (isCompiledVar) {
        gl20->glGetProgramiv(program, GL20::GL_INFO_LOG_LENGTH, &intbuf);
        int infoLogLength = intbuf;//.get(0);
        if (infoLogLength > 1) log = gl20->glGetProgramInfoLog(program);
        return log;
    } else {
        return log;
    }
}

bool ShaderProgram::isCompiled () {
    return isCompiledVar;
}

int ShaderProgram::fetchAttributeLocation (const std::string& name) {
    GL20 * gl = graphics->getGL20();
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

int ShaderProgram::fetchUniformLocation (const std::string& name) {
    GL20 * gl = graphics->getGL20();
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

void ShaderProgram::setUniformi (const std::string& name, int value) {
    GL20 * gl = graphics->getGL20();
    checkManaged();
    int location = fetchUniformLocation(name);
    gl->glUniform1i(location, value);
}

void ShaderProgram::setUniformi (const std::string& name, int value1, int value2) {
    GL20 * gl = graphics->getGL20();
    checkManaged();
    int location = fetchUniformLocation(name);
    gl->glUniform2i(location, value1, value2);
}

void ShaderProgram::setUniformi (const std::string& name, int value1, int value2, int value3) {
    GL20 * gl = graphics->getGL20();
    checkManaged();
    int location = fetchUniformLocation(name);
    gl->glUniform3i(location, value1, value2, value3);
}

void ShaderProgram::setUniformi (const std::string& name, int value1, int value2, int value3, int value4) {
    GL20 * gl = graphics->getGL20();
    checkManaged();
    int location = fetchUniformLocation(name);
    gl->glUniform4i(location, value1, value2, value3, value4);
}

void ShaderProgram::setUniformf (const std::string& name, float value) {
    GL20 * gl = graphics->getGL20();
    checkManaged();
    int location = fetchUniformLocation(name);
    gl->glUniform1f(location, value);
}

void ShaderProgram::setUniformf (const std::string& name, float value1, float value2) {
    GL20 * gl = graphics->getGL20();
    checkManaged();
    int location = fetchUniformLocation(name);
    gl->glUniform2f(location, value1, value2);
}

void ShaderProgram::setUniformf (const std::string& name, float value1, float value2, float value3) {
    GL20 * gl = graphics->getGL20();
    checkManaged();
    int location = fetchUniformLocation(name);
    gl->glUniform3f(location, value1, value2, value3);
}

void ShaderProgram::setUniformf (const std::string& name, float value1, float value2, float value3, float value4) {
    GL20 * gl = graphics->getGL20();
    checkManaged();
    int location = fetchUniformLocation(name);
    gl->glUniform4f(location, value1, value2, value3, value4);
}

void ShaderProgram::setUniform1fv (const std::string& name, float* values, int offset, int length) {
    GL20 * gl = graphics->getGL20();
    checkManaged();
    int location = fetchUniformLocation(name);
    ensureBufferCapacity(length << 2);
    floatBuffer.clear();
    floatBuffer.copy(values, length, offset);
    gl->glUniform1fv(location, length, floatBuffer);
}

void ShaderProgram::setUniform2fv (const std::string& name, float* values, int offset, int length) {
    GL20 * gl = graphics->getGL20();
    checkManaged();
    int location = fetchUniformLocation(name);
    ensureBufferCapacity(length << 2);
    floatBuffer.clear();
    floatBuffer.copy(values, length, offset);
    gl->glUniform2fv(location, length / 2, floatBuffer);
}

void ShaderProgram::setUniform3fv (const std::string& name, float* values, int offset, int length) {
    GL20 * gl = graphics->getGL20();
    checkManaged();
    int location = fetchUniformLocation(name);
    ensureBufferCapacity(length << 2);
    floatBuffer.clear();
    floatBuffer.copy(values, length, offset);
    gl->glUniform3fv(location, length / 3, floatBuffer);
}

void ShaderProgram::setUniform4fv (const std::string& name, float* values, int offset, int length) {
    GL20 * gl = graphics->getGL20();
    checkManaged();
    int location = fetchUniformLocation(name);
    ensureBufferCapacity(length << 2);
    floatBuffer.clear();
    floatBuffer.copy(values, length, offset);
    gl->glUniform4fv(location, length / 4, floatBuffer);
}

void ShaderProgram::setUniformMatrix (const std::string& name, const Matrix4& matrix) {
    setUniformMatrix(name, matrix, false);
}

void ShaderProgram::setUniformMatrix (const std::string& name, const Matrix4& matrix, bool transpose) {
    GL20 * gl = graphics->getGL20();
    checkManaged();
    int location = fetchUniformLocation(name);
    this->matrix.clear();

    this->matrix.copy(matrix.val, matrix.length, 0);
    gl->glUniformMatrix4fv(location, 1, transpose, this->matrix);
}

void ShaderProgram::setUniformMatrix (const std::string& name, Matrix3& matrix) {
    setUniformMatrix(name, matrix, false);
}

void ShaderProgram::setUniformMatrix (const std::string& name, Matrix3& matrix, bool transpose) {
    GL20 * gl = graphics->getGL20();
    checkManaged();
    int location = fetchUniformLocation(name);
    float * vals = matrix.getValues();
    this->matrix.clear();
    this->matrix.copy(vals, matrix.length, 0);
    gl->glUniformMatrix3fv(location, 1, transpose, this->matrix);
}

void ShaderProgram::setVertexAttribute (const std::string& name, int size, int type, bool normalize, int stride, ::buffer< float >* buffer) {
    GL20 * gl = graphics->getGL20();
    checkManaged();
    int location = fetchAttributeLocation(name);
    gl->glVertexAttribPointer(location, size, type, normalize, stride, buffer);
}

void ShaderProgram::setVertexAttribute (const std::string& name, int size, int type, bool normalize, int stride, int offset) {
    GL20 * gl = graphics->getGL20();
    checkManaged();
    int location = fetchAttributeLocation(name);
    if (location == -1) return;
    gl->glVertexAttribPointer(location, size, type, normalize, stride, offset);
}

void ShaderProgram::begin () {
    GL20 * gl = graphics->getGL20();
    checkManaged();
    gl->glUseProgram(program);
}

void ShaderProgram::end () {
    GL20 * gl = graphics->getGL20();
    gl->glUseProgram(0);
}

void ShaderProgram::dispose () {
    GL20 * gl = graphics->getGL20();
    gl->glUseProgram(0);
    gl->glDeleteShader(vertexShaderHandle);
    gl->glDeleteShader(fragmentShaderHandle);
    gl->glDeleteProgram(program);
    if (shaders.count(app) > 0) shaders[app]->erase(this);
}

void ShaderProgram::disableVertexAttribute (const std::string& name) {
    GL20 * gl = graphics->getGL20();
    checkManaged();
    int location = fetchAttributeLocation(name);
    if (location == -1) return;
    gl->glDisableVertexAttribArray(location);
}

void ShaderProgram::enableVertexAttribute (const std::string& name) {
    GL20 * gl = graphics->getGL20();
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

void ShaderProgram::addManagedShader (Application* app, ShaderProgram* shaderProgram) {
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

void ShaderProgram::invalidateAllShaderPrograms (Application* app) {
    if (graphics->getGL20() == NULL) return;

    if (shaders.count(app) > 0) return;

    std::set<ShaderProgram *> * shaderList = shaders[app];

    std::set<ShaderProgram *>::iterator it;
    for ( it=shaderList->begin() ; it != shaderList->end(); it++ )
    {
       (**it).invalidated = true;
       (*it)->checkManaged();
    }
}

void ShaderProgram::clearAllShaderPrograms (Application* app) {
    shaders.erase(app);
}

std::string ShaderProgram::getManagedStatus () {
    std::stringstream builder;
    builder << "Managed shaders/app: { ";
    std::tr1::unordered_map<Application *, std::set<ShaderProgram *> * >::iterator it;
    for (it = shaders.begin(); it != shaders.end(); ++it) {
        builder << it->second->size();
        builder << " ";
    }
    builder << "}";
    return builder.str();
}

void ShaderProgram::setAttributef (std::string& name,float value1,float value2,float value3,float value4) {
    GL20 * gl = graphics->getGL20();
    int location = fetchAttributeLocation(name);
    gl->glVertexAttrib4f(location, value1, value2, value3, value4);
}

void ShaderProgram::ensureBufferCapacity (int numBytes) {
    if (buffer.capacity() != numBytes) {
        buffer = byte_buffer(numBytes);
        floatBuffer = buffer.convert<float>();
        intBuffer = buffer.convert<int>();
    }
}

void ShaderProgram::fetchUniforms () {
    params=0;
    gl20->glGetProgramiv(program, GL20::GL_ACTIVE_UNIFORMS, &params);
    int numUniforms = params;

    uniformNames.reserve(numUniforms);

    for (int i = 0; i < numUniforms; i++) {
        params=256;
        type=0;
        std::string name =  gl20->glGetActiveUniform(program, i, &params, (char *) &type);
        int location = gl20->glGetUniformLocation(program, name);
        uniforms[name] =  location;
        uniformTypes[name] = type;
        uniformNames[i] = name;
    }
}

void ShaderProgram::fetchAttributes () {
    params = 0;
    gl20->glGetProgramiv(program, GL20::GL_ACTIVE_ATTRIBUTES, &params);
    int numAttributes = params;

    attributeNames.reserve(numAttributes);

    for (int i = 0; i < numAttributes; i++) {
        params = 256;
        type = 0;
        std::string name = gl20->glGetActiveAttrib(program, i, &params, (char*) &type);
        int location = gl20->glGetAttribLocation(program, name);
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

