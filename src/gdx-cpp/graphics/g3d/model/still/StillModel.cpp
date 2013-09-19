/*
 * StillModel.cpp
 *
 *  Created on: Jan 20, 2013
 *      Author: anton
 */

#include "StillModel.hpp"

using namespace gdx;

BoundingBox StillModel::tmpbox;

StillModel::~StillModel()
{
    for (auto & elem : subMeshes) {
        delete elem;
    }
    subMeshes.clear();
}

StillModel::StillModel()
{

}

StillModel::StillModel ( vector<SubMesh*>& meshes )
{
    for (auto & meshe : meshes) {
        subMeshes.push_back ( static_cast<StillSubMesh*> ( meshe ) );
    }
}

void StillModel::render()
{
    size_t len = subMeshes.size();
    for ( size_t i = 0; i < len; i++ ) {
        StillSubMesh* subMesh = subMeshes[i];
        if ( i == 0 ) {
            subMesh->material->bind();
        } else if ( subMeshes[i - 1]->material != subMesh->material ) {
            subMesh->material->bind();
        }
        subMesh->mesh->render ( subMesh->primitiveType );
    }
}

void StillModel::render ( ShaderProgram& shader )
{
    size_t len = subMeshes.size();
    for ( size_t i = 0; i < len; i++ ) {
        StillSubMesh* subMesh = subMeshes[i];
        if ( i == 0 ) {
            subMesh->material->bind();
        } else if ( subMeshes[i - 1]->material != subMesh->material ) {
            subMesh->material->bind();
        }
        subMesh->mesh->render ( shader, subMesh->primitiveType );
    }
}

Model* StillModel::getSubModel ( const vector<string>& subMeshNames )
{
    vector<SubMesh*> refSubMeshes;
    for (auto & subMeshName : subMeshNames) {
        for (auto & elem : subMeshes) {
            if ( subMeshName == elem->name ) {
                refSubMeshes.push_back ( elem );
            }
        }
    }
    if ( refSubMeshes.size() > 0 ) {
        return new StillModel ( refSubMeshes );
    }
    return nullptr;
}

StillSubMesh* StillModel::getSubMesh ( string name )
{
    for (auto & elem : subMeshes) {
        if ( elem->name == name ) {
            return elem;
        }
    }
    return nullptr;
}

vector<SubMesh*>& StillModel::getSubMeshes() const
{
    return ( vector<SubMesh*>& ) subMeshes;
}

void StillModel::setMaterials ( vector<Material*> materials )
{
    if ( materials.size() != subMeshes.size() ) {
        //TODO: should throw unsupport exception
        throw exception();
    }
    for ( size_t i = 0; i < subMeshes.size(); i++ ) {
        subMeshes[i]->material = materials[i];
    }

}

void StillModel::setMaterial ( Material* material )
{
    for (auto & elem : subMeshes) {
        elem->material = material;
    }
}

void StillModel::getBoundingBox ( BoundingBox& bbox )
{
    bbox.inf();
    for (auto & elem : subMeshes) {
        elem->mesh->calculateBoundingBox ( tmpbox );
        bbox.ext ( tmpbox );
    }
}

void StillModel::dispose()
{
    for (auto & elem : subMeshes) {
        elem->mesh->dispose();
    }
}

/* namespace gdx */
