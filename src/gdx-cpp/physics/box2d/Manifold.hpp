
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

#ifndef GDX_CPP_PHYSICS_BOX2D_MANIFOLD_HPP_
#define GDX_CPP_PHYSICS_BOX2D_MANIFOLD_HPP_
#include "World.hpp"
#include "gdx-cpp/math/Vector2.hpp"
#include "ManifoldPoint.hpp"

class b2Manifold;
namespace gdx_cpp {
namespace physics {
namespace box2d {

class Manifold {
public:
    enum ManifoldType {
        Circle, FaceA, FaceB
    };

    Manifold(gdx_cpp::physics::box2d::World::ptr _world, b2Manifold* mani);

    ManifoldType getType ();
    int getPointCount ();
    gdx_cpp::math::Vector2& getLocalNormal ();
    gdx_cpp::math::Vector2& getLocalPoint ();
    ManifoldPoint* getPoints ();

    World::ptr world;
    b2Manifold * addr;
    ManifoldPoint points[2];
    gdx_cpp::math::Vector2 localNormal;
    gdx_cpp::math::Vector2 localPoint;

protected:


private:

};

} // namespace gdx_cpp
} // namespace physics
} // namespace box2d

#endif // GDX_CPP_PHYSICS_BOX2D_MANIFOLD_HPP_
