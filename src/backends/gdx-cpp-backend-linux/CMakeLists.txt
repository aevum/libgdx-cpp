project(gdx-cpp-backend-linux)

include_directories(${GDXCPP_INCLUDE_DIR} ${SVG_BACKEND_ANTIGRAIN_INCLUDES})

set(GDX_CPP_BACKEND_LINUX_SRC LinuxApplication.cpp  LinuxOpenALMusic.cpp
LinuxGraphics.cpp LinuxGLU.cpp LinuxSystem.cpp LinuxInput.cpp LinuxFiles.cpp LinuxFileHandle.cpp init.cpp
LinuxOpenALAudio.cpp LinuxOpenALSound.cpp LinuxOgg.cpp LinuxOggInputStream.cpp LinuxOpenALMusic.cpp Log.cpp
)
set(GDX_CPP_BACKEND_LINUX_HEADERS LinuxApplication.hpp  LinuxGraphics.hpp
LinuxFiles.hpp LinuxFileHandle.hpp LinuxGLU.hpp LinuxSystem.hpp LinuxInput.hpp
LinuxOpenALAudio.hpp LinuxOpenALSound.hpp LinuxOgg.hpp LinuxOggInputStream.hpp LinuxOpenALMusic.hpp Log.hpp
)

gdx_setup_target(gdx-cpp-backend-linux STATIC "${GDX_CPP_BACKEND_LINUX_SRC};${GDX_CPP_BACKEND_LINUX_HEADERS}")

target_link_libraries(gdx-cpp-backend-linux openal ogg vorbis vorbisfile SDL pthread)

install(DIRECTORY . DESTINATION include/gdx-cpp/backends/gdx-cpp-backend-linux
          FILES_MATCHING PATTERN "*.hpp")

install(TARGETS gdx-cpp-backend-linux
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)