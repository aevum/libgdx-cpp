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
				int a, b, c = 0;
				str >> a;
				a--;
				faces.push_back(a);
				if (str.get() == '/') {
					if (str.get() != '/') {
						str >> b;
						b--;
					}
					if (str.get() == '/') {
						str >> c;
						c--;
					}
				}
			}

		} else if (key == "o" || key == "g") {
		}
//		} else if ("mtllib" )
		//if (currentLine[0] == 'v' && currentLine[1] == ' ')
	}
}

int ObjLoader::getIndex(string index, int size) {
	if (index.empty()) {
		return 0;
	}
	int idx = atoi(index.c_str());
	if (idx < 0) {
		return size + idx;
	} else {
		return idx - 1;
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

ObjLoader::MtlLoader::MtlLoader() {
	if (emptyTexture == NULL) {
		Pixmap::ptr pm = Pixmap::newFromRect(1, 1, Pixmap::Format::RGB888, Pixmap::PixmapType::PixmapType_Gdx2d);
		pm.get()->setColor(0.5, 0.5, 0.5, 1);
		pm.get()->fill();
		emptyTexture = new Texture(pm, false);
	}
}
