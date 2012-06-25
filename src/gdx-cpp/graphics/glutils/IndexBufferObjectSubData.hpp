
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

#ifndef GDX_CPP_GRAPHICS_GLUTILS_INDEXBUFFEROBJECTSUBDATA_HPP_
#define GDX_CPP_GRAPHICS_GLUTILS_INDEXBUFFEROBJECTSUBDATA_HPP_

#include "IndexData.hpp"

namespace gdx {

class IndexBufferObjectSubData : public IndexData {
public:
    IndexBufferObjectSubData (bool isStatic, int maxIndices) ;
    IndexBufferObjectSubData (int maxIndices) ;
    
    int getNumIndices ();
    int getNumMaxIndices ();
    void setIndices (const std::vector< short int >& indices, int offset, int count);
    short_buffer& getBuffer ();
    void bind ();
    void unbind ();
    void invalidate ();
    void dispose ();

protected:
    int tmpHandle;
    
    short_buffer buffer;
    byte_buffer byteBuffer;
    int bufferHandle;
    bool isDirect;
    bool isDirty;
    bool isBound;
    int usage;

private:
    int createBufferObject ();
};

} // namespace gdx

#endif // GDX_CPP_GRAPHICS_GLUTILS_INDEXBUFFEROBJECTSUBDATA_HPP_
