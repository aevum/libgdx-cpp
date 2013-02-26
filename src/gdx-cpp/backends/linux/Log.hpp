#ifndef LOG_LINUX_HPP
#define LOG_LINUX_HPP

#include <gdx-cpp/Log.hpp>
#include <stdarg.h>
#include <stdio.h>
#include <string>

namespace gdx {
namespace nix {
class Log : public gdx::Log {
public:
    virtual void log( gdx::Log::LogLevel logLevel, const std::string& tag, const std::string& line, const std::string& file, const char* format, ... ) override;
};
}
}

#endif // LOG_LINUX_HPP
