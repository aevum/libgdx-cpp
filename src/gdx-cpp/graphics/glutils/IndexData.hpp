
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

#ifndef GDX_CPP_GRAPHICS_GLUTILS_INDEXDATA_HPP_
#define GDX_CPP_GRAPHICS_GLUTILS_INDEXDATA_HPP_

#include <vector>

#include "gdx-cpp/utils/Disposable.hpp"
#include "gdx-cpp/utils/Buffer.hpp"

namespace gdx_cpp {
namespace graphics {
namespace glutils {

class IndexData: public gdx_cpp::utils::Disposable {
public:
    virtual   int getNumIndices () = 0;
    virtual   int getNumMaxIndices () = 0;
    virtual   void setIndices (int offset,int count) = 0;
    virtual   utils::short_buffer getBuffer () = 0;
    virtual   void bind () = 0;
    virtual   void unbind () = 0;
    virtual   void invalidate () = 0;
    virtual   void dispose () = 0;
};

} // namespace gdx_cpp
} // namespace graphics
} // namespace glutils

#endif // GDX_CPP_GRAPHICS_GLUTILS_INDEXDATA_HPP_
