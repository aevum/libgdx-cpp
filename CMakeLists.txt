project(gdx-cpp)

cmake_minimum_required(VERSION 2.8)

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
set(GDX_BINARY_ROOT_DIR ${PROJECT_BINARY_DIR})

LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/finders)
set(GDXCPP_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(GDXCPP_BOX2D_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/Box2D)

if (UNIX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -Wall")
endif()

option(BUILD_BACKEND_LINUX "Builds the linux backend for gdx-cpp" FALSE)
option(BUILD_BACKEND_IOS "Builds the ios backend for gdx-cpp" FALSE)
option(BUILD_BACKEND_ANDROID "Builds the android backend for gdx-cpp" FALSE)
option(BUILD_BACKEND_WINDOWS "Builds the windows backend for gdx-cpp" FALSE)

option(BUILD_BOX2D "Builds Box2D" TRUE)

option(BUILD_GDX_TESTS "Builds(tries) all libgdx tests" TRUE)
set(GENERATED_APPLICATION_TYPE "EXECUTABLE")

# option(BUILD_GDX_DEPENDENCIES "Builds  the required dependencies for LibGDX-CPP" TRUE)

option(BUILD_SVG_ANTIGRAIN "Build the antigrain's svg backend" TRUE)

SET(SVG_BACKEND_ANTIGRAIN_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/src/agg/include ${CMAKE_CURRENT_SOURCE_DIR}/src/agg/svg)

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

if (BUILD_SVG_ANTIGRAIN)
  add_subdirectory(src/agg)
endif()

if (BUILD_BACKEND_LINUX)
  OPTION(BUILD_LINUX_GRAPHICS_OPENGL "Builds the linux backend with OpenGL" FALSE)
  OPTION(BUILD_LINUX_GRAPHICS_OPENGLES "Builds the linux backend with OpenGL ES" TRUE)
  
  if (BUILD_LINUX_GRAPHICS_OPENGL)
    add_definitions(-DLIBGDX_CPP_BUILD_OPENGL_INSTEAD_GLES)
    SET(GL_DEPENDENCIES GL)
  else()
    SET(GL_DEPENDENCIES GLESv1_CM GLESv2)
  endif()

  if(CMAKE_COMPILER_IS_GNUCXX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -Wdouble-promotion")    
  endif()

  list(APPEND ACTIVE_BACKENDS LINUX)
  set(BACKEND-LINUX-DEPENDENCIES SDL ${GL_DEPENDENCIES} GLU gdx-cpp-agg-svg)
  set(GDX_CPP_BACKEND_LINUX_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/src/backends)
  add_subdirectory(src/backends/gdx-cpp-backend-linux)
endif()

if (BUILD_BOX2D)
    add_subdirectory(src/Box2D)
endif()

if (BUILD_BACKEND_IOS)
    list(APPEND ACTIVE_BACKENDS IOS)

	cmake_policy(SET CMP0015 NEW)
	cmake_policy(SET CMP0016 NEW)
	
	set(SDKVER "4.3" CACHE STRING "The iPhoneOs SDK version")
	set(DEVROOT "/Developer/Platforms/iPhoneOS.platform/Developer")
	set(SDKROOT "${DEVROOT}/SDKs/iPhoneOS${SDKVER}.sdk")
	set(CMAKE_OSX_SYSROOT "${SDKROOT}")
	set(CMAKE_OSX_ARCHITECTURES "${ARCHS_UNIVERSAL_IPHONE_OS}")
	
	set(CMAKE_CXX_FLAGS "-x objective-c++")
	set(CMAKE_EXE_LINKER_FLAGS
		"-framework Foundation -framework AudioToolbox -framework CoreGraphics -framework QuartzCore -framework UIKit -framework OpenGLES")

	link_directories(\${HOME}/\${SDKROOT}/lib)
	
	set(MACOSX_BUNDLE_GUI_IDENTIFIER "com.aevumlab.\${PRODUCT_NAME:identifier}")
	set(BACKEND-IOS-DEPENDENCIES gdx-cpp-agg-svg)
	set(GDX_CPP_BACKEND_IOS_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/src/backends)
	add_subdirectory(src/backends/gdx-cpp-backend-ios)
endif()

if (BUILD_BACKEND_ANDROID)
    set(GENERATED_APPLICATION_TYPE "SHARED_LIB")
    SET(ANDROID_NDK "" CACHE PATH "Were the android NDK is located")

    list(APPEND ACTIVE_BACKENDS ANDROID)
    set(BACKEND-ANDROID-DEPENDENCIES dl log GLESv1_CM GLESv2 android gdx-cpp gdx-cpp-agg-svg)
    set(GDX_CPP_BACKEND_ANDROID_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/src/backends)
    add_subdirectory(src/backends/gdx-cpp-backend-android)    
endif()

if (BUILD_BACKEND_WINDOWS)
    add_subdirectory(src/backends/windows)
endif()

if (BUILD_GDX_TESTS)
    add_subdirectory(src/tests)
endif()