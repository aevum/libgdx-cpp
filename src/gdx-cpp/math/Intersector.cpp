
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

#include <math.h>
#include <stddef.h>
#include <cassert>
#include <limits>
#include <vector>

#include "Circle.hpp"
#include "Intersector.hpp"
#include "Plane.hpp"
#include "Rectangle.hpp"
#include "Vector2.hpp"
#include "Vector3.hpp"
#include "collision/BoundingBox.hpp"
#include "collision/Ray.hpp"
#include "gdx-cpp/Gdx.hpp"



using namespace gdx;


Vector3 Intersector::v0;
Vector3 Intersector::v1;
Vector3 Intersector::v2;
Vector3 Intersector::tmp;
Vector3 Intersector::tmp1;
Vector3 Intersector::tmp2;
Vector3 Intersector::tmp3;
Vector3 Intersector::best;
Plane Intersector::p = Plane(Vector3(), 0);
Vector3 Intersector::i;
Vector3 Intersector::dir;
Vector3 Intersector::start;

float Intersector::getLowestPositiveRoot (float a,float b,float c) {
    float det = b * b - 4 * a * c;
    if (det < 0) return std::numeric_limits<float>::quiet_NaN();

    float sqrtD = (float)sqrt(det);
    float invA = 1 / (2 * a);
    float r1 = (-b - sqrtD) * invA;
    float r2 = (-b + sqrtD) * invA;

    if (r1 > r2) {
        float tmp = r2;
        r2 = r1;
        r1 = tmp;
    }

    if (r1 > 0) return r1;

    if (r2 > 0) return r2;

    return std::numeric_limits<float>::quiet_NaN();
}

bool Intersector::isPointInTriangle (const Vector3& point, const Vector3& t1, const Vector3& t2, const Vector3& t3) {
    v0.set(t1).sub(point);
    v1.set(t2).sub(point);
    v2.set(t3).sub(point);

    float ab = v0.dot(v1);
    float ac = v0.dot(v2);
    float bc = v1.dot(v2);
    float cc = v2.dot(v2);

    if (bc * ac - cc * ab < 0) return false;
    float bb = v1.dot(v1);
    if (ab * bc - ac * bb < 0) return false;
    return true;
}

bool Intersector::intersectSegmentPlane (const Vector3& start,const Vector3& end, Plane& plane, Vector3* intersection) {
    Vector3 dir = end.tmp().sub(start);
    float denom = dir.dot(plane.getNormal());
    float t = -(start.dot(plane.getNormal()) + plane.getD()) / denom;
    if (t < 0 || t > 1) return false;

    intersection->set(start).add(dir.mul(t));
    return true;
}

bool Intersector::isPointInPolygon (std::vector<Vector2>& polygon,const Vector2& point) {

    int j = polygon.size() - 1;
    bool oddNodes = false;
    for (unsigned int i = 0; i < polygon.size(); i++) {
        if ((polygon.at(i).y < point.y && polygon.at(j).y >= point.y)
                || (polygon.at(j).y < point.y && polygon.at(i).y >= point.y)) {
            if (polygon.at(i).x + (point.y - polygon.at(i).y) / (polygon.at(j).y - polygon.at(i).y)
                    * (polygon.at(j).x - polygon.at(i).x) < point.x) {
                oddNodes = !oddNodes;
            }
        }
        j = i;
    }

    return oddNodes;
}

float Intersector::distanceLinePoint (const Vector2& start,const Vector2& end,const Vector2& point) {
    tmp.set(end.x, end.y, 0).sub(start.x, start.y, 0);
    float l = tmp.len();
    tmp2.set(start.x, start.y, 0).sub(point.x, point.y, 0);
    return tmp.crs(tmp2).len() / l;
}

