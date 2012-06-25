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

#include "IosFileHandle.hpp"
#import <UIKit/UIKit.h>
#include <stdexcept>

using namespace gdx::ios;

IosFileHandle::IosFileHandle(const std::string& fileName, gdx::Files::FileType type)
: gdx::files::FileHandle(fileName, type)
{	
}

int IosFileHandle::readBytes(gdx::files::FileHandle::buffer_ptr& c) const {
	if (this->type == Files::Internal) {		
		NSString *filePath = [[NSBundle mainBundle] pathForResource:[NSString stringWithUTF8String: file.nameWithoutExtension().c_str()] 
															 ofType:[NSString stringWithUTF8String: file.extension().c_str()]
														inDirectory:[NSString stringWithUTF8String: file.getParent().c_str()]];

		if (filePath) {
			NSData* data = [NSData dataWithContentsOfFile:filePath];
			if (data) {
				NSUInteger len = [data length];
				Byte *byteData = new Byte[len];
				memcpy(byteData, [data bytes], len);
				
				gdx::files::FileHandle::buffer_ptr new_ptr((char*) byteData, shared_ptr_array_deleter());
				c.swap(new_ptr);
				
				return len;
			}
		}
		throw std::runtime_error("Failed to load contents of file: " + this->file.getAbsolutePath());
	}
	throw std::runtime_error("Not implemented yet");
}

bool IosFileHandle::exists() const {
    return[[NSBundle mainBundle] pathForResource:[NSString stringWithUTF8String: file.getName().c_str()] ofType:[NSString stringWithUTF8String:file.extension().c_str()]];
}
