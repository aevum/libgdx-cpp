/*
 * SubMesh.cpp
 *
 *  Created on: Jan 20, 2013
 *      Author: anton
 */

#include "SubMesh.hpp"

namespace gdx
{

SubMesh::SubMesh(const char* newName, const Mesh& mesh, int primitiveType, Material* material)
: name(newName)
{
	setMesh(mesh);
	this->primitiveType = primitiveType;
	this->material = material;
}

SubMesh::SubMesh(const char* newName, const Mesh& mesh, int primitiveType)
: SubMesh(newName, mesh, primitiveType, nullptr)
{
}

SubMesh::~SubMesh()
{
	delete material;
	delete mesh;
}

Mesh& SubMesh::getMesh()
{
	return *mesh;
}

void SubMesh::setMesh(const Mesh& mesh)
{
	this->mesh = (Mesh*)&mesh;
}


} /* namespace gdx */
