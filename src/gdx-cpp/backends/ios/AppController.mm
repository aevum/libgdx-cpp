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
#include "IosGraphics.hpp"
#include "init.hpp"

@implementation AppController

@synthesize window, viewController;

- (BOOL)application:(UIApplication*)application didFinishLaunchingWithOptions:(NSDictionary*)launchOptions {
	self.window = [[UIWindow alloc] initWithFrame: [[UIScreen mainScreen] bounds]];
 
    viewController = [[IosGdxViewController alloc] initWithNibName:nil bundle:nil];
	viewController.wantsFullScreenLayout = YES;
    
    CGFloat scale = [UIScreen mainScreen].scale;
    CGRect screenRect = [UIScreen mainScreen].bounds;
    
    screenRect.size.width *= scale;
    screenRect.size.height *= scale;
        
	gdxcpp_initialize_application(screenRect.size.width, screenRect.size.height);
	
	gdxcpp_create_listener();
    
    static_cast<gdx::ios::IosGraphics*>(gdx::graphics)->resetTimer();
    
    [[UIApplication sharedApplication] setStatusBarHidden:YES withAnimation:UIStatusBarAnimationFade];
    
    [window setRootViewController:viewController];
	[window makeKeyAndVisible];
    
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
    [self.viewController pause];
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
    [self.viewController resume];
}

- (void)dealloc
{
    [viewController release];
    [window release];
    
    [super dealloc];
}

@end
