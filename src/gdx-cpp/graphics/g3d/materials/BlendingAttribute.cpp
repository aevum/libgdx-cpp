/*
 * BlendingAttribute.cpp
 *
 *  Created on: Feb 17, 2013
 *      Author: toha
 */

#include "BlendingAttribute.h"
#include <gdx-cpp/internal/gl>

Pool<BlendingAttribute> BlendingAttribute::pool;

BlendingAttribute::BlendingAttribute() {
	// TODO Auto-generated constructor stub

}

BlendingAttribute::~BlendingAttribute() {
}

BlendingAttribute::BlendingAttribute(string name, int srcFunc = GL_SRC_ALPHA, int dstFunc = GL_ONE_MINUS_DST_COLOR)
: MaterialAttribute(name),
  blendSrcFunc(srcFunc),
  blendDstFunc(dstFunc){
}

void BlendingAttribute::bind() {
	gdx::gl->glBlendFunc(blendSrcFunc, blendDstFunc);
}

void BlendingAttribute::bind(ShaderProgram& program) {
	gdx::gl->glBlendFunc(blendSrcFunc, blendDstFunc);
}

MaterialAttribute& BlendingAttribute::copy() {
	return *(new BlendingAttribute(this->name, this->blendSrcFunc, this->blendDstFunc));
}

void BlendingAttribute::set(MaterialAttribute& attribute) {
	BlendingAttribute& blendAttr = dynamic_cast<BlendingAttribute&>(attribute);
	name = blendAttr.name;
	blendSrcFunc = blendAttr.blendSrcFunc;
	blendDstFunc = blendAttr.blendDstFunc;
}

MaterialAttribute& BlendingAttribute::pooledCopy() {
	BlendingAttribute* attr = pool.obtain();
	attr->set(*this);
	return *attr;
}

void BlendingAttribute::free() {
	if (isPooled) {
		pool.free(this);
	}
}
