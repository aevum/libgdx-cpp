
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

#ifndef GDX_CPP_FILES_FILEHANDLESTREAM_HPP_
#define GDX_CPP_FILES_FILEHANDLESTREAM_HPP_

#include <cstdio>
#include <string>
#include "FileHandle.hpp"
#include "File.hpp"

namespace gdx_cpp {
namespace files {

class FileHandleStream : public gdx_cpp::files::FileHandle{
public:
    FileHandleStream(std::string path);
    bool isDirectory ();
    long length ();
    bool exists ();
    FileHandle& child (const std::string& name);
    FileHandle& parent ();
    InputStream& read ();
    OutputStream& write (bool overwrite);
    FileHandle* list ();
    void mkdirs ();
    bool delete ();
    bool deleteDirectory ();
    void copyTo (const FileHandle& dest);
    void moveTo (const FileHandle& dest);

protected:


private:

};

} // namespace gdx_cpp
} // namespace files

#endif // GDX_CPP_FILES_FILEHANDLESTREAM_HPP_
