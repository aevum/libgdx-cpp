project(gdx-cpp-backend-ios)

include_directories(${GDXCPP_INCLUDE_DIR} ${SVG_BACKEND_ANTIGRAIN_INCLUDES})

set(GDX_CPP_BACKEND_IOS_SRC init.cpp IosApplication.cpp AppController.mm EAGLView.h
View.mm
IosGL10.hpp
IosGL11.hpp
IosGL20.hpp
IosGLU.hpp
IosSystem.hpp
)
set(GDX_CPP_BACKEND_IOS_HEADERS init.hpp IosApplication.hpp AppController.h EAGLView.mm
	View.h
IosGL10.cpp
IosGL11.cpp
IosGL20.cpp
IosSystem.cpp
)

add_library(gdx-cpp-backend-ios ${GDX_CPP_BACKEND_IOS_SRC} ${GDX_CPP_BACKEND_IOS_HEADERS})
add_dependencies(gdx-cpp-backend-ios gdx-cpp gdx-cpp-agg-svg)

target_link_libraries(gdx-cpp-backend-ios openal vorbis ogg vorbisfile gdx-cpp gdx-cpp-agg-svg)

install(DIRECTORY . DESTINATION include/gdx-cpp/backends/ios
          FILES_MATCHING PATTERN "*.hpp")
