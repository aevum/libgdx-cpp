#include "init.hpp"
#include <cassert>
#include <jni.h>
#include <gdx-cpp/Gdx.hpp>
#include <gdx-cpp/implementation/System.hpp>
#include <gdx-cpp/ApplicationListener.hpp>
#include "AndroidSystem.hpp"
#include "AndroidApplication.hpp"

#include <android/log.h>

using namespace gdx_cpp;
using namespace gdx_cpp::backends::android;

gdx_cpp::ApplicationListener* applicationListener = 0;

void createApplication(gdx_cpp::ApplicationListener* listener, const std::string& applicationName, int width, int height)
{
    applicationListener = listener;
}

extern "C" void
Java_com_aevumlab_gdxcpp_ApplicationManager_nativeInitSystem(JNIEnv* env) {
    __android_log_print(ANDROID_LOG_INFO, "GdxCpp", "nativeInit");
    Gdx::initializeSystem(new AndroidSystem);
    init();
}

extern "C" void
Java_com_aevumlab_gdxcpp_ApplicationManager_nativeInitialize(JNIEnv* env, jobject object, int width, int height) {
    __android_log_print(ANDROID_LOG_INFO, "GdxCpp", "nativeInitialize");
    assert(applicationListener);
    new AndroidApplication(applicationListener, "test", width, height, false);
}

extern "C" void
Java_com_aevumlab_gdxcpp_ApplicationManager_nativeCreate(JNIEnv* env) {
    __android_log_print(ANDROID_LOG_INFO, "GdxCpp", "nativeCreate");
    assert(applicationListener);    
    applicationListener->create();
}

extern "C" void
Java_com_aevumlab_gdxcpp_ApplicationManager_nativeUpdate(JNIEnv* env) {
    assert(applicationListener);
    static_cast<AndroidApplication*>(Gdx::app)->update();
}

extern "C" void
Java_com_aevumlab_gdxcpp_ApplicationManager_nativePause(JNIEnv* env) {
    __android_log_print(ANDROID_LOG_INFO, "GdxCpp", "nativePause foi!");
    assert(applicationListener);
    static_cast<AndroidApplication*>(Gdx::app)->pause();
}

extern "C" void
Java_com_aevumlab_gdxcpp_ApplicationManager_nativeResize(JNIEnv* env, jobject object, jint width, jint height) {
    __android_log_print(ANDROID_LOG_INFO, "GdxCpp", "nativeResize: width %d height %d", width, height);
    assert(applicationListener);
    static_cast<AndroidGraphics*>(Gdx::app->getGraphics())->resize(width, height);
}