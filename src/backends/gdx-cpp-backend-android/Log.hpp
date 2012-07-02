#ifndef LOG_HPP
#define LOG_HPP

#include <gdx-cpp/Log.hpp>
namespace gdx {
namespace android {
class Log : public gdx::Log{
public:
    virtual void debug ( const std::string& tag, const std::string& line, const std::string& file, const char* format, va_list& list );
    virtual void error ( const std::string& tag, const std::string& line, const std::string& file, const char* format, va_list& list );
    virtual void info ( const std::string& tag, const std::string& line, const std::string& file, const char* format, va_list& list );
};
}
}

#endif // LOG_HPP
