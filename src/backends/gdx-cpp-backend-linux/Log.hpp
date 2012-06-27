#ifndef LOG_LINUX_HPP
#define LOG_LINUX_HPP

#include <gdx-cpp/Log.hpp>
namespace gdx {
namespace nix {
class Log : public gdx::Log{
public:
    virtual void debug ( const std::string& tag, const std::string& line, const std::string& file, const char* format, ... );
    virtual void error ( const std::string& tag, const std::string& line, const std::string& file, const char* format, ... );
    virtual void info ( const std::string& tag, const std::string& line, const std::string& file, const char* format, ... );
};
}
}

#endif // LOG_LINUX_HPP
