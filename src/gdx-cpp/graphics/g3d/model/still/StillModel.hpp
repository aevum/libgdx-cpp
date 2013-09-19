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
    StillModel ( vector<SubMesh*>& subMeshes );
    virtual ~StillModel();
    void render() override;
    void render ( ShaderProgram& program ) override;
    Model* getSubModel ( const vector<string>& subMeshNames ) override;
    StillSubMesh* getSubMesh ( string name ) override;
    vector<SubMesh*>& getSubMeshes() const override;
    void setMaterials ( vector<Material*> materials ) override;
    void setMaterial ( Material* material ) override;
    void getBoundingBox ( BoundingBox& bbox ) override;
    void dispose() override;
};

} /* namespace gdx */
#endif /* STILLMODEL_H_ */
