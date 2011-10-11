/*
 Copyright 2011 Aevum Software aevum @ aevumlab.com
 
 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at
 
 http://www.apache.org/licenses/LICENSE-2.0
 
 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 
 @author Victor Vicente de Carvalho victor.carvalho@aevumlab.com
 */

#ifndef GDX_CPP_BACKEND_IOS_IOS_APPLICATION_HPP
#define GDX_CPP_BACKEND_IOS_IOS_APPLICATION_HPP

#include <gdx-cpp/Application.hpp>
#include <gdx-cpp/ApplicationListener.hpp>
#include <gdx-cpp/utils/Synchronized.hpp>
#include <gdx-cpp/Gdx.hpp>
#include <list>

namespace gdx_cpp {
namespace backends {
namespace ios {
	
class IosGraphics;
class IosAudio;
class IosFiles;
class IosInput;
			
class IosApplication : public Application, public Synchronizable {
public:		
	IosApplication(ApplicationListener* p_listener);
		
	void error(const std::string& tag, const char* format, ...);
    void exit();
    Audio* getAudio();
    Files* getFiles();
    Graphics* getGraphics();
    Input* getInput();
    Preferences* getPreferences(std::string& name);
    ApplicationType getType();
    int getVersion();
    void log(const std::string& tag, const char* format, ...);
    void postRunnable(Runnable::ptr runnable);
    void setLogLevel(int logLevel);
	void update();
	void pause();
    void onRunnableStop();
protected:
    void run();
    
    bool useGL20iFAvailable;
    std::string title;
    
	int height;
    int width;
    
	ApplicationListener* listener;
    
	IosGraphics* graphics;
    IosInput* input;
    IosFiles* files;
    IosAudio* audio;
    
    std::list< Runnable::ptr > runnables;
	
    gdx_cpp::implementation::Thread::ptr mainLoopThread;
    
    void initialize();
	
    int logLevel;
};
}
}
}


#endif GDX_CPP_BACKEND_IOS_IOS_APPLICATION_HPP
