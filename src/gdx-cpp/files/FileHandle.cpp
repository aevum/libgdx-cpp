
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
#include "gdx-cpp/Gdx.hpp"
#include "gdx-cpp/Log.hpp"

using namespace gdx;

FileHandle::FileHandle()
{
}

FileHandle::FileHandle (const std::string &fileName)
  :   file(fileName),
type(gdx::Files::Absolute)
{
}

FileHandle::FileHandle (File const& file)
  : file(file),
type(gdx::Files::Absolute)
{
}

FileHandle::FileHandle (const std::string &fileName, gdx::Files::FileType _type)
  : file(fileName),
type(_type)
{
}

FileHandle::FileHandle (const gdx::File &file, gdx::Files::FileType type)
  : file(file),
type(type)
{
}

const std::string FileHandle::path () const {
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
    if(type == gdx::Files::Absolute) return "Absolute";
    if (type == gdx::Files::External) return "External";
    if (type == gdx::Files::Internal) return "Internal";
    return "Classpath";
}

gdx::Files::FileType FileHandle::getType () const {
    return type;
}

File FileHandle::getFile () const {
    if (type == gdx::Files::External) return File( gdx::files->getExternalStoragePath(), file.getPath());
    return file;
}

int FileHandle::readBytes (buffer_ptr &c) const {
    gdx_log_error("gdx","Not implemented, if you're seeing this error your backend"
                             " hasn't implemented the readBytes method, wich he should");
    
    return 0;
}


int FileHandle::write ( const char* data, int lenght, bool append) {
    gdx_log_error("gdx","Not implemented, if you're seeing this error your backend"
                             " hasn't implemented the write method, wich he should");
    
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
        if (type == gdx::Files::Absolute)
            parent = File("/");
        else
            parent = File("");
    }
    return FileHandle(parent, type);
}

void FileHandle::mkdirs () {
    if (type == gdx::Files::Internal) gdx_log_error("gdx","Cannot mkdirs with an internal file: %s", file.getPath().c_str());
    getFile().mkdirs();
}

bool FileHandle::exists () const {
    switch (type) {
    case gdx::Files::Private:
        return true;
    case gdx::Files::Internal:    
        if (file.exists()) return true;
        break;
    default:
        break;        
    }
    return getFile().exists();
}

bool FileHandle::deleteFile ()
{
    if (type == gdx::Files::Internal) gdx_log_error("gdx","Cannot delete an internal file: ", file.getPath().c_str());
    return getFile().deleteFile();
}

bool FileHandle::deleteDirectory () {
    if (type == gdx::Files::Internal) gdx_log_error("gdx","Cannot delete an internal file: ", file.getPath().c_str());
    File target = getFile();
    return deleteDirectory(target);
}

void FileHandle::copyTo (FileHandle& dest) {
    gdx_log_error("gdx","Not implemented, if you're seeing this error your backend"
                             " hasn't implemented the readBytes method, wich he should");    
}

void FileHandle::moveTo (FileHandle& dest) {
    if (type == gdx::Files::Internal) gdx_log_error("gdx","Cannot move an internal file: %s", file.getPath().c_str());
    copyTo(dest);
    deleteFile();
}

int64_t FileHandle::length () const {
    gdx_log_error("gdx","Not implemented, if you're seeing this error your backend"
    " hasn't implemented the length method, wich he should");
    
    return -1;
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
