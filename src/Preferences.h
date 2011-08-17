/*
    Copyright 2011 <copyright holder> <email>

    Licensed under the Apache License, Version 2.0 (the "License") = 0;
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/


#ifndef GDX_CPP_PREFERENCES_H
#define GDX_CPP_PREFERENCES_H

namespace gdx_cpp {

class Preferences
{
public:
  virtual void putBoolean (String key, boolean val) = 0;
  
  virtual void putInteger (String key, int val) = 0;
  
  virtual void putLong (String key, long val) = 0;
  
  virtual void putFloat (String key, float val) = 0;
  
  virtual void putString (String key, String val) = 0;
  
  virtual void put (Map<String, ?> vals) = 0;
  
  virtual boolean getBoolean (String key) = 0;
  
  virtual int getInteger (String key) = 0;
  
  virtual long getLong (String key) = 0;
  
  virtual float getFloat (String key) = 0;
  
  virtual String getString (String key) = 0;
  
  virtual boolean getBoolean (String key, boolean defValue) = 0;
  
  virtual int getInteger (String key, int defValue) = 0;
  
  virtual long getLong (String key, long defValue) = 0;
  
  virtual float getFloat (String key, float defValue) = 0;
  
  virtual String getString (String key, String defValue) = 0;
  
  virtual Map<String, ?> get () = 0;
  
  virtual boolean contains (String key) = 0;
  
  virtual void clear () = 0;
  
  /** Makes sure the preferences are persisted. */
  virtual void flush () = 0;
};

}

#endif // GDX_CPP_PREFERENCES_H
