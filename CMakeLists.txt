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

if(APPLE)
    message("MacOSX (iOS) found. Setting the backend to IOS")
    SET(GDX_BACKEND IOS)
    SET(GDX_BACKEND_LIB gdx-cpp-backend-ios)
    
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/agg/include ${CMAKE_CURRENT_SOURCE_DIR}/src/agg/svg)
    add_subdirectory(src/agg)
elseif (UNIX)
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
    SET(SDKVER "5.0")
    
    execute_process(COMMAND xcode-select -print-path OUTPUT_VARIABLE _output OUTPUT_STRIP_TRAILING_WHITESPACE)
	set(CMAKE_XCODE_EFFECTIVE_PLATFORMS "-iphoneos;-iphonesimulator")

	SET(DEVROOT "${_output}/iPhoneOS.platform/Developer")
	SET(SDKROOT "${DEVROOT}/SDKs/iPhoneOS${SDKVER}.sdk")
	SET(CMAKE_OSX_SYSROOT "${SDKROOT}")

	SET (CMAKE_OSX_ARCHITECTURES "$(ARCHS_UNIVERSAL_IPHONE_OS)")
   
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -x objective-c++ -mno-thumb")
    set(CMAKE_EXE_LINKER_FLAGS "-framework Foundation -framework AudioToolbox -framework CoreGraphics -framework QuartzCore -framework UIKit -framework OpenGLES")

    set(BACKEND-IOS-DEPENDENCIES gdx-cpp-agg-svg)
    add_subdirectory(src/backends/gdx-cpp-backend-ios)
    
    set_target_properties(gdx-cpp-backend-ios PROPERTIES
  			MACOSX_BUNDLE_GUI_IDENTIFIER "com.aevumlab.\${PRODUCT_NAME:identifier}"
 			MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/Info.plist.in
 			RESOURCE "${RESOURCES}"
  			XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "iPhone Developer"
  			XCODE_ATTRIBUTE_DEBUG_INFORMATION_FORMAT "dwarf-with-dsym"
 			XCODE_ATTRIBUTE_GCC_PRECOMPILE_PREFIX_HEADER YES  		
            XCODE_ATTRIBUTE_INFOPLIST_PREPROCESS YES
  			XCODE_ATTRIBUTE_IPHONEOS_DEPLOYMENT_TARGET 4.3 # minimum deployment target
  			XCODE_ATTRIBUTE_TARGETED_DEVICE_FAMILY "1,2" # target both iPhone and iPad
  			XCODE_ATTRIBUTE_SKIP_INSTALL NO # needed for archive to actually show up in organizer
  			XCODE_ATTRIBUTE_INSTALL_PATH "/Application" # Archiving doesn't work with an empty path
	)
	
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