#include "init.hpp"
#include <cassert>
#include <jni.h>
#include <gdx-cpp/Gdx.hpp>
#include <gdx-cpp/implementation/System.hpp>
#include "AndroidSystem.hpp"
#include "AndroidApplication.hpp"

using namespace gdx_cpp;
using namespace gdx_cpp::backends::android;

static gdx_cpp::ApplicationListener* applicationListener = 0;

void setApplicationListener(ApplicationListener* listener)
{
    applicationListener = listener;
}

void
Java_com_aevumlab_gdxcpp_ApplicationHandler_nativeInit(JNIEnv* env) {
    Gdx::initializeSystem(new AndroidSystem);
}

void
Java_com_aevumlab_gdxcpp_ApplicationHandler_nativeCreate(JNIEnv* env) {
    assert(applicationListener);
    AndroidApplication* app = new AndroidApplication(applicationListener, "test", 840, 480, false);
}

void
Java_com_aevumlab_gdxcpp_ApplicationHandler_nativeUpdate(JNIEnv* env) {
    assert(applicationListener);
    Gdx::app->update();
}

void
Java_com_aevumlab_gdxcpp_ApplicationHandler_nativePause(JNIEnv* env) {
    assert(applicationListener);
    Gdx::app->pause();
}