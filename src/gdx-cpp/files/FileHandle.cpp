
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

using namespace gdx_cpp::files;

FileHandle::FileHandle (){}

FileHandle::FileHandle (const std::string &fileName)
  :   file(File(fileName)),
      type(gdx_cpp::Files::Absolute)
{
}

FileHandle::FileHandle (File const& file)
  : file(file),
    type(gdx_cpp::Files::Absolute)
{
}

FileHandle::FileHandle (const std::string &fileName, gdx_cpp::Files::FileType type)
  : type(type),
    file(File(fileName))
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
    std::string name = file.getName();
    int dotIndex = name.rfind('.');
    if (dotIndex == std::string::npos) return "";
    return name.substr(dotIndex + 1);
}

std::string FileHandle::nameWithoutExtension () const {
    std::string name = file.getName();
    int dotIndex = name.rfind('.');
    if (dotIndex == std::string::npos) return name;
    return name.substr(0, dotIndex);
}

std::string FileHandle::typetoString () {
    if(type == gdx_cpp::Files::Absolute) return "Absolute";
    if (type == gdx_cpp::Files::External) return "External";
    if (type == gdx_cpp::Files::Internal) return "Internal";
    return "Classpath";
}

gdx_cpp::Files::FileType& FileHandle::getType () {
    return type;
}

File FileHandle::getFile () {
    if (type == gdx_cpp::Files::External) return File( gdx_cpp::Gdx::files->getExternalStoragePath(), file.getPath());
    return file;
}

FileHandle::ifstream_ptr FileHandle::read ()
{
    ifstream_ptr input;
    
    if (type == gdx_cpp::Files::Internal && !file.exists()) {
        int found;
        std::string s = "/" + file.getPath();
        while((found = s.find("//")) != s.npos) s.replace(found, 2, "/");
        input = ifstream_ptr (new std::ifstream( s.c_str(), std::ios::in | std::ios::binary));
        if(!input->is_open()) throw std::runtime_error("File not found: " + file.getPath() + " (" + typetoString() + ")");
        
        return input;
    }

    input = ifstream_ptr (new std::ifstream(file.getPath().c_str(), std::ios::in | std::ios::binary));

    if(!input->is_open())
    {
      if(file.isDirectory()) throw std::runtime_error("Cannot open a stream to a directory: " + file.getPath() + " (" + typetoString() + ")");
      else throw std::runtime_error("Error reading file: " + file.getPath() + " (" + typetoString() + ")");
    }
    return input; 
}

std::string FileHandle::readString () {
    return readString("");
}

std::string FileHandle::readString (const std::string& charset) {
    std::string output = "";
    ifstream_ptr reader;

    if (charset == "") reader = read();
    //else     TODO TEM QUE CRIAR CHARSET AQUI
    //    reader = new InputStreamReader(read(), charset);
    try
    {
        char buffer[257];
        std::streampos  earlypos;
        buffer[256] = '\0';
        while (true) {
                    earlypos = reader->tellg();
                    if(!reader->read(buffer, 256)) break;
                    output += std::string(buffer);
        }
        reader->clear();
        reader->seekg (earlypos);
        reader->seekg (0, std::ios::end);
        buffer[((int) reader->tellg()-earlypos)] = '\0';
        output += std::string(buffer);
    }
    catch(std::runtime_error e)
    {
        if (reader->is_open()) reader->close();
        throw std::runtime_error("Error reading file: " + this->toString());
    }
    if (reader->is_open()) reader->close();
    return output;
}

int FileHandle::readBytes (char_ptr &c) {
    char p;
    int Length = (int) length();
    if (Length == 0) Length = 512;
    int bufferlength = Length;
    c = char_ptr (new char[bufferlength]);
    int position = 0;
    ifstream_ptr input = read();
    try
    {
        while (true)
        {
            int count = 0;
            input->read( c.get() + position, Length - position);
            count = input->gcount();
            position += count;
            if(input->eof() || !count || input->peek() == EOF)
            {
              break;
            }

            if (position == bufferlength) {
                // Grow buffer.
            char_ptr newBuffer = char_ptr (new char[bufferlength * 2]);
            for(int i = 0; i< bufferlength; i++) newBuffer.get()[i] = c.get()[i];
            c.swap(newBuffer);
            bufferlength *= 2;
            }
        }
    }
    catch(std::runtime_error e)
    {
        if(input->is_open()) input->close();
        throw std::runtime_error("Error reading file: " + this->toString());
    }
    if(input->is_open()) input->close();
    if(position < bufferlength)
    {
        // Shrink buffer.
        char_ptr newBuffer = char_ptr (new char[position]);
        for(int i = 0; i<position; i++) newBuffer.get()[i] = c.get()[i];
        c.swap(newBuffer);
    }
    return position;
}

FileHandle::ofstream_ptr FileHandle::write (bool append) {
    if (type == gdx_cpp::Files::Internal) throw std::runtime_error("Cannot write to an internal file: " + file.getPath());
    ofstream_ptr output;
    try
    {
        if(append) output = ofstream_ptr (new std::ofstream(file.getPath().c_str(), std::fstream::out | std::ios::app));
        else output = ofstream_ptr (new std::ofstream(file.getPath().c_str(), std::ios::out | std::ios::trunc));
    }
    catch(std::runtime_error e)
    {
        if(getFile().isDirectory()) throw std::runtime_error("Cannot open a stream to a directory: " + file.getPath() + " (" + typetoString() + ")");
        else throw std::runtime_error("Error writing file: " + file.getPath() + " (" + typetoString() + ")");
    }
    return output;
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
    int count = 0, found;
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

FileHandle FileHandle::child (const std::string &name) {
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
        // Fall through.
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
    ifstream_ptr input;
    ofstream_ptr output;
    try {
        input = read();
        output = dest.write(false);
        char buffer[4096];
        while (true) {
            input->read(buffer, 4096);
            output->write(buffer, input->gcount());
            if(input->eof() || input->peek() == EOF) break;
        }
    } catch(std::runtime_error ex) {
        if(input->is_open()) input->close();
        if(output->is_open()) output->close();
        throw std::runtime_error("Error copying source file: " + path() + " (" + typetoString() + ")\n" + "To destination: " + dest.path() + " (" + dest.typetoString() + ")");
    }
   if(input->is_open()) input->close();
   if(output->is_open()) output->close();
}

void FileHandle::moveTo (FileHandle& dest) {
    if (type == gdx_cpp::Files::Internal) throw std::runtime_error("Cannot move an internal file: " + file.getPath());
    copyTo(dest);
    deleteFile();
}

int64_t FileHandle::length () {
    if ((type == gdx_cpp::Files::Internal && !file.exists())) {
      int64_t length = 0;
      ifstream_ptr input = read();
      try
      {
          if(input != NULL)
          {
              input->seekg (0, std::ios::end);
              length = (int64_t) input->tellg();
              input->close();
          }
      }
      catch(std::runtime_error ignored)
      {
          if(input->is_open()) input->close();
      }
      return length;
    }
   
    return getFile().length();
}

std::string FileHandle::toString () {
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
