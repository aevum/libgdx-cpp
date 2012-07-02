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

#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <sys/types.h>

#include "gdx-cpp/Files.hpp"
#include "gdx-cpp/Application.hpp"
#include "gdx-cpp/files/File.hpp"
#include "gdx-cpp/utils/Aliases.hpp"

#include <iosfwd>
#include <string>
#include <vector>

namespace gdx {

class Files;

class File;
  
class FileHandle {
public:
    typedef ref_ptr_maker<FileHandle>::shared_ptr_def ptr;
    typedef ref_ptr_maker< char >::shared_ptr_def buffer_ptr;

    FileHandle();
    FileHandle (const std::string &fileName);
    FileHandle (const gdx::File &file);
    
    const std::string& path () const;
    std::string name () const;
    std::string extension () const;
    std::string nameWithoutExtension () const;
    std::string typetoString () const;
    gdx::Files::FileType getType () const;

    virtual int readBytes (gdx::FileHandle::buffer_ptr& c) const;
    virtual int write ( const char* data, int lenght, bool append);
    
    void list (std::vector<FileHandle> &handles);
    void list (const std::string& suffix, std::vector<FileHandle> &handles);
    bool isDirectory ();
    FileHandle child (const std::string &name);
    FileHandle parent ();
    void mkdirs ();
    virtual bool exists () const;
    bool deleteFile ();
    bool deleteDirectory ();
    virtual void copyTo (FileHandle& dest);
    void moveTo (FileHandle& dest);
    virtual int64_t length () const;
    std::string toString () const;
    FileHandle (const std::string &fileName, gdx::Files::FileType type);
    FileHandle (const gdx::File &file, gdx::Files::FileType type);

    virtual ~FileHandle() {};
protected:
    gdx::File file;
    gdx::Files::FileType type;

private:
    gdx::File getFile() const;
    static bool deleteDirectory (File &file);
};

} // namespace gdx

#endif // GDX_CPP_FILES_FILEHANDLE_HPP_