bool Intersector::intersectSegmentCircle (const Vector2& start,const Vector2& end,const Vector2& center,float squareRadius) {
    tmp.set(end.x - start.x, end.y - start.y, 0);
    tmp1.set(center.x - start.x, center.y - start.y, 0);
    float l = tmp.len();
    float u = tmp1.dot(tmp.nor());
    if (u <= 0) {
        tmp2.set(start.x, start.y, 0);
    } else if (u >= l) {
        tmp2.set(end.x, end.y, 0);
    } else {
        tmp3.set(tmp.mul(u)); // remember tmp is already normalized
        tmp2.set(tmp3.x + start.x, tmp3.y + start.y, 0);
    }

    float x = center.x - tmp2.x;
    float y = center.y - tmp2.y;

    return x * x + y * y <= squareRadius;
}

float Intersector::intersectSegmentCircleDisplace (const Vector2& start,const Vector2& end,const Vector2& point,float radius, Vector2& displacement) {
    float u = (point.x - start.x) * (end.x - start.x) + (point.y - start.y) * (end.y - start.y);
    float d = start.dst(end);
    u /= (d * d);
    if (u < 0 || u > 1) return std::numeric_limits<float>::infinity();
    tmp.set(end.x, end.y, 0).sub(start.x, start.y, 0);
    tmp2.set(start.x, start.y, 0).add(tmp.mul(u));
    d = tmp2.dst(point.x, point.y, 0);
    if (d < radius) {
        displacement.set(point).sub(tmp2.x, tmp2.y).nor();
        return d;
    } else
        return std::numeric_limits<float>::infinity();
}

bool Intersector::intersectRayPlane (const Ray& ray, Plane& plane, Vector3* intersection) {
    float denom = ray.direction.dot(plane.getNormal());
    if (denom != 0) {
        float t = -(ray.origin.dot(plane.getNormal()) + plane.getD()) / denom;
        if (t < 0) return false;

        if (intersection != nullptr) intersection->set(ray.origin).add(ray.direction.tmp().mul(t));
        return true;
    } else if (plane.testPoint(ray.origin) == Plane::PlaneSide_OnPlane) {
        if (intersection != nullptr) intersection->set(ray.origin);
        return true;
    } else
        return false;
}

bool Intersector::intersectRayTriangle (const Ray& ray,const Vector3& t1,const Vector3& t2,const Vector3& t3, Vector3* intersection) {
    p.set(t1, t2, t3);
    if (!intersectRayPlane(ray, p, &i)) return false;

    v0.set(t3).sub(t1);
    v1.set(t2).sub(t1);
    v2.set(i).sub(t1);

    float dot00 = v0.dot(v0);
    float dot01 = v0.dot(v1);
    float dot02 = v0.dot(v2);
    float dot11 = v1.dot(v1);
    float dot12 = v1.dot(v2);

    float denom = dot00 * dot11 - dot01 * dot01;
    if (denom == 0) return false;

    float u = (dot11 * dot02 - dot01 * dot12) / denom;
    float v = (dot00 * dot12 - dot01 * dot02) / denom;

    if (u >= 0 && v >= 0 && u + v <= 1) {
        if (intersection != nullptr) intersection->set(i);
        return true;
    } else {
        return false;
    }

}

bool Intersector::intersectRaySphere (const Ray& ray,const Vector3& center,float radius, Vector3* intersection) {
    dir.set(ray.direction).nor();
    start.set(ray.origin);
    float b = 2 * (dir.dot(start.tmp().sub(center)));
    float c = start.dst2(center) - radius * radius;
    float disc = b * b - 4 * c;
    if (disc < 0) return false;

    // compute q as described above
    float distSqrt = (float)sqrt(disc);
    float q;
    if (b < 0)
        q = (-b - distSqrt) / 2.0f;
    else
        q = (-b + distSqrt) / 2.0f;

    // compute t0 and t1
    float t0 = q / 1;
    float t1 = c / q;

    // make sure t0 is smaller than t1
    if (t0 > t1) {
        // if t0 is bigger than t1 swap them around
        float temp = t0;
        t0 = t1;
        t1 = temp;
    }

    // if t1 is less than zero, the object is in the ray's negative
    // direction
    // and consequently the ray misses the sphere
    if (t1 < 0) return false;

    // if t0 is less than zero, the intersection point is at t1
    if (t0 < 0) {
        if (intersection != nullptr) intersection->set(start).add(dir.tmp().mul(t1));
        return true;
    }
    // else the intersection point is at t0
    else {
        if (intersection != nullptr) intersection->set(start).add(dir.tmp().mul(t0));
        return true;
    }
}

