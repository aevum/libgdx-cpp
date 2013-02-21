/*
 * ObjLoader.cpp
 *
 *  Created on: Jan 20, 2013
 *      Author: anton
 */

#include "ObjLoader.h"

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
	string tokens;
	string key;
	MtlLoader mtl;

	Group activeGroup("default");
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
			vector<int>& faces = activeGroup.faces;
			int i = 0;
			while (!str.eof()) {
				int vertexIndex, textureIndex, normalIndex = 0;
				str >> vertexIndex;
				vertexIndex--;
				faces.push_back(getIndex(vertexIndex, verts.size()));
				if (str.get() == '/') {
					if (str.peek() != '/') {
						str >> textureIndex;
						textureIndex--;
						activeGroup.hasUVs = true;
					} else {
						str >> normalIndex;
						normalIndex--;
						activeGroup.hasNorms = true;
					}
					if (str.get() == '/') {
						str >> normalIndex;
						normalIndex--;
						activeGroup.hasNorms = true;
					}
					if (activeGroup.hasNorms) {
						faces.push_back(normalIndex);
					}
					if (activeGroup.hasUVs) {
						faces.push_back(textureIndex);
					}
				}
			}
			activeGroup.numFaces++;
		} else if (key == "o" || key == "g") {
			string name;
			str >> name;
			if (!name.empty()) {
				activeGroup = setActiveGroup(name);
			} else {
				activeGroup = setActiveGroup("default");
			}
		}
//		} else if ("mtllib" )
		//if (currentLine[0] == 'v' && currentLine[1] == ' ')
	}
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

ObjLoader::Group& ObjLoader::setActiveGroup(const string& name) {
	for (size_t i = 0; i < groups.size(); i++) {
		if (groups[i].name == name) {
			return groups[i];
		}
	}
	Group* group = new Group(name);
	groups.push_back(*group);
	return *group;
}

ObjLoader::MtlLoader::MtlLoader() {
	if (emptyTexture == NULL) {
		Pixmap::ptr pm = Pixmap::newFromRect(1, 1, Pixmap::Format::RGB888, Pixmap::PixmapType::PixmapType_Gdx2d);
		pm.get()->setColor(0.5, 0.5, 0.5, 1);
		pm.get()->fill();
		emptyTexture = new Texture(pm, false);
	}
}
