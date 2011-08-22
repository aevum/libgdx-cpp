
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

#ifndef GDX_CPP_UTILS_SCREENUTILS_HPP_
#define GDX_CPP_UTILS_SCREENUTILS_HPP_

namespace gdx_cpp {
namespace utils {

class ScreenUtils {
public:
    static gdx_cpp::graphics::g2d::TextureRegion& getFrameBufferTexture ();
    static gdx_cpp::graphics::g2d::TextureRegion& getFrameBufferTexture (int x,int y,int w,int h);
    static char* getFrameBufferPixels (bool flipY);
    static char* getFrameBufferPixels (int x,int y,int w,int h,bool flipY);

protected:


private:

};

} // namespace gdx_cpp
} // namespace utils

#endif // GDX_CPP_UTILS_SCREENUTILS_HPP_
