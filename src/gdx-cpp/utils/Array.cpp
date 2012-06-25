
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

#include "Array<T>.hpp"

using namespace gdx;

void Array<T>::add (const T& value) {
    T[] items = this.items;
    if (size == items.length) items = resize(Math.max(8, (int)(size * 1.75f)));
    items[size++] = value;
}

void Array<T>::addAll (const Array& array) {
    addAll(array, 0, array.size);
}

void Array<T>::addAll (const Array& array,int offset,int length) {
    if (offset + length > array.size)
        throw new IllegalArgumentException("offset + length must be <= size: " + offset + " + " + length + " <= " + array.size);
    addAll((T[])array.items, offset, length);
}

void Array<T>::addAll () {
    addAll(array, 0, array.length);
}

void Array<T>::addAll (int offset,int length) {
    T[] items = this.items;
    int sizeNeeded = size + length - offset;
    if (sizeNeeded >= items.length) items = resize(Math.max(8, (int)(sizeNeeded * 1.75f)));
    System.arraycopy(array, offset, items, size, length);
    size += length;
}

T& Array<T>::get (int index) {
    if (index >= size) throw new IndexOutOfBoundsException(String.valueOf(index));
    return items[index];
}

void Array<T>::set (int index,const T& value) {
    if (index >= size) throw new IndexOutOfBoundsException(String.valueOf(index));
    items[index] = value;
}

void Array<T>::insert (int index,const T& value) {
    T[] items = this.items;
    if (size == items.length) items = resize(Math.max(8, (int)(size * 1.75f)));
    if (ordered)
        System.arraycopy(items, index, items, index + 1, size - index);
    else
        items[size] = items[index];
    size++;
    items[index] = value;
}

bool Array<T>::contains (const T& value,bool identity) {
    Object[] items = this.items;
    int i = size - 1;
    if (identity || value == null) {
        while (i >= 0)
            if (items[i--] == value) return true;
    } else {
        while (i >= 0)
            if (value.equals(items[i--])) return true;
    }
    return false;
}

int Array<T>::indexOf (const T& value,bool identity) {
    Object[] items = this.items;
    if (identity || value == null) {
        for (int i = 0, n = size; i < n; i++)
            if (items[i] == value) return i;
    } else {
        for (int i = 0, n = size; i < n; i++)
            if (value.equals(items[i])) return i;
    }
    return -1;
}

bool Array<T>::removeValue (const T& value,bool identity) {
    Object[] items = this.items;
    if (identity || value == null) {
        for (int i = 0, n = size; i < n; i++) {
            if (items[i] == value) {
                removeIndex(i);
                return true;
            }
        }
    } else {
        for (int i = 0, n = size; i < n; i++) {
            if (value.equals(items[i])) {
                removeIndex(i);
                return true;
            }
        }
    }
    return false;
}

T& Array<T>::removeIndex (int index) {
    if (index >= size) throw new IndexOutOfBoundsException(String.valueOf(index));
    Object[] items = this.items;
    T value = (T)items[index];
    size--;
    if (ordered)
        System.arraycopy(items, index + 1, items, index, size - index);
    else
        items[index] = items[size];
    items[size] = null;
    return value;
}

T& Array<T>::pop () {
    --size;
    T item = items[size];
    items[size] = null;
    return item;
}

T& Array<T>::peek () {
    return items[size - 1];
}

void Array<T>::clear () {
    Object[] items = this.items;
    for (int i = 0, n = size; i < n; i++)
        items[i] = null;
    size = 0;
}

void Array<T>::shrink () {
    resize(size);
}

T* Array<T>::ensureCapacity (int additionalCapacity) {
    int sizeNeeded = size + additionalCapacity;
    if (sizeNeeded >= items.length) resize(Math.max(8, sizeNeeded));
    return items;
}

T* Array<T>::resize (int newSize) {
    T[] items = this.items;
    T[] newItems = (T[])java.lang.reflect.Array.newInstance(items.getClass().getComponentType(), newSize);
    System.arraycopy(items, 0, newItems, 0, Math.min(items.length, newItems.length));
    this.items = newItems;
    return newItems;
}

void Array<T>::sort () {
    Sort.instance().sort(items, 0, size);
}

void Array<T>::sort (const Comparator<T>& comparator) {
    Sort.instance().sort(items, comparator, 0, size);
}

void Array<T>::reverse () {
    for (int i = 0, lastIndex = size - 1, n = size / 2; i < n; i++) {
        int ii = lastIndex - i;
        T temp = items[i];
        items[i] = items[ii];
        items[ii] = temp;
    }
}

void Array<T>::shuffle () {
    for (int i = size - 1; i >= 0; i--) {
        int ii = MathUtils.random(i);
        T temp = items[i];
        items[i] = items[ii];
        items[ii] = temp;
    }
}

Iterator<T>& Array<T>::iterator () {
    if (iterator == null) iterator = new ArrayIterator(this);
    iterator.index = 0;
    return iterator;
}

T* Array<T>::toArray () {
    return (T[])toArray(items.getClass().getComponentType());
}

std::string& Array<T>::toString () {
    if (size == 0) return "[]";
    Object[] items = this.items;
    StringBuilder buffer = new StringBuilder(32);
    buffer.append('[');
    buffer.append(items[0]);
    for (int i = 1; i < size; i++) {
        buffer.append(", ");
        buffer.append(items[i]);
    }
    buffer.append(']');
    return buffer.toString();
}

bool Array<T>::hasNext () {
    return index < array.size;
}

T& Array<T>::next () {
    if (index >= array.size) throw new NoSuchElementException(String.valueOf(index));
    return array.items[index++];
}

void Array<T>::remove () {
    index--;
    array.removeIndex(index);
}

void Array<T>::reset () {
    index = 0;
}

Iterator<T>& Array<T>::iterator () {
    iterator.reset();
    return iterator;
}

