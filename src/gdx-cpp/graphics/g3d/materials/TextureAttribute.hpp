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
#include "gdx-cpp/utils/Pool.hpp"

using namespace gdx;

class TextureAttribute: public MaterialAttribute
{

public:
    const static int MAX_TEXTURE_UNITS = 16;
    const static char* diffuseTexture;
    const static char* lightmapTexture;
    const static char* specularTexture;

    Texture* texture;
    int unit;
    int minFilter;
    int magFilter;
    int uWrap;
    int vWrap;

    TextureAttribute ( const Texture& texture, int unit, const char* name, const Texture::TextureFilter& minFilter, const Texture::TextureFilter& magFilter, const Texture::TextureWrap& uWarp, const Texture::TextureWrap& vWarp );
    TextureAttribute ( const Texture& texture, int unit, const char* name, int minFilter, int magFilter,int uWrap, int vWrap );
    TextureAttribute ( const Texture& texture, int unit, const char* name );
    void bind() override;
    void bind ( ShaderProgram& program ) override;
    MaterialAttribute& copy() override;
    void set ( MaterialAttribute& attr ) override;
    bool texturePortionEquals ( const TextureAttribute* other );
    MaterialAttribute& pooledCopy() override;
    void free() override;
    
    virtual ~TextureAttribute();
private:
    static Pool<TextureAttribute> pool;
public:
    TextureAttribute();
};

#endif /* TEXTUREATTRIBUTE_HPP_ */
