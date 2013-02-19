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
 */

#import <QuartzCore/QuartzCore.h>

#import "EAGLView.h"

#include <gdx-cpp/Gdx.hpp>
#include "IosInput.hpp"

@interface EAGLView (PrivateMethods)
- (void)createFramebuffer;
- (void)deleteFramebuffer;
- (BOOL) setupSurfaceWithSharegroup:(EAGLSharegroup*)sharegroup;
@end

@implementation EAGLView

@synthesize surfaceSize=size_;
@synthesize pixelFormat=pixelformat_, depthFormat=depthFormat_;
@synthesize multiSampling=multiSampling_;
@synthesize viewWidth=framebufferWidth, viewHeight=framebufferHeight;

@dynamic context;

// You must implement this method
+ (Class)layerClass
{
    return [CAEAGLLayer class];
}

+ (id) viewWithFrame:(CGRect)frame
{
	return [[[self alloc] initWithFrame:frame] autorelease];
}

+ (id) viewWithFrame:(CGRect)frame pixelFormat:(NSString*)format
{
	return [[[self alloc]initWithFrame:frame pixelFormat:format] autorelease];
}

+ (id) viewWithFrame:(CGRect)frame pixelFormat:(NSString*)format depthFormat:(GLuint)depth
{
	return [[[self alloc] initWithFrame:frame pixelFormat:format depthFormat:depth preserveBackbuffer:NO sharegroup:nil multiSampling:NO numberOfSamples:0] autorelease];
}

+ (id) viewWithFrame:(CGRect)frame pixelFormat:(NSString*)format depthFormat:(GLuint)depth preserveBackbuffer:(BOOL)retained sharegroup:(EAGLSharegroup*)sharegroup multiSampling:(BOOL)multisampling numberOfSamples:(unsigned int)samples
{
	return [[[self alloc]initWithFrame:frame pixelFormat:format depthFormat:depth preserveBackbuffer:retained sharegroup:sharegroup multiSampling:multisampling numberOfSamples:samples] autorelease];
}

- (id) initWithFrame:(CGRect)frame
{
	return [self initWithFrame:frame pixelFormat:kEAGLColorFormatRGB565 depthFormat:0 preserveBackbuffer:NO sharegroup:nil multiSampling:NO numberOfSamples:0];
}

- (id) initWithFrame:(CGRect)frame pixelFormat:(NSString*)format 
{
	return [self initWithFrame:frame pixelFormat:format depthFormat:0 preserveBackbuffer:NO sharegroup:nil multiSampling:NO numberOfSamples:0];
}

- (id) initWithFrame:(CGRect)frame pixelFormat:(NSString*)format depthFormat:(GLuint)depth preserveBackbuffer:(BOOL)retained sharegroup:(EAGLSharegroup*)sharegroup multiSampling:(BOOL)sampling numberOfSamples:(unsigned int)nSamples
{
	if((self = [super initWithFrame:frame]))
	{
		pixelformat_ = format;
		depthFormat_ = depth;
		multiSampling_ = sampling;			
		requestedSamples_ = nSamples;
		preserveBackbuffer_ = retained;
		if( ! [self setupSurfaceWithSharegroup:sharegroup] ) {
			[self release];
			return nil;
		}
        
        self.multipleTouchEnabled = YES;
        toucheshHolder = [[NSMutableArray alloc] init];
        scale = [[UIScreen mainScreen] scale];
	}
		
	return self;
}

- (id)initWithCoder:(NSCoder*)coder
{
	if( (self = [super initWithCoder:coder]) ) {			
		CAEAGLLayer* eaglLayer = (CAEAGLLayer*)[self layer];
		
		pixelformat_ = kEAGLColorFormatRGB565;
		depthFormat_ = 0; // GL_DEPTH_COMPONENT24_OES;
		multiSampling_= NO;
		requestedSamples_ = 0;
		size_ = [eaglLayer bounds].size;
		
		if( ! [self setupSurfaceWithSharegroup:nil] ) {
			[self release];
			return nil;
		}

        self.multipleTouchEnabled = YES;
        toucheshHolder = [[NSMutableArray alloc] init];
	}
	
	return self;
}

-(BOOL) setupSurfaceWithSharegroup:(EAGLSharegroup*)sharegroup
{
	CAEAGLLayer *eaglLayer = (CAEAGLLayer *)self.layer;
	
	eaglLayer.opaque = YES;
	eaglLayer.drawableProperties = [NSDictionary dictionaryWithObjectsAndKeys:
									[NSNumber numberWithBool:preserveBackbuffer_], kEAGLDrawablePropertyRetainedBacking,
									pixelformat_, kEAGLDrawablePropertyColorFormat, nil];
	
    eaglLayer.contentsScale = [[UIScreen mainScreen] scale];
	
	self.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES1];
	
	if (!self.context)
		NSLog(@"Failed to create ES context");
	else if (![EAGLContext setCurrentContext:self.context])
		NSLog(@"Failed to set ES context current");
		
	[self.context renderbufferStorage:GL_RENDERBUFFER_OES fromDrawable:eaglLayer];
	
    [EAGLContext setCurrentContext:context];
    
	return YES;
}

- (void)dealloc
{
    [self deleteFramebuffer];    
    [context release];
    
    [super dealloc];
}

- (EAGLContext *)context
{
    return context;
}

- (void)setContext:(EAGLContext *)newContext
{
    if (context != newContext)
    {
        [self deleteFramebuffer];
        
        [context release];
        context = [newContext retain];
        
        [EAGLContext setCurrentContext:nil];
    }
}

