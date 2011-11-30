#include <cassert>
#include <gdx-cpp/Gdx.hpp>
#include <gdx-cpp/implementation/System.hpp>
#include <gdx-cpp/ApplicationListener.hpp>
#include "AndroidSystem.hpp"
#include "AndroidApplication.hpp"
#include "AndroidFiles.hpp"

#include <android/log.h>
#include <jni.h>
#include <gdx-cpp/files/FileHandle.hpp>
#include "AndroidAudio.hpp"

using namespace gdx_cpp;
using namespace gdx_cpp::backends::android;

gdx_cpp::ApplicationListener* applicationListener = 0;
JavaVM* vm = 0;
AndroidApplication* app = 0;

void createApplication(gdx_cpp::ApplicationListener* listener, const std::string& applicationName, int width, int height)
{
    applicationListener = listener;
}

extern "C" {
   
    void Java_com_aevumlab_gdxcpp_ApplicationManager_nativeInitSystem(JNIEnv* env) {
        __android_log_print(ANDROID_LOG_INFO, "GdxCpp", "nativeInit");
        Gdx::initializeSystem(new AndroidSystem);
        init(1, NULL);       
    }

    void Java_com_aevumlab_gdxcpp_ApplicationManager_nativeInitialize(JNIEnv* env, jclass clazz, jobject assetManager, int width, int height) {
        __android_log_print(ANDROID_LOG_INFO, "GdxCpp", "nativeInitialize aaaaaaaaaaa");

        assert(applicationListener);
        app = new AndroidApplication(applicationListener, "test", width, height, false);
        app->setJavaVM(vm);
    }

    void Java_com_aevumlab_gdxcpp_ApplicationManager_nativeCreate(JNIEnv* env) {
        __android_log_print(ANDROID_LOG_INFO, "GdxCpp", "nativeCreate, list %p", applicationListener);
        assert(applicationListener);
        applicationListener->create();        
    }

    void Java_com_aevumlab_gdxcpp_ApplicationManager_nativeUpdate(JNIEnv* env) {
        assert(applicationListener);
        app->update();
    }

    void Java_com_aevumlab_gdxcpp_ApplicationManager_nativePause(JNIEnv* env) {
        __android_log_print(ANDROID_LOG_INFO, "GdxCpp", "nativePause foi!");
        assert(applicationListener);
        app->pause();
    }

    void Java_com_aevumlab_gdxcpp_ApplicationManager_nativeResize(JNIEnv* env, jobject object, jint width, jint height) {
        __android_log_print(ANDROID_LOG_INFO, "GdxCpp", "nativeResize: width %d height %d", width, height);
        assert(applicationListener);
        static_cast<AndroidGraphics*>(Gdx::app->getGraphics())->resize(width, height);
    }

    enum EventType {
        MOUSE_DOWN,
        MOUSE_DRAG,
        MOUSE_UP
    };


    class EventRunnable : public Runnable {
    public:
        EventRunnable(float _x, float _y, int _button, char _type) :
        x(_x),
        y(_y),
        button(_button),
        type(_type)
        {
        }
        
        virtual void onRunnableStop() {
            delete this;
        }
        
        virtual void run() {
            switch (type) {
                case MOUSE_DOWN:
                    static_cast<AndroidInput*>(Gdx::app->getInput())->handleTouchDown(x, y, button);
                    return;
                case MOUSE_DRAG:
                    static_cast<AndroidInput*>(Gdx::app->getInput())->handleTouchDrag(x, y, button);
                    return;
                case MOUSE_UP:
                    static_cast<AndroidInput*>(Gdx::app->getInput())->handleTouchUp(x, y, button);
                    return;
            }            
        }
        
        float x, y;
        int button;
        char type;
    };
    
    void Java_com_aevumlab_gdxcpp_ApplicationManager_nativeTouchDownEvent(JNIEnv* env, jobject object, jfloat x, jfloat y, int button ) {
        assert(applicationListener);        
        Gdx::app->postRunnable(Runnable::ptr(new EventRunnable(x, y, button, MOUSE_DOWN)));
    }

    void Java_com_aevumlab_gdxcpp_ApplicationManager_nativeTouchUpEvent(JNIEnv* env, jobject object, jfloat x, jfloat y, int button ) {
        assert(applicationListener);
        Gdx::app->postRunnable(Runnable::ptr(new EventRunnable(x, y, button, MOUSE_UP)));
    }

    void Java_com_aevumlab_gdxcpp_ApplicationManager_nativeTouchDragEvent(JNIEnv* env, jobject object, jfloat x, jfloat y, int button ) {
        assert(applicationListener);
        Gdx::app->postRunnable(Runnable::ptr(new EventRunnable(x, y, button, MOUSE_DRAG)));
    }

    void Java_com_badlogic_gdx_backends_android_AndroidAudio_registerAudioEngine(JNIEnv* env, jclass clazz, jobject object) {
        assert(applicationListener);
        static_cast<AndroidAudio*>(Gdx::app->getAudio())->setupJNI(env, object);
    }
    
    JNIEXPORT jint JNICALL
    JNI_OnLoad(JavaVM *jvm, void *reserved) {
        __android_log_print(ANDROID_LOG_INFO, "GdxCpp", "onLoad");
        vm = jvm;

        return JNI_VERSION_1_2;
    }
}


