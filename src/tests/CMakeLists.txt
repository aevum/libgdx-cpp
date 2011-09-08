project(gdx-cpp-tests)

include_directories(${GDXCPP_INCLUDE_DIR})

set(APPLICATIONS SimpleTest SimpleGdxApp MyFirstTriangle SpriteBatchTest PixmapTest ParticleEmitterTest box2d/Box2DTest)

message("Active backend is: " ${ACTIVE_BACKENDS})

foreach(BACKEND ${ACTIVE_BACKENDS})
    include_directories(${GDX_CPP_BACKEND_${BACKEND}_INCLUDES})
    string(TOLOWER ${BACKEND} backend)
    set(EXECUTABLE_OUTPUT_PATH ${GDX_BINARY_ROOT_DIR}/bin/tests/${backend})

    foreach(APP ${APPLICATIONS})
        if (${GENERATED_APPLICATION_TYPE} STREQUAL "EXECUTABLE")
            add_executable(${APP} ${APP}.cpp)            
        elseif (${GENERATED_APPLICATION_TYPE} STREQUAL "SHARED_LIB")
            add_library(${APP} SHARED ${APP}.cpp)
        endif()        
        target_link_libraries(${APP} gdx-cpp gdx-cpp-backend-${backend} ${BACKEND-${BACKEND}-DEPENDENCIES})
        add_definitions(-DCURRENT_BACKEND_${BACKEND})
        add_dependencies(${APP} gdx-cpp gdx-cpp-backend-${backend})
    endforeach()
endforeach()