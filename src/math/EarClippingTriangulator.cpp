
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

#include "EarClippingTriangulator.hpp"

using namespace gdx_cpp::math;

std::list<Vector2>& EarClippingTriangulator::computeTriangles (const final& List) {
    // TODO Check if LinkedList performs better
    final ArrayList<Vector2> triangles = new ArrayList<Vector2>();
    final ArrayList<Vector2> vertices = new ArrayList<Vector2>(polygon.size());
    vertices.addAll(polygon);

    /*
     * ESpitz: For the sake of performance, we only need to test for eartips while the polygon has more than three verts. If
     * there are only three verts left to test, or there were only three verts to begin with, there is no need to continue with
     * this loop.
     */
    while (vertices.size() > 3) {
        // TODO Usually(Always?) only the Types of the vertices next to the
        // ear change! --> Improve
        final int vertexTypes[] = this.classifyVertices(vertices);

        final int vertexCount = vertices.size();
        for (int index = 0; index < vertexCount; index++) {
            if (this.isEarTip(vertices, index, vertexTypes)) {
                this.cutEarTip(vertices, index, triangles);
                break;
            }
        }
    }

    /*
     * ESpitz: If there are only three verts left to test, or there were only three verts to begin with, we have the final
     * triangle.
     */
    if (vertices.size() == 3) {
        triangles.addAll(vertices);
    }

    return triangles;
}

bool EarClippingTriangulator::areVerticesClockwise (const final& ArrayList) {
    final int vertexCount = pVertices.size();

    float area = 0;
    for (int i = 0; i < vertexCount; i++) {
        final Vector2 p1 = pVertices.get(i);
        final Vector2 p2 = pVertices.get(EarClippingTriangulator.computeNextIndex(pVertices, i));
        area += p1.x * p2.y - p2.x * p1.y;
    }

    if (area < 0) {
        return true;
    } else {
        return false;
    }
}

int* EarClippingTriangulator::classifyVertices (const final& ArrayList) {
    final int vertexCount = pVertices.size();

    final int[] vertexTypes = new int[vertexCount];
    this.concaveVertexCount = 0;

    /* Ensure vertices are in clockwise order. */
    if (!EarClippingTriangulator.areVerticesClockwise(pVertices)) {
        Collections.reverse(pVertices);
    }

    for (int index = 0; index < vertexCount; index++) {
        final int previousIndex = EarClippingTriangulator.computePreviousIndex(pVertices, index);
        final int nextIndex = EarClippingTriangulator.computeNextIndex(pVertices, index);

        final Vector2 previousVertex = pVertices.get(previousIndex);
        final Vector2 currentVertex = pVertices.get(index);
        final Vector2 nextVertex = pVertices.get(nextIndex);

        if (EarClippingTriangulator.isTriangleConvex(previousVertex.x, previousVertex.y, currentVertex.x, currentVertex.y,
                nextVertex.x, nextVertex.y)) {
            vertexTypes[index] = CONVEX;
        } else {
            vertexTypes[index] = CONCAVE;
            this.concaveVertexCount++;
        }
    }

    return vertexTypes;
}

bool EarClippingTriangulator::isTriangleConvex (const final& float,const final& float,const final& float,const final& float,const final& float,const final& float) {
    if (EarClippingTriangulator.computeSpannedAreaSign(pX1, pY1, pX2, pY2, pX3, pY3) < 0) {
        return false;
    } else {
        return true;
    }
}

int EarClippingTriangulator::computeSpannedAreaSign (const final& float,const final& float,const final& float,const final& float,const final& float,const final& float) {
    /*
     * Espitz: using doubles corrects for very rare cases where we run into floating point imprecision in the area test, causing
     * the method to return a 0 when it should have returned -1 or 1.
     */
    double area = 0;

    area += (double)pX1 * (pY3 - pY2);
    area += (double)pX2 * (pY1 - pY3);
    area += (double)pX3 * (pY2 - pY1);

    return (int)Math.signum(area);
}

