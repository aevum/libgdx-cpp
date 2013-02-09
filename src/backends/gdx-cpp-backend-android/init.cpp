#include <cassert>
#include <gdx-cpp/Gdx.hpp>
#include <gdx-cpp/implementation/System.hpp>
#include <gdx-cpp/ApplicationListener.hpp>
#include "AndroidSystem.hpp"
#include "AndroidApplication.hpp"
#include "AndroidFiles.hpp"

#include <jni.h>
#include <android/log.h>
#include <gdx-cpp/files/FileHandle.hpp>
#include "AndroidAudio.hpp"
#include "Android.hpp"
#include "Log.hpp"
#include "AndroidFileHandle.hpp"


#include <unistd.h>
using namespace gdx;
using namespace gdx::android;

gdx::ApplicationListener* applicationListener = 0;
JavaVM* vm = 0;
namespace gdx {
namespace android {
AndroidApplication* app = 0;
}
}
extern "C" void gdxcpp_create_application(gdx::ApplicationListener* listener, const std::string& applicationName, int width, int height, bool useGl20)
{
    applicationListener = listener;
}

extern "C" {  
    void Java_com_aevumlab_gdxcpp_ApplicationManager_nativeInitSystem(JNIEnv* env) {        
        initializeSystem(new AndroidSystem, new gdx::android::Log);
        static_cast<AndroidSystem*>(gdx::system)->setJavaVM(vm);
        gdxcpp_init(1, NULL);
    }

    void Java_com_aevumlab_gdxcpp_ApplicationManager_nativeInitialize(JNIEnv* env, jclass clazz, jobject assetManager, int width, int height) {
        assert(applicationListener);
        gdx::android::app = new AndroidApplication(applicationListener, "gdx-android", width, height, false);
    }

    void Java_com_aevumlab_gdxcpp_ApplicationManager_nativeCreate(JNIEnv* env) {
        assert(applicationListener);
        applicationListener->create();        
    }

    void Java_com_aevumlab_gdxcpp_ApplicationManager_nativeUpdate(JNIEnv* env) {
        assert(applicationListener);
        gdx::android::app->update();
    }

    void Java_com_aevumlab_gdxcpp_ApplicationManager_nativePause(JNIEnv* env) {
        assert(applicationListener);
        gdx::android::app->pause();
    }
    
    void Java_com_aevumlab_gdxcpp_ApplicationManager_nativeResume(JNIEnv* env) {
        assert(applicationListener);
        gdx::android::app->resume();
    }

    void Java_com_aevumlab_gdxcpp_ApplicationManager_nativeResize(JNIEnv* env, jobject object, jint width, jint height) {
        assert(applicationListener);
        static_cast<AndroidGraphics*>(gdx::android::app->getGraphics())->resize(width, height);
    }

    void Java_com_aevumlab_gdxcpp_ApplicationManager_nativeKeyEvent(JNIEnv* env, jobject object, jint keycode, jint action ) {
        assert(applicationListener);        
        static AndroidInput* input = static_cast<AndroidInput*>(gdx::android::app->getInput());
        gdx::android::app->postRunnable([=] {            
            switch(action) {
                case 0:
                    input->handleKeyDown(keycode);
                    break;
                case 1:
                    input->handleKeyUp(keycode);
                    break;
                default:
                    gdx_log_debug("gdx", "received an unhandler onKey action: %d", action);
                    break;
            };
        });
    }
    
    void Java_com_aevumlab_gdxcpp_ApplicationManager_nativeTouchDownEvent(JNIEnv* env, jobject object, jfloat x, jfloat y, int button ) {
        assert(applicationListener);
        static AndroidInput* input = static_cast<AndroidInput*>(gdx::android::app->getInput());
        gdx::android::app->postRunnable([=] {
            input->handleTouchDown(x, y, button);            
        });
    }
    
    void Java_com_aevumlab_gdxcpp_ApplicationManager_nativeTouchUpEvent(JNIEnv* env, jobject object, jfloat x, jfloat y, int button ) {
        assert(applicationListener);
        static AndroidInput* input = static_cast<AndroidInput*>(gdx::android::app->getInput());
        gdx::android::app->postRunnable([=] {
            input->handleTouchUp(x, y, button);            
        });
    }

    void Java_com_aevumlab_gdxcpp_ApplicationManager_nativeTouchDragEvent(JNIEnv* env, jobject object, jfloat x, jfloat y, int button ) {
        assert(applicationListener);       
        static AndroidInput* input = static_cast<AndroidInput*>(gdx::android::app->getInput());       
        gdx::android::app->postRunnable([=] {
            input->handleTouchDrag(x, y, button);
        });
    }

    void Java_com_badlogic_gdx_backends_android_AndroidAudio_registerAudioEngine(JNIEnv* env, jclass clazz, jobject object) {
        assert(applicationListener);
        static_cast<AndroidAudio*>(gdx::android::app->getAudio())->setupJNI(object);
    }
    
    JNIEXPORT jint JNICALL
    JNI_OnLoad(JavaVM *jvm, void *reserved) {
        vm = jvm;
        
        JNIEnv* env;
        vm->GetEnv((void**)&env, JNI_VERSION_1_2);
        
        gdx::android::AndroidFileHandle::bindClasses(env);
        
        return JNI_VERSION_1_2;
    }
}

