project(gdx-cpp)

cmake_minimum_required(VERSION 2.8)

LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/finders)
set(GDXCPP_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

find_package(STLPort)

include_directories(${STLPORT_INCLUDE_DIR})
include_directories(${GDXCPP_INCLUDE_DIR})

add_subdirectory(src)
