
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

#ifndef GDX_CPP_MATH_COLLISION_RAY_HPP_
#define GDX_CPP_MATH_COLLISION_RAY_HPP_

#include "math/Vector3.hpp"

namespace gdx_cpp {
namespace math {
namespace collision {

class Ray {
public:
    Ray& cpy ();
    gdx_cpp::math::Vector3& getEndPoint (float distance);
    Ray& mul (const gdx_cpp::math::Matrix4& matrix);
    std::string& toString ();
    Ray& set (const gdx_cpp::math::Vector3& origin,const gdx_cpp::math::Vector3& direction);
    Ray& set (float x,float y,float z,float dx,float dy,float dz);
    Ray& set (const Ray& ray);

protected:


private:

};

} // namespace gdx_cpp
} // namespace math
} // namespace collision

#endif // GDX_CPP_MATH_COLLISION_RAY_HPP_
