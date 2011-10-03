project(gdx-cpp-agg-svg)

include_directories(include)

set(AGG_SVG_SRC svg/agg_svg_path_tokenizer.h
svg/agg_svg_exception.h
svg/agg_svg_path_renderer.cpp
svg/agg_svg_path_renderer.h
svg/agg_svg_path_tokenizer.cpp
svg/agg_svg_parser.h)

file(GLOB AGG_SRC src/*.cpp src/ctrl/*.cpp)
file(GLOB AGG_SRC_HEADERS src/*.h src/ctrl/*.h)

message("headers" ${AGG_SRC_HEADERS})
add_library(gdx-cpp-agg-svg ${AGG_SVG_SRC} ${AGG_SRC} ${AGG_SRC_HEADERS})