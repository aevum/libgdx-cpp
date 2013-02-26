#ifndef LOG_HPP
#define LOG_HPP

#include <gdx-cpp/Log.hpp>
namespace gdx {
namespace android {
class Log : public gdx::Log{
public:
    virtual void log (gdx::Log::LogLevel loglevel, const std::string& tag, const std::string& line, const std::string& file, const char* format, ...) override;
};
}
}

#endif // LOG_HPP
