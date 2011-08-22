
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

namespace gdx_cpp {
namespace graphics {
namespace glutils {

class ShaderProgram: public gdx_cpp::utils::Disposable {
public:
    std::string& getLog ();
    bool isCompiled ();
    void setUniformi (const std::string& name,int value);
    void setUniformi (const std::string& name,int value1,int value2);
    void setUniformi (const std::string& name,int value1,int value2,int value3);
    void setUniformi (const std::string& name,int value1,int value2,int value3,int value4);
    void setUniformf (const std::string& name,float value);
    void setUniformf (const std::string& name,float value1,float value2);
    void setUniformf (const std::string& name,float value1,float value2,float value3);
    void setUniformf (const std::string& name,float value1,float value2,float value3,float value4);
    void setUniform1fv (const std::string& name,int offset,int length);
    void setUniform2fv (const std::string& name,int offset,int length);
    void setUniform3fv (const std::string& name,int offset,int length);
    void setUniform4fv (const std::string& name,int offset,int length);
    void setUniformMatrix (const std::string& name,const gdx_cpp::math::Matrix4& matrix);
    void setUniformMatrix (const std::string& name,const gdx_cpp::math::Matrix4& matrix,bool transpose);
    void setUniformMatrix (const std::string& name,const gdx_cpp::math::Matrix3& matrix);
    void setUniformMatrix (const std::string& name,const gdx_cpp::math::Matrix3& matrix,bool transpose);
    void setVertexAttribute (const std::string& name,int size,int type,bool normalize,int stride,const FloatBuffer& buffer);
    void setVertexAttribute (const std::string& name,int size,int type,bool normalize,int stride,int offset);
    void begin ();
    void end ();
    void dispose ();
    void disableVertexAttribute (const std::string& name);
    void enableVertexAttribute (const std::string& name);
    static void invalidateAllShaderPrograms (const gdx_cpp::Application& app);
    static void clearAllShaderPrograms (const gdx_cpp::Application& app);
    static std::string& getManagedStatus ();
    void setAttributef (const std::string& name,float value1,float value2,float value3,float value4);
    bool hasAttribute (const std::string& name);
    int getAttributeType (const std::string& name);
    int getAttributeLocation (const std::string& name);
    bool hasUniform (const std::string& name);
    int getUniformType (const std::string& name);
    int getUniformLocation (const std::string& name);
    std::string* getAttributes ();
    std::string* getUniforms ();

protected:


private:
    void compileShaders (const std::string& vertexShader,const std::string& fragmentShader);
    int loadShader (int type,const std::string& source);
    int linkProgram ();
    int fetchAttributeLocation (const std::string& name);
    int fetchUniformLocation (const std::string& name);
    void checkManaged ();
    void addManagedShader (const gdx_cpp::Application& app,const ShaderProgram& shaderProgram);
    void ensureBufferCapacity (int numBytes);
    void fetchUniforms ();
    void fetchAttributes ();
    FloatBuffer matrix;
    String vertexShaderSource;
    String fragmentShaderSource;
};

} // namespace gdx_cpp
} // namespace graphics
} // namespace glutils

#endif // GDX_CPP_GRAPHICS_GLUTILS_SHADERPROGRAM_HPP_
