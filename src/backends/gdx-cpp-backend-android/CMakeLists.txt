project(gdx-cpp-backend-android)

include_directories(${GDXCPP_INCLUDE_DIR} ${SVG_BACKEND_ANTIGRAIN_INCLUDES})

file(GLOB ANDROID_SOURCES *.cpp *.hpp)
add_library(gdx-cpp-backend-android ${ANDROID_SOURCES})

add_dependencies(gdx-cpp-backend-android gdx-cpp gdx-cpp gdx-cpp-agg-svg)