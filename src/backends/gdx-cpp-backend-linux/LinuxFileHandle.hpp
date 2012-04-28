/*
 *  Copyright 2011 Aevum Software aevum @ aevumlab.com
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  @author Victor Vicente de Carvalho victor.carvalho@aevumlab.com
 *  @author Ozires Bortolon de Faria ozires@aevumlab.com
 *  @author aevum team
 */

#ifndef GDX_CPP_BACKENDS_LINUX_LINUXFILEHANDLE_HPP
#define GDX_CPP_BACKENDS_LINUX_LINUXFILEHANDLE_HPP

#include <gdx-cpp/files/FileHandle.hpp>

namespace gdx_cpp {

class Files;

namespace backends {

namespace nix {

class LinuxFileHandle : public gdx_cpp::files::FileHandle
{

public:

    LinuxFileHandle (const std::string &fileName, gdx_cpp::Files::FileType type);
    LinuxFileHandle (const gdx_cpp::files::File &file, gdx_cpp::Files::FileType type);

    virtual int readBytes(buffer_ptr& c) const;
    virtual int write(const char* data, int length, bool append);
    virtual void copyTo(FileHandle& dest);
    virtual int64_t length() const;
private:
    void runtime_error(const char* arg1);
};

}

}

}

#endif // GDX_CPP_BACKENDS_LINUX_LINUXFILEHANDLE_HPP
