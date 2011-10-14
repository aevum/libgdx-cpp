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


#import "IosGdxViewController.h"
#import "EAGLView.h"

#include <gdx-cpp/Gdx.hpp>
#import <QuartzCore/QuartzCore.h>

@interface IosGdxViewController ()
@property (nonatomic, retain) EAGLContext *context;
@end

@implementation IosGdxViewController

@synthesize context, displayLink;

- (id) initWithNibName:(NSString* ) nibNameOrNil bundle:(NSBundle*)nibBundleOrNil {
	if (self = [ super initWithNibName:nibNameOrNil bundle:nibBundleOrNil]) {
		isRunning = FALSE;
	}
	return self;
}

- (void) loadView {
	
}

- (void) viewDidLoad {
	[super viewDidLoad];	 
}

- (BOOL) shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation) interfaceOrientation {
	return UIInterfaceOrientationIsLandscape(interfaceOrientation);
}

- (void) didReceiveMemoryWarning {
	[super didReceiveMemoryWarning];
}

- (void) viewDidUnload {
	[super viewDidUnload];
}

- (void) dealloc {
	if ([EAGLContext currentContext] == context)
        [EAGLContext setCurrentContext:nil];
    
    [context release];
    
    [super dealloc];
}

- (void) resume {
	if (!isRunning) {
		CADisplayLink *aDisplayLink = [[UIScreen mainScreen] displayLinkWithTarget:self selector:@selector(mainLoop)];
		[aDisplayLink setFrameInterval:1];
		[aDisplayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
		self.displayLink = aDisplayLink;
	}
}

- (void) pause {
	if (isRunning)
    {
        [self.displayLink invalidate];
        self.displayLink = nil;
        isRunning = FALSE;
    }	
}

- (void) mainLoop {
	[(EAGLView*)self.view setFramebuffer];
	gdx_cpp::Gdx::app->update();
	[(EAGLView*)self.view presentFramebuffer];
}

@end