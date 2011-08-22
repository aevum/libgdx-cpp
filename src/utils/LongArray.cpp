
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

#include "LongArray.hpp"

using namespace gdx_cpp::utils;

void LongArray::add (long value) {
    long[] items = this.items;
    if (size == items.length) items = resize(Math.max(8, (int)(size * 1.75f)));
    items[size++] = value;
}

void LongArray::addAll (const LongArray& array) {
    addAll(array, 0, array.size);
}

void LongArray::addAll (const LongArray& array,int offset,int length) {
    if (offset + length > array.size)
        throw new IllegalArgumentException("offset + length must be <= size: " + offset + " + " + length + " <= " + array.size);
    addAll(array.items, offset, length);
}

void LongArray::addAll () {
    addAll(array, 0, array.length);
}

void LongArray::addAll (int offset,int length) {
    long[] items = this.items;
    int sizeNeeded = size + length - offset;
    if (sizeNeeded >= items.length) items = resize(Math.max(8, (int)(sizeNeeded * 1.75f)));
    System.arraycopy(array, offset, items, size, length);
    size += length;
}

long LongArray::get (int index) {
    if (index >= size) throw new IndexOutOfBoundsException(String.valueOf(index));
    return items[index];
}

void LongArray::set (int index,long value) {
    if (index >= size) throw new IndexOutOfBoundsException(String.valueOf(index));
    items[index] = value;
}

void LongArray::insert (int index,long value) {
    long[] items = this.items;
    if (size == items.length) items = resize(Math.max(8, (int)(size * 1.75f)));
    if (ordered)
        System.arraycopy(items, index, items, index + 1, size - index);
    else
        items[size] = items[index];
    size++;
    items[index] = value;
}

bool LongArray::contains (long value) {
    int i = size - 1;
    long[] items = this.items;
    while (i >= 0)
        if (items[i--] == value) return true;
    return false;
}

int LongArray::indexOf (long value) {
    long[] items = this.items;
    for (int i = 0, n = size; i < n; i++)
        if (items[i] == value) return i;
    return -1;
}

bool LongArray::removeValue (long value) {
    long[] items = this.items;
    for (int i = 0, n = size; i < n; i++) {
        if (items[i] == value) {
            removeIndex(i);
            return true;
        }
    }
    return false;
}

long LongArray::removeIndex (int index) {
    if (index >= size) throw new IndexOutOfBoundsException(String.valueOf(index));
    long[] items = this.items;
    long value = items[index];
    size--;
    if (ordered)
        System.arraycopy(items, index + 1, items, index, size - index);
    else
        items[index] = items[size];
    return value;
}

long LongArray::pop () {
    return items[--size];
}

long LongArray::peek () {
    return items[size - 1];
}

void LongArray::clear () {
    size = 0;
}

void LongArray::shrink () {
    resize(size);
}

long* LongArray::ensureCapacity (int additionalCapacity) {
    int sizeNeeded = size + additionalCapacity;
    if (sizeNeeded >= items.length) resize(Math.max(8, sizeNeeded));
    return items;
}

long* LongArray::resize (int newSize) {
    long[] newItems = new long[newSize];
    long[] items = this.items;
    System.arraycopy(items, 0, newItems, 0, Math.min(items.length, newItems.length));
    this.items = newItems;
    return newItems;
}

void LongArray::sort () {
    Arrays.sort(items, 0, size);
}

void LongArray::reverse () {
    for (int i = 0, lastIndex = size - 1, n = size / 2; i < n; i++) {
        int ii = lastIndex - i;
        long temp = items[i];
        items[i] = items[ii];
        items[ii] = temp;
    }
}

void LongArray::shuffle () {
    for (int i = size - 1; i >= 0; i--) {
        int ii = MathUtils.random(i);
        long temp = items[i];
        items[i] = items[ii];
        items[ii] = temp;
    }
}

std::string& LongArray::toString () {
    if (size == 0) return "[]";
    long[] items = this.items;
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

