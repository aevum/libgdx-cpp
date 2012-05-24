project(gdx-cpp)

cmake_minimum_required(VERSION 2.8)

include(cmake/gdx.cmake)

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

include_directories(src)

link_directories(${LIBRARY_OUTPUT_PATH})

set(ANDROID_NDK $ENV{ANDROID_NDK})

option(BUILD_BOX2D "Builds Box2D" TRUE)
option(BUILD_AS_SHARED_LIBRARIES "Build libraries as shared libraries instead of static" FALSE)

if(APPLE)
    message("MacOSX (iOS) found. Setting the backend to IOS")
    SET(GDX_BACKEND IOS)
    SET(GDX_BACKEND_LIB gdx-cpp-backend-ios)

    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/agg/include ${CMAKE_CURRENT_SOURCE_DIR}/src/agg/svg)
    add_subdirectory(src/agg)

    set(BOX2D_BUILD_STATIC TRUE)
    set(BOX2D_BUILD_SHARED FALSE)
elseif (UNIX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -Wall")

    if (ANDROID_NDK)        
        message("ANDROID_NDK Found. Setting the backend to ANDROID")

        SET(GDX_BACKEND ANDROID)
        SET(GDX_BACKEND_LIB gdx-cpp-backend-android)
        set(BOX2D_BUILD_STATIC FALSE)
        set(BOX2D_BUILD_SHARED TRUE)        
    else()
        message("Linux found. Setting the backend to LINUX")
        set(LIBGDX_CPP_BUILD_OPENGL_INSTEAD_GLES ON)        

        SET(GDX_BACKEND LINUX)
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
    SET(GDX_BACKEND WIN32)
    SET(GDX_BACKEND_LIB gdx-cpp-backend-win32)
endif()

CONFIGURE_FILE( ${CMAKE_SOURCE_DIR}/src/gdx-cpp/gl.hpp.in ${CMAKE_SOURCE_DIR}/src/gdx-cpp/gl.hpp )

if (BUILD_BOX2D)
    set(BOX2D_INSTALL TRUE)

    add_subdirectory(src/Box2D)
    add_subdirectory(src/gdx-cpp/physics/box2d)
endif()

if (${GDX_BACKEND} STREQUAL "IOS")
    add_subdirectory(src/backends/gdx-cpp-backend-ios)
    SET(BUILD_AGG TRUE)
elseif(${GDX_BACKEND} STREQUAL "ANDROID")
    add_subdirectory(src/backends/gdx-cpp-backend-android)

    SET(BUILD_AGG TRUE)
elseif(${GDX_BACKEND} STREQUAL "WIN32")
    add_subdirectory(src/backends/windows)
elseif(${GDX_BACKEND} STREQUAL "LINUX")
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



