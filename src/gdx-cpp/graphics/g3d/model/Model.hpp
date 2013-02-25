/*
 * Model.h
 *
 *  Created on: Jan 20, 2013
 *      Author: anton
 */

#ifndef MODEL_H_
#define MODEL_H_

#include "gdx-cpp/graphics/glutils/ShaderProgram.hpp"
#include "gdx-cpp/graphics/g3d/model/SubMesh.hpp"
#include <string>

using namespace std;
using namespace gdx;

class Model
{
public:
	virtual ~Model() {};
	virtual void render() = 0;
	virtual void render(ShaderProgram& program) = 0;
	virtual Model* getSubModel (const vector<string>& subMeshNames) = 0;
	virtual SubMesh* getSubMesh(string name) = 0;
	virtual vector<SubMesh*>& getSubMeshes() = 0;
	virtual void getBoundingBox(BoundingBox& bbox) = 0;
	virtual void setMaterials (vector<Material*> materials) = 0;
	virtual void setMaterial (Material* material) = 0;
	virtual void dispose () = 0;

};

#endif /* MODEL_H_ */
