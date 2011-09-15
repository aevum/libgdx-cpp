project(gdx-cpp-tests)

include_directories(${GDXCPP_INCLUDE_DIR})

set(APPLICATIONS MyFirstTriangle SpriteBatchTest PixmapTest SpriteCacheTest
            AlphaTest DeltaTimeTest SpritePerformanceTest ParticleEmitterTest
    box2d/Chain box2d/ApplyForce box2d/Bridge box2d/Cantilever box2d/CharacterCollision box2d/CollisionFiltering box2d/ContinuousTest
    box2d/DebugRendererTest box2d/OneSidedPlatform box2d/Prismatic box2d/Pyramid box2d/SimpleTest box2d/SphereStack box2d/VaryingRestitution
    box2d/VerticalStack)

message("Active backend is: " ${ACTIVE_BACKENDS})

foreach(BACKEND ${ACTIVE_BACKENDS})
    include_directories(${GDX_CPP_BACKEND_${BACKEND}_INCLUDES})
    string(TOLOWER ${BACKEND} backend)
    set(EXECUTABLE_OUTPUT_PATH ${GDX_BINARY_ROOT_DIR}/bin/tests/${backend})

    foreach(APP ${APPLICATIONS})
        get_filename_component(APP_NAME ${APP} NAME)
        if (${GENERATED_APPLICATION_TYPE} STREQUAL "EXECUTABLE")
            add_executable(${APP_NAME} ${APP}.cpp)
        elseif (${GENERATED_APPLICATION_TYPE} STREQUAL "SHARED_LIB")
            add_library(${APP_NAME} SHARED ${APP}.cpp)
        endif()        
        target_link_libraries(${APP_NAME} gdx-cpp gdx-cpp-backend-${backend} ${BACKEND-${BACKEND}-DEPENDENCIES} gdx-cpp-box2d gdx-cpp-box2d-layer)
        add_definitions(-DCURRENT_BACKEND_${BACKEND})
        add_dependencies(${APP_NAME} gdx-cpp gdx-cpp-backend-${backend})
    endforeach()
endforeach()