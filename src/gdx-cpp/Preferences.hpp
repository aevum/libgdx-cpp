
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

#ifndef GDX_CPP__PREFERENCES_HPP_
#define GDX_CPP__PREFERENCES_HPP_

namespace gdx {

class Preferences {
public:
    virtual   void putBoolean (const std::string& key,bool val) = 0;
    virtual   void putInteger (const std::string& key,int val) = 0;
    virtual   void putLong (const std::string& key,long val) = 0;
    virtual   void putFloat (const std::string& key,float val) = 0;
    virtual   void putString (const std::string& key,const std::string& val) = 0;
    virtual   void put (const Map<String, ?>& vals) = 0;
    virtual   bool getBoolean (const std::string& key) = 0;
    virtual   int getInteger (const std::string& key) = 0;
    virtual   long getLong (const std::string& key) = 0;
    virtual   float getFloat (const std::string& key) = 0;
    virtual   std::string& getString (const std::string& key) = 0;
    virtual   bool getBoolean (const std::string& key,bool defValue) = 0;
    virtual   int getInteger (const std::string& key,int defValue) = 0;
    virtual   long getLong (const std::string& key,long defValue) = 0;
    virtual   float getFloat (const std::string& key,float defValue) = 0;
    virtual   std::string& getString (const std::string& key,const std::string& defValue) = 0;
    virtual   bool contains (const std::string& key) = 0;
    virtual   void clear () = 0;
    virtual   void flush () = 0;

protected:


private:

};

} // namespace gdx

#endif // GDX_CPP__PREFERENCES_HPP_
