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

#include "LinuxFileHandle.hpp"

using namespace gdx_cpp::backends::nix;

LinuxFileHandle::LinuxFileHandle (const std::string &fileName, gdx_cpp::Files::FileType type)
  : FileHandle(fileName, type)
{
}

LinuxFileHandle::LinuxFileHandle (const gdx_cpp::files::File &file, gdx_cpp::Files::FileType type)
  : FileHandle(file, type)
{
}

gdx_cpp::Files::fhandle_ptr LinuxFileHandle::child (const std::string &name)
{
    if (file.getPath().length() == 0) return gdx_cpp::Files::fhandle_ptr (new LinuxFileHandle(gdx_cpp::files::File(name), this->type));
    return gdx_cpp::Files::fhandle_ptr (new LinuxFileHandle(gdx_cpp::files::File(file, name), this->type));
}
        
gdx_cpp::Files::fhandle_ptr LinuxFileHandle::parent ()
{
    gdx_cpp::files::File parent = file.getParentFile();
    if (parent.getPath() == "")
    {
        if (type == gdx_cpp::Files::Absolute)
            parent = gdx_cpp::files::File("/");
        else
            parent = gdx_cpp::files::File("");
    }
    return gdx_cpp::Files::fhandle_ptr (new LinuxFileHandle(parent, type));
}
