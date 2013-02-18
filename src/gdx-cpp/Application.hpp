/*
 *  Copyright 2011 Aevum Software aevum @ aevumlab.com
 * 
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 * 
 *      http://www.apache.org/licenses/LICENSE-2.0
 * 
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 * 
 *  @author Victor Vicente de Carvalho victor.carvalho@aevumlab.com
 *  @author Ozires Bortolon de Faria ozires@aevumlab.com
 */

#ifndef GDXCPP_APPLICATION_H
#define GDXCPP_APPLICATION_H

#include <string>
#include <ostream>
#include <functional>
#include "gdx-cpp/utils/Runnable.hpp"

class Runnable;

namespace gdx {

class Graphics;
class Audio;
class Files;
class Preferences;
class Input;

class Application
{
public:
    /** Enumeration of possible {@link Application} types
     * 
     * @author mzechner */
    enum ApplicationType {
      Android, Desktop, IOs
    };
    
    static const int LOG_NONE = 0;
    static const int LOG_INFO = 1;
    static const int LOG_ERROR = 2;
    
    virtual Graphics* getGraphics () = 0;
    
    virtual Audio* getAudio () = 0;
    
    virtual Input* getInput () = 0;
    
    virtual Files* getFiles () = 0;
        
    virtual void setLogLevel (int logLevel) = 0;
    
    virtual ApplicationType getType () = 0;
    
    virtual int getVersion () = 0;
    
    virtual Preferences* getPreferences (std::string& name) = 0;
    
    virtual void postRunnable (Runnable::ptr runnable) = 0;
    virtual void postRunnable (std::function< void() > runnable) = 0;
    
    virtual void exit () = 0;
    virtual void update() = 0;
    virtual void pause() = 0;
    
    virtual ~Application() {}
};

}
#endif // GDXCPP_APPLICATION_H
