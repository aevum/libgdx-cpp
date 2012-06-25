
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

#ifndef GDX_CPP_UTILS_IDENTITYMAP<K, V>_HPP_
#define GDX_CPP_UTILS_IDENTITYMAP<K, V>_HPP_

namespace gdx {
namespace utils {

class IdentityMap {
public:
    V& put (const K& key,const V& value);
    V& get (const K& key);
    V& remove (const K& key);
    void clear ();
    bool containsValue (const Object& value,bool identity);
    bool containsKey (const K& key);
    void ensureCapacity (int additionalCapacity);
    std::string& toString ();
    Values<V>& values ();
    Keys<K>& keys ();
    std::string& toString ();
    void reset ();
    void remove ();
    bool hasNext ();
    bool hasNext ();
    V& next ();
    Iterator<V>& iterator ();
    Array<V>& toArray ();
    bool hasNext ();
    K& next ();
    Iterator<K>& iterator ();
    Array<K>& toArray ();

protected:


private:
    void putResize (const K& key,const V& value);
    void push (const K& insertKey,const V& insertValue,int index1,const K& key1,int index2,const K& key2,int index3,const K& key3);
    void putStash (const K& key,const V& value);
    V& getStash (const K& key);
    bool containsKeyStash (const K& key);
    void resize (int newSize);
    int hash2 (long h);
    int hash3 (long h);
};

} // namespace gdx
} // namespace utils

#endif // GDX_CPP_UTILS_IDENTITYMAP<K, V>_HPP_
