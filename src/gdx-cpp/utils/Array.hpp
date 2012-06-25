
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

#ifndef GDX_CPP_UTILS_ARRAY<T>_HPP_
#define GDX_CPP_UTILS_ARRAY<T>_HPP_

namespace gdx {
class Array {
public:
    void add (const T& value);
    void addAll (const Array& array);
    void addAll (const Array& array,int offset,int length);
    void addAll ();
    void addAll (int offset,int length);
    T& get (int index);
    void set (int index,const T& value);
    void insert (int index,const T& value);
    bool contains (const T& value,bool identity);
    int indexOf (const T& value,bool identity);
    bool removeValue (const T& value,bool identity);
    T& removeIndex (int index);
    T& pop ();
    T& peek ();
    void clear ();
    void shrink ();
    T* ensureCapacity (int additionalCapacity);
    void sort ();
    void sort (const Comparator<T>& comparator);
    void reverse ();
    void shuffle ();
    Iterator<T>& iterator ();
    T* toArray ();
    std::string& toString ();
    bool hasNext ();
    T& next ();
    void remove ();
    void reset ();
    Iterator<T>& iterator ();

protected:
    T* resize (int newSize);

private:
    Array<T> array;
};

} // namespace gdx

#endif // GDX_CPP_UTILS_ARRAY<T>_HPP_
