
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

#include <memory>

#include "CatmullRomSpline.hpp"
#include "gdx-cpp/math/Vector3.hpp"

using namespace gdx;

CatmullRomSpline::CatmullRomSpline()
{
}

void CatmullRomSpline::add (const Vector3& point) {
    controlPoints.push_back(point);
}

std::vector<Vector3>& CatmullRomSpline::getControlPoints () {
    return controlPoints;
}

CatmullRomSpline::vector3_vector_ptr CatmullRomSpline::getPath (int numPoints) {
    vector3_vector_ptr points = vector3_vector_ptr (new std::vector<Vector3>());

    if (controlPoints.size() < 4) return points;

    Vector3 T1;
    Vector3 T2;

    for (unsigned int i = 1; i <= controlPoints.size() - 3; i++) {
        points->push_back(controlPoints[i]);
        float increment = 1.0f / (numPoints + 1);
        float t = increment;

        T1.set(controlPoints[i + 1].sub(controlPoints[i - 1])).mul(0.5f);
        T2.set(controlPoints[i + 2].sub(controlPoints[i])).mul(0.5f);

        for (int j = 0; j < numPoints; j++) {
            float h1 = 2 * t * t * t - 3 * t * t + 1; // calculate basis
            // function 1
            float h2 = -2 * t * t * t + 3 * t * t; // calculate basis
            // function 2
            float h3 = t * t * t - 2 * t * t + t; // calculate basis
            // function 3
            float h4 = t * t * t - t * t; // calculate basis function 4

            Vector3 point(controlPoints[i]);
            point.mul(h1);
            point.add(controlPoints[i + 1].tmp().mul(h2));
            point.add(T1.tmp().mul(h3));
            point.add(T2.tmp().mul(h4));
            points->push_back(point);
            t += increment;
        }
    }

    if (controlPoints.size() >= 4) points->push_back(controlPoints[controlPoints.size() - 2]);

    return points;
}

void CatmullRomSpline::getPath (std::vector<Vector3>& points, int numPoints) {
    int idx = 0;
    if (controlPoints.size() < 4) return;

    for (unsigned int i = 1; i <= controlPoints.size() - 3; i++) {
        points[idx++] = controlPoints[i];
        float increment = 1.0f / (numPoints + 1);
        float t = increment;

        T1.set(controlPoints[i + 1]).sub(controlPoints[i - 1]).mul(0.5f);
        T2.set(controlPoints[i + 2]).sub(controlPoints[i]).mul(0.5f);

        for (int j = 0; j < numPoints; j++) {
            float h1 = 2 * t * t * t - 3 * t * t + 1; // calculate basis
            // function 1
            float h2 = -2 * t * t * t + 3 * t * t; // calculate basis
            // function 2
            float h3 = t * t * t - 2 * t * t + t; // calculate basis
            // function 3
            float h4 = t * t * t - t * t; // calculate basis function 4

            Vector3 point = points[idx++].set(controlPoints[i]).mul(h1);
            point.add(controlPoints[i + 1].tmp().mul(h2));
            point.add(T1.tmp().mul(h3));
            point.add(T2.tmp().mul(h4));
            t += increment;
        }
    }

    points[idx].set(controlPoints[controlPoints.size() - 2]);
}

CatmullRomSpline::vector3_vector_ptr CatmullRomSpline::getTangents (int numPoints) {
    vector3_vector_ptr tangents = vector3_vector_ptr(new std::vector<Vector3>());

    if (controlPoints.size() < 4) return tangents;

    Vector3 T1;
    Vector3 T2;

    for (unsigned int i = 1; i <= controlPoints.size() - 3; i++) {
        float increment = 1.0f / (numPoints + 1);
        float t = increment;

        T1.set(controlPoints[i + 1]).sub(controlPoints[i - 1]).mul(0.5f);
        T2.set(controlPoints[i + 2]).sub(controlPoints[i]).mul(0.5f);

        tangents->push_back(Vector3(T1).nor());

        for (int j = 0; j < numPoints; j++) {
            float h1 = 6 * t * t - 6 * t; // calculate basis function 1
            float h2 = -6 * t * t + 6 * t; // calculate basis function 2
            float h3 = 3 * t * t - 4 * t + 1; // calculate basis function 3
            float h4 = 3 * t * t - 2 * t; // calculate basis function 4

            Vector3 point(controlPoints[i]);
            point.mul(h1);
            point.add(controlPoints[i + 1].tmp().mul(h2));
            point.add(T1.tmp().mul(h3));
            point.add(T2.tmp().mul(h4));
            tangents->push_back(point.nor());
            t += increment;
        }
    }

    if (controlPoints.size() >= 4)
        tangents->push_back(T1.set(controlPoints[controlPoints.size() - 1]).sub(controlPoints[controlPoints.size() - 3])
                            .mul(0.5f).cpy().nor());

    return tangents;
}

CatmullRomSpline::vector3_vector_ptr CatmullRomSpline::getTangentNormals2D (int numPoints) {
    vector3_vector_ptr tangents = vector3_vector_ptr(new std::vector<Vector3>());

    if (controlPoints.size() < 4) return tangents;

    Vector3 T1;
    Vector3 T2;

    for (unsigned int i = 1; i <= controlPoints.size() - 3; i++) {
        float increment = 1.0f / (numPoints + 1);
        float t = increment;

        T1.set(controlPoints[i + 1]).sub(controlPoints[i - 1]).mul(0.5f);
        T2.set(controlPoints[i + 2]).sub(controlPoints[i]).mul(0.5f);

        Vector3 normal = Vector3(T1).nor();
        float x = normal.x;
        normal.x = normal.y;
        normal.y = -x;
        tangents->push_back(normal);

        for (int j = 0; j < numPoints; j++) {
            float h1 = 6 * t * t - 6 * t; // calculate basis function 1
            float h2 = -6 * t * t + 6 * t; // calculate basis function 2
            float h3 = 3 * t * t - 4 * t + 1; // calculate basis function 3
            float h4 = 3 * t * t - 2 * t; // calculate basis function 4

            Vector3 point(controlPoints[i]);
            point.mul(h1);
            point.add(controlPoints[i + 1].tmp().mul(h2));
            point.add(T1.tmp().mul(h3));
            point.add(T2.tmp().mul(h4));
            point.nor();
            x = point.x;
            point.x = point.y;
            point.y = -x;
            tangents->push_back(point);
            t += increment;
        }
    }

    return tangents;
}

CatmullRomSpline::vector3_vector_ptr CatmullRomSpline::getTangentNormals (int numPoints,const Vector3& up) {
    vector3_vector_ptr tangents = getTangents(numPoints);
    vector3_vector_ptr normals = vector3_vector_ptr(new std::vector<Vector3>());

    auto it = tangents->begin();
    auto end = tangents->end();

    for (;it != end; ++it)
        normals->push_back(it->crs(up).nor());

    return normals;
}

CatmullRomSpline::vector3_vector_ptr CatmullRomSpline::getTangentNormals (int numPoints, std::vector<Vector3>& up) {
    vector3_vector_ptr tangents = getTangents(numPoints);
    vector3_vector_ptr normals = vector3_vector_ptr(new std::vector<Vector3>());

    auto it = tangents->begin();
    auto end = tangents->end();

    int i = 0;
    for (;it != end; ++it) {
        normals->push_back(it->crs(up[i++]).nor());
    }

    return normals;
}

