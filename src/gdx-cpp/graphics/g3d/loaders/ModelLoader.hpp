/*
 * ModelLoader.h
 *
 *  Created on: Jan 23, 2013
 *      Author: anton
 */

#ifndef MODELLOADER_H_
#define MODELLOADER_H_

#include "gdx-cpp/graphics/g3d/ModelLoaderHints.hpp"
#include "gdx-cpp/graphics/g3d/model/Model.hpp"
#include "gdx-cpp/files/FileHandle.hpp"

namespace gdx {

class ModelLoader
{
public:
	virtual Model* load(const FileHandle& file, ModelLoaderHints hints) = 0;
};

}
 /* namespace gdx */
#endif /* MODELLOADER_H_ */
