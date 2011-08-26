
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

#ifndef GDX_CPP_GRAPHICS_GLUTILS_ETC1_HPP_
#define GDX_CPP_GRAPHICS_GLUTILS_ETC1_HPP_

#include "gdx-cpp/utils/Disposable.hpp"
#include <string>

namespace gdx_cpp {
namespace files {

class FileHandle;
}

namespace graphics {
namespace glutils {

class ETC1 {
public:
    class ETC1Data : public utils::Disposable {
        public:
            int width;
            int height;
            char* compressedData;          
            int dataOffset;

            ETC1Data (int width, int height, const char* compressedData, int dataOffset) ;
            ETC1Data (files::FileHandle& pkmFile) ;

            bool hasPKMHeader ();
            void write (files::FileHandle& file);
            void dispose () ;

            std::string toString();
    };
    
    bool hasPKMHeader ();
    void write (const gdx_cpp::files::FileHandle& file);
    void dispose ();
    std::string& toString ();
    static ETC1Data& encodeImage (const gdx_cpp::graphics::Pixmap& pixmap);
    static ETC1Data& encodeImagePKM (const gdx_cpp::graphics::Pixmap& pixmap);
    static gdx_cpp::graphics::Pixmap& decodeImage (const ETC1Data& etc1Data,const gdx_cpp::graphics::Pixmap::Format& format);
    int width;
    int height;
    ByteBuffer compressedData;
    int dataOffset;

protected:


private:
    static int getPixelSize (const gdx_cpp::graphics::Pixmap::Format& format);
};

} // namespace gdx_cpp
} // namespace graphics
} // namespace glutils

#endif // GDX_CPP_GRAPHICS_GLUTILS_ETC1_HPP_
