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
#import <OpenGLES/EAGL.h>

#import "IosGdxViewController.h"

#import <OpenGLES/EAGLDrawable.h>
#include <gdx-cpp/Gdx.hpp>

#include "init.hpp"

@implementation AppController

@synthesize window, viewController;

- (void) applicationDidFinishLaunching:(UIApplication *)application {
	NSLog(@"Teste");	
}

- (BOOL)application:(UIApplication*)application didFinishLaunchingWithOptions:(NSDictionary*)launchOptions {
	self.window = [[UIWindow alloc] initWithFrame: [[UIScreen mainScreen] bounds]];
	
	EAGLView *glView = [EAGLView viewWithFrame: [window bounds]
									 pixelFormat: kEAGLColorFormatRGBA8
									 depthFormat: GL_DEPTH_COMPONENT16_OES
							  preserveBackbuffer: NO
									  sharegroup:nil
								   multiSampling:NO
								 numberOfSamples:0];
    
	
	viewController = [[IosGdxViewController alloc] initWithNibName:nil bundle:nil];
	[viewController retain];
	
	viewController.wantsFullScreenLayout = YES;
	[viewController setView:glView];
	[glView setFramebuffer];
	[glView retain];
	
	window.rootViewController = viewController;
	[window makeKeyAndVisible];
	
	gdxcpp_initialize_application();	
	gdx_cpp::Gdx::graphics->setDisplayMode(glView.viewWidth, glView.viewHeight, true);
	gdxcpp_create_listener();
	
    [[UIApplication sharedApplication] setStatusBarHidden:NO withAnimation:UIStatusBarAnimationFade];
    
	return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application
{
    [self.viewController pause];
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
    [self.viewController resume];
}

- (void)applicationWillTerminate:(UIApplication *)application
{
    [self.viewController pause];
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
}

- (void)dealloc
{
    [viewController release];
    [window release];
    
    [super dealloc];
}



@end
