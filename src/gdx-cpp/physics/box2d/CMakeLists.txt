project(gdx-cpp-box2d-layer)

include_directories(${GDXCPP_INCLUDE_DIR})

file(GLOB GDX_CPP_BOX2D_LAYER_SRC ManifoldPoint.cpp
#     Shape.cpp
#     PolygonShape.cpp
#     Filter.cpp
#     CircleShape.cpp
#     Fixture.cpp
#     FixtureDef.cpp
#     MassData.cpp
#     Transform.cpp
#     Joint.cpp
#     JointDef.cpp
#     JointEdge.cpp
#     WorldManifold.cpp
#     Contact.cpp
#      BodyDef.cpp
#      Body.cpp
#      World.cpp
# joints/*.cpp
*.cpp
)
file(GLOB GDX_CPP_BOX2D_LAYER_HEADERS
#     Shape.hpp
#     PolygonShape.hpp
#     Filter.hpp
#     CircleShape.hpp
#     Fixture.hpp
#     FixtureDef.hpp
#     MassData.hpp
#     Transform.hpp
#     Joint.hpp
#     JointDef.hpp
#     JointEdge.hpp
#     WorldManifold.hpp
#     Contact.hpp
#     BodyDef.hpp
#     Body.hpp
#       World.hpp
# joints/*.hpp
*.hpp
)


include_directories(${GDXCPP_BOX2D_INCLUDE_DIR})

add_library(gdx-cpp-box2d-layer SHARED ${GDX_CPP_BOX2D_LAYER_SRC} ${GDX_CPP_BOX2D_LAYER_H})