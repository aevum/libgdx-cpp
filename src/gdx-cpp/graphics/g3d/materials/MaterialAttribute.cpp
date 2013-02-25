/*
 * MaterialAttribute.cpp
 *
 *  Created on: Jan 21, 2013
 *      Author: anton
 */

#include "MaterialAttribute.hpp"

string MaterialAttribute::FLAG = "Flag";

MaterialAttribute::MaterialAttribute(const string& name) {
	this->name = name;
	isPooled = false;
}

string MaterialAttribute::getShaderFlag() {
	return name + FLAG;
}

MaterialAttribute::MaterialAttribute() {
	isPooled = true;
}
