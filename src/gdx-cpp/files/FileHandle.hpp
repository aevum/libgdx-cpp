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

#ifndef GDX_CPP_FILES_FILEHANDLE_HPP_
#define GDX_CPP_FILES_FILEHANDLE_HPP_
#include "gdx-cpp/Files.hpp"
#include "gdx-cpp/Gdx.hpp"
#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <sys/types.h>
#include "gdx-cpp/files/File.hpp"
#include "gdx-cpp/utils/Aliases.hpp"

namespace gdx_cpp {
namespace files {

class FileHandle {
public:
    
    typedef ref_ptr_maker< std::ifstream >::type ifstream_ptr;
    typedef ref_ptr_maker< std::ofstream >::type ofstream_ptr;
    typedef ref_ptr_maker< char >::type char_ptr;
    FileHandle ();
    FileHandle (const std::string &fileName);
    FileHandle (const gdx_cpp::files::File &file);
    std::string& path ();
    std::string name ();
    std::string extension ();
    std::string nameWithoutExtension ();
    std::string typetoString ();
    gdx_cpp::Files::FileType& getType ();
    ifstream_ptr read ();
    std::string readString ();
    std::string readString (const std::string& charset);
    int readBytes (char_ptr c);
    ofstream_ptr write (bool append);
    void list (std::vector<FileHandle> &handles);
    void list (const std::string& suffix, std::vector<FileHandle> &handles);
    bool isDirectory ();
    FileHandle child (const std::string &name);
    FileHandle parent ();
    void mkdirs ();
    bool exists ();
    bool deleteFile ();
    bool deleteDirectory ();
    void copyTo (FileHandle& dest);
    void moveTo (FileHandle& dest);
    int64_t length ();
    std::string toString ();
    

protected:
    gdx_cpp::files::File file;
    gdx_cpp::Files::FileType type;
    FileHandle (const std::string &fileName, gdx_cpp::Files::FileType type);
    FileHandle (const gdx_cpp::files::File &file, gdx_cpp::Files::FileType type);

private:
    gdx_cpp::files::File getFile();
    static bool deleteDirectory (File &file);
};

} // namespace gdx_cpp
} // namespace files

#endif // GDX_CPP_FILES_FILEHANDLE_HPP_
