#ifndef GDX_CPP_FILES_FILE_HPP_
#define GDX_CPP_FILES_FILE_HPP_

#include <cstdio>
#include <string>

namespace gdx_cpp {
namespace files {

class File
{

public:
    File();
    File(const std::string& fileName);
    File(const std::string& parent, const std::string& child);
    File(const File &parent, const std::string& child);
    void set(const std::string& fileName);
    void set(const std::string& parent, const std::string& child);
    void set(const File& other);
    virtual File& operator=(const File& other);
    std::string &getPath();
    std::string getName();
    File getParentFile();
    void makePath();
    bool exists();
    bool isDirectory();
    bool gotParent();
    int64_t length ();
    void list(std::vector<std::string> &relativePath);
    void listFiles(std::vector<File> &files);
    void mkdirs();
    bool deleteFile();

private:
    std::string path;
    std::string child;
    std::string parent;
    static std::string pathSeparator;   //The system-dependent path-separator character, represented as a string for convenience.
    static char pathSeparatorChar;    //The system-dependent path-separator character.
    static std::string separator;    //The system-dependent default name-separator character, represented as a string for convenience.
    static char     separatorChar; //The system-dependent default name-separator character.
};

}
}
#endif