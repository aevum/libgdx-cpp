project(gdx-cpp)

cmake_minimum_required(VERSION 2.8)

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
set(GDX_BINARY_ROOT_DIR ${PROJECT_BINARY_DIR})

LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/finders)

if (UNIX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -Wall")
    if (ANDROID_NDK)
        SET(USE_LINUX FALSE)
    else()
        SET(USE_LINUX TRUE)
    endif()
endif()

option(BUILD_BACKEND_LINUX "Builds the linux backend for gdx-cpp" ${USE_LINUX})
option(BUILD_BACKEND_IOS "Builds the ios backend for gdx-cpp" MACOSX)
option(BUILD_BACKEND_ANDROID "Builds the android backend for gdx-cpp" ANDROID_NDK)
option(BUILD_BACKEND_WINDOWS "Builds the windows backend for gdx-cpp" WIN32)

option(BUILD_BOX2D "Builds Box2D" TRUE)

option(BUILD_GDX_TESTS "Builds(tries) all libgdx tests" TRUE)
set(GENERATED_APPLICATION_TYPE "EXECUTABLE")

include_directories(src)
add_subdirectory(src/gdx-cpp)

SET(SVG_BACKEND_ANTIGRAIN TRUE CACHE BOOL "Build the antigrain's svg backend")

if(SVG_BACKEND_ANTIGRAIN)
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/agg/include ${CMAKE_CURRENT_SOURCE_DIR}/src/agg/svg)
    add_subdirectory(src/agg)
endif()

if (BUILD_BACKEND_LINUX)
  OPTION(BUILD_LINUX_GRAPHICS_OPENGL "Builds the linux backend with OpenGL" FALSE)
  OPTION(BUILD_LINUX_GRAPHICS_OPENGLES "Builds the linux backend with OpenGL ES" TRUE)
  
  if (BUILD_LINUX_GRAPHICS_OPENGL)
    set(GdxCpp_BUILD_GRAPHICS_OPENGL TRUE)
    add_definitions(-DLIBGDX_CPP_BUILD_OPENGL_INSTEAD_GLES)
  endif()

  if(CMAKE_COMPILER_IS_GNUCXX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -Wdouble-promotion")    
  endif()

  add_subdirectory(src/backends/gdx-cpp-backend-linux)
endif()

if (BUILD_BOX2D)
    set(BOX2D_BUILD_SHARED TRUE)
    set(BOX2D_INSTALL TRUE)
    add_subdirectory(src/Box2D)
    add_subdirectory(src/gdx-cpp/physics/box2d)
endif()

if (BUILD_BACKEND_IOS)
    list(APPEND ACTIVE_BACKENDS IOS)
    add_subdirectory(src/backends/ios)
endif()

if (BUILD_BACKEND_ANDROID)
    set(GENERATED_APPLICATION_TYPE "SHARED_LIB")
    SET(ANDROID_NDK "" CACHE PATH "Were the android NDK is located")

    add_subdirectory(src/backends/gdx-cpp-backend-android)    
endif()

if (BUILD_BACKEND_WINDOWS)
    add_subdirectory(src/backends/windows)
endif()

if (BUILD_GDX_TESTS)
    add_subdirectory(src/tests)
endif()

install(FILES cmake/finders/FindGdxCpp.cmake
        DESTINATION share/cmake-2.8/Modules)

