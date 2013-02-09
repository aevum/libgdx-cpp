/*
 * StillSubMesh.cpp
 *
 *  Created on: Jan 20, 2013
 *      Author: anton
 */

#include "StillSubMesh.hpp"

namespace gdx
{

StillSubMesh::StillSubMesh(const string& name, const Mesh& mesh, int primitiveType, Material* material)
: SubMesh(name, mesh, primitiveType, material)
{
}

StillSubMesh::StillSubMesh(const string& name, const Mesh& mesh, int primitiveType)
: SubMesh(name, mesh, primitiveType)
{
}

StillSubMesh::~StillSubMesh()
{
}

void StillSubMesh::getBoundingBox(BoundingBox& bbox)
{
	mesh->calculateBoundingBox(bbox);
}

} /* namespace gdx */