bool Intersector::intersectRayBoundsFast (const Ray& ray, const BoundingBox& box) {
    float a, b;
    float min, max;
    float divX = 1 / ray.direction.x;
    float divY = 1 / ray.direction.y;
    float divZ = 1 / ray.direction.z;

    a = (box.min.x - ray.origin.x) * divX;
    b = (box.max.x - ray.origin.x) * divX;
    if (a < b) {
        min = a;
        max = b;
    } else {
        min = b;
        max = a;
    }

    a = (box.min.y - ray.origin.y) * divY;
    b = (box.max.y - ray.origin.y) * divY;
    if (a > b) {
        float t = a;
        a = b;
        b = t;
    }

    if (a > min) min = a;
    if (b < max) max = b;

    a = (box.min.z - ray.origin.z) * divZ;
    b = (box.max.z - ray.origin.z) * divZ;
    if (a > b) {
        float t = a;
        a = b;
        b = t;
    }

    if (a > min) min = a;
    if (b < max) max = b;

    return (max >= 0) && (max >= min);
}

bool Intersector::intersectRayTriangles (const Ray& ray, const std::vector<float>& triangles, Vector3* intersection) {
    float min_dist = std::numeric_limits<float>::max();
    bool hit = false;

    if ((triangles.size() / 3) % 3 != 0)
    {
      gdx_log_error("GDX-CPP Intersector.cpp","triangle list size is not a multiple of 3");
      assert(false);
    }

    for (unsigned int i = 0; i < triangles.size() - 6; i += 9) {
        bool result = intersectRayTriangle(ray, tmp1.set(triangles[i], triangles[i + 1], triangles[i + 2]),
                                              tmp2.set(triangles[i + 3], triangles[i + 4], triangles[i + 5]),
                                              tmp3.set(triangles[i + 6], triangles[i + 7], triangles[i + 8]), &tmp);

        if (result == true) {
            float dist = ray.origin.tmp().sub(tmp).len();
            if (dist < min_dist) {
                min_dist = dist;
                best.set(tmp);
                hit = true;
            }
        }
    }

    if (hit == false)
        return false;
    else {
        if (intersection != nullptr) intersection->set(best);
        return true;
    }
}

bool Intersector::intersectRayTriangles (const Ray& ray, const std::vector<float>& vertices, const std::vector<short>& indices, int vertexSize, Vector3* intersection) {
    float min_dist = std::numeric_limits<float>::max();
    bool hit = false;

    if ((indices.size() % 3) != 0)
    {
      gdx_log_error("GDX-CPP Intersector.cpp", "triangle list size is not a multiple of 3");
      assert(false);
    } 

    for (unsigned int i = 0; i < indices.size(); i += 3) {
        int i1 = indices[i] * vertexSize;
        int i2 = indices[i + 1] * vertexSize;
        int i3 = indices[i + 2] * vertexSize;

        bool result = intersectRayTriangle(ray, tmp1.set(vertices[i1], vertices[i1 + 1], vertices[i1 + 2]),
                                              tmp2.set(vertices[i2], vertices[i2 + 1], vertices[i2 + 2]),
                                              tmp3.set(vertices[i3], vertices[i3 + 1], vertices[i3 + 2]), &tmp);

        if (result == true) {
            float dist = ray.origin.tmp().sub(tmp).len();
            if (dist < min_dist) {
                min_dist = dist;
                best.set(tmp);
                hit = true;
            }
        }
    }

    if (hit == false)
        return false;
    else {
        if (intersection != nullptr) intersection->set(best);
        return true;
    }
}

