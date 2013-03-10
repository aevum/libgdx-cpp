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

#import <gdx-cpp/Gdx.hpp>		
#import "IosApplication.hpp"
#import "IosSystem.hpp"
#import "AppController.h"

#include <iostream>

static gdx::ApplicationListener* g_Listener = 0;

class IosLog : public gdx::Log {
public:
    virtual void log (LogLevel log_level, const std::string& tag, const std::string& line, const std::string& file, const char* format, ...) {
        
        static char* levels[] = { "DEBUG" , "INFO", "ERROR", "OTHER" };
        
        va_list list;
        va_start(list, format);
        
        
        NSLogv([NSString stringWithFormat:@"[%s] %s [LINE: %s] %s", levels[(int) log_level], tag.c_str(), line.c_str(), format], list);
        
        va_end(list);
    }
};

extern "C" void gdxcpp_create_application(gdx::ApplicationListener* listener, const std::string& applicationName, int width, int height, bool useOpenGLES2) {
    g_Listener = listener;
}

void gdxcpp_initialize_application(int width, int height) {
    gdxcpp_init(0, NULL);
    new gdx::ios::IosApplication(g_Listener, width, height);
}

void gdxcpp_create_listener() {
    g_Listener->create();
}

int main(int argc, char** argv) {
    NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];

    gdx::initializeSystem(new gdx::ios::IosSystem, new IosLog);
    
    const char* controller = gdxcpp_get_app_controller();
    
    @try {
        int retVal = UIApplicationMain(argc, argv, nil, controller != nil? [NSString stringWithCString:controller encoding:NSASCIIStringEncoding] : NSStringFromClass([AppController class]));
        [pool release];
        return retVal;
    } @catch (NSException * e) {
        NSLog(@"Exception: %@", [e reason]);
    }
    return -1;
}
