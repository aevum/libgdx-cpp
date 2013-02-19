/*
 * ColorAttribute.cpp
 *
 *  Created on: Feb 19, 2013
 *      Author: toha
 */

#include "ColorAttribute.hpp"

const char* ColorAttribute::diffuse = "diffuseColor";
const char* ColorAttribute::specular = "specularColor";
const char* ColorAttribute::emissive = "emissiveColor";
const char* ColorAttribute::rim = "rimColor";
const char* ColorAttribute::fog = "fogColor";
Pool<ColorAttribute> ColorAttribute::pool;

ColorAttribute::ColorAttribute() {

}

ColorAttribute::ColorAttribute(const Color& color, const char* name)
: MaterialAttribute(string(name)) {
	this->color.set(color);
}

void ColorAttribute::bind() {
	if (gdx::gl10 == NULL) {
		gdx_log_error("gdx", "Can't call ColorAttribute.bind() in a GL20 context");
	}
	if (diffuse == diffuse) {
		gdx::gl10->glColor4f(color.r, color.g, color.b, color.a);
	}
}

void ColorAttribute::bind(ShaderProgram& program) {
	program.setUniformf(name, color.r, color.g, color.b, color.a);
}

MaterialAttribute& ColorAttribute::copy() {
	return *new ColorAttribute(color, name.c_str());
}

void ColorAttribute::set(MaterialAttribute& attr) {
	ColorAttribute& colorAttr = static_cast<ColorAttribute&>(attr);
	name = colorAttr.name;
	color.r = colorAttr.color.r;
	color.g = colorAttr.color.g;
	color.b = colorAttr.color.b;
	color.a = colorAttr.color.a;
}

MaterialAttribute& ColorAttribute::pooledCopy() {
	ColorAttribute* attr = pool.obtain();
	attr->set(*this);
	return *attr;
}

void ColorAttribute::free() {
	if (isPooled) {
		pool.free(this);
	}
}
