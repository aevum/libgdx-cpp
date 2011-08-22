
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

#include "Vector3.hpp"
#include "Plane.hpp"
#include <vector>



namespace gdx_cpp {
namespace math {
namespace collision {
  class Ray;
  class BoundingBox;
}
class Circle;
class Rectangle;
class BoundingBox;
class Vector2;


class Intersector {
public:

    static float getLowestPositiveRoot (float a,float b,float c);
    static bool isPointInTriangle (const Vector3& point,const Vector3& t1,const Vector3& t2,const Vector3& t3);
    static bool intersectSegmentPlane (const gdx_cpp::math::Vector3& start, const gdx_cpp::math::Vector3& end, gdx_cpp::math::Plane& plane, gdx_cpp::math::Vector3* intersection);
    static bool isPointInPolygon (std::vector<Vector2>& polygon,const Vector2& point);
    static float distanceLinePoint (const Vector2& start,const Vector2& end,const Vector2& point);
    static bool intersectSegmentCircle (const Vector2& start,const Vector2& end,const Vector2& center,float squareRadius);
    static float intersectSegmentCircleDisplace (const gdx_cpp::math::Vector2& start, const gdx_cpp::math::Vector2& end, const gdx_cpp::math::Vector2& point, float radius, gdx_cpp::math::Vector2& displacement);
    static bool intersectRayPlane (const gdx_cpp::math::collision::Ray& ray, gdx_cpp::math::Plane& plane, gdx_cpp::math::Vector3* intersection);
    static bool intersectRayTriangle (const gdx_cpp::math::collision::Ray& ray, const gdx_cpp::math::Vector3& t1, const gdx_cpp::math::Vector3& t2, const gdx_cpp::math::Vector3& t3, gdx_cpp::math::Vector3* intersection);
    static bool intersectRaySphere (const gdx_cpp::math::collision::Ray& ray, const gdx_cpp::math::Vector3& center, float radius, gdx_cpp::math::Vector3* intersection);
    static bool intersectRayBoundsFast (const gdx_cpp::math::collision::Ray& ray,const gdx_cpp::math::collision::BoundingBox& box);
    static bool intersectRayTriangles (const gdx_cpp::math::collision::Ray& ray, const std::vector< float, std::allocator< float > >& triangles, gdx_cpp::math::Vector3* intersection);
    static bool intersectRayTriangles (const gdx_cpp::math::collision::Ray& ray, const std::vector< float, std::allocator< float > >& vertices, const std::vector< short int, std::allocator< short int > >& indices, int vertexSize, gdx_cpp::math::Vector3* intersection);
    static bool intersectRayTriangles (const gdx_cpp::math::collision::Ray& ray,std::vector<Vector3>& triangles, Vector3* intersection);
    static bool intersectRectangles (const Rectangle& a,const Rectangle& b);
    static bool intersectLines (const Vector2& p1,const Vector2& p2,const Vector2& p3,const Vector2& p4, Vector2& intersection);
    static bool intersectSegments (const gdx_cpp::math::Vector2& p1, const gdx_cpp::math::Vector2& p2, const gdx_cpp::math::Vector2& p3, const gdx_cpp::math::Vector2& p4, gdx_cpp::math::Vector2& intersection);
    static bool overlapCircles (const Circle& c1,const Circle& c2);
    static bool overlapRectangles (const Rectangle& r1,const Rectangle& r2);
    static bool overlapCircleRectangle (const Circle& c,const Rectangle& r);

protected:
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

} // namespace gdx_cpp
} // namespace math

#endif // GDX_CPP_MATH_INTERSECTOR_HPP_
