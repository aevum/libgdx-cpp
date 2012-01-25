project(gdx-cpp-agg-svg)

include_directories(include)

set(AGG_SVG_SRC svg/agg_svg_path_tokenizer.h
svg/agg_svg_exception.h
svg/agg_svg_path_renderer.cpp
svg/agg_svg_path_renderer.h
svg/agg_svg_path_tokenizer.cpp
svg/agg_svg_parser.h
svg/AggSvgPixmap.cpp
)

file(GLOB AGG_SRC src/*.cpp src/ctrl/*.cpp)
add_library(gdx-cpp-agg-svg STATIC ${AGG_SVG_SRC} ${AGG_SRC})

IF( CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" )
  SET_TARGET_PROPERTIES(gdx-cpp-agg-svg PROPERTIES COMPILE_FLAGS "-fPIC")
ENDIF( CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" )

install(TARGETS gdx-cpp-agg-svg ARCHIVE DESTINATION lib)