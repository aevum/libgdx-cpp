project(gdx-cpp-box2d-layer)

include_directories(${GDXCPP_INCLUDE_DIR})

file(GLOB GDX_CPP_BOX2D_LAYER_SRC
    Shape.cpp
    PolygonShape.cpp
    Filter.cpp
)
file(GLOB GDX_CPP_BOX2D_LAYER_HEADERS
    Shape.hpp
    PolygonShape.hpp
    Filter.hpp
)


include_directories(${GDXCPP_BOX2D_INCLUDE_DIR})

add_library(gdx-cpp-box2d-layer SHARED ${GDX_CPP_BOX2D_LAYER_SRC} ${GDX_CPP_BOX2D_LAYER_H})