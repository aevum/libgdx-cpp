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

StillModel* ObjLoader::loadObj(FileHandle& file, bool flipV)
{
	FileHandle textureFolder = file.parent();
	return loadObj(file, textureFolder, flipV);
}

StillModel* ObjLoader::loadObj(FileHandle& file, FileHandle& textureDir, bool filpV)
{
	string line;
	string tokens;
	char firstChar;
	MtlLoader mtl;

	Group activeGroup("default");
	groups.push_back(activeGroup);
	FileHandle::buffer_ptr buffer;
	file.readBytes(buffer);
	std::istringstream content(buffer.get());
	string currentLine;
	while(getline(content, currentLine)) {
		if (currentLine.size() == 0) {
			continue;
		} else if ((firstChar = currentLine[0]) == '#') {
			continue;
		} else if (firstChar == 'v') {
			if (currentLine[1] == ' ') {
				proccessVerteOrNormal(currentLine, "v %f %f %f", verts);
			} else if (currentLine[1] == 'n') {
				proccessVerteOrNormal(currentLine, "vn %f %f %f", norms);
			}else if (currentLine[1] == 't') {
				proccessUV(currentLine);
			}
		} else if (firstChar == 'f') {
			
		}
		//if (currentLine[0] == 'v' && currentLine[1] == ' ')
	}
}

void ObjLoader::proccessVerteOrNormal(string& line, const char* templ, vector<float>& container) {
	float tmp1, tmp2, tmp3;
	sscanf(line.c_str(), templ, &tmp1, &tmp2, &tmp3);
	container.push_back(tmp1);
	container.push_back(tmp2);
	container.push_back(tmp3);
}

void ObjLoader::proccessUV(string& line) {
	float tmp1, tmp2;
	sscanf(line.c_str(), "vt %f %f", &tmp1, &tmp2);
	uvs.push_back(tmp1);
	uvs.push_back(tmp2);
}

StillModel* ObjLoader::load(FileHandle& handle, ModelLoaderHints hints) {
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