- (void)createFramebuffer
{
    if (context && !defaultFramebuffer)
    {
        [EAGLContext setCurrentContext:context];
        
        // Create default framebuffer object.
        glGenFramebuffers(1, &defaultFramebuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, defaultFramebuffer);
        
        // Create color render buffer and allocate backing store.
        glGenRenderbuffers(1, &colorRenderbuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, colorRenderbuffer);
        [context renderbufferStorage:GL_RENDERBUFFER fromDrawable:(CAEAGLLayer *)self.layer];
        glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH, &framebufferWidth);
        glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, &framebufferHeight);
        
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, colorRenderbuffer);
               
        if (multiSampling_) {
            //Generate our MSAA Frame and Render buffers
            glGenFramebuffers(1, &msaaFrameBuffer);
            glBindFramebuffer(GL_FRAMEBUFFER, msaaFrameBuffer);
        
            glGenFramebuffers(1, &msaaRenderBuffer);
            glBindRenderbuffer(GL_RENDERBUFFER, msaaRenderBuffer);
        
            
            GLint maxSamples;
            glGetIntegerv(GL_MAX_SAMPLES_APPLE, &maxSamples);
            int resultSamples = MIN(requestedSamples_, maxSamples);
            
            // Generate the msaaDepthBuffer.
            // 4 will be the number of pixels that the MSAA buffer will use in order to make one pixel on the render buffer.
            glRenderbufferStorageMultisampleAPPLE(GL_RENDERBUFFER, resultSamples, GL_RGB5_A1, framebufferWidth, framebufferHeight);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, msaaRenderBuffer);
        }
        
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            NSLog(@"Failed to make complete framebuffer object %x", glCheckFramebufferStatus(GL_FRAMEBUFFER));
    }
}

- (void)deleteFramebuffer
{
    if (context)
    {
        [EAGLContext setCurrentContext:context];
        
        if (defaultFramebuffer)
        {
            glDeleteFramebuffers(1, &defaultFramebuffer);
            defaultFramebuffer = 0;
        }
        
        if (colorRenderbuffer)
        {
            glDeleteRenderbuffers(1, &colorRenderbuffer);
            colorRenderbuffer = 0;
        }
        
        if (msaaFrameBuffer) {
            glDeleteFramebuffers(1, &msaaFrameBuffer);
            msaaFrameBuffer = 0;
        }
        
        if (msaaRenderBuffer) {
            glDeleteRenderbuffers(1, &msaaRenderBuffer);
            msaaRenderBuffer = 0;
        }
        
        if (msaaDepthBuffer) {
            glDeleteRenderbuffers(1, &msaaDepthBuffer);
            msaaDepthBuffer = 0;
        }
    }
}

- (void)setFramebuffer
{
    if (context)
    {
        [EAGLContext setCurrentContext:context];
        
        if (!defaultFramebuffer)
            [self createFramebuffer];
        
        glBindFramebuffer(GL_FRAMEBUFFER, multiSampling_ ? msaaFrameBuffer : defaultFramebuffer);
        glViewport(0, 0, framebufferWidth, framebufferHeight);
    }
}

- (BOOL)presentFramebuffer
{
    BOOL success = FALSE;
    
    if (context)
    {
        [EAGLContext setCurrentContext:context];
                
        if (multiSampling_) {
            glBindFramebuffer(GL_READ_FRAMEBUFFER_APPLE, msaaFrameBuffer);
            glBindFramebuffer(GL_DRAW_FRAMEBUFFER_APPLE, defaultFramebuffer);
        
            glResolveMultisampleFramebufferAPPLE();
        
            GLenum attachments[] = { GL_COLOR_ATTACHMENT0 };
            glDiscardFramebufferEXT(GL_READ_FRAMEBUFFER_APPLE, 1, attachments);
        }
        
        glBindRenderbuffer(GL_RENDERBUFFER, colorRenderbuffer);
        
        success = [context presentRenderbuffer:GL_RENDERBUFFER];
    }
    
    return success;
}

- (void)layoutSubviews
{
    // The framebuffer will be re-created at the beginning of the next setFramebuffer method call.
    [self deleteFramebuffer];
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {
	for (UITouch *touch in touches) {
        if (![toucheshHolder containsObject:touches]) {
            CGPoint pos = [touch locationInView:self];
            ((gdx::ios::IosInput*)gdx::input)->handleTouchDown(pos.x * scale, pos.y * scale, [toucheshHolder count]);
            [toucheshHolder addObject:touch];
        }		
	}
}	

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event {
	for (UITouch *touch in touches) {
		CGPoint pos = [touch locationInView:self];
		((gdx::ios::IosInput*)gdx::input)->handleTouchDrag(pos.x * scale, pos.y * scale, [toucheshHolder indexOfObject:touch]);
	}
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event {
    NSMutableArray* toRemove = [[NSMutableArray alloc] init];
    
	for (UITouch *touch in touches) {
		CGPoint pos = [touch locationInView:self];
		((gdx::ios::IosInput*)gdx::input)->handleTouchUp(pos.x * scale, pos.y * scale, [toucheshHolder indexOfObject:touch]);
        [toRemove addObject:touch];
	}
    
    for (UITouch* rm in toRemove) {
        [toucheshHolder removeObject:rm];
    }
}

- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event {
	int i = 0;
	for (UITouch *touch in touches) {
		CGPoint pos = [touch locationInView:self];
		((gdx::ios::IosInput*)gdx::input)->handleTouchUp(pos.x * scale, pos.y * scale, i++);
	}
}

@end
