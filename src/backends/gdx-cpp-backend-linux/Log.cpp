#include "Log.hpp"
#include <stdio.h>
#include <stdarg.h>


void gdx::nix::Log::debug ( const std::string& tag, const std::string& line, const std::string& file, const char* format, va_list& list ) {
    std::string newTag =  "[" + file + "/" + line + "]" + tag + ":" + format + "\n";

    vfprintf(stdout, newTag.c_str(), list);
    fflush(stdout);
}

void gdx::nix::Log::error ( const std::string& tag, const std::string& line, const std::string& file, const char* format, va_list& list ) {
    std::string newTag =  "[" + file + "/" + line + "]" + tag + ":" + format + "\n";

    vfprintf(stderr, newTag.c_str(), list);
    fflush(stderr);
}

void gdx::nix::Log::info ( const std::string& tag, const std::string& line, const std::string& file, const char* format, va_list& list) {
    std::string newTag = "[" + file + "/" + line + "]" + tag + ":" + format + "\n";

    vfprintf(stdout, newTag.c_str(), list);
    fflush(stdout);
}

