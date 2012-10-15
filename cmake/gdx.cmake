macro(gdx_add_ios_framework target_name framework additional_paths)
    if (APPLE)
        execute_process(COMMAND xcode-select -print-path OUTPUT_VARIABLE _output OUTPUT_STRIP_TRAILING_WHITESPACE)                
        SET(DEVROOT "${_output}/Platforms/iPhoneOS.platform/Developer")
        SET(SDKROOT "${DEVROOT}/SDKs/iPhoneOS${SDKVER}.sdk")
        
        if (NOT EXISTS ${SDKROOT})
            message(FATAL_ERROR "Could not find the base SDK for version ${SDKVER}. Please verify if you have it correctly installed")
        endif()

        find_library(FOUND_FRAMEWORK_${framework} NAMES ${framework} PATHS ${SDKROOT}/System/Library
            ${additional_paths}
            PATH_SUFFIXES Frameworks
            NO_DEFAULT_PATH)

        message("Library: " ${FOUND_FRAMEWORK_${framework}})
        target_link_libraries(${target_name} ${FOUND_FRAMEWORK_${framework}})
    endif()
endmacro()

macro(gdx_ios_copy_resources target_name target_files destination)
    add_custom_command(
        TARGET ${target_name}
        POST_BUILD
        COMMAND rsync -r --exclude .DS_Store --exclude CVS --exclude .svn --exclude .git --exclude *~ ${target_files} "\${BUILT_PRODUCTS_DIR}/\${CONTENTS_FOLDER_PATH}/${destination}")
endmacro()

macro(gdx_make_resources target_name target_files destination)
    if (APPLE) 
        gdx_ios_copy_resources(${target_name} ${target_files} ${destination})
    elseif(ANDROID_NDK)
        if (NOT GDX_JAVA_APPLICATION_DIR)
            message(FATAL_ERROR "Please specify the folder where the eclipse project it's located on the variable GDX_JAVA_APPLICATION_DIR")
        endif()        
        if (NOT EXISTS ${GDX_JAVA_APPLICATION_DIR}/assets/${destination}) 
            execute_process(COMMAND ln -s ${target_files} ${GDX_JAVA_APPLICATION_DIR}/assets/${destination})     
        endif()
    else()
        if (NOT EXISTS ${PROJECT_BINARY_DIR}/${destination}) 
            execute_process(COMMAND ln -s ${target_files} ${PROJECT_BINARY_DIR}/${destination})     
        endif()
    endif()
endmacro()

macro(gdx_setup_target target_name target_type sources)
    string(TOUPPER ${target_type} target_type)
    
    if(CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo" OR GDX_LOG_LEVEL STREQUAL "INFO")
        add_definitions(-DGDX_LOG_LEVEL_INFO)
        add_definitions(-DGDX_LOG_LEVEL_ERROR)
    elseif(CMAKE_BUILD_TYPE STREQUAL "Release" OR GDX_LOG_LEVEL STREQUAL "RELEASE")
        add_definitions(-DGDX_LOG_LEVEL_ERROR)
    else()
        add_definitions(-DGDX_LOG_LEVEL_DEBUG)
        add_definitions(-DGDX_LOG_LEVEL_INFO)
        add_definitions(-DGDX_LOG_LEVEL_ERROR)
    endif()

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
        SET(CMAKE_OSX_SYSROOT ${SDKROOT})

        SET (CMAKE_OSX_ARCHITECTURES "$(ARCHS_UNIVERSAL_IPHONE_OS)")

        set(CMAKE_CXX_FLAGS "-x objective-c++ -mno-thumb")      
        set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++11")
        set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")
        
        if (${target_type} STREQUAL "EXECUTABLE")
            add_executable(${target_name} MACOSX_BUNDLE ${sources})
            set(IOS_FRAMEWORKS "Foundation;AudioToolbox;CoreGraphics;QuartzCore;UIKit;OpenGLES;AVFoundation;OpenAL")
        
            foreach(FRAMEWORK ${IOS_FRAMEWORKS})
                gdx_add_ios_framework(${target_name} ${FRAMEWORK} "")
            endforeach()

            set_target_properties(${target_name} PROPERTIES XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "iPhone Developer")
        else()
            add_library(${target_name} STATIC ${sources})
        endif()
    elseif (ANDROID_NDK)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu++0x")
        
        if (${target_type} STREQUAL "EXECUTABLE")
            add_library(${target_name} SHARED ${sources})
        else() 
            add_library(${target_name} ${library_type} ${sources})
        endif()
    elseif(UNIX)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x")
        
        if (${target_type} STREQUAL "EXECUTABLE")
            add_executable(${target_name} ${sources})
        else()
            add_library(${target_name} ${target_type} ${sources})
        endif()
    endif()
endmacro()
