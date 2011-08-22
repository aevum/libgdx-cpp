file(GLOB GDX_HEADERS Intersector.hpp)
set(GDX_SRC )

file(GLOB GDX_HEADERS_MATH math/Intersector.hpp)
file(GLOB GDX_SOURCE_MATH math/Intersector.cpp)

file(COPY ${GDX_HEADERS} DESTINATION ${GDXCPP_INCLUDE_DIR}/gdx)
file(COPY ${GDX_HEADERS_MATH} DESTINATION ${GDXCPP_INCLUDE_DIR}/gdx/math)

add_library(gdx-cpp ${GDX_HEADERS} ${GDX_SRC} ${GDX_SOURCE_MATH} ${GDX_HEADERS_MATH})
