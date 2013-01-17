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

    enum EventType {
        MOUSE_DOWN,
        MOUSE_DRAG,
        MOUSE_UP,
        BACK_PRESSED
    };


    class EventRunnable : public Runnable {
    public:
        EventRunnable(float _x, float _y, int _button, char _type) :
        x(_x),
y(_y),
button(_button),
type(_type) {
        }
        
        EventRunnable(char _type) :
        type(_type) {
        }
        
        virtual void onRunnableStop() {
            delete this;
        }
        
        virtual void run() {
            switch (type) {
                case MOUSE_DOWN:
                    static_cast<AndroidInput*>(gdx::android::app->getInput())->handleTouchDown(x, y, button);
                    return;
                case MOUSE_DRAG:
                    static_cast<AndroidInput*>(gdx::android::app->getInput())->handleTouchDrag(x, y, button);
                    return;
                case MOUSE_UP:
                    static_cast<AndroidInput*>(gdx::android::app->getInput())->handleTouchUp(x, y, button);
                    return;
                case BACK_PRESSED:
                    static_cast<AndroidInput*>(gdx::android::app->getInput())->backPressed();
                    return;
            }            
        }
        
        float x, y;
        int button;
        char type;
    };
    
    void Java_com_aevumlab_gdxcpp_ApplicationManager_nativeTouchDownEvent(JNIEnv* env, jobject object, jfloat x, jfloat y, int button ) {
        assert(applicationListener);
        gdx::android::app->postRunnable(Runnable::ptr(new EventRunnable(x, y, button, MOUSE_DOWN)));
    }
    
    void Java_com_aevumlab_gdxcpp_ApplicationManager_nativeBackPressed(JNIEnv* env, jobject object) {
        assert(applicationListener);
//         gdx_log_debug("Android", "Back Pressed");
        gdx::android::app->postRunnable(Runnable::ptr(new EventRunnable(BACK_PRESSED)));
    }

    void Java_com_aevumlab_gdxcpp_ApplicationManager_nativeTouchUpEvent(JNIEnv* env, jobject object, jfloat x, jfloat y, int button ) {
        assert(applicationListener);
        gdx::android::app->postRunnable(Runnable::ptr(new EventRunnable(x, y, button, MOUSE_UP)));
    }

    void Java_com_aevumlab_gdxcpp_ApplicationManager_nativeTouchDragEvent(JNIEnv* env, jobject object, jfloat x, jfloat y, int button ) {
        assert(applicationListener);
        gdx::android::app->postRunnable(Runnable::ptr(new EventRunnable(x, y, button, MOUSE_DRAG)));
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

