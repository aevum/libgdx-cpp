project(gdx-cpp-agg-svg)

include_directories(include)

file(GLOB AGG_SRC "src/*.cpp" "src/ctrl/*.cpp" "svg/*.cpp")
file(GLOB AGG_SRC_HEADERS "src/*.h" "src/ctrl/*.h")

gdx_setup_target(gdx-cpp-agg-svg STATIC "${AGG_SRC};${AGG_SRC_HEADERS}")

install(TARGETS gdx-cpp-agg-svg ARCHIVE DESTINATION lib LIBRARY DESTINATION lib)