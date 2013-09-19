
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

#ifndef GDX_CPP_GRAPHICS_GLUTILS_INDEXBUFFEROBJECT_HPP_
#define GDX_CPP_GRAPHICS_GLUTILS_INDEXBUFFEROBJECT_HPP_

#include <vector>

#include "IndexData.hpp"
#include "gdx-cpp/utils/Buffer.hpp"

namespace gdx {

class IndexBufferObject : public IndexData {
public:

    IndexBufferObject (bool isStatic, int maxIndices) ;
    IndexBufferObject (int maxIndices) ;
    
    int getNumIndices () override;
    int getNumMaxIndices () override;
    void setIndices (const std::vector< short >& indices, int offset, int count) override;
    short_buffer& getBuffer () override;
    void bind () override;
    void unbind () override;
    void invalidate () override;
    void dispose () override;

protected:
    short_buffer buffer;
    byte_buffer byteBuffer;
    int bufferHandle;
    bool isDirect;
    bool isDirty;
    bool isBound;
    int usage;
    int tmpHandle;
    
private:
    int createBufferObject ();
};

} // namespace gdx

#endif // GDX_CPP_GRAPHICS_GLUTILS_INDEXBUFFEROBJECT_HPP_
