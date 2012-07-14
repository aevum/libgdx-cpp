project(gdx-cpp-backend-android)

include_directories(${GDXCPP_INCLUDE_DIR} ${SVG_BACKEND_ANTIGRAIN_INCLUDES})

file(GLOB ANDROID_SOURCES *.cpp *.hpp)

gdx_setup_library_target(gdx-cpp-backend-android STATIC "${ANDROID_SOURCES}")
#add_dependencies(gdx-cpp-backend-android gdx-cpp gdx-cpp gdx-cpp-agg-svg GLESv1_CM GLESv2)

install(DIRECTORY . DESTINATION include/gdx-cpp/backends/gdx-cpp-backend-android
          FILES_MATCHING PATTERN "*.hpp")

install(TARGETS gdx-cpp-backend-android
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)
