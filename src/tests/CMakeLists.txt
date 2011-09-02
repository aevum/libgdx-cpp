project(gdx-cpp-tests)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin/tests)

include_directories(${GDXCPP_INCLUDE_DIR})
include_directories(${GDX_CPP_BACKEND_LINUX_INCLUDES})

set(APPLICATIONS SimpleTest SimpleGdxApp MyFirstTriangle)

foreach(APP ${APPLICATIONS})
    add_executable(${APP} ${APP}.cpp)
    target_link_libraries(${APP} gdx-cpp gdx-cpp-backend-linux GLESv1_CM SDL GLU)
    add_dependencies(${APP} gdx-cpp)    
endforeach()