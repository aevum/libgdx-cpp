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

#ifndef GDX_CPP_BACKENDS_LINUX_LINUXFILES_HPP
#define GDX_CPP_BACKENDS_LINUX_LINUXFILES_HPP

#include <gdx-cpp/Files.hpp>
#include <gdx-cpp/files/FileHandle.hpp>

namespace gdx_cpp {

class Files;

namespace backends {

namespace nix {

  class LinuxFiles : public gdx_cpp::Files
  {
    public:
        //Override
        gdx_cpp::Files::fhandle_ptr getFileHandle (const std::string &fileName, gdx_cpp::Files::FileType type);

        //Override
        gdx_cpp::Files::fhandle_ptr internal (const std::string &path);

        //Override
        gdx_cpp::Files::fhandle_ptr external (const std::string &path);

        //Override
        gdx_cpp::Files::fhandle_ptr absolute (const std::string &path);

        //Override
        std::string& getExternalStoragePath ();

        //Override
        bool isExternalStorageAvailable ();

    private:
        std::string externalPath;
  };
    
}

}

}

#endif // GDX_CPP_BACKENDS_LINUX_LINUXFILES_HPP