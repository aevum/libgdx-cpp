
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

#ifndef GDX_CPP_PHYSICS_BOX2D_FIXTURE_HPP_
#define GDX_CPP_PHYSICS_BOX2D_FIXTURE_HPP_

#include "Shape.hpp"
#include "Filter.hpp"
#include <gdx-cpp/utils/Aliases.hpp>
#include "Body.hpp"

class b2Fixture;
namespace gdx_cpp {
namespace math{
  class Vector2;
}
namespace physics {
namespace box2d {
  
class Body;

class Fixture {
public:
  
    Shape::Type getType ();
    Shape::ptr getShape ();
    void setSensor (bool sensor);
    bool isSensor ();
    void setFilterData (const gdx_cpp::physics::box2d::Filter& filter);
    Filter& getFilterData ();
    Body::ptr getBody ();
    bool testPoint (const gdx_cpp::math::Vector2& p);
    bool testPoint (float x,float y);
    void setDensity (float density);
    float getDensity ();
    float getFriction ();
    void setFriction (float friction);
    float getRestitution ();
    void setRestitution (float restitution);
    void setUserData (void * userData);
    void * getUserData ();
    
    b2Fixture* addr;
    void reset (gdx_cpp::physics::box2d::Body::ptr body, b2Fixture* addr);

protected:

    Shape::ptr shape;
    void * userData;

private:
    Filter filter;
    Body::ptr body;
    
};

} // namespace gdx_cpp
} // namespace physics
} // namespace box2d

#endif // GDX_CPP_PHYSICS_BOX2D_FIXTURE_HPP_
