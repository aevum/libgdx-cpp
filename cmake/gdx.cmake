macro(gdx_add_ios_framework target_name framework additional_paths)
    LIST(APPEND CMAKE_FRAMEWORK_PATH ${additional_paths})
    find_library(FOUND_FRAMEWORK_${framework} NAMES ${framework})

    message("Library: " ${FOUND_FRAMEWORK_${framework}})
    target_link_libraries(${target_name} ${FOUND_FRAMEWORK_${framework}})
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
    elseif(GDX_BACKEND_EMSCRIPTEN)
        if (NOT EXISTS ${PROJECT_BINARY_DIR}/${destination})
            execute_process(COMMAND ln -s ${target_files} ${PROJECT_BINARY_DIR}/${destination})
        endif()
        set_property(TARGET "${target_name}-html" APPEND_STRING PROPERTY LINK_FLAGS " --preload-file ${destination}")
    else()
        if (NOT EXISTS ${PROJECT_BINARY_DIR}/${destination})
            execute_process(COMMAND ln -s ${target_files} ${PROJECT_BINARY_DIR}/${destination})
        endif()
    endif()
endmacro()

macro(gdx_setup_target target_name target_type sources)
    message("gdx_setup_target" ${target_name})
    string(TOUPPER ${target_type} target_type)

    if (APPLE)
        if (${target_type} STREQUAL "EXECUTABLE")
            add_executable(${target_name} MACOSX_BUNDLE ${sources})
            set(IOS_FRAMEWORKS "Foundation;AudioToolbox;CoreGraphics;QuartzCore;UIKit;OpenGLES;AVFoundation;OpenAL")

            foreach(FRAMEWORK ${IOS_FRAMEWORKS})
                gdx_add_ios_framework(${target_name} ${FRAMEWORK} "")
            endforeach()

            set_target_properties(${target_name} PROPERTIES XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "iPhone Developer")
        else()
            add_library(${target_name} STATIC ${sources})
            ADD_CUSTOM_COMMAND(
                TARGET ${target_name}   
                POST_BUILD
                COMMAND mkdir -p ${EXECUTABLE_OUTPUT_PATH}/$(CONFIGURATION)
                COMMAND ln -fs \"${EXECUTABLE_OUTPUT_PATH}/$<TARGET_FILE_NAME:${target_name}>\" \"$<TARGET_FILE_DIR:${target_name}>\"
            )
        endif()

        set_property (TARGET ${target_name} PROPERTY XCODE_ATTRIBUTE_SYMROOT ${EXECUTABLE_OUTPUT_PATH})
        set_property (TARGET ${target_name} PROPERTY XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "$(BUILD_DIR)")
        set_property (TARGET ${target_name} PROPERTY XCODE_ATTRIBUTE_CONFIGURATION_TEMP_DIR "$(PROJECT_TEMP_DIR)")
        set_property (TARGET ${target_name} PROPERTY XCODE_ATTRIBUTE_CONFIGURATION_ARCHS "$(ARCHS_STANDARD_32_BIT)")
        set_property (TARGET ${target_name} PROPERTY XCODE_ATTRIBUTE_ONLY_ACTIVE_ARCH "YES")
    elseif (ANDROID_NDK)
        if (${target_type} STREQUAL "EXECUTABLE")
            add_library(${target_name} SHARED ${sources})
        else()
            add_library(${target_name} ${library_type} ${sources})
        endif()
    elseif (GDX_BACKEND_EMSCRIPTEN)
        if (${target_type} STREQUAL "EXECUTABLE")
            add_executable(${target_name} ${sources})            
            
            #strangely, if we change the prefix of the build to .bc
            #the linking process doesn't work
            set_property(TARGET ${target_name} PROPERTY SUFFIX ".so")
            
#add_custom_target(${target_name}-html 
#               COMMAND ${CMAKE_C_COMPILER} ${target_name}.so -O2 -s FULL_ES2=1 -s WARN_ON_UNDEFINED_SYMBOLS=1 -o ${target_name}.html
#                   DEPENDS ${target_name})
            
            add_executable(${target_name}-html ${sources})
            
            set_target_properties(${target_name}-html 
                PROPERTIES 
                    LINK_FLAGS "-O2 --closure 0 -s FULL_ES2=1 -s WARN_ON_UNDEFINED_SYMBOLS=1 -s TOTAL_MEMORY=268435456"
                    SUFFIX ".html"
                    OUTPUT_NAME ${target_name})
            
            link_libraries(${target_name}-html ${target_name})
            
            add_custom_target(${target_name}-js 
                COMMAND ${CMAKE_C_COMPILER} ${target_name}.so -O2 -s FULL_ES2=1 -s WARN_ON_UNDEFINED_SYMBOLS=1 -o ${target_name}.js
                DEPENDS ${target_name})
        else()
            #On emscripten we want everything as shared libraries
            add_library(${target_name} SHARED ${sources})
        endif()
    elseif(UNIX)
        if (${target_type} STREQUAL "EXECUTABLE")
            add_executable(${target_name} ${sources})
        else()
            add_library(${target_name} ${target_type} ${sources})
        endif()
    endif()
