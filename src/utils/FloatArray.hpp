
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

#ifndef GDX_CPP_UTILS_FLOATARRAY_HPP_
#define GDX_CPP_UTILS_FLOATARRAY_HPP_

namespace gdx_cpp {
namespace utils {

class FloatArray {
public:
    void add (float value);
    void addAll (const FloatArray& array);
    void addAll (const FloatArray& array,int offset,int length);
    void addAll ();
    void addAll (int offset,int length);
    float get (int index);
    void set (int index,float value);
    void insert (int index,float value);
    bool contains (float value);
    int indexOf (float value);
    bool removeValue (float value);
    float removeIndex (int index);
    float pop ();
    float peek ();
    void clear ();
    void shrink ();
    float* ensureCapacity (int additionalCapacity);
    void sort ();
    void reverse ();
    void shuffle ();
    std::string& toString ();

protected:
    float* resize (int newSize);

private:

};

} // namespace gdx_cpp
} // namespace utils

#endif // GDX_CPP_UTILS_FLOATARRAY_HPP_
