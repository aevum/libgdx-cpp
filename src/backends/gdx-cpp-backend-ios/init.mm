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

static gdx_cpp::ApplicationListener* g_Listener = 0;

void gdxcpp_create_application(gdx_cpp::ApplicationListener* listener, const std::string& applicationName,
                               int width, int height) {
    g_Listener = listener;
}

void gdxcpp_initialize_application() {
    gdxcpp_init(0, NULL);
    new gdx_cpp::backends::ios::IosApplication(g_Listener);
}

void gdxcpp_create_listener() {
    g_Listener->create();
}

int main(int argc, char** argv) {
    NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
    gdx_cpp::Gdx::initializeSystem(new gdx_cpp::backends::ios::IosSystem);
    
    NSString* controller = gdxcpp_get_app_controller();
    
    int retVal = UIApplicationMain(argc, argv, nil, controller != nil? controller : NSStringFromClass([AppController class]));

    [pool release];
    return retVal;
}
