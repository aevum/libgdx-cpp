
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
#include <stdint.h>

using namespace gdx_cpp::files;

FileHandleStream::FileHandleStream(std::string path) :
  FileHandle(File(path), gdx_cpp::Files::Absolute)
{
}

bool FileHandleStream::isDirectory () {
    return false;
}

int64_t FileHandleStream::length () {
    return 0;
}

bool FileHandleStream::exists () {
    return true;
}

FileHandle FileHandleStream::child (const std::string& name) {
    gdx_cpp::Gdx::app->error("FileHandleStream", "UnsupportedOperationException()");
}

FileHandle FileHandleStream::parent () {
    gdx_cpp::Gdx::app->error("FileHandleStream","UnsupportedOperationException()");
}

FileHandleStream::ifstream_ptr FileHandleStream::read () {
    gdx_cpp::Gdx::app->error("FileHandleStream","UnsupportedOperationException()");
}

FileHandleStream::ofstream_ptr FileHandleStream::write (bool overwrite) {
    gdx_cpp::Gdx::app->error("FileHandleStream","UnsupportedOperationException()");
}

void FileHandleStream::list (std::vector<FileHandle> &handles) {
    gdx_cpp::Gdx::app->error("FileHandleStream","UnsupportedOperationException()");
}

void FileHandleStream::mkdirs () {
    gdx_cpp::Gdx::app->error("FileHandleStream","UnsupportedOperationException()");
}

bool FileHandleStream::deleteFile () {
    gdx_cpp::Gdx::app->error("FileHandleStream","UnsupportedOperationException()");
}

bool FileHandleStream::deleteDirectory () {
    gdx_cpp::Gdx::app->error("FileHandleStream","UnsupportedOperationException()");
}

void FileHandleStream::copyTo (FileHandle& dest) {
    gdx_cpp::Gdx::app->error("FileHandleStream","UnsupportedOperationException()");
}

void FileHandleStream::moveTo (FileHandle& dest) {
    gdx_cpp::Gdx::app->error("FileHandleStream","UnsupportedOperationException()");
}

