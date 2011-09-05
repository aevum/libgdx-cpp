#include "FileHandleStream.hpp"
#include <cstdio>
#include <cassert>
#include <gdx-cpp/implementation/System.hpp>
#include <gdx-cpp/Gdx.hpp>
#include <stdexcept>

using namespace gdx_cpp::files;

int File::getPrefixLength()
{
    return prefixLength;
}

const char separatorChar = gdx_cpp::Gdx::system->getSeparator();
const std::string separator = std::string("") + separatorChar;
const char pathSeparatorChar = gdx_cpp::Gdx::system->getPathSeparator();
const std::string pathSeparator = std::string("") + pathSeparatorChar;

File::File()  //USADO PARA FAZER COISA FEIA(GAMBS)
  : path("")
{
}

File::File(const std::string& pathname, const int &prefixLength)
{
    this->path = pathname;
    this->prefixLength = prefixLength;
}

File::File(const std::string& child, const File &parent)
{
    //assert(parent.path != null);
    assert(parent.path != "");
    this->path = gdx_cpp::Gdx::system->resolve(parent.path, child);
    this->prefixLength = parent.prefixLength;
}


File::File(const std::string& pathname)
{
    this->path = gdx_cpp::Gdx::system->normalize(pathname);
    this->prefixLength = gdx_cpp::Gdx::system->prefixLength(this->path);
}

File::File(const std::string& parent, const std::string& child)
{
    if(parent == "")
    {
        this->path = gdx_cpp::Gdx::system->resolve(gdx_cpp::Gdx::system->getDefaultParent(), gdx_cpp::Gdx::system->normalize(child));
    }
    else
    {
        this->path = gdx_cpp::Gdx::system->resolve(gdx_cpp::Gdx::system->normalize(parent), gdx_cpp::Gdx::system->normalize(child));
    }
    this->prefixLength = gdx_cpp::Gdx::system->prefixLength(this->path);
}

File::File(const File &parent, const std::string& child)
{
    if(parent.path == ""){
        this->path = gdx_cpp::Gdx::system->resolve(gdx_cpp::Gdx::system->getDefaultParent(), gdx_cpp::Gdx::system->normalize(child));
    }
    else{
        this->path = gdx_cpp::Gdx::system->resolve(parent.path, gdx_cpp::Gdx::system->normalize(child));
    }
    this->prefixLength = gdx_cpp::Gdx::system->prefixLength(this->path);
}

//File(URI uri);
//virtual File& operator=(const File& other);

std::string File::getName() const
{
    int index = path.rfind(separatorChar);
    if(index == path.npos || index < prefixLength) return path.substr(prefixLength);
    return path.substr(index + 1);
}

std::string File::getParent()
{
    int index = path.rfind(separatorChar);
    if(index == path.npos) return "";   //O RETORNO EH GAMBS
    if (index < prefixLength){
        if ((prefixLength > 0) && (path.length() > prefixLength))
            return path.substr(0, prefixLength);
    }
    return path.substr(0, index);
}

File File::getParentFile()
{
    std::string p = this->getParent();
    if(p == "") return File();            //GAMBS
    return File(p, this->prefixLength);
}

const std::string &File::getPath()
{
    return path;
}

bool File::isAbsolute()
{
    return gdx_cpp::Gdx::system->isAbsolute(*this);
}

std::string File::getAbsolutePath()
{
    return gdx_cpp::Gdx::system->resolve(*this);
}

File File::getAbsoluteFile()
{
    std::string absPath = getAbsolutePath();
    return File(absPath, gdx_cpp::Gdx::system->prefixLength(absPath));
}

std::string File::getCanonicalPath() //throws IOException
{
    std::string p = gdx_cpp::Gdx::system->resolve(*this);
    return gdx_cpp::Gdx::system->canonicalize(p);
}

File File::getCanonicalFile() //throws IOException
{
    std::string canonPath = getCanonicalPath();
    int prefix = gdx_cpp::Gdx::system->prefixLength(canonPath);
    return File(canonPath, prefix);
}
//public URL(); throw MalformedURLException
//URI toURI()
//bool canRead();
//bool canWrite();

bool File::exists()
{
    gdx_cpp::Gdx::system->checkRead(path);
    return ((gdx_cpp::Gdx::system->getBooleanAttributes(*this) & gdx_cpp::Gdx::system->BA_DIRECTORY) != 0);
}

bool File::isDirectory()
{
    gdx_cpp::Gdx::system->checkRead(path);
    return ((gdx_cpp::Gdx::system->getBooleanAttributes(*this) & gdx_cpp::Gdx::system->BA_DIRECTORY) != 0);
}

//bool gotParent();

bool File::isFile()
{
    gdx_cpp::Gdx::system->checkRead(path);
    return ((gdx_cpp::Gdx::system->getBooleanAttributes(*this) & gdx_cpp::Gdx::system->BA_REGULAR) != 0);
}

//bool isHidden();
//int64_t lastModified();

int64_t File::length ()
{
    gdx_cpp::Gdx::system->checkRead(path);
    return gdx_cpp::Gdx::system->getLength(*this);
}

//bool createNewFile();  //throw IOException()

bool File::deleteFile()
{
    gdx_cpp::Gdx::system->checkDelete(path);
    return gdx_cpp::Gdx::system->deleteFile(*this);
}

//void deleteOnExit();

void File::list(std::vector<std::string> &relativePaths)
{
    gdx_cpp::Gdx::system->checkRead(path);
    gdx_cpp::Gdx::system->list(*this, relativePaths);
}

//void list(std::vector<std::string> &relativePath, FilenameFilter filter);

void File::listFiles(std::vector<File> &fileList)
{
    std::vector<std::string> ss;
    list(ss);
    if(ss.empty())
    {
        fileList.resize(0);
        return;
    }
    int n = ss.size();
    fileList.resize(n);
    for(int i = 0; i<n; i++){
      fileList[i] = File(ss[i], *this);
    }
    return;
}

//void listFiles(std::vector<std::string> &relativePath, FilenameFilter filter);
//void listFiles(FileFilter filter);

bool File::mkdir()
{
    gdx_cpp::Gdx::system->checkWrite(path);
    return gdx_cpp::Gdx::system->createDirectory(*this);
}

bool File::mkdirs()
{
    if(exists()) return false;
    if(mkdir()) return true;
    File canonFile;
    try{
        canonFile = getCanonicalFile();
    }
    catch (std::runtime_error e)
    {
        return false;
    }
    File parent = canonFile.getParentFile();
    return (parent.getPath() != "" && (parent.mkdirs() || parent.exists()) && canonFile.mkdir()); //GAMBS NAO SABIA O QUE FAZER

}

bool File::renameTo(const File &dest)
{
    gdx_cpp::Gdx::system->checkWrite(path);
    gdx_cpp::Gdx::system->checkWrite(dest.path);
    return gdx_cpp::Gdx::system->rename(*this, dest);
}

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

std::string File::toString()
{
    return getPath();
}



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
