
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

#include "Decal.hpp"

using namespace gdx_cpp::graphics::g3d::decals;

void Decal::setColor (float r,float g,float b,float a) {
    int intBits = ((int)(255 * a) << 24) | ((int)(255 * b) << 16) | ((int)(255 * g) << 8) | ((int)(255 * r));
    float color = Float.intBitsToFloat(intBits & 0xfeffffff);
    vertices[C1] = color;
    vertices[C2] = color;
    vertices[C3] = color;
    vertices[C4] = color;
}

void Decal::rotateX (float angle) {
    rotator.set(X_AXIS, angle);
    rotation.mul(rotator);
    updated = false;
}

void Decal::rotateY (float angle) {
    rotator.set(Y_AXIS, angle);
    rotation.mul(rotator);
    updated = false;
}

void Decal::rotateZ (float angle) {
    rotator.set(Z_AXIS, angle);
    rotation.mul(rotator);
    updated = false;
}

void Decal::setRotation (const gdx_cpp::math::Vector3& dir,const gdx_cpp::math::Vector3& up) {
    tmp.set(up).crs(dir).nor();
    tmp2.set(dir).crs(tmp).nor();
    rotation.setFromAxes(tmp.x, tmp.y, tmp.z, tmp2.x, tmp2.y, tmp2.z, dir.x, dir.y, dir.z);
    updated = false;
}

gdx_cpp::math::Quaternion& Decal::getRotation () {
    return rotation;
}

void Decal::translateX (float units) {
    this.position.x += units;
    updated = false;
}

void Decal::setX (float x) {
    this.position.x = x;
    updated = false;
}

float Decal::getX () {
    return this.position.x;
}

void Decal::translateY (float units) {
    this.position.y += units;
    updated = false;
}

void Decal::setY (float y) {
    this.position.y = y;
    updated = false;
}

float Decal::getY () {
    return this.position.y;
}

void Decal::translateZ (float units) {
    this.position.z += units;
    updated = false;
}

void Decal::setZ (float z) {
    this.position.z = z;
    updated = false;
}

float Decal::getZ () {
    return this.position.z;
}

void Decal::translate (float x,float y,float z) {
    this.position.add(x, y, z);
    updated = false;
}

void Decal::setPosition (float x,float y,float z) {
    this.position.set(x, y, z);
    updated = false;
}

gdx_cpp::math::Vector3& Decal::getPosition () {
    return position;
}

void Decal::setScaleX (float scale) {
    this.scale.x = scale;
    updated = false;
}

float Decal::getScaleX () {
    return this.scale.x;
}

void Decal::setScaleY (float scale) {
    this.scale.y += scale;
    updated = false;
}

float Decal::getScaleY () {
    return this.scale.y;
}

void Decal::setScale (float scaleX,float scaleY) {
    this.scale.set(scaleX, scaleY);
    updated = false;
}

void Decal::setScale (float scale) {
    this.scale.set(scale, scale);
    updated = false;
}

void Decal::setWidth (float width) {
    this.dimensions.x = width;
    updated = false;
}

float Decal::getWidth () {
    return this.dimensions.x;
}

void Decal::setHeight (float height) {
    this.dimensions.y += height;
    updated = false;
}

float Decal::getHeight () {
    return dimensions.y;
}

void Decal::setDimensions (float width,float height) {
    dimensions.set(width, height);
    updated = false;
}

float* Decal::getVertices () {
    return vertices;
}

void Decal::update () {
    if (!updated) {
        resetVertices();
        transformVertices();
    }
}

