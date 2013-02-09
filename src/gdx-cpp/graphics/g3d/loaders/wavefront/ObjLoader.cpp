/*
 * ObjLoader.cpp
 *
 *  Created on: Jan 20, 2013
 *      Author: anton
 */

#include "ObjLoader.h"

ObjLoader::ObjLoader()
{
}

ObjLoader::~ObjLoader()
{
}

StillModel* ObjLoader::loadObj(FileHandle& file, bool flipV)
{
	return loadObj(file, file.parent(), flipV);
}

StillModel* ObjLoader::loadObj(FileHandle& file, FileHandle& textureDir, bool filpV)
{
	string line;
	string tokens;
	char firstChar;
//	MtlLoader mtl = new MtlLoader();

	Group activeGroup("default");
	groups.push_back(activeGroup);

	BufferReader
}
