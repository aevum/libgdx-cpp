#ifndef GDX_CPP_BACKEND_HPP
#define GDX_CPP_BACKEND_HPP

#include <string>

#include "gdx-cpp/ApplicationListener.hpp"

extern "C" void gdxcpp_init(int argc, char** argv);
extern "C" void gdxcpp_create_application(gdx_cpp::ApplicationListener* listener, const std::string& applicationName, int width, int height);

typedef int (*gdx_main)(int, char**);

struct gdxcpp_main_selector {
    static gdx_main selector;
};

#endif // GDX_CPP_BACKEN_HPP