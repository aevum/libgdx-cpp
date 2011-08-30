project(gdx-cpp-tests)

include_directories(${GDXCPP_INCLUDE_DIR})

add_executable(simple-test SimpleTest.cpp)
target_link_libraries(simple-test gdx-cpp gdx-cpp-backend-linux)