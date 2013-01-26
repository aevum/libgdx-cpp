
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

#ifndef GDX_CPP_MATH_EARCLIPPINGTRIANGULATOR_HPP_
#define GDX_CPP_MATH_EARCLIPPINGTRIANGULATOR_HPP_

#include <list>
#include <vector>

#include "Vector2.hpp"
#include "gdx-cpp/internal/memory"

namespace gdx {

class Vector2;

class EarClippingTriangulator {
public:
  std::vector<Vector2> computeTriangles (const std::vector<Vector2>& polygon);
  EarClippingTriangulator();
  
private:
    static bool areVerticesClockwise (const std::vector<Vector2>& pVertices);
    std::vector<int> classifyVertices (std::vector< Vector2 >& pVertices);
    static bool isTriangleConvex (float pX1, float pY1, float pX2, float pY2, float pX3,
                                  float pY3);
    static int computeSpannedAreaSign (float pX1, float pY1, float pX2, float pY2,
                                       float pX3, float pY3);
    static bool isAnyVertexInTriangle (std::vector<Vector2>& pVertices, const std::vector<int>& pVertexTypes, float pX1,
                                       float pY1, float pX2, float pY2, float pX3, float pY3);
    bool isEarTip (std::vector<Vector2>& pVertices, int pEarTipIndex, const std::vector<int>& pVertexTypes);
    void cutEarTip (std::vector< Vector2 >& pVertices, int pEarTipIndex, std::vector< Vector2 >& pTriangles);
    static void removeCollinearNeighborEarsAfterRemovingEarTip (std::vector<Vector2>& pVertices,
                                                                int pEarTipCutIndex);
    static bool isCollinear (const std::vector<Vector2>& pVertices, int pIndex);
    static bool isCollinear (const std::vector<Vector2>& pVertices, int pPreviousIndex, int pIndex,
                             int pNextIndex);
    static int computePreviousIndex (const std::vector< Vector2 >& pVertices, int pIndex);
    static int computeNextIndex (const std::vector<Vector2>& pVertices, int pIndex);
    
    int concaveVertexCount;
};

} // namespace gdx

#endif // GDX_CPP_MATH_EARCLIPPINGTRIANGULATOR_HPP_
