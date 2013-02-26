/*
 * TextureAttribute.cpp
 *
 *  Created on: Feb 20, 2013
 *      Author: toha
 */

#include "TextureAttribute.hpp"

const char* TextureAttribute::diffuseTexture = "diffuseTexture";
const char* TextureAttribute::lightmapTexture = "lightmapTexture";
const char* TextureAttribute::specularTexture = "specularTexture";

Pool<TextureAttribute> TextureAttribute::pool;

TextureAttribute::TextureAttribute() {
}

TextureAttribute::TextureAttribute(const Texture& texture, int unit, const char* name, const Texture::TextureFilter& minFilter, const Texture::TextureFilter& magFilter, const Texture::TextureWrap& uWarp, const Texture::TextureWrap& vWarp)
: TextureAttribute(texture, unit, name, minFilter.getGLEnum(), magFilter.getGLEnum(), uWarp.getGLEnum(), vWarp.getGLEnum()){
}

TextureAttribute::TextureAttribute(const Texture& texture, int unit, const char* name, int minFilter, int magFilter, int uWrap, int vWrap)
: MaterialAttribute(name),
  texture(const_cast<Texture*>(&texture)),
  unit(unit),
  uWrap(uWrap),
  vWrap(vWrap),
  minFilter(minFilter),
  magFilter(magFilter){
	if (unit > MAX_TEXTURE_UNITS) {
		gdx_log_error("gdx", "%d is max texture units supported", MAX_TEXTURE_UNITS);
	}
}

TextureAttribute::TextureAttribute(const Texture& texture, int unit, const char* name)
: TextureAttribute(texture, unit, name, texture.getMinFilter(), texture.getMagFilter(), texture.getUWrap(), texture.getVWrap()){

}

void TextureAttribute::bind() {
	texture->bind(unit);
//	gdx::gl->glTexParameterf(GL10::GL_TEXTURE_2D, GL10::GL_TEXTURE_MIN_FILTER, minFilter);
//	gdx::gl->glTexParameterf(GL10::GL_TEXTURE_2D, GL10::GL_TEXTURE_MAG_FILTER, magFilter);
//	gdx::gl->glTexParameterf(GL10::GL_TEXTURE_2D, GL10::GL_TEXTURE_WRAP_S, uWrap);
//	gdx::gl->glTexParameterf(GL10::GL_TEXTURE_2D, GL10::GL_TEXTURE_WRAP_T, vWrap);
}

void TextureAttribute::bind(ShaderProgram& program) {
	texture->bind(unit);
	//	gdx::gl->glTexParameterf(GL10::GL_TEXTURE_2D, GL10::GL_TEXTURE_MIN_FILTER, minFilter);
	//	gdx::gl->glTexParameterf(GL10::GL_TEXTURE_2D, GL10::GL_TEXTURE_MAG_FILTER, magFilter);
	//	gdx::gl->glTexParameterf(GL10::GL_TEXTURE_2D, GL10::GL_TEXTURE_WRAP_S, uWrap);
	//	gdx::gl->glTexParameterf(GL10::GL_TEXTURE_2D, GL10::GL_TEXTURE_WRAP_T, vWrap);
	program.setUniformi(name, unit);
}

MaterialAttribute& TextureAttribute::copy() {
	return *new TextureAttribute(*texture, unit, name.c_str(), minFilter, magFilter, uWrap, vWrap);
}

void TextureAttribute::set(MaterialAttribute& attr) {
	TextureAttribute& texAttr = static_cast<TextureAttribute&>(attr);
	name = texAttr.name;
	texture = texAttr.texture;
	unit = texAttr.unit;
	magFilter = texAttr.magFilter;
	minFilter = texAttr.minFilter;
	uWrap = texAttr.uWrap;
	vWrap = texAttr.vWrap;
}

bool TextureAttribute::texturePortionEquals(const TextureAttribute* other) {
	if (other == NULL) return false;
	if (this == NULL) return true;

	return (texture == other->texture) && (unit == other->unit) && (minFilter == other->minFilter)
		&& (magFilter == other->magFilter) && (uWrap == other->uWrap) && (vWrap == other->vWrap);
}

MaterialAttribute& TextureAttribute::pooledCopy() {
	TextureAttribute* attr = pool.obtain();
	attr->set(*this);
	return *attr;
}

void TextureAttribute::free() {
	if (isPooled) {
		pool.free(this);
	}
}