void Decal::transformVertices () {
    /** It would be possible to also load the x,y,z into a Vector3 and apply all the transformations using already existing
     * methods. Especially the quaternion rotation already exists in the Quaternion class, it then would look like this:
     * ----------------------------------------------------------------------------------------------------
     * v3.set(vertices[xIndex] * scale.x, vertices[yIndex] * scale.y, vertices[zIndex]); rotation.transform(v3);
     * v3.add(position); vertices[xIndex] = v3.x; vertices[yIndex] = v3.y; vertices[zIndex] = v3.z;
     * ---------------------------------------------------------------------------------------------------- However, a half ass
     * benchmark with dozens of thousands decals showed that doing it "by hand", as done here, is about 10% faster. So while
     * duplicate code should be avoided for maintenance reasons etc. the performance gain is worth it. The math doesn't change. */
    float x, y, z, w;
    float tx, ty;
    if (transformationOffset != null) {
        tx = -transformationOffset.x;
        ty = -transformationOffset.y;
    } else {
        tx = ty = 0;
    }
    /** Transform the first vertex */
    // first apply the scale to the vector
    x = (vertices[X1] + tx) * scale.x;
    y = (vertices[Y1] + ty) * scale.y;
    z = vertices[Z1];
    // then transform the vector using the rotation quaternion
    vertices[X1] = rotation.w * x + rotation.y * z - rotation.z * y;
    vertices[Y1] = rotation.w * y + rotation.z * x - rotation.x * z;
    vertices[Z1] = rotation.w * z + rotation.x * y - rotation.y * x;
    w = -rotation.x * x - rotation.y * y - rotation.z * z;
    rotation.conjugate();
    x = vertices[X1];
    y = vertices[Y1];
    z = vertices[Z1];
    vertices[X1] = w * rotation.x + x * rotation.w + y * rotation.z - z * rotation.y;
    vertices[Y1] = w * rotation.y + y * rotation.w + z * rotation.x - x * rotation.z;
    vertices[Z1] = w * rotation.z + z * rotation.w + x * rotation.y - y * rotation.x;
    rotation.conjugate(); // <- don't forget to conjugate the rotation back to normal
    // finally translate the vector according to position
    vertices[X1] += position.x - tx;
    vertices[Y1] += position.y - ty;
    vertices[Z1] += position.z;
    /** Transform the second vertex */
    // first apply the scale to the vector
    x = (vertices[X2] + tx) * scale.x;
    y = (vertices[Y2] + ty) * scale.y;
    z = vertices[Z2];
    // then transform the vector using the rotation quaternion
    vertices[X2] = rotation.w * x + rotation.y * z - rotation.z * y;
    vertices[Y2] = rotation.w * y + rotation.z * x - rotation.x * z;
    vertices[Z2] = rotation.w * z + rotation.x * y - rotation.y * x;
    w = -rotation.x * x - rotation.y * y - rotation.z * z;
    rotation.conjugate();
    x = vertices[X2];
    y = vertices[Y2];
    z = vertices[Z2];
    vertices[X2] = w * rotation.x + x * rotation.w + y * rotation.z - z * rotation.y;
    vertices[Y2] = w * rotation.y + y * rotation.w + z * rotation.x - x * rotation.z;
    vertices[Z2] = w * rotation.z + z * rotation.w + x * rotation.y - y * rotation.x;
    rotation.conjugate(); // <- don't forget to conjugate the rotation back to normal
    // finally translate the vector according to position
    vertices[X2] += position.x - tx;
    vertices[Y2] += position.y - ty;
    vertices[Z2] += position.z;
    /** Transform the third vertex */
    // first apply the scale to the vector
    x = (vertices[X3] + tx) * scale.x;
    y = (vertices[Y3] + ty) * scale.y;
    z = vertices[Z3];
    // then transform the vector using the rotation quaternion
    vertices[X3] = rotation.w * x + rotation.y * z - rotation.z * y;
    vertices[Y3] = rotation.w * y + rotation.z * x - rotation.x * z;
    vertices[Z3] = rotation.w * z + rotation.x * y - rotation.y * x;
    w = -rotation.x * x - rotation.y * y - rotation.z * z;
    rotation.conjugate();
    x = vertices[X3];
    y = vertices[Y3];
    z = vertices[Z3];
    vertices[X3] = w * rotation.x + x * rotation.w + y * rotation.z - z * rotation.y;
    vertices[Y3] = w * rotation.y + y * rotation.w + z * rotation.x - x * rotation.z;
    vertices[Z3] = w * rotation.z + z * rotation.w + x * rotation.y - y * rotation.x;
    rotation.conjugate(); // <- don't forget to conjugate the rotation back to normal
    // finally translate the vector according to position
    vertices[X3] += position.x - tx;
    vertices[Y3] += position.y - ty;
    vertices[Z3] += position.z;
    /** Transform the fourth vertex */
    // first apply the scale to the vector
    x = (vertices[X4] + tx) * scale.x;
    y = (vertices[Y4] + ty) * scale.y;
    z = vertices[Z4];
    // then transform the vector using the rotation quaternion
    vertices[X4] = rotation.w * x + rotation.y * z - rotation.z * y;
    vertices[Y4] = rotation.w * y + rotation.z * x - rotation.x * z;
    vertices[Z4] = rotation.w * z + rotation.x * y - rotation.y * x;
    w = -rotation.x * x - rotation.y * y - rotation.z * z;
    rotation.conjugate();
    x = vertices[X4];
    y = vertices[Y4];
    z = vertices[Z4];
    vertices[X4] = w * rotation.x + x * rotation.w + y * rotation.z - z * rotation.y;
    vertices[Y4] = w * rotation.y + y * rotation.w + z * rotation.x - x * rotation.z;
    vertices[Z4] = w * rotation.z + z * rotation.w + x * rotation.y - y * rotation.x;
    rotation.conjugate(); // <- don't forget to conjugate the rotation back to normal
    // finally translate the vector according to position
    vertices[X4] += position.x - tx;
    vertices[Y4] += position.y - ty;
    vertices[Z4] += position.z;
    updated = true;
}

