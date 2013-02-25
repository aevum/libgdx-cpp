/*
 * BlendingAttribute.h
 *
 *  Created on: Feb 17, 2013
 *      Author: toha
 */

#ifndef BLENDINGATTRIBUTE_H_
#define BLENDINGATTRIBUTE_H_

#include <gdx-cpp/graphics/g3d/materials/MaterialAttribute.hpp>
#include <gdx-cpp/utils/Pool.hpp>
#include <gdx-cpp/graphics/GL10.hpp>
#include <gdx-cpp/Gdx.hpp>
#include <string>
#include <GLES2/gl2.h>

using namespace std;

class BlendingAttribute : public MaterialAttribute {
private:
	static Pool<BlendingAttribute> pool;
public:
	const static string translucent;
	int blendSrcFunc;
	int blendDstFunc;
	BlendingAttribute();
	BlendingAttribute(string name, int srcFunc = GL_SRC_ALPHA, int dstFunc = GL_ONE_MINUS_DST_COLOR);
	void bind();
	void bind(ShaderProgram& program);
	MaterialAttribute& copy();
	void set(MaterialAttribute& attr);
	MaterialAttribute& pooledCopy();
	void free();
	virtual ~BlendingAttribute();
};

#endif /* BLENDINGATTRIBUTE_H_ */
