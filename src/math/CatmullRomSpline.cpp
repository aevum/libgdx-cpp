
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

#include "CatmullRomSpline.hpp"

using namespace gdx_cpp::math;

void CatmullRomSpline::add (const Vector3& point) {
    controlPoints.add(point);
}

std::list<Vector3>& CatmullRomSpline::getControlPoints () {
    return controlPoints;
}

std::list<Vector3>& CatmullRomSpline::getPath (int numPoints) {
    ArrayList<Vector3> points = new ArrayList<Vector3>();

    if (controlPoints.size() < 4) return points;

    Vector3 T1 = new Vector3();
    Vector3 T2 = new Vector3();

    for (int i = 1; i <= controlPoints.size() - 3; i++) {
        points.add(controlPoints.get(i));
        float increment = 1.0f / (numPoints + 1);
        float t = increment;

        T1.set(controlPoints.get(i + 1)).sub(controlPoints.get(i - 1)).mul(0.5f);
        T2.set(controlPoints.get(i + 2)).sub(controlPoints.get(i)).mul(0.5f);

        for (int j = 0; j < numPoints; j++) {
            float h1 = 2 * t * t * t - 3 * t * t + 1; // calculate basis
            // function 1
            float h2 = -2 * t * t * t + 3 * t * t; // calculate basis
            // function 2
            float h3 = t * t * t - 2 * t * t + t; // calculate basis
            // function 3
            float h4 = t * t * t - t * t; // calculate basis function 4

            Vector3 point = new Vector3(controlPoints.get(i)).mul(h1);
            point.add(controlPoints.get(i + 1).tmp().mul(h2));
            point.add(T1.tmp().mul(h3));
            point.add(T2.tmp().mul(h4));
            points.add(point);
            t += increment;
        }
    }

    if (controlPoints.size() >= 4) points.add(controlPoints.get(controlPoints.size() - 2));

    return points;
}

void CatmullRomSpline::getPath (int numPoints) {
    int idx = 0;
    if (controlPoints.size() < 4) return;

    for (int i = 1; i <= controlPoints.size() - 3; i++) {
        points[idx++].set(controlPoints.get(i));
        float increment = 1.0f / (numPoints + 1);
        float t = increment;

        T1.set(controlPoints.get(i + 1)).sub(controlPoints.get(i - 1)).mul(0.5f);
        T2.set(controlPoints.get(i + 2)).sub(controlPoints.get(i)).mul(0.5f);

        for (int j = 0; j < numPoints; j++) {
            float h1 = 2 * t * t * t - 3 * t * t + 1; // calculate basis
            // function 1
            float h2 = -2 * t * t * t + 3 * t * t; // calculate basis
            // function 2
            float h3 = t * t * t - 2 * t * t + t; // calculate basis
            // function 3
            float h4 = t * t * t - t * t; // calculate basis function 4

            Vector3 point = points[idx++].set(controlPoints.get(i)).mul(h1);
            point.add(controlPoints.get(i + 1).tmp().mul(h2));
            point.add(T1.tmp().mul(h3));
            point.add(T2.tmp().mul(h4));
            t += increment;
        }
    }

    points[idx].set(controlPoints.get(controlPoints.size() - 2));
}

std::list<Vector3>& CatmullRomSpline::getTangents (int numPoints) {
    ArrayList<Vector3> tangents = new ArrayList<Vector3>();

    if (controlPoints.size() < 4) return tangents;

    Vector3 T1 = new Vector3();
    Vector3 T2 = new Vector3();

    for (int i = 1; i <= controlPoints.size() - 3; i++) {
        float increment = 1.0f / (numPoints + 1);
        float t = increment;

        T1.set(controlPoints.get(i + 1)).sub(controlPoints.get(i - 1)).mul(0.5f);
        T2.set(controlPoints.get(i + 2)).sub(controlPoints.get(i)).mul(0.5f);

        tangents.add(new Vector3(T1).nor());

        for (int j = 0; j < numPoints; j++) {
            float h1 = 6 * t * t - 6 * t; // calculate basis function 1
            float h2 = -6 * t * t + 6 * t; // calculate basis function 2
            float h3 = 3 * t * t - 4 * t + 1; // calculate basis function 3
            float h4 = 3 * t * t - 2 * t; // calculate basis function 4

            Vector3 point = new Vector3(controlPoints.get(i)).mul(h1);
            point.add(controlPoints.get(i + 1).tmp().mul(h2));
            point.add(T1.tmp().mul(h3));
            point.add(T2.tmp().mul(h4));
            tangents.add(point.nor());
            t += increment;
        }
    }

    if (controlPoints.size() >= 4)
        tangents.add(T1.set(controlPoints.get(controlPoints.size() - 1)).sub(controlPoints.get(controlPoints.size() - 3))
                     .mul(0.5f).cpy().nor());

    return tangents;
}

std::list<Vector3>& CatmullRomSpline::getTangentNormals2D (int numPoints) {
    ArrayList<Vector3> tangents = new ArrayList<Vector3>();

    if (controlPoints.size() < 4) return tangents;

    Vector3 T1 = new Vector3();
    Vector3 T2 = new Vector3();

    for (int i = 1; i <= controlPoints.size() - 3; i++) {
        float increment = 1.0f / (numPoints + 1);
        float t = increment;

        T1.set(controlPoints.get(i + 1)).sub(controlPoints.get(i - 1)).mul(0.5f);
        T2.set(controlPoints.get(i + 2)).sub(controlPoints.get(i)).mul(0.5f);

        Vector3 normal = new Vector3(T1).nor();
        float x = normal.x;
        normal.x = normal.y;
        normal.y = -x;
        tangents.add(normal);

        for (int j = 0; j < numPoints; j++) {
            float h1 = 6 * t * t - 6 * t; // calculate basis function 1
            float h2 = -6 * t * t + 6 * t; // calculate basis function 2
            float h3 = 3 * t * t - 4 * t + 1; // calculate basis function 3
            float h4 = 3 * t * t - 2 * t; // calculate basis function 4

            Vector3 point = new Vector3(controlPoints.get(i)).mul(h1);
            point.add(controlPoints.get(i + 1).tmp().mul(h2));
            point.add(T1.tmp().mul(h3));
            point.add(T2.tmp().mul(h4));
            point.nor();
            x = point.x;
            point.x = point.y;
            point.y = -x;
            tangents.add(point);
            t += increment;
        }
    }

    return tangents;
}

std::list<Vector3>& CatmullRomSpline::getTangentNormals (int numPoints,const Vector3& up) {
    List<Vector3> tangents = getTangents(numPoints);
    ArrayList<Vector3> normals = new ArrayList<Vector3>();

for (Vector3 tangent : tangents)
        normals.add(new Vector3(tangent).crs(up).nor());

    return normals;
}

std::list<Vector3>& CatmullRomSpline::getTangentNormals (int numPoints,std::list<Vector3>& up) {
    List<Vector3> tangents = getTangents(numPoints);
    ArrayList<Vector3> normals = new ArrayList<Vector3>();

    int i = 0;
for (Vector3 tangent : tangents)
        normals.add(new Vector3(tangent).crs(up.get(i++)).nor());

    return normals;
}

