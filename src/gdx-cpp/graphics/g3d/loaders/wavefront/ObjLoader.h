/*
 * ObjLoader.h
 *
 *  Created on: Jan 20, 2013
 *      Author: anton
 */

#ifndef OBJLOADER_H_
#define OBJLOADER_H_

#include "gdx-cpp/utils/FloatArray.hpp"
#include "gdx-cpp/graphics/g3d/loaders/StillModelLoader.hpp"

using namespace std;
using namespace gdx;

class ObjLoader : public StillModelLoader
{
private:
	class Group
	{
		string name;
		string materialName;
		vector<int> faces;
		int numFaces;
		bool hasNorms;
		bool hasUVs;
		Material mat;

		Group(string name) {
			this->name = name;
			numFaces = 0;
			hasNorms = false;
			hasUVs = false;
			materialName = "default";
		}
	};

	FloatArray verts;
	FloatArray norms;
	FloatArray uvs;
	vector<Group> groups;
	Group setActiveGroup(const string& group);
	int getIndex(string index, int size);

public:
	ObjLoader();
	virtual ~ObjLoader();
	StillModel* loadObj(FileHandle& file, bool flipV = false);
	StillModel* loadObj(FileHandle& file, FileHandle& textureDir, bool flipV);
	StillModel* load(FileHandle& handle, ModelLoaderHints hints);
};

#endif /* OBJLOADER_H_ */
