#ifndef GDX_CPP_LOG
#define GDX_CPP_LOG

#include <gdx-cpp/config.hpp>

#define S(x) #x
#define S_(x) S(x)
#define S_LINE_ S_(__LINE__)

#ifdef GDX_LOG_LEVEL_DEBUG
#define gdx_log_debug(tag, format, ...) gdx::internal_log_debug(tag, S_LINE_, __FILE__, format, ##__VA_ARGS__);
#else
#define gdx_log_debug(tag, format, ...) ((void) 0)
#endif

#ifdef GDX_LOG_LEVEL_INFO
#define gdx_log_info(tag, format, ...) gdx::internal_log_info(tag, S_LINE_, __FILE__, format, ##__VA_ARGS__);
#else
#define gdx_log_info(tag, format, ...) ((void) 0)
#endif

#ifdef GDX_LOG_LEVEL_ERROR
#define gdx_log_error(tag, format, ...) gdx::internal_log_error(tag, S_LINE_, __FILE__, format,  ##__VA_ARGS__);
#else
#define gdx_log_error(tag, format, ...) ((void) 0)
#endif

#include <string>
namespace gdx {
class Log {
public:
    virtual void debug ( const std::string& tag, const std::string& line, const std::string& file, const char* format, va_list& list ) = 0;
    virtual void error ( const std::string& tag, const std::string& line, const std::string& file, const char* format, va_list& list ) = 0;
    virtual void info ( const std::string& tag, const std::string& line, const std::string& file, const char* format, va_list& list ) = 0;
    
    virtual ~Log() { }
};
}

#endif // GDX_CPP_LOG
