
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

#include "Pool.hpp"
#include <cmath>
#include <limits>
#include <stdexcept>

using namespace gdx_cpp::utils;

template <class T>
Pool<T>::Pool (): max(std::numeric_limits<int>::max())
{
    create(16, max);
}

template <class T>
Pool<T>::Pool (int initialCapacity): max(std::numeric_limits<int>::max())
{
    create(initialCapacity, max);
}

template <class T>
Pool<T>::Pool (int initialCapacity, int _max) : max(max)
{
    create(initialCapacity, max);
}

template <class T>
void Pool<T>::create(int initialCapacity, int max)
{
    freeObjects.reserve(initialCapacity);
}

template <class T>
T& Pool<T>::newObject () {
    return new T();
}

template <class T>
T& Pool<T>::obtain () {
    return *(freeObjects.size() == 0 ? newObject() : freeObjects.pop_back());
}

template <class T>
void Pool<T>::free (T& object) {
    if (object == NULL) throw std::runtime_error("object cannot be null.");
    if (freeObjects.size < max)
    {
      freeObjects.push_back(object);
    } else
    {
      delete object;
    }
    
}

template <class T>
void Pool<T>::free (std::vector<T*>& objects) {
    for (int i = 0; i < objects.size(); i++)
        free(objects[i]);
}

template <class T>
void Pool<T>::clear () {
    freeObjects.clear();
}

