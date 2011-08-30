
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

#include "FileHandleStream.hpp"

using namespace gdx_cpp::files;

FileHandleStream::FileHandleStream(std::string path) :
  FileHandle(File(path), gdx_cpp::Files::Absolute)
{
}

bool FileHandleStream::isDirectory () {
    return false;
}

long FileHandleStream::length () {
    return 0;
}

bool FileHandleStream::exists () {
    return true;
}

FileHandle& FileHandleStream::child (const std::string& name) {
    throw new UnsupportedOperationException();
}

FileHandle& FileHandleStream::parent () {
    throw new UnsupportedOperationException();
}

InputStream& FileHandleStream::read () {
    throw new UnsupportedOperationException();
}

OutputStream& FileHandleStream::write (bool overwrite) {
    throw new UnsupportedOperationException();
}

FileHandle* FileHandleStream::list () {
    throw new UnsupportedOperationException();
}

void FileHandleStream::mkdirs () {
    throw new UnsupportedOperationException();
}

bool FileHandleStream::delete () {
    throw new UnsupportedOperationException();
}

bool FileHandleStream::deleteDirectory () {
    throw new UnsupportedOperationException();
}

void FileHandleStream::copyTo (const FileHandle& dest) {
    throw new UnsupportedOperationException();
}

void FileHandleStream::moveTo (const FileHandle& dest) {
    throw new UnsupportedOperationException();
}

