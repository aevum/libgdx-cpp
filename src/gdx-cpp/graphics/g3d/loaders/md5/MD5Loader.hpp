
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

#ifndef GDX_CPP_GRAPHICS_G3D_LOADERS_MD5_MD5LOADER_HPP_
#define GDX_CPP_GRAPHICS_G3D_LOADERS_MD5_MD5LOADER_HPP_

namespace gdx_cpp {
namespace graphics {
namespace g3d {
namespace loaders {
namespace md5 {

class MD5Loader {
public:
    static MD5Model& loadModel (const InputStream& in,bool allocateNormals);
    static MD5Animation& loadAnimation (const InputStream& in);

protected:


private:
    static float parseFloat (const std::string& value);
    static int parseInt (const std::string& value);
    static void buildFrameSkeleton (const MD5Animation& animation,int frameIndex);
    static void tokenize (const std::string& line,std::list<String>& tokens);
};

} // namespace gdx_cpp
} // namespace graphics
} // namespace g3d
} // namespace loaders
} // namespace md5

#endif // GDX_CPP_GRAPHICS_G3D_LOADERS_MD5_MD5LOADER_HPP_