bool Intersector::intersectRayTriangles (const Ray& ray, const std::vector<Vector3>& triangles, Vector3* intersection) {
    float min_dist = std::numeric_limits<float>::max();

    if (triangles.size() % 3 != 0)
    {
      gdx_log_error("GDX-CPP Intersector.cpp", "triangle list size is not a multiple of 3");
      assert(false);
    } 

    for (unsigned int i = 0; i < triangles.size() - 2; i += 3) {
        bool result = intersectRayTriangle(ray, triangles.at(i), triangles.at(i + 1), triangles.at(i + 2), &tmp);

        if (result == true) {
            float dist = ray.origin.tmp().sub(tmp).len();
            if (dist < min_dist) {
                min_dist = dist;
                best.set(tmp);
            }
        }
    }

    if (best == nullptr)
        return false;
    else {
        if (intersection != nullptr) intersection->set(best);
        return true;
    }
}

bool Intersector::intersectRectangles (const Rectangle& a,const Rectangle& b) {
    return !(a.getX() > b.getX() + b.getWidth() || a.getX() + a.getWidth() < b.getX() || a.getY() > b.getY() + b.getHeight() || a
             .getY() + a.getHeight() < b.getY());
}

bool Intersector::intersectLines (const Vector2& p1, const Vector2& p2, const Vector2& p3, const Vector2& p4, Vector2& intersection) {
    float x1 = p1.x, y1 = p1.y, x2 = p2.x, y2 = p2.y, x3 = p3.x, y3 = p3.y, x4 = p4.x, y4 = p4.y;

    float det1 = det(x1, y1, x2, y2);
    float det2 = det(x3, y3, x4, y4);
    float det3 = det(x1 - x2, y1 - y2, x3 - x4, y3 - y4);

    float x = det(det1, x1 - x2, det2, x3 - x4) / det3;
    float y = det(det1, y1 - y2, det2, y3 - y4) / det3;

    intersection.x = x;
    intersection.y = y;

    return true;
}

bool Intersector::intersectSegments (const Vector2& p1,const Vector2& p2,const Vector2& p3,const Vector2& p4, Vector2* intersection) {
    float x1 = p1.x, y1 = p1.y, x2 = p2.x, y2 = p2.y, x3 = p3.x, y3 = p3.y, x4 = p4.x, y4 = p4.y;

    float d = (y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1);
    if (d == 0) return false;

    float ua = ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / d;
    float ub = ((x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3)) / d;

    if (ua < 0 || ua > 1) return false;
    if (ub < 0 || ub > 1) return false;

    if (intersection != nullptr) intersection->set(x1 + (x2 - x1) * ua, y1 + (y2 - y1) * ua);
    return true;
}

bool Intersector::overlapCircles (const Circle& c1,const Circle& c2) {
    float x = c1.x - c2.x;
    float y = c1.y - c2.y;
    float distance = x * x + y * y;
    float radiusSum = c1.radius + c2.radius;
    return distance <= radiusSum * radiusSum;
}

float Intersector::det (float a, float b, float c, float d) {
    return a * d - b * c;
}

double Intersector::detd (double a, double b, double c, double d) {
    return a * d - b * c;
}

bool Intersector::overlapRectangles (const Rectangle& r1,const Rectangle& r2) {
    if (r1.x < r2.x + r2.width && r1.x + r1.width > r2.x && r1.y < r2.y + r2.height && r1.y + r1.height > r2.y)
        return true;
    else
        return false;
}

bool Intersector::overlapCircleRectangle (const Circle& c,const Rectangle& r) {
    float closestX = c.x;
    float closestY = c.y;

    if (c.x < r.x) {
        closestX = r.x;
    } else if (c.x > r.x + r.width) {
        closestX = r.x + r.width;
    }

    if (c.y < r.y) {
        closestY = r.y;
    } else if (c.y > r.y + r.height) {
        closestY = r.y + r.height;
    }

    closestX = closestX - c.x;
    closestX *= closestX;
    closestY = closestY - c.y;
    closestY *= closestY;

    return closestX + closestY < c.radius * c.radius;
}

