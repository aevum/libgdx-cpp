project(gdx-cpp-agg-svg)

include_directories(include)

set(AGG_SVG_SRC svg/agg_svg_path_tokenizer.h
svg/agg_svg_exception.h
svg/agg_svg_path_renderer.cpp
svg/agg_svg_path_renderer.h
svg/agg_svg_path_tokenizer.cpp
svg/agg_svg_parser.h)

file(GLOB AGG_SRC src/*.cpp src/ctrl/*.cpp)

#crazy bug on gcc 4.6 that requires a STATIC lib to be compiled with fPIC :S
if (!ANDROID_NDK)
    if (UNIX)
        set(CMAKE_CXX_FLAGS "-fPIC")
    endif()
endif()

add_library(gdx-cpp-agg-svg STATIC ${AGG_SVG_SRC} ${AGG_SRC})

install(TARGETS gdx-cpp-agg-svg ARCHIVE DESTINATION lib)