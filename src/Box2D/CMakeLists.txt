project(gdx-cpp-box2d)

file(GLOB GDX_CPP_BOX2D_SRC
    Collision/*.cpp Collision/Shapes/*.cpp Common/*.cpp Dynamics/*.cpp Dynamics/Contacts/*.cpp Dynamics/Joints/*.cpp
    Collision/*.c Common/*.c Dynamics/*.c 
)
file(GLOB GDX_CPP_BOX2D_LAYER_H
    Collision/*.hpp Collision/Shapes/*.h Common/*.hpp Dynamics/*.hpp Dynamics/Contacts/*.hpp Dynamics/Joints/*.hpp
    Collision/*.h Common/*.h Dynamics/*.h
)

add_library(gdx-cpp-box2d SHARED ${GDX_CPP_BOX2D_SRC} ${GDX_CPP_BOX2D_LAYER_H})

install(DIRECTORY . DESTINATION include/Box2D
          FILES_MATCHING PATTERN "*.h")

install(TARGETS gdx-cpp-box2d
    LIBRARY DESTINATION lib)