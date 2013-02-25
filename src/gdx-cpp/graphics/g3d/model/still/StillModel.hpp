/*
 * StillModel.h
 *
 *  Created on: Jan 20, 2013
 *      Author: anton
 */

#ifndef STILLMODEL_H_
#define STILLMODEL_H_

#include "gdx-cpp/graphics/g3d/model/Model.hpp"
#include "gdx-cpp/graphics/g3d/model/still/StillSubMesh.hpp"

namespace gdx
{
using namespace std;

class StillModel : public Model
{
private:
	static BoundingBox tmpbox;
public:
	vector<StillSubMesh*> subMeshes;
	StillModel();
	StillModel(vector<SubMesh*>& subMeshes);
	virtual ~StillModel();
	void render();
	void render(ShaderProgram& program);
	Model* getSubModel(const vector<string>& subMeshNames);
	StillSubMesh* getSubMesh(string name);
	vector<SubMesh*>& getSubMeshes();
	void setMaterials(vector<Material*> materials);
	void setMaterial(Material* material);
	void getBoundingBox(BoundingBox& bbox);
	void dispose();
};

} /* namespace gdx */
#endif /* STILLMODEL_H_ */
