project(gdx-cpp)

cmake_minimum_required(VERSION 2.8)

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

include(cmake/gdx.cmake)

include_directories(src)

link_directories(${LIBRARY_OUTPUT_PATH})

set(ANDROID_NDK $ENV{ANDROID_NDK})

option(BUILD_BOX2D "Builds Box2D" TRUE)
option(BUILD_AS_SHARED_LIBRARIES "Build libraries as shared libraries instead of static" FALSE)

if(APPLE)
    message("MacOSX (iOS) found. Setting the backend to IOS")
    SET(GDX_BACKEND_IOS ON)
    SET(GDX_BACKEND_LIB gdx-cpp-backend-ios)
    
    set(BOX2D_BUILD_STATIC TRUE)
    set(BOX2D_BUILD_SHARED FALSE)
elseif (UNIX)
    if (ANDROID_NDK)        
        message("ANDROID_NDK Found. Setting the backend to ANDROID")

        SET(GDX_BACKEND_ANDROID ON)
        SET(GDX_BACKEND_LIB gdx-cpp-backend-android)
        set(BOX2D_BUILD_STATIC FALSE)
        set(BOX2D_BUILD_SHARED TRUE)        
    else()
        message("Linux found. Setting the backend to LINUX")
        add_definitions(-DLIBGDX_CPP_BUILD_OPENGL_INSTEAD_GLES)        

        SET(GDX_BACKEND_LINUX ON)
        SET(GDX_BACKEND_LIB gdx-cpp-backend-linux)

        if (BUILD_AS_SHARED_LIBRARIES)
            set(BOX2D_BUILD_STATIC FALSE)
            set(BOX2D_BUILD_SHARED TRUE)
        else()
            set(BOX2D_BUILD_STATIC TRUE)
            set(BOX2D_BUILD_SHARED FALSE)
        endif()
    endif()

elseif(WIN32)
    message("Win32 found. Setting the backend to WIN32")
    SET(GDX_BACKEND_WIN32 ON)
    SET(GDX_BACKEND_LIB gdx-cpp-backend-win32)
endif()

CONFIGURE_FILE(src/gdx-cpp/gl.hpp.in ${CMAKE_CURRENT_SOURCE_DIR}/src/gdx-cpp/gl.hpp )
CONFIGURE_FILE(src/gdx-cpp/config.hpp.in ${CMAKE_CURRENT_SOURCE_DIR}/src/gdx-cpp/config.hpp )

if(CMAKE_COMPILER_IS_GNUCXX)
    # get gnu compiler version number
    exec_program(${CMAKE_C_COMPILER} ARGS --version OUTPUT_VARIABLE _gcc_version_info)

    string (REGEX MATCH " [34]\\.[0-9]" _gcc_version "${_gcc_version_info}")
    string(REGEX REPLACE "[^0-9]*([0-9]+)\\.[0-9]+.*" "\\1" gcc_major_vers "${_gcc_version}")
    string(REGEX REPLACE "[^0-9]*[0-9]+\\.([0-9]+).*" "\\1" gcc_minor_vers "${_gcc_version}")
    # g++' -Wdouble-promotion needs at least version 4.6
    
    if(${gcc_major_vers} LESS 4 AND ${gcc_minor_vers} LESS 6)
        message(FATAL_ERROR "gdx++ requires a gcc that's newer than 4.5 to fully support the new c++11 standard. Please upgrade your ndk to r8b or newer if using android.")
    endif()
    
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wreorder")
endif()

if (BUILD_BOX2D)
    set(BOX2D_INSTALL TRUE)

    add_subdirectory(src/Box2D)
    add_subdirectory(src/gdx-cpp/physics/box2d)
endif()

if (GDX_BACKEND_IOS)
    add_subdirectory(src/backends/gdx-cpp-backend-ios)

    SET(BUILD_AGG TRUE)
elseif(GDX_BACKEND_ANDROID)
    add_subdirectory(src/backends/gdx-cpp-backend-android)
#     SET(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} --allow-shlib-undefined")
    SET(CMAKE_SHARED_LINKER_FLAGS -Wl,--allow-shlib-undefined)
    SET(BUILD_AGG TRUE)
elseif(GDX_BACKEND_WIN32)
    add_subdirectory(src/backends/windows)
elseif(GDX_BACKEND_LINUX)
  SET(BUILD_AGG TRUE)
  add_subdirectory(src/backends/gdx-cpp-backend-linux)
endif()

if (BUILD_AGG)
  include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/agg/include ${CMAKE_CURRENT_SOURCE_DIR}/src/agg/svg)
  add_subdirectory(src/agg)
endif()

add_subdirectory(src/gdx-cpp)

install(FILES cmake/finders/FindGdxCpp.cmake
        DESTINATION share/gdx/cmake)

install(FILES cmake/gdx.cmake
        DESTINATION share/gdx/cmake)



