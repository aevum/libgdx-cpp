project(gdx-cpp)

cmake_minimum_required(VERSION 2.8)

LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/finders)
set(GDXCPP_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

option(BUILD_BACKEND_LINUX "Builds the linux backend for gdx-cpp" ${UNIX})
option(BUILD_BACKEND_IOS "Builds the ios backend for gdx-cpp" FALSE)
option(BUILD_BACKEND_ANDROID "Builds the android backend for gdx-cpp" FALSE)
option(BUILD_BACKEND_WINDOWS "Builds the windows backend for gdx-cpp" ${WIN32})

option(BUILD_TESTS "Builds(tries) all libgdx tests" TRUE)

include_directories(src)
add_subdirectory(src/gdx-cpp)

if (BUILD_BACKEND_LINUX)
  set(GDX_CPP_BACKEND_LINUX_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/src/backends)
  add_subdirectory(src/backends/linux)
endif()

if (BUILD_BACKEND_IOS)
    add_subdirectory(src/backends/ios)
endif()

if (BUILD_BACKEND_ANDROID)
    add_subdirectory(src/backends/android)
endif()

if (BUILD_BACKEND_WINDOWS)
    add_subdirectory(src/backends/windows)
endif()

if (BUILD_TESTS)
    add_subdirectory(src/tests)
endif()
