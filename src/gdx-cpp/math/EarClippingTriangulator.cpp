
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

#include <algorithm>

#include "EarClippingTriangulator.hpp"
#include "MathUtils.hpp"
#include "gdx-cpp/math/Vector2.hpp"

using namespace gdx;

#define CONCAVE 1
#define CONVEX - 1

EarClippingTriangulator::EarClippingTriangulator() : concaveVertexCount(0)
{
}

std::vector<Vector2> EarClippingTriangulator::computeTriangles (const std::vector<Vector2>& polygon) {
    std::vector<Vector2> triangles;
    std::vector<Vector2> vertices(polygon);

    /*
     * ESpitz: For the sake of performance, we only need to test for eartips while the polygon has more than three verts. If
     * there are only three verts left to test, or there were only three verts to begin with, there is no need to continue with
     * this loop.
     */
    while (vertices.size() > 3) {
        // TODO Usually(Always?) only the Types of the vertices next to the
        // ear change! --> Improve
        std::vector<int> vertexTypes = this->classifyVertices(vertices);

        int vertexCount = vertices.size();
        for (int index = 0; index < vertexCount; index++) {
            if (this->isEarTip(vertices, index, vertexTypes)) {
                this->cutEarTip(vertices, index, triangles);
                break;
            }
        }
    }

    /*
     * ESpitz: If there are only three verts left to test, or there were only three verts to begin with, we have the final
     * triangle.
     */
    if (vertices.size() == 3) {
        triangles.insert(triangles.end(), vertices.begin(), vertices.end());
    }

    return triangles;
}

bool EarClippingTriangulator::areVerticesClockwise (const std::vector<Vector2>& pVertices) {
    int vertexCount = pVertices.size();

    float area = 0;
    for (int i = 0; i < vertexCount; i++) {
        const Vector2& p1 = pVertices[i];
        const Vector2& p2 = pVertices[EarClippingTriangulator::computeNextIndex(pVertices, i)];
        area += p1.x * p2.y - p2.x * p1.y;
    }

    if (area < 0) {
        return true;
    } else {
        return false;
    }
}

std::vector<int> EarClippingTriangulator::classifyVertices (std::vector<Vector2>& pVertices) {
    int vertexCount = pVertices.size();

    std::vector<int> vertexTypes(vertexCount);
    this->concaveVertexCount = 0;

    /* Ensure vertices are in clockwise order. */
    if (!EarClippingTriangulator::areVerticesClockwise(pVertices)) {
      std::reverse(pVertices.begin(),pVertices.end());
    }

    for (int index = 0; index < vertexCount; index++) {
        int previousIndex = EarClippingTriangulator::computePreviousIndex(pVertices, index);
        int nextIndex = EarClippingTriangulator::computeNextIndex(pVertices, index);

        const Vector2& previousVertex = pVertices[previousIndex];
        const Vector2& currentVertex = pVertices[index];
        const Vector2& nextVertex = pVertices[nextIndex];

        if (EarClippingTriangulator::isTriangleConvex(previousVertex.x, previousVertex.y, currentVertex.x, currentVertex.y,
                nextVertex.x, nextVertex.y)) {
            vertexTypes[index] = CONVEX;
        } else {
            vertexTypes[index] = CONCAVE;
            this->concaveVertexCount++;
        }
    }

    return vertexTypes;
}

bool EarClippingTriangulator::isTriangleConvex (float pX1, float pY1, float pX2, float pY2, float pX3,
                                                float pY3) {
    if (EarClippingTriangulator::computeSpannedAreaSign(pX1, pY1, pX2, pY2, pX3, pY3) < 0) {
        return false;
    } else {
        return true;
    }
}

int EarClippingTriangulator::computeSpannedAreaSign (float pX1, float pY1, float pX2, float pY2,
                                                     float pX3, float pY3) {
    /*
     * Espitz: using doubles corrects for very rare cases where we run into floating point imprecision in the area test, causing
     * the method to return a 0 when it should have returned -1 or 1.
     */
    float area = 0;

    area += pX1 * (pY3 - pY2);
    area += pX2 * (pY1 - pY3);
    area += pX3 * (pY2 - pY1);

    return (int) signum(area);
}

bool EarClippingTriangulator::isAnyVertexInTriangle (std::vector<Vector2>& pVertices, const std::vector<int>& pVertexTypes, float pX1,
                                                     float pY1, float pX2, float pY2, float pX3, float pY3) {
    int i = 0;

    int vertexCount = pVertices.size();
    while (i < vertexCount - 1) {
        if ((pVertexTypes[i] == CONCAVE)) {
            Vector2& currentVertex = pVertices[i];

            float currentVertexX = currentVertex.x;
            float currentVertexY = currentVertex.y;

            int areaSign1 = EarClippingTriangulator::computeSpannedAreaSign(pX1, pY1, pX2, pY2, currentVertexX,
                                  currentVertexY);
            int areaSign2 = EarClippingTriangulator::computeSpannedAreaSign(pX2, pY2, pX3, pY3, currentVertexX,
                                  currentVertexY);
            int areaSign3 = EarClippingTriangulator::computeSpannedAreaSign(pX3, pY3, pX1, pY1, currentVertexX,
                                  currentVertexY);

            if (areaSign1 > 0 && areaSign2 > 0 && areaSign3 > 0) {
                return true;
            } else if (areaSign1 <= 0 && areaSign2 <= 0 && areaSign3 <= 0) {
                return true;
            }
        }
        i++;
    }
    return false;
}

