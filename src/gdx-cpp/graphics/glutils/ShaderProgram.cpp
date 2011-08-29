
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


using namespace gdx_cpp::graphics::glutils;


const std::string ShaderProgram::POSITION_ATTRIBUTE = "a_position";
const std::string ShaderProgram::NORMAL_ATTRIBUTE = "a_normal";
const std::string ShaderProgram::COLOR_ATTRIBUTE = "a_color";
const std::string ShaderProgram::TEXCOORD_ATTRIBUTE = "a_texCoord";
const std::string ShaderProgram::TANGENT_ATTRIBUTE = "a_tangent";
const std::string ShaderProgram::BINORMAL_ATTRIBUTE = "a_binormal";

const std::tr1::unordered_map <gdx_cpp::Application *, std::vector<ShaderProgram> > * ShaderProgram::shaders = new std::tr1::unordered_map <gdx_cpp::Application *, std::vector<ShaderProgram> >();


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

std::string& ShaderProgram::getLog () {
    if (isCompiledVar) {
        gdx_cpp::Gdx::gl20->glGetProgramiv(program, gdx_cpp::graphics::GL20::GL_INFO_LOG_LENGTH, intbuf);
        int infoLogLength = intbuf[0];//.get(0);
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
    if (attributes->count(name) == 0)
    {
        location = gl->glGetAttribLocation(program, name);
        if (location != -1) (*attributes)[name] = location;
    } else
    {
        location = (*attributes)[name];
    }
    return location;
}

int ShaderProgram::fetchUniformLocation (const std::string& name) {
    gdx_cpp::graphics::GL20 * gl = gdx_cpp::Gdx::graphics->getGL20();
    int location;
    if (uniforms->count(name) == 0) {
        location = gl->glGetUniformLocation(program, name);
        if (location == -1 && pedantic) throw std::std_runtime_exception("no uniform with name '" + name + "' in shader");
        uniforms.put(name, location);
    }else
    {
        location = uniforms[name];
    }
    return location;
}

void ShaderProgram::setUniformi (const std::string& name,int value) {
    gdx_cpp::graphics::GL20 * gl = gdx_cpp::Gdx::graphics->getGL20();
    checkManaged();
    int location = fetchUniformLocation(name);
    gl->glUniform1i(location, value);
}

void ShaderProgram::setUniformi (const std::string& name,int value1,int value2) {
    gdx_cpp::graphics::GL20 * gl = gdx_cpp::Gdx::graphics->getGL20();
    checkManaged();
    int location = fetchUniformLocation(name);
    gl->glUniform2i(location, value1, value2);
}

void ShaderProgram::setUniformi (const std::string& name,int value1,int value2,int value3) {
    gdx_cpp::graphics::GL20 * gl = gdx_cpp::Gdx::graphics->getGL20();
    checkManaged();
    int location = fetchUniformLocation(name);
    gl->glUniform3i(location, value1, value2, value3);
}

void ShaderProgram::setUniformi (const std::string& name,int value1,int value2,int value3,int value4) {
    gdx_cpp::graphics::GL20 * gl = gdx_cpp::Gdx::graphics->getGL20();
    checkManaged();
    int location = fetchUniformLocation(name);
    gl->glUniform4i(location, value1, value2, value3, value4);
}

void ShaderProgram::setUniformf (const std::string& name,float value) {
    gdx_cpp::graphics::GL20 * gl = gdx_cpp::Gdx::graphics->getGL20();
    checkManaged();
    int location = fetchUniformLocation(name);
    gl->glUniform1f(location, value);
}

void ShaderProgram::setUniformf (const std::string& name,float value1,float value2) {
    gdx_cpp::graphics::GL20 * gl = gdx_cpp::Gdx::graphics->getGL20();
    checkManaged();
    int location = fetchUniformLocation(name);
    gl->glUniform2f(location, value1, value2);
}

void ShaderProgram::setUniformf (const std::string& name,float value1,float value2,float value3) {
    gdx_cpp::graphics::GL20 * gl = gdx_cpp::Gdx::graphics->getGL20();
    checkManaged();
    int location = fetchUniformLocation(name);
    gl->glUniform3f(location, value1, value2, value3);
}

void ShaderProgram::setUniformf (const std::string& name,float value1,float value2,float value3,float value4) {
    gdx_cpp::graphics::GL20 * gl = gdx_cpp::Gdx::graphics->getGL20();
    checkManaged();
    int location = fetchUniformLocation(name);
    gl->glUniform4f(location, value1, value2, value3, value4);
}

void ShaderProgram::setUniform1fv (const std::string& name,int offset,int length) {
    gdx_cpp::graphics::GL20 * gl = gdx_cpp::Gdx::graphics->getGL20();
    checkManaged();
    int location = fetchUniformLocation(name);
    ensureBufferCapacity(length << 2);
    floatBuffer.clear();
    BufferUtils.copy(values, floatBuffer, length, offset);
    gl->glUniform1fv(location, length, floatBuffer);
}

void ShaderProgram::setUniform2fv (const std::string& name,int offset,int length) {
    GL20 gl = Gdx.graphics.getGL20();
    checkManaged();
    int location = fetchUniformLocation(name);
    ensureBufferCapacity(length << 2);
    floatBuffer.clear();
    BufferUtils.copy(values, floatBuffer, length, offset);
    gl.glUniform2fv(location, length / 2, floatBuffer);
}

void ShaderProgram::setUniform3fv (const std::string& name,int offset,int length) {
    GL20 gl = Gdx.graphics.getGL20();
    checkManaged();
    int location = fetchUniformLocation(name);
    ensureBufferCapacity(length << 2);
    floatBuffer.clear();
    BufferUtils.copy(values, floatBuffer, length, offset);
    gl.glUniform3fv(location, length / 3, floatBuffer);
}

void ShaderProgram::setUniform4fv (const std::string& name,int offset,int length) {
    GL20 gl = Gdx.graphics.getGL20();
    checkManaged();
    int location = fetchUniformLocation(name);
    ensureBufferCapacity(length << 2);
    floatBuffer.clear();
    BufferUtils.copy(values, floatBuffer, length, offset);
    gl.glUniform4fv(location, length / 4, floatBuffer);
}

void ShaderProgram::setUniformMatrix (const std::string& name,const gdx_cpp::math::Matrix4& matrix) {
    setUniformMatrix(name, matrix, false);
}

void ShaderProgram::setUniformMatrix (const std::string& name,const gdx_cpp::math::Matrix4& matrix,bool transpose) {
    GL20 gl = Gdx.graphics.getGL20();
    checkManaged();
    int location = fetchUniformLocation(name);
    this.matrix.clear();
    BufferUtils.copy(matrix.val, this.matrix, matrix.val.length, 0);
    gl.glUniformMatrix4fv(location, 1, transpose, this.matrix);
}

void ShaderProgram::setUniformMatrix (const std::string& name,const gdx_cpp::math::Matrix3& matrix) {
    setUniformMatrix(name, matrix, false);
}

void ShaderProgram::setUniformMatrix (const std::string& name,const gdx_cpp::math::Matrix3& matrix,bool transpose) {
    GL20 gl = Gdx.graphics.getGL20();
    checkManaged();
    int location = fetchUniformLocation(name);
    float[] vals = matrix.getValues();
    this.matrix.clear();
    BufferUtils.copy(vals, this.matrix, vals.length, 0);
    gl.glUniformMatrix3fv(location, 1, transpose, this.matrix);
}

void ShaderProgram::setVertexAttribute (const std::string& name,int size,int type,bool normalize,int stride,const FloatBuffer& buffer) {
    GL20 gl = Gdx.graphics.getGL20();
    checkManaged();
    int location = fetchAttributeLocation(name);
    gl.glVertexAttribPointer(location, size, type, normalize, stride, buffer);
}

void ShaderProgram::setVertexAttribute (const std::string& name,int size,int type,bool normalize,int stride,int offset) {
    GL20 gl = Gdx.graphics.getGL20();
    checkManaged();
    int location = fetchAttributeLocation(name);
    if (location == -1) return;
    gl.glVertexAttribPointer(location, size, type, normalize, stride, offset);
}

void ShaderProgram::begin () {
    GL20 gl = Gdx.graphics.getGL20();
    checkManaged();
    gl.glUseProgram(program);
}

void ShaderProgram::end () {
    GL20 gl = Gdx.graphics.getGL20();
    gl.glUseProgram(0);
}

void ShaderProgram::dispose () {
    GL20 gl = Gdx.graphics.getGL20();
    gl.glUseProgram(0);
    gl.glDeleteShader(vertexShaderHandle);
    gl.glDeleteShader(fragmentShaderHandle);
    gl.glDeleteProgram(program);
    if (shaders.get(Gdx.app) != null) shaders.get(Gdx.app).remove(this);
}

void ShaderProgram::disableVertexAttribute (const std::string& name) {
    GL20 gl = Gdx.graphics.getGL20();
    checkManaged();
    int location = fetchAttributeLocation(name);
    if (location == -1) return;
    gl.glDisableVertexAttribArray(location);
}

void ShaderProgram::enableVertexAttribute (const std::string& name) {
    GL20 gl = Gdx.graphics.getGL20();
    checkManaged();
    int location = fetchAttributeLocation(name);
    if (location == -1) return;
    gl.glEnableVertexAttribArray(location);
}

void ShaderProgram::checkManaged () {
    if (invalidated) {
        compileShaders(vertexShaderSource, fragmentShaderSource);
        invalidated = false;
    }
}

void ShaderProgram::addManagedShader (const gdx_cpp::Application& app,const ShaderProgram& shaderProgram) {
    List<ShaderProgram> managedResources = shaders.get(app);
    if (managedResources == null) managedResources = new ArrayList<ShaderProgram>();
    managedResources.add(shaderProgram);
    shaders.put(app, managedResources);
}

void ShaderProgram::invalidateAllShaderPrograms (const gdx_cpp::Application& app) {
    if (Gdx.graphics.getGL20() == null) return;

    List<ShaderProgram> shaderList = shaders.get(app);
    if (shaderList == null) return;

    for (int i = 0; i < shaderList.size(); i++) {
        shaderList.get(i).invalidated = true;
        shaderList.get(i).checkManaged();
    }
}

void ShaderProgram::clearAllShaderPrograms (const gdx_cpp::Application& app) {
    shaders.remove(app);
}

std::string& ShaderProgram::getManagedStatus () {
    StringBuilder builder = new StringBuilder();
    int i = 0;
    builder.append("Managed shaders/app: { ");
for (Application app : shaders.keySet()) {
        builder.append(shaders.get(app).size());
        builder.append(" ");
    }
    builder.append("}");
    return builder.toString();
}

void ShaderProgram::setAttributef (const std::string& name,float value1,float value2,float value3,float value4) {
    GL20 gl = Gdx.graphics.getGL20();
    int location = fetchAttributeLocation(name);
    gl.glVertexAttrib4f(location, value1, value2, value3, value4);
}

void ShaderProgram::ensureBufferCapacity (int numBytes) {
    if (buffer == null || buffer.capacity() != numBytes) {
        buffer = BufferUtils.newByteBuffer(numBytes);
        floatBuffer = buffer.asFloatBuffer();
        intBuffer = buffer.asIntBuffer();
    }
}

void ShaderProgram::fetchUniforms () {
    params.clear();
    Gdx.gl20.glGetProgramiv(program, GL20.GL_ACTIVE_UNIFORMS, params);
    int numUniforms = params.get(0);

    uniformNames = new String[numUniforms];

    for (int i = 0; i < numUniforms; i++) {
        params.clear();
        params.put(0, 256);
        type.clear();
        String name = Gdx.gl20.glGetActiveUniform(program, i, params, type);
        int location = Gdx.gl20.glGetUniformLocation(program, name);
        uniforms.put(name, location);
        uniformTypes.put(name, type.get(0));
        uniformNames[i] = name;
    }
}

void ShaderProgram::fetchAttributes () {
    params.clear();
    Gdx.gl20.glGetProgramiv(program, GL20.GL_ACTIVE_ATTRIBUTES, params);
    int numAttributes = params.get(0);

    attributeNames = new String[numAttributes];

    for (int i = 0; i < numAttributes; i++) {
        params.clear();
        params.put(0, 256);
        type.clear();
        String name = Gdx.gl20.glGetActiveAttrib(program, i, params, type);
        int location = Gdx.gl20.glGetAttribLocation(program, name);
        attributes.put(name, location);
        attributeTypes.put(name, type.get(0));
        attributeNames[i] = name;
    }
}

bool ShaderProgram::hasAttribute (const std::string& name) {
    return attributes.containsKey(name);
}

int ShaderProgram::getAttributeType (const std::string& name) {
    Integer type = attributes.get(name);
    if (type == null)
        return 0;
    else
        return type;
}

int ShaderProgram::getAttributeLocation (const std::string& name) {
    Integer location = attributes.get(name);
    if (location == null)
        return -1;
    else
        return location;
}

bool ShaderProgram::hasUniform (const std::string& name) {
    return uniforms.containsKey(name);
}

int ShaderProgram::getUniformType (const std::string& name) {
    Integer type = attributes.get(name);
    if (type == null)
        return 0;
    else
        return type;
}

int ShaderProgram::getUniformLocation (const std::string& name) {
    Integer location = uniforms.get(name);
    if (location == null)
        return -1;
    else
        return location;
}

std::string* ShaderProgram::getAttributes () {
    return attributeNames;
}

std::string* ShaderProgram::getUniforms () {
    return uniformNames;
}

