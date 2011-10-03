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
 @author Ozires Bortolon de Faria ozires@aevumlab.com
 */

#include "init.hpp"

#import <UIKit/UIKit.h>
#import <gdx-cpp/Gdx.hpp>
#import "IosApplication.h"
#import "IosSystem.hpp"

static gdx_cpp::ApplicationListener* g_Listener = 0;
static int g_width = 0;
static int g_height = 0;

void createApplication(gdx_cpp::ApplicationListener* listener, const std::string& applicationName, 
					   int width, int height) {
	g_Listener = listener;
	g_width = width;
	g_height = height;
}

void initializeGdxApplication(){
	new gdx_cpp::backends::ios::IosApplication(g_Listener, g_width, g_height);
}

int main(int argc, char** argv) {
	gdx_cpp::Gdx::initializeSystem(new gdx_cpp::backends::ios::IosSystem);
	
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	int retVal = UIApplicationMain(argc, argv, nil, nil);
	[pool release];
	return retVal;
}
