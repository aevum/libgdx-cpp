/*
 * ObjLoader.cpp
 *
 *  Created on: Jan 20, 2013
 *      Author: anton
 */

#include "gdx-cpp/graphics/g3d/loaders/wavefront/ObjLoader.hpp"
#include <limits.h>
#include <gdx-cpp/gl.hpp>

using namespace gdx;

Texture* ObjLoader::MtlLoader::emptyTexture = NULL;

ObjLoader::ObjLoader()
{
}

ObjLoader::~ObjLoader()
{
}

StillModel* ObjLoader::loadObj(const FileHandle& file, bool flipV)
{
	FileHandle textureFolder = file.parent();
	return loadObj(file, textureFolder, flipV);
}

StillModel* ObjLoader::loadObj(const FileHandle& file, FileHandle& textureDir, bool flipV)
{
	string line;
	string key;
	MtlLoader mtl;
	Group* activeGroup = new Group("default");
	groups.push_back(activeGroup);
	FileHandle::buffer_ptr buffer;
	file.readBytes(buffer);
	std::istringstream content(buffer.get());
	string currentLine;
	while(content.good() && !content.eof() && getline(content, currentLine)) {
		stringstream str(currentLine);
		str >> key >> ws;
		if (key == "#") {
			continue;
		} else if (key == "v") {
			proccessVerteOrNormal(currentLine, "v %f %f %f", verts);
		} else if (key == "vn") {
			proccessVerteOrNormal(currentLine, "vn %f %f %f", norms);
		} else if (key == "vt") {
			proccessUV(currentLine, flipV);
		} else if (key == "f") {
			vector<int>& faces = activeGroup->faces;
			int i = 0;
			while (!str.eof()) {
				int vertexIndex, textureIndex, normalIndex = 0;
				str >> vertexIndex;
				faces.push_back(getIndex(vertexIndex, verts.size()));
				if (str.get() == '/') {
					if (str.peek() != '/') {
						str >> textureIndex;
						activeGroup->hasUVs = true;
					}
					if (str.get() == '/') {
						str >> normalIndex;
						activeGroup->hasNorms = true;
					}
					if (activeGroup->hasNorms) {
						faces.push_back(getIndex(normalIndex, norms.size()));
					}
					if (activeGroup->hasUVs) {
						faces.push_back(getIndex(textureIndex, uvs.size()));
					}
				}
			}
			activeGroup->numFaces++;
		} else if (key == "o" || key == "g") {
			string name;
			str >> name;
			if (!name.empty()) {
				activeGroup = setActiveGroup(name);
			} else {
				activeGroup = setActiveGroup("default");
			}
		} else if (key == "mtllib") {
			string path;
			str >> path;
			if (file.path().find('/') != string::npos) {
				path = file.path().substr(0, file.path().find_last_of('/') + 1) + path;
			}
			mtl.load(path, textureDir);
		} else if (key == "usemtl") {
			string token;
			str >> token;
			if (token.empty()) {
				activeGroup->materialName = "default";
			} else {
				activeGroup->materialName = token;
			}
		}
	}
	for (size_t i = 0; i < groups.size(); i++) {
		if (groups[i]->numFaces < 1) {
			groups.erase(groups.begin() + i);
			i--;
		}
	}
	if (groups.size() < 1) return nullptr;
	size_t numGroups = groups.size();
	StillModel* model = new StillModel();
	for (size_t g = 0; g < numGroups; g++) {
		Group& group = *groups[g];
		vector<int>& faces = group.faces;
		const int numElements = faces.size();
		const int numFaces = group.numFaces;
		const bool hasNorms = group.hasNorms;
		const bool hasUVs = group.hasUVs;
		const int numVerts = (numFaces * 3) * (3 + (hasNorms ? 3 : 0) + (hasUVs ? 2 : 0));
		float finalVerts[numVerts];
		for (size_t i = 0, vi = 0; i < numElements;) {
			int vertIndex = faces[i++] * 3;
			finalVerts[vi++] = verts[vertIndex++];
			finalVerts[vi++] = verts[vertIndex++];
			finalVerts[vi++] = verts[vertIndex];
			if (hasNorms) {
				int normIndex = faces[i++] * 3;
				finalVerts[vi++] = norms[normIndex++];
				finalVerts[vi++] = norms[normIndex++];
				finalVerts[vi++] = norms[normIndex];
			}
			if (hasUVs) {
				int uvIndex = faces[i++] * 2;
				finalVerts[vi++] = uvs[uvIndex++];
				finalVerts[vi++] = uvs[uvIndex];
			}
		}
		int numIndices = numFaces * 3 >= SHRT_MAX ? 0 : numFaces * 3;
		vector<short> finalIndices;
		if (numIndices > 0) {
			for (size_t in = 0; in < numIndices; in++) {
				finalIndices.push_back((short)in);
			}
		}
		Mesh* mesh;
		vector<VertexAttribute> attributes;
		attributes.push_back(VertexAttribute(VertexAttributes::Usage::Position, 3, ShaderProgram::POSITION_ATTRIBUTE));
		if (hasNorms) {
			attributes.push_back(VertexAttribute(VertexAttributes::Usage::Normal, 3, ShaderProgram::NORMAL_ATTRIBUTE));
		}
		if (hasUVs) {
			attributes.push_back(VertexAttribute(VertexAttributes::Usage::TextureCoordinates, 2, ShaderProgram::TEXCOORD_ATTRIBUTE + "0"));
		}
		mesh = new Mesh(true, numFaces * 3, numIndices, attributes);
		mesh->setVertices(finalVerts, numVerts);
		if (numIndices > 0) {
			mesh->setIndices(finalIndices);
		}
		const char* subMeshName = group.name.c_str();
		StillSubMesh* subMesh = new StillSubMesh(subMeshName, *mesh, gdx::GL::TRIANGLES);
		subMesh->material = mtl.getMaterial(group.materialName);
		model->subMeshes.push_back(subMesh);
	}
	if (verts.size() > 0) {
		verts.clear();
	}
	if (norms.size() > 0) {
		norms.clear();
	}
	if (uvs.size() > 0) {
		uvs.clear();
	}
	if (groups.size() > 0) {
		groups.clear();
	}
	return model;
}

