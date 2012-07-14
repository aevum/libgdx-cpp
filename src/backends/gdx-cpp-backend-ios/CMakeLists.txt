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
)

gdx_setup_library_target(gdx-cpp-backend-ios STATIC "${GDX_CPP_BACKEND_IOS_SRC};${GDX_CPP_BACKEND_IOS_HEADERS}")
add_dependencies(gdx-cpp-backend-ios gdx-cpp gdx-cpp-agg-svg)

install(DIRECTORY . DESTINATION include/gdx-cpp/backends/ios
          FILES_MATCHING PATTERN "*.hpp")
