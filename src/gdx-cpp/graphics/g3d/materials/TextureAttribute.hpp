/*
 * TextureAttribute.hpp
 *
 *  Created on: Feb 20, 2013
 *      Author: toha
 */

#ifndef TEXTUREATTRIBUTE_HPP_
#define TEXTUREATTRIBUTE_HPP_

#include "MaterialAttribute.hpp"
#include "gdx-cpp/graphics/Texture.hpp"

using namespace gdx;

class TextureAttribute: public MaterialAttribute {

public:
	const static int MAX_TEXTURE_UNITS = 16;
	const static char* diffuseTexture = "diffuseTexture";
	const static char* lightmapTexture = "lightmapTexture";
	const static char* specularTexture = "specularTexture";

	Texture& texture;
	int unit;
	int minFilter;
	int magFilter;
	int uWrap;
	int vWrap;

	TextureAttribute(const Texture& texture, int unit, const char* name, const Texture::TextureFilter& minFilter, const Texture::TextureFilter& magFilter, const Texture::TextureWrap& uWarp, const Texture::TextureWrap& vWarp);
	TextureAttribute(const Texture& texture, int unit, const char* name, int minFilter, int magFilter,int uWrap, int vWrap);
	TextureAttribute(const Texture& texture, int unit, const char* name);
	void bind();
	void bind(ShaderProgram& program);
	MaterialAttribute& copy();
	void set(MaterialAttribute& attr);
	bool texturePortionEquals(const TextureAttribute* other);
	MaterialAttribute& pooledCopy();
	void free();
private:
	static Pool<TextureAttribute> pool;
protected:
	TextureAttribute();
};

#endif /* TEXTUREATTRIBUTE_HPP_ */
