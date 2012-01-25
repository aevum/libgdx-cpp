#Look for a directory containing STLport.
#
# The following values are defined
# GDXCPP_INCLUDE_DIR - where to find vector, etc.
# GDXCPP_LIBRARIES   - link against these to use STLport
# GDXCPP_FOUND       - True if the STLport is available.

# also defined, but not for general use are
IF(GDXCPP_LIBRARIES AND GDXCPP_INCLUDE_DIR)
# in cache already
SET(GDXCPP_FIND_QUIETLY TRUE)
ENDIF(GDXCPP_LIBRARIES AND GDXCPP_INCLUDE_DIR)

FIND_PATH(GDXCPP_INCLUDE_DIR
gdx-cpp/Gdx.hpp
PATHS
/usr/local/include
/usr/include
/sw/include
/opt/local/include
/opt/csw/include
/opt/include
${GDX_ROOT}/include
)

macro(find_libraries)
    foreach(lib ${ARGV0})
        FIND_LIBRARY(GDXCPP_${lib}
            NAMES
            ${lib}
            PATHS
            /usr/local/lib
            /usr/lib
            /opt/local/lib
            /opt/lib
            /usr/lib/x86_64-linux-gnu
            ${GDX_ROOT}/lib
            )

        if (GDXCPP_${lib})
            LIST(APPEND GDXCPP_LIBRARIES "${GDXCPP_${lib}}")
        else()
            message("Could not find Libgdx library dependency:" ${lib})
            SET(GDXCPP_LIBRARIES GDXCPP_LIBRARIES-NOTFOUND)
            return(find_libraries)
        endif()
    endforeach()
endmacro()

if (UNIX)
    find_libraries(gdx-cpp)

    if (GdxCpp_USE_BOX2D)
        find_libraries("Box2D;gdx-cpp-box2d-layer")
    endif()
    
    if (ANDROID_NDK)
        find_libraries("gdx-cpp-backend-android;gdx-cpp-agg-svg;")
         set(GDXCPP_LIBRARIES "${GDXCPP_LIBRARIES};dl;log;GLESv1_CM;GLESv2;")
    else(ANDROID_NDK)
        find_libraries("gdx-cpp-backend-linux;gdx-cpp-agg-svg;vorbis;vorbisfile;openal;ogg;SDL;GLU;")

        if (GdxCpp_BUILD_GRAPHICS_OPENGL)
            find_libraries("GL")
        else()
            find_libraries("GLESv1_CM;GLESv2")
        endif()
    endif()
endif()

if(GDXCPP_INCLUDE_DIR)
    if(GDXCPP_LIBRARIES)
        set(GDXCPP_FOUND TRUE)
    endif(GDXCPP_LIBRARIES)
endif(GDXCPP_INCLUDE_DIR)

if(GDXCPP_FOUND)
    if(NOT GDXCPP_FIND_QUIETLY)
        foreach(LIB ${GDXCP_LIBRARIES})
			message("Found GDX Library: " ${LIB})
		endforeach()
    endif()
else(GDXCPP_FOUND)
    if(NOT GDXCPP_FIND_QUIETLY)
        message(STATUS "Warning: Unable to find GdxCPP!")
    endif()
endif(GDXCPP_FOUND)

MARK_AS_ADVANCED(GDXCPP_LIBRARY)