bool EarClippingTriangulator::isAnyVertexInTriangle (const final& ArrayList,const final& int,const final& float,const final& float,const final& float,const final& float,const final& float,const final& float) {
    int i = 0;

    final int vertexCount = pVertices.size();
    while (i < vertexCount - 1) {
        if ((pVertexTypes[i] == CONCAVE)) {
            final Vector2 currentVertex = pVertices.get(i);

            final float currentVertexX = currentVertex.x;
            final float currentVertexY = currentVertex.y;

            final int areaSign1 = EarClippingTriangulator.computeSpannedAreaSign(pX1, pY1, pX2, pY2, currentVertexX,
                                  currentVertexY);
            final int areaSign2 = EarClippingTriangulator.computeSpannedAreaSign(pX2, pY2, pX3, pY3, currentVertexX,
                                  currentVertexY);
            final int areaSign3 = EarClippingTriangulator.computeSpannedAreaSign(pX3, pY3, pX1, pY1, currentVertexX,
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

bool EarClippingTriangulator::isEarTip (const final& ArrayList,const final& int,const final& int) {
    if (this.concaveVertexCount != 0) {
        final Vector2 previousVertex = pVertices.get(EarClippingTriangulator.computePreviousIndex(pVertices, pEarTipIndex));
        final Vector2 currentVertex = pVertices.get(pEarTipIndex);
        final Vector2 nextVertex = pVertices.get(EarClippingTriangulator.computeNextIndex(pVertices, pEarTipIndex));

        if (EarClippingTriangulator.isAnyVertexInTriangle(pVertices, pVertexTypes, previousVertex.x, previousVertex.y,
                currentVertex.x, currentVertex.y, nextVertex.x, nextVertex.y)) {
            return false;
        } else {
            return true;
        }
    } else {
        return true;
    }
}

void EarClippingTriangulator::cutEarTip (const final& ArrayList,const final& int,const final& ArrayList) {
    final int previousIndex = EarClippingTriangulator.computePreviousIndex(pVertices, pEarTipIndex);
    final int nextIndex = EarClippingTriangulator.computeNextIndex(pVertices, pEarTipIndex);

    if (!EarClippingTriangulator.isCollinear(pVertices, previousIndex, pEarTipIndex, nextIndex)) {
        pTriangles.add(new Vector2(pVertices.get(previousIndex)));
        pTriangles.add(new Vector2(pVertices.get(pEarTipIndex)));
        pTriangles.add(new Vector2(pVertices.get(nextIndex)));
    }

    pVertices.remove(pEarTipIndex);
    if (pVertices.size() >= 3) {
        EarClippingTriangulator.removeCollinearNeighborEarsAfterRemovingEarTip(pVertices, pEarTipIndex);
    }
}

void EarClippingTriangulator::removeCollinearNeighborEarsAfterRemovingEarTip (const final& ArrayList,const final& int) {
    final int collinearityCheckNextIndex = pEarTipCutIndex % pVertices.size();
    int collinearCheckPreviousIndex = EarClippingTriangulator.computePreviousIndex(pVertices, collinearityCheckNextIndex);

    if (EarClippingTriangulator.isCollinear(pVertices, collinearityCheckNextIndex)) {
        pVertices.remove(collinearityCheckNextIndex);

        if (pVertices.size() > 3) {
            /* Update */
            collinearCheckPreviousIndex = EarClippingTriangulator.computePreviousIndex(pVertices, collinearityCheckNextIndex);
            if (EarClippingTriangulator.isCollinear(pVertices, collinearCheckPreviousIndex)) {
                pVertices.remove(collinearCheckPreviousIndex);
            }
        }
    } else if (EarClippingTriangulator.isCollinear(pVertices, collinearCheckPreviousIndex)) {
        pVertices.remove(collinearCheckPreviousIndex);
    }
}

bool EarClippingTriangulator::isCollinear (const final& ArrayList,const final& int) {
    final int previousIndex = EarClippingTriangulator.computePreviousIndex(pVertices, pIndex);
    final int nextIndex = EarClippingTriangulator.computeNextIndex(pVertices, pIndex);

    return EarClippingTriangulator.isCollinear(pVertices, previousIndex, pIndex, nextIndex);
}

bool EarClippingTriangulator::isCollinear (const final& ArrayList,const final& int,const final& int,const final& int) {
    final Vector2 previousVertex = pVertices.get(pPreviousIndex);
    final Vector2 vertex = pVertices.get(pIndex);
    final Vector2 nextVertex = pVertices.get(pNextIndex);

    return EarClippingTriangulator.computeSpannedAreaSign(previousVertex.x, previousVertex.y, vertex.x, vertex.y, nextVertex.x,
            nextVertex.y) == 0;
}

int EarClippingTriangulator::computePreviousIndex (const final& List,const final& int) {
    return pIndex == 0 ? pVertices.size() - 1 : pIndex - 1;
}

int EarClippingTriangulator::computeNextIndex (const final& List,const final& int) {
    return pIndex == pVertices.size() - 1 ? 0 : pIndex + 1;
}

