
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

namespace gdx_cpp {
namespace math {

class EarClippingTriangulator {
public:
    std::list<Vector2>& computeTriangles (const final& List);

protected:


private:
    static bool areVerticesClockwise (const final& ArrayList);
    int* classifyVertices (const final& ArrayList);
    static bool isTriangleConvex (const final& float,const final& float,const final& float,const final& float,const final& float,const final& float);
    static int computeSpannedAreaSign (const final& float,const final& float,const final& float,const final& float,const final& float,const final& float);
    static bool isAnyVertexInTriangle (const final& ArrayList,const final& int,const final& float,const final& float,const final& float,const final& float,const final& float,const final& float);
    bool isEarTip (const final& ArrayList,const final& int,const final& int);
    void cutEarTip (const final& ArrayList,const final& int,const final& ArrayList);
    static void removeCollinearNeighborEarsAfterRemovingEarTip (const final& ArrayList,const final& int);
    static bool isCollinear (const final& ArrayList,const final& int);
    static bool isCollinear (const final& ArrayList,const final& int,const final& int,const final& int);
    static int computePreviousIndex (const final& List,const final& int);
    static int computeNextIndex (const final& List,const final& int);
};

} // namespace gdx_cpp
} // namespace math

#endif // GDX_CPP_MATH_EARCLIPPINGTRIANGULATOR_HPP_
