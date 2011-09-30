project(gdx-cpp-box2d-layer)

include_directories(${GDXCPP_INCLUDE_DIR})

file(GLOB GDX_CPP_BOX2D_LAYER_SRC Box2DDebugRenderer.cpp)
file(GLOB GDX_CPP_BOX2D_LAYER_HEADERS Box2DDebugRenderer.hpp)

include_directories(${GDXCPP_BOX2D_INCLUDE_DIR})

add_library(gdx-cpp-box2d-layer ${GDX_CPP_BOX2D_LAYER_SRC} ${GDX_CPP_BOX2D_LAYER_H})
add_dependencies(gdx-cpp-box2d-layer gdx-cpp-box2d)