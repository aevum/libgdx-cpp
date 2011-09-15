/*
    Copyright 2011 <copyright holder> <email>

    Licensed under the Apache License, Version 2.0 (the "License")
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#ifndef GDX_CPP_FILES_H
#define GDX_CPP_FILES_H

#include <string>
#include "gdx-cpp/utils/Aliases.hpp"

namespace gdx_cpp {

namespace files
{
  class FileHandle;
}
  
class Files {
public:

  typedef ref_ptr_maker< files::FileHandle >::type fhandle_ptr;

    enum FileType {
        /** Path relative to the asset directory on Android and to the application's root directory on the desktop. On the desktop,
         * if the file is not found, then the classpath is checked. This enables files to be found when using JWS or applets.
         * Internal files are always readonly. */
        Internal,

        /** Path relative to the root of the SD card on Android and to the home directory of the current user on the desktop. */
        External,

        /** Path that is a fully qualified, absolute filesystem path. To ensure portability across platforms use absolute files only
         * when absolutely (heh) necessary. */
        Absolute
    };

    virtual fhandle_ptr getFileHandle (const std::string& path, FileType type) = 0;

    virtual fhandle_ptr internal (const std::string& path) = 0;

    virtual fhandle_ptr external (const std::string& path) = 0;

    virtual fhandle_ptr absolute (const std::string& path) = 0;

    virtual std::string& getExternalStoragePath () = 0;

    virtual bool isExternalStorageAvailable () = 0;
};

}

#endif // GDX_CPP_FILES_H
