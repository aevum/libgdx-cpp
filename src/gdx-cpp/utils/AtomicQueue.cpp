
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

#include "AtomicQueue<T>.hpp"

using namespace gdx;

int AtomicQueue<T>::next (int idx) {
    return idx + 1 & queue.length() - 1;
}

bool AtomicQueue<T>::put (const T& value) {
    int write = writeIndex.get();
    int read = readIndex.get();
    int next = next(write);
    if (next == read) return false;
    queue.set(write, value);
    writeIndex.set(next);
    return true;
}

T& AtomicQueue<T>::poll () {
    int read = readIndex.get();
    int write = writeIndex.get();
    if (read == write) return null;
    T value = queue.get(read);
    readIndex.set(next(read));
    return value;
}

