
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

#include <string.h>
#include <vector>

#include "Frustum.hpp"
#include "Matrix4.hpp"
#include "Vector3.hpp"
#include "collision/BoundingBox.hpp"
#include "gdx-cpp/math/Plane.hpp"

using namespace gdx;


Vector3 Frustum::clipSpacePlanePoints[] = { Vector3(-1, -1, -1), Vector3(1, -1, -1),
        Vector3(1, 1, -1), Vector3(-1, 1, -1), // near clip
        Vector3(-1, -1, 1), Vector3(1, -1, 1), Vector3(1, 1, 1), Vector3(-1, 1, 1)}; // far clip

float Frustum::clipSpacePlanePointsArray[8 * 3];

Frustum::Frustum()
{
    for (auto & elem : planes) {
        elem = new Plane(Vector3(), 0);
    }
}

Frustum::~Frustum()
{
  for (auto & elem : planes) {
    delete elem;
  }
}

void Frustum::update (const Matrix4& inverseProjectionView) {
    memcpy(planePointsArray, clipSpacePlanePointsArray, 24 );

    Matrix4::prj(inverseProjectionView.val, planePointsArray, 0, 8, 3);
    for (int i = 0, j = 0; i < 8; i++) {
        Vector3& v = planePoints[i];
        v.x = planePointsArray[j++];
        v.y = planePointsArray[j++];
        v.z = planePointsArray[j++];
    }

    planes[0]->set(planePoints[1], planePoints[0], planePoints[2]);
    planes[1]->set(planePoints[4], planePoints[5], planePoints[7]);
    planes[2]->set(planePoints[0], planePoints[4], planePoints[3]);
    planes[3]->set(planePoints[5], planePoints[1], planePoints[6]);
    planes[4]->set(planePoints[2], planePoints[3], planePoints[6]);
    planes[5]->set(planePoints[4], planePoints[0], planePoints[1]);
}

bool Frustum::pointInFrustum (const Vector3& point) {
    for (auto & elem : planes) {
        Plane::PlaneSide result = elem->testPoint(point);
        if (result == Plane::PlaneSide_Back) return false;
    }

    return true;
}

bool Frustum::sphereInFrustum (const Vector3& center,float radius) {
    for (auto & elem : planes)
        if (elem->distance(center) < -radius) return false;

    return true;
}

bool Frustum::sphereInFrustumWithoutNearFar (const Vector3& center,float radius) {
    for (auto & elem : planes)
        if (elem->distance(center) < -radius) return false;

    return true;
}

bool Frustum::boundsInFrustum (BoundingBox& bounds) {
    const std::vector<Vector3>& corners = bounds.getCorners();
    int len = corners.size();

    for (int i = 0, len2 = 6; i < len2; i++) {
        int out = 0;

        for (int j = 0; j < len; j++)
          if (planes[i]->testPoint(corners[j]) == Plane::PlaneSide_Back) out++;

        if (out == 8) return false;
    }

    return true;
}
