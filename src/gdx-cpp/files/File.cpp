#include "FileHandleStream.hpp"
#include <cstdio>

using namespace gdx_cpp::files;

std::string File::pathSeparator = ":";
char File::pathSeparatorChar = ':';
std::string File::separator = "/";
char File::separatorChar = '/';

File::File()
  : pathname(""),
    parent(""),
    path("")
{
}

File::File(const std::string& fileName)
  : parent(""),
    path("")
{
    child = fileName;
}

File(const std::string& parent, const std::string& child)
  : path("")
{
    if(parent == "") File(child);
    //assumindo que pai e filho sao paths validos
    else
    {
      this->parent = parent;
      this->child = child;
    }
}

File(File& parent, const std::string& child)
{
  
}

bool File::isDirectory()
{
    std::string p = getPath();
    int found = p.find_last_of("./");
    if(found == npos || p[found] == '/') return true;
    return false;
}

void File::set(const std::string& fileName)
{
    path = "";
    parent = "";
    child = fileName;
}

void File::set(const std::string& parent, const std::string& child)
{
    this->path = "";
    this->parent = parent;
    this->pathname = child;
}

void File::set(const std::string& path, const std::string& parent, const std::string& child)
{
    this->path = path;
    this->parent = parent;
    this->pathname = child;
}

void File::set(const File& other)
{
    this->set(other.path, other.parent, other.pathname);
}

std::string& File::getPath()
{
    if(path = "") this->makePath();
    return path;
}
    
std::string File::getName()
{
  if(this->pathname.length() == 0) return "";
  size_t found = this->pathname.rfind(separator);
  if (found != string::npos)
    return this->pathname.substr(found);
  return pathname;
}

void File::makePath()
{
    if(parent == "") path = child;
    else
    {
      path = parent + child;
    }
}

File File::getParentFile()
{
  
}

bool File::gotParent()
{
    if(parent == "") return true;
    return false;
}

int64_t File::length ()
{
    
}

void File::list(std::vector<std::string> &relativePath)
{
  
}

void File::listFiles(std::vector<File> &files)
{
  
}

void File::mkdirs()
{
  
}

bool File::deleteFile()
{
  
}

File& File::operator=(const File& other)
{
    this->set(other);
    return this;
}

bool File::exists()
{
    fstream f;
    f.open(getPath().c_str());
    if(f.is_open()) return true;
    return false;
}

