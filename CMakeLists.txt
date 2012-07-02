project(gdx-cpp)

cmake_minimum_required(VERSION 2.8)

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

include(cmake/gdx.cmake)

include_directories(src)

link_directories(${LIBRARY_OUTPUT_PATH})

set(ANDROID_NDK $ENV{ANDROID_NDK})

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --std=gnu++0x")

option(BUILD_BOX2D "Builds Box2D" TRUE)
option(BUILD_AS_SHARED_LIBRARIES "Build libraries as shared libraries instead of static" FALSE)

option(GDX_LOG_DEBUG "Enables the output of debug logs" TRUE)
option(GDX_LOG_INFO "Enables the output of debug logs" FALSE)
option(GDX_LOG_ERROR "Enables the output of debug logs" FALSE)

if (GDX_LOG_DEBUG)
    set(GDX_LOG_LEVEL_DEBUG TRUE)
    set(GDX_LOG_LEVEL_INFO TRUE)
    set(GDX_LOG_LEVEL_ERROR TRUE)
elseif(GDX_LOG_INFO)
    set(GDX_LOG_LEVEL_INFO TRUE)
    set(GDX_LOG_LEVEL_ERROR TRUE)
elseif(GDX_LOG_ERROR)
    set(GDX_LOG_LEVEL_ERROR TRUE)
endif()

CONFIGURE_FILE(src/gdx-cpp/log.hpp.in ${CMAKE_SOURCE_DIR}/src/gdx-cpp/Log.hpp )

if(APPLE)
    message("MacOSX (iOS) found. Setting the backend to IOS")
    SET(GDX_BACKEND_IOS ON)
    SET(GDX_BACKEND_LIB gdx-cpp-backend-ios)
    
    set(BOX2D_BUILD_STATIC TRUE)
    set(BOX2D_BUILD_SHARED FALSE)
elseif (UNIX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -Wall")

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

CONFIGURE_FILE(src/gdx-cpp/gl.hpp.in ${CMAKE_SOURCE_DIR}/src/gdx-cpp/gl.hpp )

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
  if(CMAKE_COMPILER_IS_GNUCXX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -Wdouble-promotion")
  endif()

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



