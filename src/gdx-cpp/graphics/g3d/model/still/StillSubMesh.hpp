/*
 * StillSubMesh.h
 *
 *  Created on: Jan 20, 2013
 *      Author: anton
 */

#ifndef STILLSUBMESH_H_
#define STILLSUBMESH_H_

#include "gdx-cpp/graphics/g3d/model/SubMesh.hpp"

namespace gdx
{

class StillSubMesh : public SubMesh
{
public:
	StillSubMesh(const char* name, const Mesh& mesh, int primitiveType, Material* material);
	StillSubMesh(const char* name, const Mesh& mesh, int primitiveType);
	virtual ~StillSubMesh();
	void getBoundingBox(BoundingBox& bbox);

};

} /* namespace gdx */
#endif /* STILLSUBMESH_H_ */
