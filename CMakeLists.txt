project(gdx-cpp)

cmake_minimum_required(VERSION 2.8)

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
set(GDX_BINARY_ROOT_DIR ${PROJECT_BINARY_DIR})

LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/finders)
set(GDXCPP_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

if (UNIX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -Wall")
endif()

option(BUILD_BACKEND_LINUX "Builds the linux backend for gdx-cpp" FALSE)
option(BUILD_BACKEND_IOS "Builds the ios backend for gdx-cpp" FALSE)
option(BUILD_BACKEND_ANDROID "Builds the android backend for gdx-cpp" FALSE)
option(BUILD_BACKEND_WINDOWS "Builds the windows backend for gdx-cpp" FALSE)

option(BUILD_GDX_TESTS "Builds(tries) all libgdx tests" TRUE)
set(GENERATED_APPLICATION_TYPE "EXECUTABLE")

# option(BUILD_GDX_DEPENDENCIES "Builds  the required dependencies for LibGDX-CPP" TRUE)


# if (BUILD_GDX_DEPENDENCIES)
#     set(GDX_CPP_EXTERNAL_DEPENDENCIES gdx-cpp-mpg123 gdx-cpp-kiss-fft gdx-cpp-vorbis)
#     add_subdirectory(dependencies/kissfft)
#     add_subdirectsrc/backends/gdx-cpp-backend-linuxpg123)
# else(BUILD_GDX_DEPENDENCIES)
#     set(GDX_CPP_EXTERNAL_DEPENDENCIES mpg123 kiss-fft vorbisfile vorbis)
# endif()

SET(ACTIVE_BACKENDS "")

include_directories(src)
add_subdirectory(src/gdx-cpp)

if (BUILD_BACKEND_LINUX)
  OPTION(BUILD_LINUX_GRAPHICS_OPENGL "Builds the linux backend with OpenGL" FALSE)
  OPTION(BUILD_LINUX_GRAPHICS_OPENGLES "Builds the linux backend with OpenGL ES" TRUE)
  
  if (BUILD_LINUX_GRAPHICS_OPENGL)
    add_definitions(-DLIBGDX_CPP_BUILD_OPENGL_INSTEAD_GLES)
    SET(GL_DEPENDENCIES GL)
  else()
    SET(GL_DEPENDENCIES GLESv1_CM GLESv2)
  endif()
    
  SET(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -Wdouble-promotion")
  list(APPEND ACTIVE_BACKENDS LINUX)
  set(BACKEND-LINUX-DEPENDENCIES SDL ${GL_DEPENDENCIES} GLU)
  set(GDX_CPP_BACKEND_LINUX_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/src/backends)
  add_subdirectory(src/backends/gdx-cpp-backend-linux)
endif()

if (BUILD_BACKEND_IOS)
    list(APPEND ACTIVE_BACKENDS IOS)
    add_subdirectory(src/backends/ios)
endif()

if (BUILD_BACKEND_ANDROID)
    set(GENERATED_APPLICATION_TYPE "SHARED_LIB")
    SET(ANDROID_NDK "" CACHE PATH "Were the android NDK is located")
    set(CMAKE_SHARED_LINKER_FLAGS "-Wl,--no-gc-sections")

#     include(cmake/android.toolchain.cmake)
    list(APPEND ACTIVE_BACKENDS ANDROID)
    set(BACKEND-ANDROID-DEPENDENCIES dl log GLESv1_CM GLESv2)
    set(GDX_CPP_BACKEND_ANDROID_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/src/backends)
    add_subdirectory(src/backends/gdx-cpp-backend-android)    
endif()

if (BUILD_BACKEND_WINDOWS)
    add_subdirectory(src/backends/windows)
endif()

if (BUILD_GDX_TESTS)
    add_subdirectory(src/tests)
endif()
