
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

#ifndef GDX_CPP_GRAPHICS_G3D_LOADERS_MD5_MD5ANIMATION_HPP_
#define GDX_CPP_GRAPHICS_G3D_LOADERS_MD5_MD5ANIMATION_HPP_

namespace gdx_cpp {
namespace graphics {
namespace g3d {
namespace loaders {
namespace md5 {

class MD5Animation: public gdx_cpp::graphics::g3d::Animation {
public:
    void write (const DataOutputStream& out);
    void read (const DataInputStream& in);
    static void interpolate (const MD5Joints& skeletonA,const MD5Joints& skeletonB,const MD5Joints& skeletonOut,float t);
    float getLength ();
    int getNumFrames ();

protected:


private:

};

} // namespace gdx_cpp
} // namespace graphics
} // namespace g3d
} // namespace loaders
} // namespace md5

#endif // GDX_CPP_GRAPHICS_G3D_LOADERS_MD5_MD5ANIMATION_HPP_
