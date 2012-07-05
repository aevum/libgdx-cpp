macro(gdx_setup_target target_type target_name sources)
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

        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++ -x objective-c++ -mno-thumb")

        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework Foundation -framework AudioToolbox -framework CoreGraphics -framework  QuartzCore -framework UIKit -framework OpenGLES -framework AVFoundation")

        if (${target_type} STREQUAL "application")
            add_executable(${target_name} MACOSX_BUNDLE ${sources})
        else()
            add_library(${target_name} ${sources})
        endif()

        set_target_properties(${target_name} PROPERTIES
                        MACOSX_BUNDLE_GUI_IDENTIFIER "${COMPANY_NAME}\${PRODUCT_NAME:identifier}"
        )
    elseif (ANDROID_NDK)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu++0x")
        add_library(${target_name} SHARED ${sources})

    elseif(UNIX)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
        if (${target_type} STREQUAL "application")
            add_executable(${target_name} ${sources})
        else()
            if (BUILD_AS_SHARED_LIBRARIES) 
                add_library(${target_name} SHARED ${sources})
            else()
                add_library(${target_name} STATIC ${sources})
            endif()
        endif()
    endif()
endmacro()

#This macro has the task to figure out how the application is supposed to run
#on each backend.
macro(gdx_setup_runnable_target target_name sources)
    gdx_setup_target("application" ${target_name} "${sources}")
endmacro()

macro(gdx_setup_library_target target_name sources)
    gdx_setup_target("library" ${target_name} "${sources}")
endmacro()
