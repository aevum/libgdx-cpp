//
///*
//    Copyright 2011 Aevum Software aevum @ aevumlab.com
//
//    Licensed under the Apache License, Version 2.0 (the "License");
//    you may not use this file except in compliance with the License.
//    You may obtain a copy of the License at
//
//        http://www.apache.org/licenses/LICENSE-2.0
//
//    Unless required by applicable law or agreed to in writing, software
//    distributed under the License is distributed on an "AS IS" BASIS,
//    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//    See the License for the specific language governing permissions and
//    limitations under the License.
//
//    @author Victor Vicente de Carvalho victor.carvalho@aevumlab.com
//    @author Ozires Bortolon de Faria ozires@aevumlab.com
//*/

#include "Material.hpp"

using namespace gdx;

Material::Material() {
}

Material::Material(string name, const vector<MaterialAttribute*>& attributes) {
	this->name = name;
	for (size_t i = 0; i < attributes.size(); i++) {
		this->attributes.push_back(attributes[i]);
	}
	checkAttributes();
}

Material::Material(string name) {
	this->name = name;
}

void Material::checkAttributes() {
	this->needBlending = false;
	this->mHasTexture = false;
	for (size_t i = 0; i < this->attributes.size(); i++) {
		if (!needBlending && dynamic_cast<BlendingAttribute*>(this->attributes[i]) != NULL) {
			this->needBlending = true;
//		} else if (!mHasTexture && dynamic_cast<>this->attributes[i])) {
//			this->mHasTexture = true;
		}
	}
}

void Material::bind() {
	for (size_t i = 0; i < attributes.size(); i++) {
		attributes[i]->bind();
	}
}

void Material::bind(ShaderProgram& program) {
	for (size_t i = 0; i < attributes.size(); i++) {
		attributes[i]->bind(program);
	}
}

string& Material::getName() {
	return name;
}

//void Material::setTmpArray (float r,float g,float b,float a) {
//    tmp[0] = r;
//    tmp[1] = g;
//    tmp[2] = b;
//    tmp[3] = a;
//}
//
//void Material::set (int face) {
//    // TODO: should probably load shaderprogram here if we're using them
//    GL10 gl = Gdx.graphics.getGL10();
//    // TODO: caching of last material set using statics to see if we need to set material states again
//    if (Ambient != null) {
//        setTmpArray(Ambient.r, Ambient.g, Ambient.b, Ambient.a);
//        gl.glMaterialfv(face, GL10.GL_AMBIENT, tmp, 0);
//    }
//    if (Diffuse != null) {
//        setTmpArray(Diffuse.r, Diffuse.g, Diffuse.b, Diffuse.a);
//        gl.glMaterialfv(face, GL10.GL_DIFFUSE, tmp, 0);
//    }
//
//    if (BlendSourceFactor > 0) {
//        gl.glBlendFunc(BlendSourceFactor, BlendDestFactor);
//        gl.glEnable(GL10.GL_BLEND);
//    } else {
//        gl.glDisable(GL10.GL_BLEND);
//    }
//}
//
//bool Material::read (const DataInputStream& i) throws IOException {
//    Name = i.readUTF();
//    TexturePath = i.readUTF();
//    boolean hasAmbient = i.readBoolean();
//    if (hasAmbient) {
//        float r = i.readFloat();
//        float g = i.readFloat();
//        float b = i.readFloat();
//        float a = i.readFloat();
//        Ambient = new Color(r, g, b, a);
//    }
//    boolean hasDiffuse = i.readBoolean();
//    if (hasDiffuse) {
//        float r = i.readFloat();
//        float g = i.readFloat();
//        float b = i.readFloat();
//        float a = i.readFloat();
//        Diffuse = new Color(r, g, b, a);
//    }
//    BlendSourceFactor = i.readInt();
//    BlendDestFactor = i.readInt();
//    return true;
//}
//
//bool Material::write (const DataOutputStream& o) throws IOException {
//    // TODO: serialize out shader
//    o.writeUTF(Name);
//    // process path
//    String filename = Texture.Name.substring(Texture.Name.lastIndexOf("\\") + 1);
//    o.writeUTF(filename);
//    o.writeBoolean(Ambient != null);
//    if (Ambient != null) {
//        o.writeFloat(Ambient.r);
//        o.writeFloat(Ambient.g);
//        o.writeFloat(Ambient.b);
//        o.writeFloat(Ambient.a);
//    }
//    o.writeBoolean(Diffuse != null);
//    if (Diffuse != null) {
//        o.writeFloat(Diffuse.r);
//        o.writeFloat(Diffuse.g);
//        o.writeFloat(Diffuse.b);
//        o.writeFloat(Diffuse.a);
//    }
//    o.writeInt(BlendSourceFactor);
//    o.writeInt(BlendDestFactor);
//    return true;
//}
//
