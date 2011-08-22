
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

#include "Frustum.hpp"

using namespace gdx_cpp::math;

void Frustum::update (const Matrix4& inverseProjectionView) {
    System.arraycopy(clipSpacePlanePointsArray, 0, planePointsArray, 0, clipSpacePlanePointsArray.length);
    Matrix4.prj(inverseProjectionView.val, planePointsArray, 0, 8, 3);
    for (int i = 0, j = 0; i < 8; i++) {
        Vector3 v = planePoints[i];
        v.x = planePointsArray[j++];
        v.y = planePointsArray[j++];
        v.z = planePointsArray[j++];
    }

    planes[0].set(planePoints[1], planePoints[0], planePoints[2]);
    planes[1].set(planePoints[4], planePoints[5], planePoints[7]);
    planes[2].set(planePoints[0], planePoints[4], planePoints[3]);
    planes[3].set(planePoints[5], planePoints[1], planePoints[6]);
    planes[4].set(planePoints[2], planePoints[3], planePoints[6]);
    planes[5].set(planePoints[4], planePoints[0], planePoints[1]);
}

bool Frustum::pointInFrustum (const Vector3& point) {
    for (int i = 0; i < planes.length; i++) {
        PlaneSide result = planes[i].testPoint(point);
        if (result == PlaneSide.Back) return false;
    }

    return true;
}

bool Frustum::sphereInFrustum (const Vector3& center,float radius) {
    for (int i = 0; i < planes.length; i++)
        if (planes[i].distance(center) < -radius) return false;

    return true;
}

bool Frustum::sphereInFrustumWithoutNearFar (const Vector3& center,float radius) {
    for (int i = 0; i < planes.length; i++)
        if (planes[i].distance(center) < -radius) return false;

    return true;
}

bool Frustum::boundsInFrustum (const gdx_cpp::math::collision::BoundingBox& bounds) {
    Vector3[] corners = bounds.getCorners();
    int len = corners.length;

    for (int i = 0, len2 = planes.length; i < len2; i++) {
        int out = 0;

        for (int j = 0; j < len; j++)
            if (planes[i].testPoint(corners[j]) == PlaneSide.Back) out++;

        if (out == 8) return false;
    }

    return true;
}

Ray& Frustum::calculatePickRay (float screen_width,float screen_height,float mouse_x,float mouse_y,const Vector3& pos,const Vector3& dir,const Vector3& up) {
// float n_x = mouse_x - screen_width / 2.0f;
// float n_y = mouse_y - screen_height / 2.0f;
// n_x /= screen_width / 2.0f;
// n_y /= screen_height / 2.0f;
//
// Z.set(dir.tmp().mul(-1)).nor();
// X.set(up.tmp().crs(Z)).nor();
// Y.set(Z.tmp().crs(X)).nor();
// near_center.set(pos.tmp3().sub(Z.tmp2().mul(near)));
// Vector3 near_point = X.tmp3().mul(near_width).mul(n_x).add(Y.tmp2().mul(near_height).mul(n_y));
// near_point.add(near_center);
//
// return ray.set(near_point.tmp(), near_point.sub(pos).nor());
// }

    void Frustum::main () {
// PerspectiveCamera camera = new PerspectiveCamera(45, 2, 2);
// // camera.rotate(90, 0, 1, 0);
// camera.update();
// System.out.println(camera.direction);
// System.out.println(Arrays.toString(camera.frustum.planes));
//
// OrthographicCamera camOrtho = new OrthographicCamera(2, 2);
// camOrtho.near = 1;
// // camOrtho.rotate(90, 1, 0, 0);
// camOrtho.update();
// System.out.println(camOrtho.direction);
// System.out.println(Arrays.toString(camOrtho.frustum.planes));
// }

