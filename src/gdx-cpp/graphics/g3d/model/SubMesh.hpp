/*
 * SubMesh.h
 *
 *  Created on: Jan 20, 2013
 *      Author: anton
 */

#ifndef SUBMESH_H_
#define SUBMESH_H_

#include <string>
#include "gdx-cpp/graphics/Mesh.hpp"
#include "gdx-cpp/graphics/g3d/materials/Material.hpp"

using namespace std;

class Mesh;

namespace gdx
{

class SubMesh
{
private:
public:
	string name;
	Material* material;
	int primitiveType;
	Mesh* mesh;

	SubMesh(const string& name, const Mesh& mesh, int primitiveType, Material* material);
	SubMesh(const string& name, const Mesh& mesh, int primitiveType);
	virtual ~SubMesh();
	void getBoundingBox(BoundingBox& bbox);
	Mesh& getMesh();
	void setMesh(const Mesh& mesh);
};

} /* namespace gdx */
#endif /* SUBMESH_H_ */
