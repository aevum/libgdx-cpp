project(gdx-cpp-backend-android)

file(GLOB ANDROID_SOURCES *.cpp *.hpp)
add_library(gdx-cpp-backend-android ${ANDROID_SOURCES})

# target_link_libraries(gdx-cpp-backend-android dl gdx-cpp GLESv1_CM log)
add_dependencies(gdx-cpp-backend-android gdx-cpp)