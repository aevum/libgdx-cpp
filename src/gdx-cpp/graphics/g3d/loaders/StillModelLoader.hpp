/*
 * StillModelLoader.h
 *
 *  Created on: Jan 23, 2013
 *      Author: anton
 */

#ifndef STILLMODELLOADER_H_
#define STILLMODELLOADER_H_

#include "ModelLoader.hpp"
#include "gdx-cpp/graphics/g3d/model/still/StillModel.hpp"

namespace gdx
{

class StillModelLoader: public ModelLoader
{
public:
	virtual StillModel* load(const FileHandle&, ModelLoaderHints hints) = 0;
};

} /* namespace gdx */
#endif /* STILLMODELLOADER_H_ */
