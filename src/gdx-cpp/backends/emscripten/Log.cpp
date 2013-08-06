#include "Log.hpp"
#include <stdio.h>
#include <stdarg.h>


void gdx::scripten::Log::log (gdx::Log::LogLevel logLevel, const std::string& tag, const std::string& line, const std::string& file, const char* format, ... ) {
    std::string newTag =  "[" + file.substr(file.find_last_of("/") + 1, file.size()) + ":" + line + "]" + tag + ":" + format + "\n";

    switch(logLevel) {
        case DEBUG:
            newTag = "[DEBUG] " + newTag ;
            break;
        case INFO:
            newTag = "[INFO] " + newTag;
            break;
        case ERROR:
            newTag = "[ERROR] " + newTag;
            break;
        default:
            break;
    }
    
    va_list list;
    va_start(list, format);
    vfprintf(stdout, newTag.c_str(), list);
    fflush(stdout);
}
