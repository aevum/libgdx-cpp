/*
 * StillModel.cpp
 *
 *  Created on: Jan 20, 2013
 *      Author: anton
 */

#include "StillModel.hpp"

using namespace gdx;

BoundingBox StillModel::tmpbox;

StillModel::~StillModel() {
	for(size_t i = 0; i < subMeshes.size(); i++) {
		delete subMeshes[i];
	}
	subMeshes.clear();
}

StillModel::StillModel() {

}

StillModel::StillModel(vector<SubMesh*>& meshes) {
	for(int i = 0; i < meshes.size(); i++) {
		subMeshes.push_back(static_cast<StillSubMesh*>(meshes[i]));
	}
}

void StillModel::render() {
	size_t len = subMeshes.size();
	for (size_t i = 0; i < len; i++) {
		StillSubMesh* subMesh = subMeshes[i];
		if (i == 0) {
			subMesh->material->bind();
		} else if (subMeshes[i - 1]->material != subMesh->material) {
			subMesh->material->bind();
		}
		subMesh->mesh->render(subMesh->primitiveType);
	}
}

void StillModel::render(ShaderProgram& shader) {
	size_t len = subMeshes.size();
	for (size_t i = 0; i < len; i++) {
		StillSubMesh* subMesh = subMeshes[i];
		if (i == 0) {
			subMesh->material->bind();
		} else if (subMeshes[i - 1]->material != subMesh->material) {
			subMesh->material->bind();
		}
		subMesh->mesh->render(shader, subMesh->primitiveType);
	}
}

Model* StillModel::getSubModel(const vector<string>& subMeshNames) {
	vector<SubMesh*> refSubMeshes;
	for (size_t i = 0; i < subMeshNames.size(); i++) {
		for (size_t j = 0; j < subMeshes.size(); j++) {
			if (subMeshNames[i] == subMeshes[j]->name) {
				refSubMeshes.push_back(subMeshes[j]);
			}
		}
	}
	if (refSubMeshes.size() > 0) {
		return new StillModel(refSubMeshes);
	}
	return NULL;
}

StillSubMesh* StillModel::getSubMesh(string name) {
	for (size_t i = 0; i < subMeshes.size(); i++) {
		if (subMeshes[i]->name == name) {
			return subMeshes[i];
		}
	}
	return NULL;
}

vector<SubMesh*>& StillModel::getSubMeshes() const {
	return (vector<SubMesh*>&) subMeshes;
}

void StillModel::setMaterials(vector<Material*> materials) {
	if (materials.size() != subMeshes.size()) {
		//TODO: should throw unsupport exception
		throw exception();
	}
	for (size_t i = 0; i < subMeshes.size(); i++) {
		subMeshes[i]->material = materials[i];
	}

}

void StillModel::setMaterial(Material* material) {
	for (size_t i = 0; i < subMeshes.size(); i++) {
		subMeshes[i]->material = material;
	}
}

void StillModel::getBoundingBox(BoundingBox& bbox) {
	bbox.inf();
	for (size_t i = 0; i < subMeshes.size(); i++) {
		subMeshes[i]->mesh->calculateBoundingBox(tmpbox);
		bbox.ext(tmpbox);
	}
}

void StillModel::dispose() {
	for (size_t i = 0; i < subMeshes.size(); i++) {
		subMeshes[i]->mesh->dispose();
	}
}

 /* namespace gdx */
