#include "Log.hpp"

#include <android/log.h>


void gdx::android::Log::debug ( const std::string& tag, const std::string& line, const std::string& file, const char* format, va_list& list ) {
    std::string newTag =  "[" + file.substr(file.find_last_of("/") + 1, file.size()) + ":" + line + "]";
    __android_log_vprint ( ANDROID_LOG_DEBUG, newTag.c_str(),format, list );
}

void gdx::android::Log::error ( const std::string& tag, const std::string& line, const std::string& file, const char* format, va_list& list ) {
    std::string newTag =  "[" + file.substr(file.find_last_of("/") + 1, file.size()) + ":" + line + "]";
    __android_log_vprint ( ANDROID_LOG_ERROR, newTag.c_str(),format, list );
}

void gdx::android::Log::info ( const std::string& tag, const std::string& line, const std::string& file, const char* format, va_list& list ) {
    std::string newTag =  "[" + file.substr(file.find_last_of("/") + 1, file.size()) + ":" + line + "]";
    __android_log_vprint ( ANDROID_LOG_INFO, newTag.c_str(),format, list );
}

