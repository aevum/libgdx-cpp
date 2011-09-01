project(gdx-cpp-backend-linux)

include_directories(${GDXCPP_INCLUDE_DIR})

set(GDX_CPP_BACKEND_LINUX_SRC LinuxApplication.cpp LinuxGL10.cpp
LinuxGraphics.cpp LinuxGL20.cpp LinuxGL11.cpp LinuxSystem.cpp)
set(GDX_CPP_BACKEND_LINUX_HEADERS LinuxApplication.hpp LinuxGL10.hpp LinuxGraphics.hpp
LinuxGL20.hpp LinuxGL11.hpp LinuxGLU.hpp LinuxSystem.hpp)

add_library(gdx-cpp-backend-linux SHARED ${GDX_CPP_BACKEND_LINUX_SRC} ${GDX_CPP_BACKEND_LINUX_HEADERS})
add_dependencies(gdx-cpp-backend-linux gdx-cpp)