int ObjLoader::getIndex(int index, int size) {
	if (index < 0) {
		return size + index;
	} else {
		return index - 1;
	}
}

void ObjLoader::proccessVerteOrNormal(string& line, const char* templ, vector<float>& container) {
	float tmp1, tmp2, tmp3;
	sscanf(line.c_str(), templ, &tmp1, &tmp2, &tmp3);
	container.push_back(tmp1);
	container.push_back(tmp2);
	container.push_back(tmp3);
}

void ObjLoader::proccessUV(string& line, bool isFlip) {
	float tmp1, tmp2;
	sscanf(line.c_str(), "vt %f %f", &tmp1, &tmp2);
	uvs.push_back(tmp1);
	uvs.push_back(isFlip ? 1 - tmp2 : tmp2);
}

StillModel* ObjLoader::load(const FileHandle& handle, ModelLoaderHints hints) {
	return loadObj(handle, hints.flipV);
}

ObjLoader::Group* ObjLoader::setActiveGroup(const string& name) {
	for (size_t i = 0; i < groups.size(); i++) {
		if (groups[i]->name == name) {
			return groups[i];
		}
	}
	Group* group = new Group(name);
	groups.push_back(group);
	return group;
}

ObjLoader::MtlLoader::MtlLoader() {
	if (emptyTexture == NULL) {
		Pixmap::ptr pm = Pixmap::newFromRect(1, 1, Pixmap::Format::RGB888, Pixmap::PixmapType::PixmapType_Gdx2d);
		pm.get()->setColor(0.5, 0.5, 0.5, 1);
		pm.get()->fill();
		emptyTexture = new Texture(pm, false);
	}
}

void ObjLoader::MtlLoader::load(string fileName, FileHandle& textureDir) {
	string line;
	string key;
	string curMatName = "default";
	Color difColor = Color::WHITE;
	Color specColor = Color::WHITE;
	Texture* texture = emptyTexture;
	FileHandle::buffer_ptr buffer;
	FileHandle::ptr file = gdx::files->internal(fileName);
	file.get()->readBytes(buffer);
	std::istringstream content(buffer.get());
	string currentLine;
	while(content.good() && !content.eof() && getline(content, currentLine)) {
		if (currentLine.size() > 0 && currentLine.at(0) == '\t') {
			currentLine = currentLine.substr(1, currentLine.size());
		}
		stringstream str(currentLine);
		str >> key >> ws;
		if (key == "#") {
			continue;
		} else if (key == "newmtl") {
			vector<MaterialAttribute*> attributes;
			attributes.push_back(new TextureAttribute(*texture, 0, TextureAttribute::diffuseTexture));
			attributes.push_back(new ColorAttribute(difColor, ColorAttribute::diffuse));
			attributes.push_back(new ColorAttribute(specColor, ColorAttribute::specular));
			Material* mat = new Material(curMatName, attributes);
			materials.push_back(mat);
			string token;
			str >> token;
			if (!token.empty()) {
				curMatName = token.replace(0, token.size(), '.', '_');
			} else {
				curMatName = "default";
			}
			difColor = Color::WHITE;
			specColor = Color::WHITE;
		} else if (key == "kd" || key == "ks") {
			float r, g, b, a;
			str >> r >> g >> b;
			a = 1;
			if (key == "kd") {
				difColor.set(r, g, b, a);
			} else {
				specColor.set(r, g, b, a);
			}
		} else if (key == "map_kd") {
			string textureName;
			str >> textureName;
			if (!textureName.empty()) {
				string texName = textureDir.child(textureName).toString();
				FileHandle::ptr file = gdx::files->internal(texName);
				Pixmap::ptr pixmap = Pixmap::newFromFile(file);
				texture = new Texture(pixmap, false);
				texture->setFilter(Texture::TextureFilter::Linear, Texture::TextureFilter::Linear);
			} else {
				texture = emptyTexture;
			}
		}
		vector<MaterialAttribute*> attributes;
		attributes.push_back(new TextureAttribute(*texture, 0, TextureAttribute::diffuseTexture));
		attributes.push_back(new ColorAttribute(difColor, ColorAttribute::diffuse));
		attributes.push_back(new ColorAttribute(specColor, ColorAttribute::specular));
		Material* material = new Material(curMatName, attributes);
		materials.push_back(material);
	}
}

Material* ObjLoader::MtlLoader::getMaterial(string name) {
	name = name.replace(0, name.length(), '.', '_');
	for (size_t i = 0; i < materials.size(); i++) {
		if (materials[i]->getName() == name) {
			return materials[i];
		}
	}
	return new Material("default");
}
