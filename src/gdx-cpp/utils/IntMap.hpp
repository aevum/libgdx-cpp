
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

#ifndef GDX_CPP_UTILS_INTMAP<V>_HPP_
#define GDX_CPP_UTILS_INTMAP<V>_HPP_

namespace gdx_cpp {
namespace utils {

class IntMap {
public:
    V& put (int key,const V& value);
    void putAll (const IntMap<V>& map);
    V& get (int key);
    V& remove (int key);
    void clear ();
    bool containsValue (const Object& value,bool identity);
    bool containsKey (int key);
    void ensureCapacity (int additionalCapacity);
    std::string& toString ();
    Entries<V>& entries ();
    Values<V>& values ();
    Keys& keys ();
    std::string& toString ();
    void reset ();
    void remove ();
    Entry<V>& next ();
    bool hasNext ();
    Iterator<Entry<V>>& iterator ();
    bool hasNext ();
    V& next ();
    Iterator<V>& iterator ();
    Array<V>& toArray ();
    int next ();
    IntArray& toArray ();

protected:


private:
    void putResize (int key,const V& value);
    void push (int insertKey,const V& insertValue,int index1,int key1,int index2,int key2,int index3,int key3);
    void putStash (int key,const V& value);
    V& getStash (int key);
    bool containsKeyStash (int key);
    void resize (int newSize);
    int hash2 (int h);
    int hash3 (int h);
};

} // namespace gdx_cpp
} // namespace utils

#endif // GDX_CPP_UTILS_INTMAP<V>_HPP_
