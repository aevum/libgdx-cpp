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
 */

#ifndef GDX_CPP_BACKENDS_IOS_IOSFILEHANDLE_HPP
#define GDX_CPP_BACKENDS_IOS_IOSFILEHANDLE_HPP

#include <gdx-cpp/files/FileHandle.hpp>

namespace gdx {

class Files;
  
namespace backends {

namespace ios {

class IosFileHandle : public gdx::files::FileHandle
{	
public:
	IosFileHandle(const std::string& fileName, gdx::Files::FileType type);
	virtual int readBytes(gdx::files::FileHandle::buffer_ptr& c) const;
    
    bool exists() const;
    
    virtual int write ( const char* data, int lenght, bool append);
};

}

}

}

#endif // GDX_CPP_BACKENDS_IOS_IOSFILEHANDLE_HPP