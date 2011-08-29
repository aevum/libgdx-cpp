
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

#ifndef GDX_CPP_GRAPHICS_GLUTILS_SHADERPROGRAM_HPP_
#define GDX_CPP_GRAPHICS_GLUTILS_SHADERPROGRAM_HPP_

#include "gdx-cpp/utils/Disposable.hpp"
#include <set>
#include <string>
#include <tr1/unordered_map>
#include <gdx-cpp/Application.hpp>
#include <gdx-cpp/utils/Buffer.hpp>

namespace gdx_cpp {
namespace math
  {
  class Matrix4;
  class Matrix3;
  }
  
namespace graphics {
namespace glutils {

class ShaderProgram: public gdx_cpp::utils::Disposable {
public:
    class FloatBuffer;
    /** default name for position attributes **/
    const static std::string POSITION_ATTRIBUTE;
    /** default name for normal attribtues **/
    const static std::string NORMAL_ATTRIBUTE;
    /** default name for color attributes **/
    const static std::string COLOR_ATTRIBUTE;
    /** default name for texcoords attributes, append texture unit number **/
    const static std::string TEXCOORD_ATTRIBUTE;
    /** default name for tangent attribute **/
    const static std::string TANGENT_ATTRIBUTE;
    /** default name for binormal attribute **/
    const static std::string BINORMAL_ATTRIBUTE;
    /** flag indicating whether attributes & uniforms must be present at all times **/
    static bool pedantic;

    ShaderProgram();

    std::string getLog ();
    bool isCompiled ();
    void setUniformi (std::string& name, int value);
    void setUniformi (std::string& name, int value1, int value2);
    void setUniformi (std::string& name, int value1, int value2, int value3);
    void setUniformi (std::string& name, int value1, int value2, int value3, int value4);
    void setUniformf (std::string& name, float value);
    void setUniformf (std::string& name, float value1, float value2);
    void setUniformf (std::string& name, float value1, float value2, float value3);
    void setUniformf (std::string& name, float value1, float value2, float value3, float value4);
    void setUniform1fv (std::string& name, float* values, int offset, int length);
    void setUniform2fv (std::string& name, float* values, int offset, int length);
    void setUniform3fv (std::string& name, float* values, int offset, int length);
    void setUniform4fv (std::string& name, float* values, int offset, int length);
    void setUniformMatrix (std::string& name, const gdx_cpp::math::Matrix4& matrix);
    void setUniformMatrix (std::string& name, const gdx_cpp::math::Matrix4& matrix, bool transpose);
    void setUniformMatrix (std::string& name, gdx_cpp::math::Matrix3& matrix);
    void setUniformMatrix (std::string& name, gdx_cpp::math::Matrix3& matrix, bool transpose);
    void setVertexAttribute (std::string& name, int size, int type, bool normalize, int stride, gdx_cpp::utils::buffer< float >* buffer);
    void setVertexAttribute (std::string& name, int size, int type, bool normalize, int stride, int offset);
    void begin ();
    void end ();
    void dispose ();
    void disableVertexAttribute (std::string& name);
    void enableVertexAttribute (std::string& name);
    static void invalidateAllShaderPrograms (gdx_cpp::Application* app);
    static void clearAllShaderPrograms (gdx_cpp::Application* app);
    std::string getManagedStatus ();
    void setAttributef (std::string& name, float value1, float value2, float value3, float value4);
    bool hasAttribute (const std::string& name);
    int getAttributeType (const std::string& name);
    int getAttributeLocation (const std::string& name);
    bool hasUniform (const std::string& name);
    int getUniformType (const std::string& name);
    int getUniformLocation (const std::string& name);
    std::vector<std::string>& getAttributes ();
    std::vector<std::string>& getUniforms ();

protected:
    static int intbuf;
    int params;
    int type;
    


private:
    void compileShaders (const std::string& vertexShader,const std::string& fragmentShader);
    int loadShader (int type,const std::string& source);
    int linkProgram ();
    int fetchAttributeLocation (const std::string& name);
    int fetchUniformLocation (std::string& name);
    void checkManaged ();
    void addManagedShader (gdx_cpp::Application* app, gdx_cpp::graphics::glutils::ShaderProgram* shaderProgram);
    void ensureBufferCapacity (int numBytes);
    void fetchUniforms ();
    void fetchAttributes ();

    static std::tr1::unordered_map <gdx_cpp::Application *, std::set< ShaderProgram* > * > shaders;

    std::string log;
    bool isCompiledVar;

//     const
    std::tr1::unordered_map <std::string, int> uniforms;
//     const
    std::tr1::unordered_map <std::string, int> uniformTypes;
    std::vector<std::string> uniformNames;

    std::tr1::unordered_map <std::string, int> attributes;
//     const
    std::tr1::unordered_map <std::string, int> attributeTypes;
    std::vector<std::string> attributeNames;

    int program;
    int vertexShaderHandle;
    int fragmentShaderHandle;
    gdx_cpp::utils::buffer<float> matrix;
    std::string vertexShaderSource;
    std::string fragmentShaderSource;
    bool invalidated;

    gdx_cpp::utils::byte_buffer buffer;
    gdx_cpp::utils::float_buffer floatBuffer;
    gdx_cpp::utils::int_buffer intBuffer;

    int refCount;

};

} // namespace gdx_cpp
} // namespace graphics
} // namespace glutils

#endif // GDX_CPP_GRAPHICS_GLUTILS_SHADERPROGRAM_HPP_
