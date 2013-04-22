#ifndef GDX_CPP_LOG
#define GDX_CPP_LOG

#include <gdx-cpp/utils/ScopedGuard.hpp>
#include <string>
#include <stdexcept>

#define GDX_TO_STRING_MACRO(x) #x
#define GDX_TO_STRING_MACRO_(x) GDX_TO_STRING_MACRO(x)
#define GDX_TO_STRING_MACRO_LINE_ GDX_TO_STRING_MACRO_(__LINE__)

#ifdef GDX_LOG_LEVEL_DEBUG
#define gdx_log_debug(tag, format, ...) gdx::log->log(gdx::Log::LogLevel::DEBUG, tag, GDX_TO_STRING_MACRO_LINE_, __FILE__, format, ##__VA_ARGS__)
#else
#define gdx_log_debug(tag, format, ...) ((void) 0)
#endif

#ifdef GDX_LOG_LEVEL_INFO
#define gdx_log_info(tag, format, ...) gdx::log->log(gdx::Log::LogLevel::INFO, tag, GDX_TO_STRING_MACRO_LINE_, __FILE__, format, ##__VA_ARGS__)
#else
#define gdx_log_info(tag, format, ...) ((void) 0)
#endif

#ifdef GDX_LOG_LEVEL_ERROR
#define gdx_log_error(tag, format, ...) do { gdx::log->log(gdx::Log::LogLevel::ERROR, tag, GDX_TO_STRING_MACRO_LINE_, __FILE__, format,  ##__VA_ARGS__); throw std::runtime_error("gdx runtime error, see the error output for detail"); } while (false)
#else
#define gdx_log_error(tag, format, ...) throw std::runtime_error("gdx runtime error, see the error output for detail");
#endif

#define gdx_log(logLevel, tag, format, ...) do { gdx::log->log(logLevel, tag, GDX_TO_STRING_MACRO_LINE_, __FILE__, format,  ##__VA_ARGS__); } while (false)


struct RuntimeLogErrorExecutor {
    void operator()() const {         
         throw std::runtime_error("gdx runtime error, see the error output for detail");
    }
};

namespace gdx {
class Log {
public:
    enum LogLevel {
        DEBUG,
        INFO,
        ERROR,
        OTHER
    };

    virtual void log(LogLevel log_level, const std::string& tag, const std::string& line, const std::string& file, const char* format, ...) = 0;
    virtual ~Log() { }
};
}

#endif // GDX_CPP_LOG
