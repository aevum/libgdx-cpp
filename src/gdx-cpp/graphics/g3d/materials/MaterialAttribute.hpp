/*
 * MaterialAttribute.h
 *
 *  Created on: Jan 20, 2013
 *      Author: anton
 */

#ifndef MATERIALATTRIBUTE_H_
#define MATERIALATTRIBUTE_H_

#include "gdx-cpp/graphics/glutils/ShaderProgram.hpp"
#include <string>

using namespace std;
using namespace gdx;

class GL10;

class MaterialAttribute
{
private:
	static string FLAG;
public:
	string name;
	MaterialAttribute(const string& name);
	virtual void bind() = 0;
	virtual void bind(ShaderProgram& program) = 0;
	virtual MaterialAttribute& copy() = 0;
	virtual MaterialAttribute& pooledCopy() = 0;
	virtual void free() = 0;
	virtual void set(MaterialAttribute& attr) = 0;
	string getShaderFlag();
protected:
	bool isPooled;
	MaterialAttribute();
};


#endif /* MATERIALATTRIBUTE_H_ */
