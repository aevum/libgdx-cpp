#include "init.hpp"
#include <cassert>
#include <jni.h>
#include <gdx-cpp/Gdx.hpp>
#include <gdx-cpp/implementation/System.hpp>
#include <gdx-cpp/ApplicationListener.hpp>
#include "AndroidSystem.hpp"
#include "AndroidApplication.hpp"
#include "AndroidFiles.hpp"

#include <android/log.h>
#include <android/asset_manager_jni.h>

using namespace gdx_cpp;
using namespace gdx_cpp::backends::android;

gdx_cpp::ApplicationListener* applicationListener = 0;
AAssetManager* manager = 0;
bool initialized = false;
bool nativeInitialized = false;
bool created = false;

void createApplication(gdx_cpp::ApplicationListener* listener, const std::string& applicationName, int width, int height)
{
    applicationListener = listener;
}

extern "C" {

void Java_com_aevumlab_gdxcpp_ApplicationManager_nativeInitSystem(JNIEnv* env, jclass clazz, jobject assetManager) {
    __android_log_print(ANDROID_LOG_INFO, "GdxCpp", "nativeInit, initialized is %d", initialized);
    if (!initialized) {
        Gdx::initializeSystem(new AndroidSystem);

        init();

        manager = AAssetManager_fromJava(env, assetManager);
        assert(manager);
                
        initialized = true;
    }
}

void Java_com_aevumlab_gdxcpp_ApplicationManager_nativeInitialize(JNIEnv* env, jobject object, int width, int height) {
    __android_log_print(ANDROID_LOG_INFO, "GdxCpp", "nativeInitialize");
    
    assert(applicationListener);
    if (!nativeInitialized) {
        new AndroidApplication(applicationListener, "test", width, height, false);
        static_cast<AndroidFiles*>(Gdx::files)->setAndroidAssetManager(manager);
        nativeInitialized = true;
    }
}

void Java_com_aevumlab_gdxcpp_ApplicationManager_nativeCreate(JNIEnv* env) {
    __android_log_print(ANDROID_LOG_INFO, "GdxCpp", "nativeCreate");
    assert(applicationListener);
    if (!created) {
        applicationListener->create();
        created = true;
    }
}

void Java_com_aevumlab_gdxcpp_ApplicationManager_nativeUpdate(JNIEnv* env) {
    assert(applicationListener);
    static_cast<AndroidApplication*>(Gdx::app)->update();
}

void Java_com_aevumlab_gdxcpp_ApplicationManager_nativePause(JNIEnv* env) {
    __android_log_print(ANDROID_LOG_INFO, "GdxCpp", "nativePause foi!");
    assert(applicationListener);
    static_cast<AndroidApplication*>(Gdx::app)->pause();
}

void Java_com_aevumlab_gdxcpp_ApplicationManager_nativeResize(JNIEnv* env, jobject object, jint width, jint height) {
    __android_log_print(ANDROID_LOG_INFO, "GdxCpp", "nativeResize: width %d height %d", width, height);
    assert(applicationListener);
    static_cast<AndroidGraphics*>(Gdx::app->getGraphics())->resize(width, height);
}

void Java_com_aevumlab_gdxcpp_ApplicationManager_nativeTouchDownEvent(JNIEnv* env, jobject object, jfloat x, jfloat y, int button ) {
    assert(applicationListener);
    static_cast<AndroidInput*>(Gdx::app->getInput())->handleTouchDown(x, y, button);
}

void Java_com_aevumlab_gdxcpp_ApplicationManager_nativeTouchUpEvent(JNIEnv* env, jobject object, jfloat x, jfloat y, int button ) {
    assert(applicationListener);
    static_cast<AndroidInput*>(Gdx::app->getInput())->handleTouchUp(x, y, button);
}

void Java_com_aevumlab_gdxcpp_ApplicationManager_nativeTouchDragEvent(JNIEnv* env, jobject object, jfloat x, jfloat y, int button ) {
    assert(applicationListener);
    static_cast<AndroidInput*>(Gdx::app->getInput())->handleTouchDrag(x, y, button);
}

}

