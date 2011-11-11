#ifndef GDX_CPP_BACKEND_HPP
#define GDX_CPP_BACKEND_HPP

#include <string>
#include "gdx-cpp/ApplicationListener.hpp"

void init(int argc, char** argv);
void createApplication(gdx_cpp::ApplicationListener* listener, const std::string& applicationName, int width, int height);

typedef int (*gdx_main)(int, char**);

struct main_selector {
    static gdx_main selector;
};

#endif // GDX_CPP_BACKEN_HPP