#include "Log.hpp"

#include <android/log.h>


void gdx::android::Log::log (gdx::Log::LogLevel loglevel, const std::string& tag, const std::string& line, const std::string& file, const char* format, ... ) {
    std::string newTag =  "[" + file.substr(file.find_last_of("/") + 1, file.size()) + ":" + line + "]";
    
    unsigned levelMap[] { ANDROID_LOG_DEBUG, ANDROID_LOG_INFO, ANDROID_LOG_ERROR, ANDROID_LOG_DEFAULT };
    
    va_list list;
    va_start(list, format);
    __android_log_vprint ( levelMap[(unsigned)loglevel], newTag.c_str(),format, list );
    va_end(list);
    
    
    
}
