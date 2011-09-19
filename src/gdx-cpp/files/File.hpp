#ifndef GDX_CPP_FILES_FILE_HPP_
#define GDX_CPP_FILES_FILE_HPP_

#include <cstdio>
#include <string>
#include <vector>

namespace gdx_cpp {
namespace files {

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
    //File(URI uri);
    
    //virtual File& operator=(const File& other);
    
    std::string getName() const;
    std::string getParent() const;
    File getParentFile() const;
    const std::string &getPath() const;
    bool isAbsolute() const;
    std::string getAbsolutePath() const;
    File getAbsoluteFile() const;
    std::string getCanonicalPath() const; //throws IOException
    File getCanonicalFile() const; //throws IOException
    //public URL(); throw MalformedURLException
    //URI toURI()
    //bool canRead();
    //bool canWrite();
    bool exists() const;
    bool isDirectory() const;
    //bool gotParent();
    bool isFile() const; 
    //bool isHidden();
    //int64_t lastModified();
    int64_t length () const;
    //bool createNewFile();  //throw IOException()
    bool deleteFile();
    //void deleteOnExit();
    void list(std::vector<std::string> &relativePath);
    //void list(std::vector<std::string> &relativePath, FilenameFilter filter);
    void listFiles(std::vector< File > &fileList);
    //void listFiles(std::vector<std::string> &relativePath, FilenameFilter filter);
    //void listFiles(FileFilter filter);
    bool mkdir();
    bool mkdirs();
    bool renameTo(const gdx_cpp::files::File& dest);
    //bool setLastModified(int64_t &time);
    //bool setReadOnly();
    //bool setWritable(bool &writable, bool &ownerOnly);
    //bool setWritable(bool &writable);
    //bool setReadable(bool &readable, bool &ownerOnly);
    //bool setReadable(bool &readable);
    //bool setExecutable(bool &executable, bool &ownerOnly);
    //bool setExecutable(bool &executable);
    //bool canExecute();
    //static void listRoots(std::vector<File> &list);
    //int64_t getTotalSpace();
    //int64_t getFreeSpace();
    //int64_t getUsableSpace();
    //static File createTempFile(const std::string &prefix, const std::string &suffix, const File &directory); //throws IOException
    //static File createTempFile(const std::string &prefix, const std::string &suffix); //throws IOException
    //int compareTo(const File &pathname);
    //boolean equals(Object obj);
    //int hashCode();
    std::string toString();
        
private:

    std::string path;
    unsigned int prefixLength;

    File(const std::string& pathname,const int &prefixLength);
    File(const std::string& child, const File &parent);
    //static std::string slashify(const std::string &path, const bool &isDirectory);
    /*
     * // lazy initialization of SecureRandom and temporary file directory
    private static class LazyInitialization {
        static final SecureRandom random = new SecureRandom();

        static final String temporaryDirectory = temporaryDirectory();
        static String temporaryDirectory() {
            return fs.normalize(
                AccessController.doPrivileged(
                    new GetPropertyAction("java.io.tmpdir")));
        }
    }
    */
    //static File generateFile(const std::string &prefix, const std::string &suffix, const File &dir);
    //static bool checkAndCreate(const std::string &filename, SecurityManager &sm);
    //void writeObject(ObjectOutputStream s); //Throws IOException e syncronized
   //void readObject(ObjectInputStream s); //Throws IOException e syncronized throws ClassNotFoundExceptionon
    /* treta loca no final do codigo
     *static {
        sun.misc.SharedSecrets.setJavaIODeleteOnExitAccess(
            new sun.misc.JavaIODeleteOnExitAccess() {
                public void run() {
                    DeleteOnExitHook.hook().run();
                }
            }
        );
    }
    */
  
};

}
}
#endif