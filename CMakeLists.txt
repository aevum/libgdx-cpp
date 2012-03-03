project(gdx-cpp)

cmake_minimum_required(VERSION 2.8)

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
set(GDX_BINARY_ROOT_DIR ${PROJECT_BINARY_DIR})

LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/finders)

include_directories(src)

link_directories(${LIBRARY_OUTPUT_PATH})

if($ENV{ANDROID_NDK})
    SET(ANDROID_NDK $ENV{ANDROID_NDK})
endif()

if (UNIX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -Wall")

    if (ANDROID_NDK)
        
        message("ANDROID_NDK Found. Setting the backend to ANDROID")
        SET(GDX_BACKEND ANDROID)
        SET(GDX_BACKEND_LIB gdx-cpp-backend-android)
    else()
        message("Linux found. Setting the backend to LINUX")
        SET(GDX_BACKEND LINUX)
        SET(GDX_BACKEND_LIB gdx-cpp-backend-linux)
    endif()

    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/agg/include ${CMAKE_CURRENT_SOURCE_DIR}/src/agg/svg)
    add_subdirectory(src/agg)
elseif(MACOSX)
    message("MacOSX (iOS) found. Setting the backend to IOS")
    SET(GDX_BACKEND IOS)
    SET(GDX_BACKEND_LIB gdx-cpp-backend-ios)
elseif(WIN32)
    message("Win32 found. Setting the backend to WIN32")
    SET(GDX_BACKEND WIN32)
    SET(GDX_BACKEND_LIB gdx-cpp-backend-win32)
endif()

option(BUILD_BOX2D "Builds Box2D" TRUE)
option(BUILD_AS_SHARED_LIBRARIES "Build libraries as shared libraries instead of static" FALSE)

if (BUILD_BOX2D)
    set(BOX2D_BUILD_STATIC NOT ${BUILD_AS_SHARED_LIBRARIES})
    set(BOX2D_BUILD_SHARED ${BUILD_AS_SHARED_LIBRARIES})
    set(BOX2D_INSTALL TRUE)

    add_subdirectory(src/Box2D)
    add_subdirectory(src/gdx-cpp/physics/box2d)
endif()

if (${GDX_BACKEND} STREQUAL "IOS")
    cmake_policy(SET CMP0015 NEW)
    cmake_policy(SET CMP0016 NEW)
	
    set(CMAKE_XCODE_ATTRIBUTE_GCC_VERSION "com.apple.compilers.llvm.clang.1_0")
    set(SDKVER "4.3" CACHE STRING "The iPhoneOs SDK version")
    set(DEVROOT "/Developer/Platforms/iPhoneOS.platform/Developer")
    set(SDKROOT "${DEVROOT}/SDKs/iPhoneOS${SDKVER}.sdk")
    set(CMAKE_OSX_SYSROOT "${SDKROOT}")
    set(CMAKE_OSX_ARCHITECTURES "${ARCHS_UNIVERSAL_IPHONE_OS}")
	
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -x objective-c++")
    set(CMAKE_EXE_LINKER_FLAGS
		"-framework Foundation -framework AudioToolbox -framework CoreGraphics -framework QuartzCore -framework UIKit -framework OpenGLES")

    link_directories(\${HOME}/\${SDKROOT}/lib)
	
    set(MACOSX_BUNDLE_GUI_IDENTIFIER "com.aevumlab.\${PRODUCT_NAME:identifier}")
    set(BACKEND-IOS-DEPENDENCIES gdx-cpp-agg-svg)
    set(GDX_CPP_BACKEND_IOS_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/src/backends)
	
    add_subdirectory(src/backends/gdx-cpp-backend-ios)
elseif(${GDX_BACKEND} STREQUAL "ANDROID")
    add_subdirectory(src/backends/gdx-cpp-backend-android)    
elseif(${GDX_BACKEND} STREQUAL "WIN32")
    add_subdirectory(src/backends/windows)
elseif(${GDX_BACKEND} STREQUAL "LINUX")
  OPTION(GDX_USE_OPENGL "Builds the linux backend with OpenGL" FALSE)
  OPTION(GDX_USE_OPENGLES "Builds the linux backend with OpenGL ES" TRUE)

  if (GDX_USE_OPENGL)
    set(GdxCpp_BUILD_GRAPHICS_OPENGL TRUE)
    add_definitions(-DLIBGDX_CPP_BUILD_OPENGL_INSTEAD_GLES)
  endif()

  if(CMAKE_COMPILER_IS_GNUCXX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -Wdouble-promotion")
  endif()

  add_subdirectory(src/backends/gdx-cpp-backend-linux)
endif()

install(FILES cmake/finders/FindGdxCpp.cmake
        DESTINATION share/cmake-2.8/Modules)

add_subdirectory(src/gdx-cpp)