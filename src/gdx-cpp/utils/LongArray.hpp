
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

#ifndef GDX_CPP_UTILS_LONGARRAY_HPP_
#define GDX_CPP_UTILS_LONGARRAY_HPP_

namespace gdx_cpp {
namespace utils {

class LongArray {
public:
    void add (long value);
    void addAll (const LongArray& array);
    void addAll (const LongArray& array,int offset,int length);
    void addAll ();
    void addAll (int offset,int length);
    long get (int index);
    void set (int index,long value);
    void insert (int index,long value);
    bool contains (long value);
    int indexOf (long value);
    bool removeValue (long value);
    long removeIndex (int index);
    long pop ();
    long peek ();
    void clear ();
    void shrink ();
    long* ensureCapacity (int additionalCapacity);
    void sort ();
    void reverse ();
    void shuffle ();
    std::string& toString ();

protected:
    long* resize (int newSize);

private:

};

} // namespace gdx_cpp
} // namespace utils

#endif // GDX_CPP_UTILS_LONGARRAY_HPP_
