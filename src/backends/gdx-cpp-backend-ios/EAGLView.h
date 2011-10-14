//
//  EAGLView.h
//  test1
//
//  Created by Henrique Vieira e Sousa on 30/09/11.
//  Copyright 2011 Universidade Federal de Uberlandia. All rights reserved.
//

#import <UIKit/UIKit.h>

#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>
#import <OpenGLES/EAGL.h>

// This class wraps the CAEAGLLayer from CoreAnimation into a convenient UIView subclass.
// The view content is basically an EAGL surface you render your OpenGL scene into.
// Note that setting the view non-opaque will only work if the EAGL surface has an alpha channel.
@interface EAGLView : UIView
{
@private
    EAGLContext *context;
    
    // The pixel dimensions of the CAEAGLLayer.
    GLint framebufferWidth;
    GLint framebufferHeight;
    
    // The OpenGL ES names for the framebuffer and renderbuffer used to render to this view.
    GLuint defaultFramebuffer, colorRenderbuffer;
	
	NSString				*pixelformat_;
	GLuint					depthFormat_;
	BOOL					preserveBackbuffer_;
	
	CGSize					size_;
	BOOL					discardFramebufferSupported_;
	
	//fsaa addition
	BOOL					multisampling_;
	unsigned int requestedSamples_;
}

@property (nonatomic, retain) EAGLContext *context;
@property(nonatomic,readonly) NSString* pixelFormat;
@property(nonatomic,readonly) GLuint depthFormat;
@property(nonatomic,readonly) CGSize surfaceSize;
@property(nonatomic,readwrite) BOOL multiSampling;
@property(nonatomic, readonly) GLint viewWidth;
@property(nonatomic, readonly) GLint viewHeight;

/** creates an initializes an EAGLView with a frame and 0-bit depth buffer, and a RGB565 color buffer */
+ (id) viewWithFrame:(CGRect)frame;
/** creates an initializes an EAGLView with a frame, a color buffer format, and 0-bit depth buffer */
+ (id) viewWithFrame:(CGRect)frame pixelFormat:(NSString*)format;
/** creates an initializes an EAGLView with a frame, a color buffer format, and a depth buffer format */
+ (id) viewWithFrame:(CGRect)frame pixelFormat:(NSString*)format depthFormat:(GLuint)depth;
/** creates an initializes an EAGLView with a frame, a color buffer format, a depth buffer format, a sharegroup, and multisamping */
+ (id) viewWithFrame:(CGRect)frame pixelFormat:(NSString*)format depthFormat:(GLuint)depth preserveBackbuffer:(BOOL)retained sharegroup:(EAGLSharegroup*)sharegroup multiSampling:(BOOL)multisampling numberOfSamples:(unsigned int)samples;

/** Initializes an EAGLView with a frame and 0-bit depth buffer, and a RGB565 color buffer */
- (id) initWithFrame:(CGRect)frame; //These also set the current context
/** Initializes an EAGLView with a frame, a color buffer format, and 0-bit depth buffer */
- (id) initWithFrame:(CGRect)frame pixelFormat:(NSString*)format;
/** Initializes an EAGLView with a frame, a color buffer format, a depth buffer format, a sharegroup and multisampling support */
- (id) initWithFrame:(CGRect)frame pixelFormat:(NSString*)format depthFormat:(GLuint)depth preserveBackbuffer:(BOOL)retained sharegroup:(EAGLSharegroup*)sharegroup multiSampling:(BOOL)sampling numberOfSamples:(unsigned int)nSamples;

- (void)setFramebuffer;
- (BOOL)presentFramebuffer;

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event;
- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event;
- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event;
- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event;

@end
