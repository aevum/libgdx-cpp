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


#ifndef GDX_CPP_PREFERENCES_H
#define GDX_CPP_PREFERENCES_H

#include <hash_map>
#include <string>

namespace gdx_cpp {

class Preferences
{
public:
  virtual void putBoolean (stlport::string& key, bool val) = 0;
  
  virtual void putInteger (stlport::string& key, int val) = 0;
  
  virtual void putLong (stlport::string& key, long val) = 0;
  
  virtual void putFloat (stlport::string& key, float val) = 0;
  
  virtual void putstlport::string (stlport::string& key, stlport::string& val) = 0;

  template <typename T>
  virtual void put (stlport::hash_map<stlport::string&, T> vals) = 0;
  
  virtual bool getBoolean (stlport::string& key) = 0;
  
  virtual int getInteger (stlport::string& key) = 0;
  
  virtual long getLong (stlport::string& key) = 0;
  
  virtual float getFloat (stlport::string& key) = 0;
  
  virtual stlport::string& getstlport::string& (stlport::string& key) = 0;
  
  virtual bool getBoolean (stlport::string& key, bool defValue) = 0;
  
  virtual int getInteger (stlport::string& key, int defValue) = 0;
  
  virtual long getLong (stlport::string& key, long defValue) = 0;
  
  virtual float getFloat (stlport::string& key, float defValue) = 0;
  
  virtual stlport::string& getstlport::string& (stlport::string& key, stlport::string& defValue) = 0;

  template <typename T>
  virtual stlport::hash_map<stlport::string&, T> get () = 0;
  
  virtual bool contains (stlport::string& key) = 0;
  
  virtual void clear () = 0;
  
  /** Makes sure the preferences are persisted. */
  virtual void flush () = 0;
};

}

#endif // GDX_CPP_PREFERENCES_H
