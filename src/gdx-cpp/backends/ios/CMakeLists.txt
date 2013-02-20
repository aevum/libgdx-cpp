project(gdx-cpp-backend-ios)

include_directories(${GDXCPP_INCLUDE_DIR} ${SVG_BACKEND_ANTIGRAIN_INCLUDES})

set(GDX_CPP_BACKEND_IOS_SRC 
init.mm
IosApplication.mm
AppController.mm
IosGdxViewController.mm
EAGLView.mm
IosGraphics.cpp
IosFileHandle.mm
IosFiles.cpp
IosSystem.mm
IosAudio.mm
IosInput.cpp
IosOpenALMusic.cpp
IosOpenALSound.cpp
IosOpenALAudio.mm
)
set(GDX_CPP_BACKEND_IOS_HEADERS init.hpp IosApplication.hpp AppController.h 
EAGLView.h
IosGdxViewController.h
IosGLU.hpp
IosSystem.hpp
IosGraphics.hpp
IosFileHandle.hpp
IosFiles.hpp
IosInput.hpp
IosAudio.hpp
IosOpenALMusic.hpp
IosOpenALSound.hpp
IosOpenALAudio.hpp
)

gdx_setup_target(gdx-cpp-backend-ios STATIC "${GDX_CPP_BACKEND_IOS_SRC};${GDX_CPP_BACKEND_IOS_HEADERS}")

target_link_libraries(gdx-cpp-backend-ios gdx-cpp gdx-cpp-agg-svg)
add_dependencies(gdx-cpp-backend-ios gdx-cpp gdx-cpp-agg-svg)
gdx_add_ios_framework(gdx-cpp-backend-ios OpenAL "")

install(DIRECTORY . DESTINATION include/gdx-cpp/backends/ios
          FILES_MATCHING PATTERN "*.h*")
