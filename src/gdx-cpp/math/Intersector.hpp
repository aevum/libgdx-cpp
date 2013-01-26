
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

#ifndef GDX_CPP_MATH_INTERSECTOR_HPP_
#define GDX_CPP_MATH_INTERSECTOR_HPP_

#include <vector>

#include "Plane.hpp"
#include "Vector3.hpp"



namespace gdx {
class BoundingBox;
class BoundingBox;
class Circle;
class Ray;
class Rectangle;
class Vector2;


class Intersector {
public:

    static float getLowestPositiveRoot (float a,float b,float c);
    static bool isPointInTriangle (const Vector3& point,const Vector3& t1,const Vector3& t2,const Vector3& t3);
    static bool intersectSegmentPlane (const Vector3& start, const Vector3& end, Plane& plane, Vector3* intersection);
    static bool isPointInPolygon (std::vector<Vector2>& polygon,const Vector2& point);
    static float distanceLinePoint (const Vector2& start,const Vector2& end,const Vector2& point);
    static bool intersectSegmentCircle (const Vector2& start,const Vector2& end,const Vector2& center,float squareRadius);
    static float intersectSegmentCircleDisplace (const Vector2& start, const Vector2& end, const Vector2& point, float radius, Vector2& displacement);
    static bool intersectRayPlane (const Ray& ray, Plane& plane, Vector3* intersection);
    static bool intersectRayTriangle (const Ray& ray, const Vector3& t1, const Vector3& t2, const Vector3& t3, Vector3* intersection);
    static bool intersectRaySphere (const Ray& ray, const Vector3& center, float radius, Vector3* intersection);
    static bool intersectRayBoundsFast (const Ray& ray,const BoundingBox& box);
    static bool intersectRayTriangles (const Ray& ray, const std::vector< float, std::allocator< float > >& triangles, Vector3* intersection);
    static bool intersectRayTriangles (const Ray& ray, const std::vector< float, std::allocator< float > >& vertices, const std::vector< short int, std::allocator< short int > >& indices, int vertexSize, Vector3* intersection);
    static bool intersectRayTriangles (const Ray& ray, const std::vector< Vector3 >& triangles, Vector3* intersection);
    static bool intersectRectangles (const Rectangle& a,const Rectangle& b);
    static bool intersectLines (const Vector2& p1,const Vector2& p2,const Vector2& p3,const Vector2& p4, Vector2& intersection);
    static bool intersectSegments (const Vector2& p1, const Vector2& p2, const Vector2& p3, const Vector2& p4, Vector2* intersection);
    static bool overlapCircles (const Circle& c1,const Circle& c2);
    static bool overlapRectangles (const Rectangle& r1,const Rectangle& r2);
    static bool overlapCircleRectangle (const Circle& c,const Rectangle& r);

protected:
    static float det (float a, float b, float c, float d);
    static double detd (double a, double b, double c, double d);
    static Vector3 tmp;
    static Vector3 best;
    static Vector3 tmp1;
    static Vector3 tmp2;
    static Vector3 tmp3;

private:
    static Vector3 v0;
    static Vector3 v1;
    static Vector3 v2;
    static Plane p;
    static Vector3 i;
    static Vector3 dir;
    static Vector3 start;
};

} // namespace gdx

#endif // GDX_CPP_MATH_INTERSECTOR_HPP_
