/*
    Copyright 2011 <copyright holder> <email>

    Licensed under the Apache License, Version 2.0 (the "License")
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/


#ifndef GDXCPP_APPLICATION_H
#define GDXCPP_APPLICATION_H

#include <string>

namespace gdx_cpp {

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
    
    /** @return the {@link Graphics} instance */
    Graphics& getGraphics () = 0;
    
    /** @return the {@link Audio} instance */
    Audio& getAudio () = 0;
    
    /** @return the {@link Input} instance */
    Input& getInput () = 0;
    
    /** @return the {@link Files} instance */
    Files& getFiles () = 0;
    
    /** Logs a message to the console or logcat */
    void log (stlport::string& tag, stlport::string& message) = 0;
    
    /** Logs a message to the console or logcat */
    void log (stlport::string& tag, stlport::string& message, stlport::exception& exception) = 0;
    
    /** Logs an error message to the console or logcat */
    void error (stlport::string& tag, stlport::string& message) = 0;
    
    /** Logs an error message to the console or logcat */
    void error (stlport::string& tag, stlport::string& message, stlport::exception& exception) = 0;
    
    /** Sets the log level. {@link #LOG_NONE} will mute all log output. {@link #LOG_ERROR} will only let messages issued with
     * {@link #error(stlport::string&, stlport::string&)} through. {@link #LOG_INFO} will let all messages though, either logged via
     * {@link #error(stlport::string&, stlport::string&)} or {@link #log(stlport::string&, stlport::string&)}.
     * @param logLevel {@link #LOG_NONE}, {@link #LOG_ERROR}, {@link #LOG_INFO}. */
    void setLogLevel (int logLevel) = 0;
    
    /** @return what {@link ApplicationType} this application has, e.g. Android or Desktop */
    ApplicationType getType () = 0;
    
    /** @return the Android API level on Android or 0 on the desktop. */
    int getVersion () = 0;
    
    /** @return the Java heap memory use in bytes */
    long getJavaHeap () = 0;
    
    /** @return the Native heap memory use in bytes */
    long getNativeHeap () = 0;
    
    /** Returns the {@link Preferences} instance of this Application. It can be used to store application settings across runs.
     * @param name the name of the preferences, must be useable as a file name.
     * @return the preferences. */
    Preferences& getPreferences (stlport::string& name) = 0;
    
    /** Posts a {@link Runnable} on the main loop thread.
     * 
     * @param runnable the runnable. */
    void postRunnable (Runnable runnable) = 0;
    
    /** Exits the application. This will cause a call to pause() and dispose() some time in the loadFuture, it will not immediately
     * finish your application! */
    void exit () = 0;
};

}
#endif // GDXCPP_APPLICATION_H
