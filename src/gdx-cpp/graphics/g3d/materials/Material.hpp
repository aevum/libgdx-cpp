
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

#ifndef GDX_CPP_GRAPHICS_G3D_MATERIAL_HPP_
#define GDX_CPP_GRAPHICS_G3D_MATERIAL_HPP_

#include <vector>
#include "gdx-cpp/graphics/g3d/materials/MaterialAttribute.hpp"

using namespace std;

namespace gdx {

class Material {
public:
	Material();
	Material(string name, const vector<MaterialAttribute*>& attributes);

	void bind();
	void bind(ShaderProgram& program);
	string& getName();
	void addAttribute(vector<MaterialAttribute*> attributes);
	void removeAttribute(vector<MaterialAttribute*>& attributes);
	void clearAttributes();
	MaterialAttribute& getAttribute(int index);
	int getNumberOfAttributes();
	Material& copy();
	int hashCode();
	//bool equals()
	bool shaderEquals(Material& other);
	void setPooled(Material& material);
	bool isNeedBlending();
	bool hasTexture();
	ShaderProgram& getShader() const;
	void setShader(const ShaderProgram& shader);
	void resetShader();

//    void set (int face);
//    bool read (const DataInputStream& i);
//    bool write (const DataOutputStream& o);

protected:
    string name;
    bool needBlending;
    bool mHasTexture;
    ShaderProgram* shader;

    void checkAttributes();

private:
    vector<MaterialAttribute*> attributes;
    void setTmpArray (float r,float g,float b,float a);
};

} // namespace gdx

#endif // GDX_CPP_GRAPHICS_G3D_MATERIAL_HPP_
