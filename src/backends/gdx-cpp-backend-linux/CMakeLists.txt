project(gdx-cpp-backend-linux)

include_directories(${GDXCPP_INCLUDE_DIR})

set(GDX_CPP_BACKEND_LINUX_SRC LinuxApplication.cpp LinuxGL10.cpp
LinuxGraphics.cpp LinuxGL20.cpp LinuxGL11.cpp LinuxSystem.cpp LinuxInput.cpp LinuxFiles.cpp LinuxFileHandle.cpp init.cpp
LinuxOpenALAudio.cpp
)
set(GDX_CPP_BACKEND_LINUX_HEADERS LinuxApplication.hpp LinuxGL10.hpp LinuxGraphics.hpp
LinuxGL20.hpp LinuxFiles.hpp LinuxFileHandle.hpp LinuxGL11.hpp LinuxGLU.hpp LinuxSystem.hpp LinuxInput.hpp
LinuxOpenALAudio.hpp
)

add_library(gdx-cpp-backend-linux SHARED ${GDX_CPP_BACKEND_LINUX_SRC} ${GDX_CPP_BACKEND_LINUX_HEADERS})
add_dependencies(gdx-cpp-backend-linux gdx-cpp)