bool EarClippingTriangulator::isEarTip (std::vector<Vector2>& pVertices, int pEarTipIndex, const std::vector<int>& pVertexTypes) {
    if (this->concaveVertexCount != 0) {
        Vector2& previousVertex = pVertices[EarClippingTriangulator::computePreviousIndex(pVertices, pEarTipIndex)];
        Vector2& currentVertex = pVertices[pEarTipIndex];
        Vector2& nextVertex = pVertices[EarClippingTriangulator::computeNextIndex(pVertices, pEarTipIndex)];

        if (EarClippingTriangulator::isAnyVertexInTriangle(pVertices, pVertexTypes, previousVertex.x, previousVertex.y,
                currentVertex.x, currentVertex.y, nextVertex.x, nextVertex.y)) {
            return false;
        } else {
            return true;
        }
    } else {
        return true;
    }
}

void EarClippingTriangulator::cutEarTip (std::vector<Vector2>& pVertices, int pEarTipIndex, std::vector<Vector2>& pTriangles) {
    int previousIndex = EarClippingTriangulator::computePreviousIndex(pVertices, pEarTipIndex);
    int nextIndex = EarClippingTriangulator::computeNextIndex(pVertices, pEarTipIndex);

    if (!EarClippingTriangulator::isCollinear(pVertices, previousIndex, pEarTipIndex, nextIndex)) {
        pTriangles.push_back(pVertices[previousIndex]);
        pTriangles.push_back(pVertices[pEarTipIndex]);
        pTriangles.push_back(pVertices[nextIndex]);
    }

    pVertices.erase(pVertices.begin() + pEarTipIndex);
    
    if (pVertices.size() >= 3) {
        EarClippingTriangulator::removeCollinearNeighborEarsAfterRemovingEarTip(pVertices, pEarTipIndex);
    }
}

void EarClippingTriangulator::removeCollinearNeighborEarsAfterRemovingEarTip (std::vector<Vector2>& pVertices,
                                                                              int pEarTipCutIndex) {
    int collinearityCheckNextIndex = pEarTipCutIndex % pVertices.size();
    int collinearCheckPreviousIndex = EarClippingTriangulator::computePreviousIndex(pVertices, collinearityCheckNextIndex);

    if (EarClippingTriangulator::isCollinear(pVertices, collinearityCheckNextIndex)) {
      pVertices.erase(pVertices.begin() + collinearityCheckNextIndex);

        if (pVertices.size() > 3) {
            /* Update */
            collinearCheckPreviousIndex = EarClippingTriangulator::computePreviousIndex(pVertices, collinearityCheckNextIndex);
            if (EarClippingTriangulator::isCollinear(pVertices, collinearCheckPreviousIndex)) {
              pVertices.erase(pVertices.begin() + collinearCheckPreviousIndex);
            }
        }
    } else if (EarClippingTriangulator::isCollinear(pVertices, collinearCheckPreviousIndex)) {
      pVertices.erase(pVertices.begin() + collinearCheckPreviousIndex);
    }
}

bool EarClippingTriangulator::isCollinear (const std::vector<Vector2>& pVertices, int pIndex) {
    int previousIndex = EarClippingTriangulator::computePreviousIndex(pVertices, pIndex);
    int nextIndex = EarClippingTriangulator::computeNextIndex(pVertices, pIndex);

    return EarClippingTriangulator::isCollinear(pVertices, previousIndex, pIndex, nextIndex);
}

bool EarClippingTriangulator::isCollinear (const std::vector<Vector2>& pVertices, int pPreviousIndex, int pIndex,
                                           int pNextIndex) {
    const Vector2& previousVertex = pVertices.at(pPreviousIndex);
    const Vector2& vertex = pVertices.at(pIndex);
    const Vector2& nextVertex = pVertices.at(pNextIndex);

    return EarClippingTriangulator::computeSpannedAreaSign(previousVertex.x, previousVertex.y, vertex.x, vertex.y, nextVertex.x,
            nextVertex.y) == 0;
}

int EarClippingTriangulator::computePreviousIndex (const std::vector<Vector2>& pVertices, int pIndex) {
    return pIndex == 0 ? pVertices.size() - 1 : pIndex - 1;
}

int EarClippingTriangulator::computeNextIndex (const std::vector<Vector2>& pVertices, int pIndex) {
    return pIndex == ((int)pVertices.size() - 1) ? 0 : pIndex + 1;
}

