/*
 * ColorAttribute.hpp
 *
 *  Created on: Feb 19, 2013
 *      Author: toha
 */

#ifndef COLORATTRIBUTE_HPP_
#define COLORATTRIBUTE_HPP_

#include "gdx-cpp/graphics/Color.hpp"
#include "gdx-cpp/graphics/g3d/materials/MaterialAttribute.hpp"
#include "gdx-cpp/utils/Pool.hpp"

//using namespace gdx;
//namespace gdx {
class ColorAttribute : public MaterialAttribute
{
public:
    static const char* diffuse;
    static const char* specular;
    static const char* emissive;
    static const char* rim;
    static const char* fog;

    Color color;
    ColorAttribute ( const Color& color, const char* name );
    void bind() override;
    void bind ( ShaderProgram& program ) override;
    MaterialAttribute& copy() override;
    void set ( MaterialAttribute& attr ) override;
    MaterialAttribute& pooledCopy() override;
    void free() override;
    
    virtual ~ColorAttribute();
private:
    static Pool<ColorAttribute> pool;
public:
    ColorAttribute();

};
//}
#endif /* COLORATTRIBUTE_HPP_ */
