
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

#include "FileHandle.hpp"
#include <iostream>
#include <stdexcept>
#include <stdlib.h>
#include <cassert>

#include "gdx-cpp/Gdx.hpp"

using namespace gdx_cpp::files;

FileHandle::FileHandle()
{
}

FileHandle::FileHandle (const std::string &fileName)
  :   file(fileName),
      type(gdx_cpp::Files::Absolute)
{
}

FileHandle::FileHandle (File const& file)
  : file(file),
    type(gdx_cpp::Files::Absolute)
{
}

FileHandle::FileHandle (const std::string &fileName, gdx_cpp::Files::FileType _type)
  : type(_type),
    file(fileName)
{
}

FileHandle::FileHandle (const gdx_cpp::files::File &file, gdx_cpp::Files::FileType type)
  : file(file),
    type(type)
{
}

const std::string& FileHandle::path () const {
    return file.getPath();
}

std::string FileHandle::name () const {
    return file.getName();
}

std::string FileHandle::extension () const {
	return file.extension();
}

std::string FileHandle::nameWithoutExtension () const {
	return file.nameWithoutExtension();
}

std::string FileHandle::typetoString () const {
    if(type == gdx_cpp::Files::Absolute) return "Absolute";
    if (type == gdx_cpp::Files::External) return "External";
    if (type == gdx_cpp::Files::Internal) return "Internal";
    return "Classpath";
}

gdx_cpp::Files::FileType FileHandle::getType () const {
    return type;
}

File FileHandle::getFile () const {
    if (type == gdx_cpp::Files::External) return File( gdx_cpp::Gdx::files->getExternalStoragePath(), file.getPath());
    return file;
}

int FileHandle::readBytes (buffer_ptr &c) const {
    throw std::runtime_error("Not implemented, if you're seeing this error your backend"
                             " hasn't implemented the readBytes method, wich he should");
    
//     int Length = (int) length();
//     if (Length == 0) Length = 512;
//     int bufferlength = Length;
//     
//     char* buf = (char*) malloc(bufferlength);
//     
//     int position = 0;
//     ifstream_ptr input = read();
//     try
//     {
//         while (true)
//         {
//             int count = 0;
//             input->read( buf + position, Length - position);
//             count = input->gcount();
//             position += count;
//             if(input->eof() || !count || input->peek() == EOF)
//             {
//               break;
//             }
// 
//             if (position == bufferlength) {
//                 // Grow buffer.
//                 buf = (char * ) realloc(buf, bufferlength * 2);
//                 assert(buf);
//                 bufferlength *= 2;
//             }
//         }
//     }
//     catch(std::runtime_error e)
//     {
//         if(input->is_open()) input->close();
//         throw std::runtime_error("Error reading file: " + this->toString());
//     }
//     
//     if(input->is_open()) {
//         input->close();
//     }
//     
//     if(position < bufferlength)
//     {
//         buf = (char *) realloc(buf, position);
//         assert(buf);
//     }
// 
//     buffer_ptr new_ptr = buffer_ptr(buf, shared_ptr_free_deleter());
//     c.swap(new_ptr);
//     return position;
}


int FileHandle::write ( const char* data, int lenght, bool append) {
//     throw std::runtime_error("Not implemented, if you're seeing this error your backend"
//                              " hasn't implemented the write method, wich he should");
    
//     if (type == gdx_cpp::Files::Internal) throw std::runtime_error("Cannot write to an internal file: " + file.getPath());
//     ofstream_ptr output;
//     try
//     {
//         if(append) output = ofstream_ptr (new std::ofstream(file.getPath().c_str(), std::fstream::out | std::ios::app));
//         else output = ofstream_ptr (new std::ofstream(file.getPath().c_str(), std::ios::out | std::ios::trunc));
//     }
//     catch(std::runtime_error e)
//     {
//         if(getFile().isDirectory()) throw std::runtime_error("Cannot open a stream to a directory: " + file.getPath() + " (" + typetoString() + ")");
//         else throw std::runtime_error("Error writing file: " + file.getPath() + " (" + typetoString() + ")");
//     }
//     return output;
    return 0;
}

void FileHandle::list(std::vector<FileHandle> &handles) {
    std::vector<std::string> relativePaths;
    getFile().list(relativePaths);
    handles.resize(relativePaths.size());
    for (int i = 0, n = relativePaths.size(); i < n; i++)
        handles[i] = child(relativePaths[i]);
    return;
}

