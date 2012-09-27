
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

#include "ShapeRenderer.hpp"

#include "gdx-cpp/graphics/GL10.hpp"
#include "gdx-cpp/Gdx.hpp"
#include "ImmediateModeRenderer10.hpp"
#include "ImmediateModeRenderer20.hpp"
#include "gdx-cpp/gl.hpp"

#include <stdexcept>

using namespace gdx;

const ShapeRenderer::ShapeType ShapeRenderer::ShapeType::Point(GL_POINTS);
const ShapeRenderer::ShapeType ShapeRenderer::ShapeType::Line(GL_LINES);
const ShapeRenderer::ShapeType ShapeRenderer::ShapeType::Rectangle(GL_LINES);
const ShapeRenderer::ShapeType ShapeRenderer::ShapeType::FilledRectangle(GL_TRIANGLES);
const ShapeRenderer::ShapeType ShapeRenderer::ShapeType::Box(GL_LINES);

int ShapeRenderer::getGlType () {
    return glType;
}

void ShapeRenderer::setColor (const Color& color) {
    this->color.set(color);
}

void ShapeRenderer::setColor (float r,float g,float b,float a) {
    this->color.set(r, g, b, a);
}

void ShapeRenderer::setProjectionMatrix (const Matrix4& matrix) {
    projView.set(matrix);
    matrixDirty = true;
}

void ShapeRenderer::setTransformMatrix (const Matrix4& matrix) {
    transform.set(matrix);
    matrixDirty = true;
}

void ShapeRenderer::identity () {
    transform.idt();
    matrixDirty = true;
}

void ShapeRenderer::translate (float x,float y,float z) {
    transform.translate(x, y, z);
    matrixDirty = true;
}

void ShapeRenderer::rotate (float axisX,float axisY,float axisZ,float angle) {
    transform.rotate(axisX, axisY, axisZ, angle);
    matrixDirty = true;
}

void ShapeRenderer::scale (float scaleX,float scaleY,float scaleZ) {
    transform.scale(scaleX, scaleY, scaleZ);
    matrixDirty = true;
}

void ShapeRenderer::begin (const ShapeType& type) {
    if(currType != NULL) gdx_log_error("gdx","Call end() before beginning a new shape batch");
    currType = &type;
    if(matrixDirty) {
        combined.set(projView);
        Matrix4::mul(combined.val, transform.val);
        matrixDirty = false;
    }
    
    if(renderer->getRendererType() == ImmediateModeRenderer::IMMEDIATE_GLES10) {
        gl10->glMatrixMode(GL_PROJECTION);
        gl10->glLoadMatrixf(combined.val);
        gl10->glMatrixMode(GL_MODELVIEW);
        gl10->glLoadIdentity();
        ((ImmediateModeRenderer10*)renderer)->begin(currType->getGlType());
    } else {
        ((ImmediateModeRenderer20*)renderer)->begin(combined, currType->getGlType());
    }
}

void ShapeRenderer::point (float x,float y,float z) {
    if(*currType != ShapeType::Point) gdx_log_error("gdx","Must call begin(ShapeType::Point)");
    checkDirty();
    checkFlush(1);
    renderer->color(color.r, color.g, color.b, color.a);
    renderer->vertex(x, y, z);
}

void ShapeRenderer::line (float x,float y,float z,float x2,float y2,float z2) {
    if(*currType != ShapeType::Line) gdx_log_error("gdx","Must call begin(ShapeType::Line)");
    checkDirty();
    checkFlush(2);
    renderer->color(color.r, color.g, color.b, color.a);
    renderer->vertex(x, y, z);
    renderer->color(color.r, color.g, color.b, color.a);
    renderer->vertex(x2, y2, z2);
}

void ShapeRenderer::line (float x,float y,float x2,float y2) {
    if(*currType != ShapeType::Line) gdx_log_error("gdx","Must call begin(ShapeType::Line)");
    checkDirty();
    checkFlush(2);
    if(*currType != ShapeType::Line) gdx_log_error("gdx","Must call begin(ShapeType::Line)");
    renderer->color(color.r, color.g, color.b, color.a);
    renderer->vertex(x, y, 0);
    renderer->color(color.r, color.g, color.b, color.a);
    renderer->vertex(x2, y2, 0);
}

void ShapeRenderer::rect (float x,float y,float width,float height) {
    if(*currType != ShapeType::Rectangle) gdx_log_error("gdx","Must call begin(ShapeType::Rectangle)");
    checkDirty();
    checkFlush(8);
    renderer->color(color.r, color.g, color.b, color.a);
    renderer->vertex(x, y, 0);
    renderer->color(color.r, color.g, color.b, color.a);
    renderer->vertex(x + width, y, 0);

    renderer->color(color.r, color.g, color.b, color.a);
    renderer->vertex(x + width, y, 0);
    renderer->color(color.r, color.g, color.b, color.a);
    renderer->vertex(x + width, y + height, 0);

    renderer->color(color.r, color.g, color.b, color.a);
    renderer->vertex(x + width, y + height, 0);
    renderer->color(color.r, color.g, color.b, color.a);
    renderer->vertex(x, y + height, 0);

    renderer->color(color.r, color.g, color.b, color.a);
    renderer->vertex(x, y + height, 0);
    renderer->color(color.r, color.g, color.b, color.a);
    renderer->vertex(x, y, 0);
}

