
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

#ifndef GDX_CPP_UTILS_INTARRAY_HPP_
#define GDX_CPP_UTILS_INTARRAY_HPP_

namespace gdx_cpp {
namespace utils {

class IntArray {
public:
    void add (int value);
    void addAll (const IntArray& array);
    void addAll (const IntArray& array,int offset,int length);
    void addAll ();
    void addAll (int offset,int length);
    int get (int index);
    void set (int index,int value);
    void insert (int index,int value);
    bool contains (int value);
    int indexOf (int value);
    bool removeValue (int value);
    int removeIndex (int index);
    int pop ();
    int peek ();
    void clear ();
    void shrink ();
    int* ensureCapacity (int additionalCapacity);
    void sort ();
    void reverse ();
    void shuffle ();
    std::string& toString ();

protected:
    int* resize (int newSize);

private:

};

} // namespace gdx_cpp
} // namespace utils

#endif // GDX_CPP_UTILS_INTARRAY_HPP_
