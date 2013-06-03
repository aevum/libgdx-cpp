project(gdx-cpp-backend-emscripten)

include_directories(${GDXCPP_INCLUDE_DIR} ${SVG_BACKEND_ANTIGRAIN_INCLUDES})

set(GDX_CPP_BACKEND_EMSCRIPTEN_SRC EmscriptenApplication.cpp  EmscriptenOpenALMusic.cpp
EmscriptenGraphics.cpp EmscriptenGLU.cpp EmscriptenSystem.cpp EmscriptenInput.cpp EmscriptenFiles.cpp EmscriptenFileHandle.cpp init.cpp
EmscriptenOpenALAudio.cpp EmscriptenOpenALSound.cpp EmscriptenOpenALMusic.cpp Log.cpp
)
set(GDX_CPP_BACKEND_EMSCRIPTEN_HEADERS EmscriptenApplication.hpp  EmscriptenGraphics.hpp
EmscriptenFiles.hpp EmscriptenFileHandle.hpp EmscriptenGLU.hpp EmscriptenSystem.hpp EmscriptenInput.hpp
EmscriptenOpenALAudio.hpp EmscriptenOpenALSound.hpp EmscriptenOpenALMusic.hpp Log.hpp
)

gdx_setup_target(gdx-cpp-backend-emscripten SHARED "${GDX_CPP_BACKEND_EMSCRIPTEN_SRC};${GDX_CPP_BACKEND_EMSCRIPTEN_HEADERS}")

install(DIRECTORY . DESTINATION include/gdx-cpp/backends/gdx-cpp-backend-linux
          FILES_MATCHING PATTERN "*.hpp")

install(TARGETS gdx-cpp-backend-emscripten
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)