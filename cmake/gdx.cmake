macro(gdx_add_ios_framework target_name framework) 
        execute_process(COMMAND xcode-select -print-path OUTPUT_VARIABLE _output OUTPUT_STRIP_TRAILING_WHITESPACE)                
        SET(DEVROOT "${_output}/Platforms/iPhoneOS.platform/Developer")
        SET(SDKROOT "${DEVROOT}/SDKs/iPhoneOS${SDKVER}.sdk")
        
        find_library(FOUND_FRAMEWORK_${framework} NAMES ${framework} PATHS ${SDKROOT}/System/Library
            PATH_SUFFIXES Frameworks
            NO_DEFAULT_PATH)

        target_link_libraries(${target_name} ${FOUND_FRAMEWORK_${framework}})
endmacro()

macro(gdx_setup_target target_type library_type target_name sources)
    if (APPLE)
        if (NOT SDKVER)
            message(FATAL_ERROR "Missing SDKVER variable. Please define it with the latest version of the ios SDK")
        endif()

        if (NOT COMPANY_NAME)
            message(FATAL_ERROR "Missing COMPANY_NAME variable. Please define it with the company namespace eg: com.mycompany")
        endif()

        execute_process(COMMAND xcode-select -print-path OUTPUT_VARIABLE _output OUTPUT_STRIP_TRAILING_WHITESPACE)
        
        set(CMAKE_XCODE_EFFECTIVE_PLATFORMS "-iphoneos;-iphonesimulator")

        SET(DEVROOT "${_output}/Platforms/iPhoneOS.platform/Developer")
        SET(SDKROOT "${DEVROOT}/SDKs/iPhoneOS${SDKVER}.sdk")
        SET(CMAKE_OSX_SYSROOT "${SDKROOT}")

        SET (CMAKE_OSX_ARCHITECTURES "$(ARCHS_UNIVERSAL_IPHONE_OS)")

        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -x objective-c++ -mno-thumb")      
        set(CMAKE_XCODE_ATTRIBUTE_GCC_VERSION "com.apple.compilers.llvm.clang.1_0")
        set(CLANG_CXX_LANGUAGE_STANDARD "c++11")
        set(CLANG_CXX_LIBRARY "libc++")

        if (${target_type} STREQUAL "application")
            add_executable(${target_name} MACOSX_BUNDLE ${sources})
            set(IOS_FRAMEWORKS "Foundation;AudioToolbox;CoreGraphics;QuartzCore;UIKit;OpenGLES;AVFoundation")
        
            foreach(FRAMEWORK ${IOS_FRAMEWORKS})
                gdx_add_ios_framework(${target_name} ${FRAMEWORK})
            endforeach()
        else()
            add_library(${target_name} STATIC ${sources})
        endif()
      
        set_target_properties(${target_name} PROPERTIES
                        MACOSX_BUNDLE_GUI_IDENTIFIER "${COMPANY_NAME}\${PRODUCT_NAME:identifier}"
        )
    elseif (ANDROID_NDK)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu++0x")
        
        if (${target_type} STREQUAL "application")
            add_library(${target_name} SHARED ${sources})
        else() 
            add_library(${target_name} ${library_type} ${sources})
        endif()
    elseif(UNIX)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x")
        
        if (${target_type} STREQUAL "application")
            add_executable(${target_name} ${sources})
        else()
            add_library(${target_name} ${library_type} ${sources})
        endif()
    endif()
endmacro()

#This macro has the task to figure out how the application is supposed to run
#on each backend.
macro(gdx_setup_runnable_target target_name sources)
    gdx_setup_target("application" none ${target_name} "${sources}")
endmacro()

macro(gdx_setup_library_target target_name library_type sources)
    gdx_setup_target("library" ${library_type} ${target_name} "${sources}")
endmacro()
