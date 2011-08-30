project(gdx-cpp-box2d)

include_directories(${GDXCPP_INCLUDE_DIR})

file(GLOB GDX_CPP_BOX2D_SRC
    Collision/*.cpp Common/*.cpp Dynamics/*.cpp
    Collision/*.c Common/*.c Dynamics/*.c
)
file(GLOB GDX_CPP_BOX2D_LAYER_H
    Collision/*.hpp Common/*.hpp Dynamics/*.hpp
    Collision/*.h Common/*.h Dynamics/*.h
)


add_library(gdx-cpp-box2d SHARED ${GDX_CPP_BOX2D_SRC} ${GDX_CPP_BOX2D_LAYER_H})