void Decal::resetVertices () {
    float left = -dimensions.x / 2f;
    float right = left + dimensions.x;
    float top = dimensions.y / 2f;
    float bottom = top - dimensions.y;

    // left top
    vertices[X1] = left;
    vertices[Y1] = top;
    vertices[Z1] = 0;
    // right top
    vertices[X2] = right;
    vertices[Y2] = top;
    vertices[Z2] = 0;
    // left bot
    vertices[X3] = left;
    vertices[Y3] = bottom;
    vertices[Z3] = 0;
    // right bot
    vertices[X4] = right;
    vertices[Y4] = bottom;
    vertices[Z4] = 0;

    updated = false;
}

void Decal::updateUVs () {
    TextureRegion tr = material.textureRegion;
    // left top
    vertices[U1] = tr.getU();
    vertices[V1] = tr.getV();
    // right top
    vertices[U2] = tr.getU2();
    vertices[V2] = tr.getV();
    // left bot
    vertices[U3] = tr.getU();
    vertices[V3] = tr.getV2();
    // right bot
    vertices[U4] = tr.getU2();
    vertices[V4] = tr.getV2();
}

void Decal::setTextureRegion (const gdx_cpp::graphics::g2d::TextureRegion& textureRegion) {
    this.material.textureRegion = textureRegion;
    updateUVs();
}

void Decal::setBlending (int srcBlendFactor,int dstBlendFactor) {
    material.srcBlendFactor = srcBlendFactor;
    material.dstBlendFactor = dstBlendFactor;
}

DecalMaterial& Decal::getMaterial () {
    return material;
}

Decal& Decal::newDecal (const gdx_cpp::graphics::g2d::TextureRegion& textureRegion) {
    return newDecal(textureRegion.getRegionWidth(), textureRegion.getRegionHeight(), textureRegion, DecalMaterial.NO_BLEND,
                    DecalMaterial.NO_BLEND);
}

Decal& Decal::newDecal (const gdx_cpp::graphics::g2d::TextureRegion& textureRegion,bool hasTransparency) {
    return newDecal(textureRegion.getRegionWidth(), textureRegion.getRegionHeight(), textureRegion,
                    hasTransparency ? GL10.GL_SRC_ALPHA : DecalMaterial.NO_BLEND, hasTransparency ? GL10.GL_ONE_MINUS_SRC_ALPHA
                    : DecalMaterial.NO_BLEND);
}

Decal& Decal::newDecal (float width,float height,const gdx_cpp::graphics::g2d::TextureRegion& textureRegion) {
    return newDecal(width, height, textureRegion, DecalMaterial.NO_BLEND, DecalMaterial.NO_BLEND);
}

Decal& Decal::newDecal (float width,float height,const gdx_cpp::graphics::g2d::TextureRegion& textureRegion,bool hasTransparency) {
    return newDecal(width, height, textureRegion, hasTransparency ? GL10.GL_SRC_ALPHA : DecalMaterial.NO_BLEND,
                    hasTransparency ? GL10.GL_ONE_MINUS_SRC_ALPHA : DecalMaterial.NO_BLEND);
}

Decal& Decal::newDecal (float width,float height,const gdx_cpp::graphics::g2d::TextureRegion& textureRegion,int srcBlendFactor,int dstBlendFactor) {
    Decal decal = new Decal();
    decal.setTextureRegion(textureRegion);
    decal.setBlending(srcBlendFactor, dstBlendFactor);
    decal.dimensions.x = width;
    decal.dimensions.y = height;
    decal.setColor(1, 1, 1, 1);
    return decal;
}

