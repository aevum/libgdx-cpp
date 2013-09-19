
/*
    Copyright 2011 Aevum Software aevum @ aevumlab.com

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.

    @author Victor Vicente de Carvalho victor.carvalho@aevumlab.com
    @author Ozires Bortolon de Faria ozires@aevumlab.com
*/

#include <algorithm>
#include <limits>
#include <sstream>
#include <string>

#include "BoundingBox.hpp"
#include "gdx-cpp/math/Vector3.hpp"

namespace gdx {
class Matrix4;
}  // namespace gdx

using namespace gdx;

BoundingBox::BoundingBox() {
	crn_dirty = true;
	for (int l_idx = 0; l_idx < 8; l_idx++) {
		crn.push_back(Vector3());
	}
	clr();
}

BoundingBox::BoundingBox (const BoundingBox& bounds) : crn_dirty(true) {
    this->crn.reserve(8);
    this->set(bounds);
}

Vector3& BoundingBox::getCenter () {
    return cnt;
}

void BoundingBox::updateCorners () {
    if (!crn_dirty) return;

    crn[0].set(min.x, min.y, min.z);
    crn[1].set(max.x, min.y, min.z);
    crn[2].set(max.x, max.y, min.z);
    crn[3].set(min.x, max.y, min.z);
    crn[4].set(min.x, min.y, max.z);
    crn[5].set(max.x, min.y, max.z);
    crn[6].set(max.x, max.y, max.z);
    crn[7].set(min.x, max.y, max.z);
    crn_dirty = false;
}

const std::vector< Vector3 >& BoundingBox::getCorners () {
    updateCorners();
    return crn;
}

Vector3& BoundingBox::getDimensions () {
    return dim;
}

Vector3& BoundingBox::getMin () {
    return min;
}

Vector3& BoundingBox::getMax () {
    return max;
}

BoundingBox& BoundingBox::set (const BoundingBox& bounds) {
    crn_dirty = true;
    return this->set(bounds.min, bounds.max);
}

BoundingBox& BoundingBox::set (const Vector3& minimum,const Vector3& maximum) {
    min.set(minimum.x < maximum.x ? minimum.x : maximum.x, minimum.y < maximum.y ? minimum.y : maximum.y,
            minimum.z < maximum.z ? minimum.z : maximum.z);
    max.set(minimum.x > maximum.x ? minimum.x : maximum.x, minimum.y > maximum.y ? minimum.y : maximum.y,
            minimum.z > maximum.z ? minimum.z : maximum.z);
    cnt.set(min).add(max).mul(0.5f);
    dim.set(max).sub(min);
    crn_dirty = true;
    return *this;
}

BoundingBox& BoundingBox::set (const std::vector<Vector3>& points) {
    this->inf();

    auto it = points.begin();
    auto end = points.end();

    for (; it != end; ++it)
        this->ext(*it);

    crn_dirty = true;
    return *this;
}

BoundingBox& BoundingBox::inf () {
    //TODO: not sure if this works
    min.set(std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity());
    max.set(-std::numeric_limits<float>::infinity(), -std::numeric_limits<float>::infinity(), -std::numeric_limits<float>::infinity());
    cnt.set(0, 0, 0);
    dim.set(0, 0, 0);
    crn_dirty = true;
    return *this;
}

BoundingBox& BoundingBox::ext (const Vector3& point) {
    crn_dirty = true;
    return this->set(min.set(_min(min.x, point.x), _min(min.y, point.y), _min(min.z, point.z)),
                     max.set(std::max(max.x, point.x), std::max(max.y, point.y), std::max(max.z, point.z)));
}

BoundingBox& BoundingBox::clr () {
    crn_dirty = true;
    return this->set(min.set(0, 0, 0), max.set(0, 0, 0));
}

bool BoundingBox::isValid () {
    return !(min.x == max.x && min.y == max.y && min.z == max.z);
}

BoundingBox& BoundingBox::ext (const BoundingBox& a_bounds) {
    crn_dirty = true;
    return this->set(min.set(_min(min.x, a_bounds.min.x), _min(min.y, a_bounds.min.y), _min(min.z, a_bounds.min.z)),
                     max.set(_max(max.x, a_bounds.max.x), _max(max.y, a_bounds.max.y), _max(max.z, a_bounds.max.z)));
}

BoundingBox& BoundingBox::mul (const Matrix4& matrix) {
    updateCorners();
    this->inf();

    for ( int i = 0; i < 8; ++i) {
        crn[i].mul(matrix);
        min.set(_min(min.x, crn[i].x), _min(min.y, crn[i].y), _min(min.z, crn[i].z));
        max.set(_max(max.x, crn[i].x), _max(max.y, crn[i].y), _max(max.z, crn[i].z));
    }

    crn_dirty = true;
    return this->set(min, max);
}

bool BoundingBox::contains (const BoundingBox& bounds) {
    if (!isValid()) return true;
    if (min.x > bounds.max.x) return false;
    if (min.y > bounds.max.y) return false;
    if (min.z > bounds.max.z) return false;
    if (max.x < bounds.min.x) return false;
    if (max.y < bounds.min.y) return false;
    if (max.z < bounds.min.z) return false;
    return true;
}

bool BoundingBox::contains (const Vector3& v) {
    if (min.x > v.x) return false;
    if (max.x < v.x) return false;
    if (min.y > v.y) return false;
    if (max.y < v.y) return false;
    if (min.z > v.z) return false;
    if (max.z < v.z) return false;

    return true;
}

std::string BoundingBox::toString () {
    std::stringstream ss;
    ss << "[" + min.toString() << "|" + max.toString() << "]";
    return ss.str();
}

BoundingBox& BoundingBox::ext (float x,float y,float z) {
    crn_dirty = true;
    return this->set(min.set(_min(min.x, x), _min(min.y, y), _min(min.z, z)), max.set(_max(max.x, x), _max(max.y, y), _max(max.z, z)));
}

