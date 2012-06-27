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

#include "IosAudio.hpp"
#include "IosGraphics.hpp"
#include "IosFiles.hpp"
#include "IosInput.hpp"

#import <UIKit/UIKit.h>

using namespace gdx::ios;
using namespace gdx;

gdx::ios::IosApplication::IosApplication(gdx::ApplicationListener* listener)
:  Synchronizable(system->getMutexFactory())
, listener(listener)
, graphics(NULL)
, input(NULL)
, files(NULL)
, logLevel(gdx::Application::LOG_INFO)
{
    initialize();
}

void IosApplication::initialize() {
	graphics = new IosGraphics();
	input = new IosInput();
	files = new IosFiles();
	audio = new IosAudio();
	
	graphics->initialize();
	graphics->setDisplayMode(width, height, false);
	
	initialize(this, graphics, audio, input, files);
}

void IosApplication::onRunnableStop()
{
    //DUMMY
}


void IosApplication::run()
{    
 	//audio->update();
    
}

void IosApplication::update()
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

void IosApplication::pause()
{    
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
	//[_format release]; 
}

void IosApplication::exit()
{
    ::exit(0);
}

Audio* IosApplication::getAudio()
{
    return audio;
}

Files* IosApplication::getFiles()
{
	return files;
}

Graphics* IosApplication::getGraphics()
{
	return graphics;
}

Input* IosApplication::getInput()
{
	return input;
}

Preferences* IosApplication::getPreferences(std::string& name)
{
	throw std::runtime_error("not implemented yet");
}

gdx::Application::ApplicationType IosApplication::getType()
{
    return gdx::Application::IOs;
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
	//[_format release]; 
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