endmacro()

macro(initialize_gdx)

if (NOT GDX_INITIALIZED)
    SET(GDX_BACKEND_IOS 0)
    SET(GDX_BACKEND_ANDROID 0)
    SET(GDX_BACKEND_LINUX 0)
    SET(GDX_BACKEND_WIN32 0)

    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_definitions(-DGDX_DEBUG)
    endif()

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

    STRING(FIND ${CMAKE_CXX_COMPILER} "em++" EMSCRIPTENPP_FOUND)
    STRING(FIND ${CMAKE_C_COMPILER} "emcc" EMSCRIPTEN_FOUND)

    if ("${EMSCRIPTEN_FOUND}" GREATER "-1" AND "${EMSCRIPTENPP_FOUND}" GREATER "-1Ŝ")
        message("Emscripten found. Setting the backend to EMSCRIPTEN")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
        SET(GDX_BACKEND_EMSCRIPTEN TRUE)
        SET(GDX_BACKEND_LIB "gdx-cpp-backend-emscripten")
        add_definitions(-DGDX_BACKEND_EMSCRIPTEN -DGDX_BACKEND_SUFFIX="emscripten")
        set(BOX2D_BUILD_STATIC FALSE)
        set(BOX2D_BUILD_SHARED TRUE)
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s LINKABLE=1 -s WARN_ON_UNDEFINED_SYMBOLS=1 --remove-duplicates")
        set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -s LINKABLE=1 -s WARN_ON_UNDEFINED_SYMBOLS=1 --remove-duplicates")
    elseif(APPLE)
        message("MacOSX (iOS) found. Setting the backend to IOS")
        set(EXECUTABLE_OUTPUT_PATH "${PROJECT_BINARY_DIR}/build/$(CONFIGURATION)$(EFFECTIVE_PLATFORM_NAME)")
        set(LIBRARY_OUTPUT_PATH "${PROJECT_BINARY_DIR}/build/$(CONFIGURATION)$(EFFECTIVE_PLATFORM_NAME)")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -x objective-c++ -mno-thumb")
        SET(GDX_BACKEND_IOS TRUE)
        SET(GDX_BACKEND_LIB "gdx-cpp-backend-ios")
        add_definitions(-DGDX_BACKEND_IOS -DGDX_BACKEND_SUFFIX="ios")
        set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++11")
        set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")
        set(BOX2D_BUILD_STATIC TRUE)
        set(BOX2D_BUILD_SHARED FALSE)
    elseif (UNIX)
        set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
        set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
         if (ANDROID_NDK)
            message("ANDROID_NDK Found. Setting the backend to ANDROID")
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
            SET(GDX_BACKEND_ANDROID TRUE)
            SET(GDX_BACKEND_LIB "gdx-cpp-backend-android")
            add_definitions(-DGDX_BACKEND_ANDROID -DGDX_BACKEND_SUFFIX="android")
            set(BOX2D_BUILD_STATIC FALSE)
            set(BOX2D_BUILD_SHARED TRUE)
         else()
            message("Linux found. Setting the backend to LINUX")
            set(CMAKE_)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
            SET(GDX_BACKEND_LINUX TRUE)
            SET(GDX_BACKEND_LIB "gdx-cpp-backend-linux")
            add_definitions(-DGDX_BACKEND_LINUX -DGDX_BACKEND_SUFFIX="linux")
            
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
        SET(GDX_BACKEND_WIN32 TRUE CACHE BOOL "")
        SET(GDX_BACKEND_LIB "gdx-cpp-backend-win32" CACHE STRING "")
        add_definitions(-DGDX_BACKEND_WIN32 -DGDX_BACKEND_SUFFIX="win32")
    endif()

    set(GDX_INITIALIZED TRUE)
endif()
endmacro()
