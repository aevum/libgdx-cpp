project(gdx-cpp-tests)

set(GdxCpp_ADDITIONAL_LIBRARY_PATHS ${LIBRARY_OUTPUT_PATH})
set(GdxCpp_USE_BOX2D TRUE)
find_package(GdxCpp)

include_directories(${GDXCPP_INCLUDE_DIR})

set(APPLICATIONS MyFirstTriangle
    SpriteBatchTest
    PixmapTest
    SpriteCacheTest
    AlphaTest
    DeltaTimeTest
    SpritePerformanceTest
    ParticleEmitterTest
    SoundTest
    SvgBackendTest
    SvgBackendTest2
    BitmapFontTest
    BitmapFontFlipTest
    BaseTest
    box2d/Chain box2d/ApplyForce
    box2d/Bridge box2d/Cantilever
    box2d/CharacterCollision
    box2d/CollisionFiltering
    box2d/ContinuousTest
    box2d/DebugRendererTest
    box2d/OneSidedPlatform
    box2d/Prismatic
    box2d/Pyramid
    box2d/SimpleTest
    box2d/SphereStack
    box2d/VaryingRestitution
    box2d/VerticalStack)


set(EXECUTABLE_OUTPUT_PATH ${GDX_BINARY_ROOT_DIR}/bin/tests/)

#if ndk_root is defined, we're building the android version
if (NDK_ROOT)
    add_subdirectory(backends/android)
endif()

foreach(APP ${APPLICATIONS})
    get_filename_component(APP_NAME ${APP} NAME)
    if (${GENERATED_APPLICATION_TYPE} STREQUAL "EXECUTABLE")
        add_executable(${APP_NAME} ${APP}.cpp)
    elseif (${GENERATED_APPLICATION_TYPE} STREQUAL "SHARED_LIB")
        add_library(${APP_NAME} SHARED ${APP}.cpp)
    endif()

    target_link_libraries(${APP_NAME} ${GDXCPP_LIBRARIES})
#     add_dependencies(${APP_NAME} ${GDXCPP_LIBRARIES})
endforeach()