#ifndef GDX_CPP_FILES_FILE_HPP_
#define GDX_CPP_FILES_FILE_HPP_

#include <cstdio>
#include <string>
#include <vector>

namespace gdx {

class File
{

public:
    int getPrefixLength() const;

    static char separatorChar;
    static std::string separator;
    static char pathSeparatorChar;
    static std::string pathSeparator;
    
    File();
    File(const std::string& pathname);
    File(const std::string& parent, const std::string& child);
    File(const File &parent, const std::string& child);
    
    std::string getName() const;
    std::string getParent() const;
	std::string extension() const;
	std::string nameWithoutExtension () const;
    File getParentFile() const;
    const std::string &getPath() const;
    bool isAbsolute() const;
    std::string getAbsolutePath() const;
    File getAbsoluteFile() const;
    std::string getCanonicalPath() const; //throws IOException
    File getCanonicalFile() const; //throws IOException
    bool exists() const;
    bool isDirectory() const;
    bool isFile() const; 
    virtual int64_t length () const;
    virtual bool deleteFile();
    void list(std::vector<std::string> &relativePath);
    void listFiles(std::vector< File > &fileList);
    bool mkdir();
    bool mkdirs();
    bool renameTo(const gdx::File& dest);
    std::string toString();
        
private:

    std::string path;
    unsigned int prefixLength;

    File(const std::string& pathname,const int &prefixLength);
    File(const std::string& child, const File &parent);  
};

}
#endif