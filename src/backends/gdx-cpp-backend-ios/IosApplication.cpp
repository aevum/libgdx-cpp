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

#include "IosApplication.hpp"

#include <iostream>
#include <cstdlib>
#include <gdx-cpp/Graphics.hpp>
#include <gdx-cpp/Gdx.hpp>
#include <gdx-cpp/implementation/System.hpp>
#include <list>
#include <stdexcept>

#include "IosGraphics.hpp"

#import <UIKit/UIKit.h>

using namespace gdx_cpp::backends::ios;
using namespace gdx_cpp;

gdx_cpp::backends::ios::IosApplication::IosApplication(gdx_cpp::ApplicationListener* listener)
:  Synchronizable(Gdx::system->getMutexFactory())
, listener(listener)
, graphics(NULL)
, input(0)
, logLevel(gdx_cpp::Application::LOG_INFO)
{
    initialize();
}

void IosApplication::initialize() {
	graphics = new IosGraphics();
//	input = new LinuxInput();
//	files = new LinuxFiles();
//	audio = new LinuxOpenALAudio();
	
	graphics->initialize();
	graphics->setDisplayMode(width, height, false);
	
	Gdx::initialize(this, graphics, NULL, NULL, NULL);
}

void IosApplication::onRunnableStop()
{
    //DUMMY
}

void IosApplication::run()
{    
     graphics->updateTime();
		        
	{
		lock_holder hnd = synchronize();
		
		std::list < Runnable::ptr >::iterator it = runnables.begin();
		std::list < Runnable::ptr >::iterator end = runnables.end();
		
		for(;it != end; ++it) {
			(*it)->run();
		}
		
		runnables.clear();
	}
	
	listener->render();
	graphics->update();
	//audio->update();
    
}


void IosApplication::error(const std::string& tag, const char* format, ...)
{
	va_list ap;
    va_start (ap, format);
	NSString* _format =[[NSString alloc] initWithCString:format];
					   
    if (![_format hasSuffix: @"\n"]) {
		_format = [_format stringByAppendingString: @"\n"];
    }
    NSString *body =  [[NSString alloc] initWithFormat: _format arguments: ap];
    va_end (ap);
    fprintf(stderr,"%s",[body UTF8String]);
    [body release];
	[_format release]; 
}

void IosApplication::exit()
{
    ::exit(0);
}

Audio* IosApplication::getAudio()
{
	
}

Files* IosApplication::getFiles()
{
	throw std::runtime_error("not implemented yet");
//    return files;
}

Graphics* IosApplication::getGraphics()
{
	throw std::runtime_error("not implemented yet");
	//    return graphics;
}

Input* IosApplication::getInput()
{
	throw std::runtime_error("not implemented yet");
//    return input;
}

Preferences* IosApplication::getPreferences(std::string& name)
{
	
}

gdx_cpp::Application::ApplicationType IosApplication::getType()
{
    return gdx_cpp::Application::IOs;
}

void IosApplication::log(const std::string& tag, const char* format, ...)
{
	va_list ap;
    va_start (ap, format);
	NSString* _format =[[NSString alloc] initWithCString:format];
	
    if (![_format hasSuffix: @"\n"]) {
		_format = [_format stringByAppendingString: @"\n"];
    }
    NSString *body =  [[NSString alloc] initWithFormat: _format arguments: ap];
    va_end (ap);
    fprintf(stdout,"%s",[body UTF8String]);
    [body release];
	[_format release]; 
}

int IosApplication::getVersion()
{
    return 0.1;
}

void IosApplication::postRunnable(Runnable::ptr runnable)
{
    lock_holder hnd = synchronize();
    runnables.push_back(runnable);
}

void IosApplication::setLogLevel(int logLevel)
{
    logLevel = logLevel;
}
