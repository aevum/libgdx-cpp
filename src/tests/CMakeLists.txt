project(gdx-cpp-tests)

include_directories(${GDXCPP_INCLUDE_DIR})
include_directories(${GDX_CPP_BACKEND_LINUX_INCLUDES})

set(APPLICATIONS SimpleTest SimpleGdxApp MyFirstTriangle SpriteBatchTest PixmapTest)

message("Active backends are: " ${ACTIVE_BACKENDS})

foreach(BACKEND ${ACTIVE_BACKENDS})
    string(TOLOWER ${BACKEND} backend)
    set(EXECUTABLE_OUTPUT_PATH ${GDX_BINARY_ROOT_DIR}/bin/tests/${backend})

    foreach(APP ${APPLICATIONS})
        add_executable(${APP} ${APP}.cpp)
        target_link_libraries(${APP} gdx-cpp gdx-cpp-backend-${backend} ${BACKEND-${BACKEND}-DEPENDENCIES})
        add_definitions(-DCURRENT_BACKEND_${BACKEND})
        add_dependencies(${APP} gdx-cpp gdx-cpp-backend-${backend})
    endforeach()
endforeach()