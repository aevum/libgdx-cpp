
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

#ifndef GDX_CPP_UTILS_LONGMAP<V>_HPP_
#define GDX_CPP_UTILS_LONGMAP<V>_HPP_

namespace gdx_cpp {
namespace utils {

class LongMap {
public:
    V& put (long key,const V& value);
    void putAll (const LongMap<V>& map);
    V& get (long key);
    V& remove (long key);
    void clear ();
    bool containsValue (const Object& value,bool identity);
    bool containsKey (long key);
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
    long next ();
    LongArray& toArray ();

protected:


private:
    void putResize (long key,const V& value);
    void push (long insertKey,const V& insertValue,int index1,long key1,int index2,long key2,int index3,long key3);
    void putStash (long key,const V& value);
    V& getStash (long key);
    bool containsKeyStash (long key);
    void resize (int newSize);
    int hash2 (long h);
    int hash3 (long h);
};

} // namespace gdx_cpp
} // namespace utils

#endif // GDX_CPP_UTILS_LONGMAP<V>_HPP_