void ShapeRenderer::filledRect (float x,float y,float width,float height) {
    if(*currType != ShapeType::FilledRectangle) gdx_log_error("gdx","Must call begin(ShapeType::FilledRectangle)");
    checkDirty();
    checkFlush(8);
    renderer->color(color.r, color.g, color.b, color.a);
    renderer->vertex(x, y, 0);
    renderer->color(color.r, color.g, color.b, color.a);
    renderer->vertex(x + width, y, 0);
    renderer->color(color.r, color.g, color.b, color.a);
    renderer->vertex(x + width, y + height, 0);

    renderer->color(color.r, color.g, color.b, color.a);
    renderer->vertex(x + width, y + height, 0);
    renderer->color(color.r, color.g, color.b, color.a);
    renderer->vertex(x, y + height, 0);
    renderer->color(color.r, color.g, color.b, color.a);
    renderer->vertex(x, y, 0);
}

void ShapeRenderer::box (float x,float y,float z,float width,float height,float depth) {
    if(*currType != ShapeType::Box) gdx_log_error("gdx","Must call begin(ShapeType::Box)");
    checkDirty();
    checkFlush(16);

    depth = -depth;
    renderer->color(color.r, color.g, color.b, color.a);
    renderer->vertex(x, y, z);
    renderer->color(color.r, color.g, color.b, color.a);
    renderer->vertex(x + width, y, z);

    renderer->color(color.r, color.g, color.b, color.a);
    renderer->vertex(x + width, y, z);
    renderer->color(color.r, color.g, color.b, color.a);
    renderer->vertex(x + width, y, z + depth);

    renderer->color(color.r, color.g, color.b, color.a);
    renderer->vertex(x + width, y, z + depth);
    renderer->color(color.r, color.g, color.b, color.a);
    renderer->vertex(x, y, z + depth);

    renderer->color(color.r, color.g, color.b, color.a);
    renderer->vertex(x, y, z + depth);
    renderer->color(color.r, color.g, color.b, color.a);
    renderer->vertex(x, y, z);

    renderer->color(color.r, color.g, color.b, color.a);
    renderer->vertex(x, y, z);
    renderer->color(color.r, color.g, color.b, color.a);
    renderer->vertex(x, y + height, z);

    renderer->color(color.r, color.g, color.b, color.a);
    renderer->vertex(x, y + height, z);
    renderer->color(color.r, color.g, color.b, color.a);
    renderer->vertex(x + width, y + height, z);

    renderer->color(color.r, color.g, color.b, color.a);
    renderer->vertex(x + width, y + height, z);
    renderer->color(color.r, color.g, color.b, color.a);
    renderer->vertex(x + width, y + height, z + depth);

    renderer->color(color.r, color.g, color.b, color.a);
    renderer->vertex(x + width, y + height, z + depth);
    renderer->color(color.r, color.g, color.b, color.a);
    renderer->vertex(x, y + height, z + depth);

    renderer->color(color.r, color.g, color.b, color.a);
    renderer->vertex(x, y + height, z + depth);
    renderer->color(color.r, color.g, color.b, color.a);
    renderer->vertex(x, y + height, z);

    renderer->color(color.r, color.g, color.b, color.a);
    renderer->vertex(x + width, y, z);
    renderer->color(color.r, color.g, color.b, color.a);
    renderer->vertex(x + width, y + height, z);

    renderer->color(color.r, color.g, color.b, color.a);
    renderer->vertex(x + width, y, z + depth);
    renderer->color(color.r, color.g, color.b, color.a);
    renderer->vertex(x + width, y + height, z + depth);

    renderer->color(color.r, color.g, color.b, color.a);
    renderer->vertex(x, y, z + depth);
    renderer->color(color.r, color.g, color.b, color.a);
    renderer->vertex(x, y + height, z + depth);
}

void ShapeRenderer::checkDirty () {
    if(!matrixDirty) return;
    end();
    begin(*currType);
}

void ShapeRenderer::checkFlush (int newVertices) {
    if(renderer->getMaxVertices() - renderer->getNumVertices() >= newVertices) return;
    const ShapeType* checkType = currType;
    end();
    begin(*checkType);
}

void ShapeRenderer::end () {
    renderer->end();
    currType = NULL;
}

void ShapeRenderer::dispose () {
    renderer->dispose();
}

ShapeRenderer::ShapeRenderer ()
: renderer(NULL),
matrixDirty(false),
color(1,1,1,1),
currType(NULL)
{
    if(graphics->isGL20Available())
        renderer = new ImmediateModeRenderer20(false, true, 0);
    else
        renderer = new ImmediateModeRenderer10();
    
    projView.setToOrtho2D(0, 0, graphics->getWidth(), graphics->getHeight());
}

int ShapeRenderer::ShapeType::getGlType() const {
    return glType;
}

ShapeRenderer::ShapeType::ShapeType(int glType) {
    this->glType = glType;
}

ShapeRenderer::~ShapeRenderer()
{
    delete renderer;
}


