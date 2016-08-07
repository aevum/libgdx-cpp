project(gdx-cpp)

cmake_minimum_required(VERSION 2.8)

include(cmake/gdx.cmake)
include(cmake/cotire.cmake)

set(ANDROID_NDK $ENV{ANDROID_NDK})

initialize_gdx()

include_directories(src)

link_directories(${LIBRARY_OUTPUT_PATH})

option(BUILD_BOX2D "Builds Box2D" TRUE)
option(BUILD_AS_SHARED_LIBRARIES "Build libraries as shared libraries instead of static" FALSE)

if(CMAKE_COMPILER_IS_GNUCXX)
    # get gnu compiler version number
    execute_process(COMMAND ${CMAKE_C_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)
    # g++' -Wdouble-promotion needs at least version 4.6
    if (GCC_VERSION VERSION_LESS 4.6)
        message(FATAL_ERROR "gdx++ requires a gcc that's newer than 4.6 to fully support the new c++11 standard. Please upgrade your ndk to r8b or newer if using android.")
    endif()
    # SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wreorder")
endif()

# SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wreorder")

if (BUILD_BOX2D)
    set(BOX2D_INSTALL TRUE)

    add_subdirectory(src/Box2D)
    add_subdirectory(src/gdx-cpp/physics/box2d)
endif()

if (GDX_BACKEND_IOS)
    add_subdirectory(src/gdx-cpp/backends/ios)
    SET(BUILD_AGG TRUE)
elseif(GDX_BACKEND_ANDROID)
    add_subdirectory(src/gdx-cpp/backends/android)
    SET(CMAKE_SHARED_LINKER_FLAGS -Wl,--allow-shlib-undefined)
    SET(BUILD_AGG TRUE)
elseif(GDX_BACKEND_WIN32)
    add_subdirectory(src/gdx-cpp/backends/windows)
elseif(GDX_BACKEND_LINUX)
  SET(BUILD_AGG TRUE)
  add_subdirectory(src/gdx-cpp/backends/linux)
elseif(GDX_BACKEND_EMSCRIPTEN)
    SET(BUILD_AGG TRUE)
    add_subdirectory(src/gdx-cpp/backends/emscripten)
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

install(FILES cmake/cotire.cmake
        DESTINATION share/gdx/cmake)
