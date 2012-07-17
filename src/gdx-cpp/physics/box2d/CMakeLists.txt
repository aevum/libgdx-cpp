project(gdx-cpp-box2d-layer)

include_directories(${GDXCPP_INCLUDE_DIR})

file(GLOB GDX_CPP_BOX2D_LAYER_SRC Box2DDebugRenderer.cpp)
file(GLOB GDX_CPP_BOX2D_LAYER_HEADERS Box2DDebugRenderer.hpp)

include_directories(${GDXCPP_BOX2D_INCLUDE_DIR})

gdx_setup_target(gdx-cpp-box2d-layer STATIC "${GDX_CPP_BOX2D_LAYER_SRC};${GDX_CPP_BOX2D_LAYER_H}")
add_dependencies(gdx-cpp-box2d-layer Box2D)

install(TARGETS gdx-cpp-box2d-layer ARCHIVE DESTINATION lib LIBRARY DESTINATION lib)