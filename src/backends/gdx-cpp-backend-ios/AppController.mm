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


#include "AppController.h"

#import <UIKit/UIKit.h>
#import "EAGLView.h"

#import <gdx-cpp/Gdx.hpp>

#include "init.cpp"

@implementation AppController

#pragma mark -
#pragma mark Application lifecycle

- (BOOL)application:(UIApplication*)application didFinishLaunchingWithOptions:(NSDictionary*)launchOptions {
	window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
	EAGLView* glview = [EAGLView viewWithFrame:[window bounds]
								   pixelFormat: kEAGLColorFormatRGBA8
								   depthFormat: GL_DEPTH_COMPONENT16_OES
							preserveBackBuffer: NO
									sharegroup: nil
								 multiSampling: NO
							   numberOfSamples:0];
	
	viewController = [[View alloc] initWithNibName:nil bundle:nil];
	viewController.wantsFullScreenLayout = YES;
	viewController.view = glview;
	
	window.rootViewController = viewController;
	[window makeAKeyAndVisible];
			  
	initializeGdxApplication();
			
	return YES;
}
			  
			  - (void) applicationWillResignActive:(UIApplication*) application {
				  
				  
			  }
			  
			  
			  @end
