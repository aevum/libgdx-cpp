/*
 * SubMesh.cpp
 *
 *  Created on: Jan 20, 2013
 *      Author: anton
 */

#include "SubMesh.hpp"

namespace gdx
{

SubMesh::SubMesh(const string& name, const Mesh& mesh, int primitiveType, Material* material)
{
	this->name = name;
	this->setMesh(mesh);
	this->primitiveType = primitiveType;
	this->material = material;
}

SubMesh::SubMesh(const string& name, const Mesh& mesh, int primitiveType)
{
	SubMesh(name, mesh, primitiveType, nullptr);
}

SubMesh::~SubMesh()
{
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
