project(gdx-cpp-tests)

include_directories(${GDXCPP_INCLUDE_DIR})

set(APPLICATIONS MyFirstTriangle SpriteBatchTest PixmapTest SpriteCacheTest
    AlphaTest DeltaTimeTest SpritePerformanceTest ParticleEmitterTest SoundTest
    SvgBackendTest
    SvgBackendTest2
    box2d/Chain box2d/ApplyForce box2d/Bridge box2d/Cantilever box2d/CharacterCollision box2d/CollisionFiltering box2d/ContinuousTest
    box2d/DebugRendererTest box2d/OneSidedPlatform box2d/Prismatic box2d/Pyramid box2d/SimpleTest box2d/SphereStack box2d/VaryingRestitution
    box2d/VerticalStack)

message("Active backend is: " ${ACTIVE_BACKENDS})
message ("REsouresasdfa : " ${CMAKE_SOURCE_DIR}/etc/assets/data)

foreach(BACKEND ${ACTIVE_BACKENDS})
    include_directories(${GDX_CPP_BACKEND_${BACKEND}_INCLUDES})
    string(TOLOWER ${BACKEND} backend)
    set(EXECUTABLE_OUTPUT_PATH ${GDX_BINARY_ROOT_DIR}/bin/tests/${backend})

    if (${BACKEND} STREQUAL ANDROID)
        add_subdirectory(backends/android)
    endif()
    
    foreach(APP ${APPLICATIONS})
        get_filename_component(APP_NAME ${APP} NAME)
        if (${GENERATED_APPLICATION_TYPE} STREQUAL "EXECUTABLE")
		add_executable(${APP_NAME} ${APP}.cpp)         
           	
           	if (${BACKEND} STREQUAL IOS)
			set_source_files_properties(
				${RESOURCES}
				PROPERTIES
				MACOSX_PACKAGE_LOCATION "Resources"
			)

			set(APP_COMPLETE_NAME \${TARGET_BUILD_DIR}/\${FULL_PRODUCT_NAME})
			set(RES_DIR ${CMAKE_SOURCE_DIR}/etc/assets/data)
			add_custom_command(
			    TARGET ${APP_NAME}
			    POST_BUILD
			    COMMAND /Developer/Library/PrivateFrameworks/DevToolsCore.framework/Resources/pbxcp -exclude .DS_Store -exclude CVS -exclude .svn -resolve-src-symlinks ${RES_DIR} ${APP_COMPLETE_NAME})

           		set_target_properties(${APP_NAME} PROPERTIES XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "iPhone Developer: Aevum Team")
           		set_target_properties(${APP_NAME} PROPERTIES MACOSX_BUNDLE ON)
           	endif()
        elseif (${GENERATED_APPLICATION_TYPE} STREQUAL "SHARED_LIB")
            add_library(${APP_NAME} SHARED ${APP}.cpp)
        endif()        
        target_link_libraries(${APP_NAME} gdx-cpp gdx-cpp-backend-${backend} ${BACKEND-${BACKEND}-DEPENDENCIES} gdx-cpp-box2d gdx-cpp-box2d-layer)
        add_definitions(-DCURRENT_BACKEND_${BACKEND})
        add_dependencies(${APP_NAME} gdx-cpp gdx-cpp-backend-${backend})
    endforeach()
endforeach()