void FileHandle::list (const std::string& suffix, std::vector<FileHandle> &handles) {
    std::vector<std::string> relativePaths;
    getFile().list(relativePaths);
    handles.resize(relativePaths.size());
    unsigned int count = 0, found;
    for (int i = 0, n = relativePaths.size(); i < n; i++) {
        found = relativePaths[i].rfind(suffix);
        if(found == relativePaths[i].npos || found != (relativePaths[i].length() - suffix.length() ) ) continue;
        handles[count++] = child(relativePaths[i]);
    }
    if (count < relativePaths.size()) handles.resize(count);
    return;
}

bool FileHandle::isDirectory () {
    return getFile().isDirectory();
}

FileHandle FileHandle::child (const std::string& name) {
    if (file.getPath().length() == 0) return FileHandle(File(name), type);
    return FileHandle(File(file, name), type);
}

FileHandle FileHandle::parent () {
    
    File parent;
    parent = file.getParentFile();
    if(parent.getPath() == "")
    {
        if (type == gdx_cpp::Files::Absolute)
            parent = File("/");
        else
            parent = File("");
    }
    return FileHandle(parent, type);
}

void FileHandle::mkdirs () {
    if (type == gdx_cpp::Files::Internal) throw std::runtime_error("Cannot mkdirs with an internal file: " + file.getPath());
    getFile().mkdirs();
}

bool FileHandle::exists () {
    switch (type) {
    case gdx_cpp::Files::Internal:
        if (file.exists()) return true;
        break;
    default:
        break;        
    }
    return getFile().exists();
}

bool FileHandle::deleteFile ()
{
    if (type == gdx_cpp::Files::Internal) throw std::runtime_error("Cannot delete an internal file: " + file.getPath());
    return getFile().deleteFile();
}

bool FileHandle::deleteDirectory () {
    if (type == gdx_cpp::Files::Internal) throw std::runtime_error("Cannot delete an internal file: " + file.getPath());
    File target = getFile();
    return deleteDirectory(target);
}

void FileHandle::copyTo (FileHandle& dest) {
    throw std::runtime_error("Not implemented, if you're seeing this error your backend"
                             " hasn't implemented the readBytes method, wich he should");    
//     ifstream_ptr input;
//     ofstream_ptr output;
//     try {
//         input = read();
//         output = dest.write(false);
//         char buffer[4096];
//         while (true) {
//             input->read(buffer, 4096);
//             output->write(buffer, input->gcount());
//             if(input->eof() || input->peek() == EOF) break;
//         }
//     } catch(std::runtime_error ex) {
//         if(input->is_open()) input->close();
//         if(output->is_open()) output->close();
//         throw std::runtime_error("Error copying source file: " + path() + " (" + typetoString() + ")\n" + "To destination: " + dest.path() + " (" + dest.typetoString() + ")");
//     }
//    if(input->is_open()) input->close();
//    if(output->is_open()) output->close();
}

void FileHandle::moveTo (FileHandle& dest) {
    if (type == gdx_cpp::Files::Internal) throw std::runtime_error("Cannot move an internal file: " + file.getPath());
    copyTo(dest);
    deleteFile();
}

int64_t FileHandle::length () const {
    throw std::runtime_error("Not implemented, if you're seeing this error your backend"
    " hasn't implemented the length method, wich he should");
    
//     if ((type == gdx_cpp::Files::Internal && !file.exists())) {
//       int64_t length = 0;
//       ifstream_ptr input = read();
//       try
//       {
//           if(input != NULL)
//           {
//               input->seekg (0, std::ios::end);
//               length = (int64_t) input->tellg();
//               input->close();
//           }
//       }
//       catch(std::runtime_error ignored)
//       {
//           if(input->is_open()) input->close();
//       }
//       return length;
//     }
//    
//     return getFile().length();
}

std::string FileHandle::toString () const {
    return getFile().getPath();
}

bool FileHandle::deleteDirectory (File& file) {
    if (file.exists())
    {
        std::vector<File> files;
        file.listFiles(files);
        for (int i = 0, n = files.size(); i < n; i++) {
                if (files[i].isDirectory())
                    deleteDirectory(files[i]);
                else
                    files[i].deleteFile();
        }
    }
    return file.deleteFile();
}
