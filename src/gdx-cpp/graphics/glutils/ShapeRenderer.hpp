
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

#ifndef GDX_CPP_GRAPHICS_GLUTILS_SHAPERENDERER_HPP_
#define GDX_CPP_GRAPHICS_GLUTILS_SHAPERENDERER_HPP_

#include "gdx-cpp/graphics/Color.hpp"
#include "gdx-cpp/math/Matrix4.hpp"
#include "ImmediateModeRenderer.hpp"

namespace gdx {

class ShapeRenderer {
public:
    class ShapeType {
    public:
        const static ShapeType Point;
        const static ShapeType Line;
        const static ShapeType Rectangle;
        const static ShapeType FilledRectangle;
        const static ShapeType Box;

        int getGlType () const;

        bool operator==(const ShapeType& other) const {
            return this == &other;
        }

        bool operator!=(const ShapeType& other) const {
            return this != &other;
        }
        
    private:
        int glType;
        ShapeType(int glType) ;
    };

    int getGlType ();
    void setColor (const Color& color);
    void setColor (float r,float g,float b,float a);
    void setProjectionMatrix (const Matrix4& matrix);
    void setTransformMatrix (const Matrix4& matrix);
    void identity ();
    void translate (float x,float y,float z);
    void rotate (float axisX,float axisY,float axisZ,float angle);
    void scale (float scaleX,float scaleY,float scaleZ);
    void begin (const ShapeType& type);
    void point (float x,float y,float z);
    void line (float x,float y,float z,float x2,float y2,float z2);
    void line (float x,float y,float x2,float y2);
    void rect (float x,float y,float width,float height);
    void filledRect (float x,float y,float width,float height);
    void box (float x,float y,float z,float width,float height,float depth);
    void end ();
    void dispose ();
    ShapeRenderer ();

    virtual ~ShapeRenderer();
protected:
    ImmediateModeRenderer* renderer;
    bool matrixDirty;
    Matrix4 projView;
    Matrix4 transform;
    Matrix4 combined;
    Matrix4 tmp;
    Color color;
    const ShapeType* currType;

private:
    void checkDirty ();
    void checkFlush (int newVertices);
    int glType ;
};

} // namespace gdx

#endif // GDX_CPP_GRAPHICS_GLUTILS_SHAPERENDERER_HPP_
