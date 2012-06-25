
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

#include "IntArray.hpp"

using namespace gdx::utils;

void IntArray::add (int value) {
    int[] items = this.items;
    if (size == items.length) items = resize(Math.max(8, (int)(size * 1.75f)));
    items[size++] = value;
}

void IntArray::addAll (const IntArray& array) {
    addAll(array, 0, array.size);
}

void IntArray::addAll (const IntArray& array,int offset,int length) {
    if (offset + length > array.size)
        throw new IllegalArgumentException("offset + length must be <= size: " + offset + " + " + length + " <= " + array.size);
    addAll(array.items, offset, length);
}

void IntArray::addAll () {
    addAll(array, 0, array.length);
}

void IntArray::addAll (int offset,int length) {
    int[] items = this.items;
    int sizeNeeded = size + length - offset;
    if (sizeNeeded >= items.length) items = resize(Math.max(8, (int)(sizeNeeded * 1.75f)));
    System.arraycopy(array, offset, items, size, length);
    size += length;
}

int IntArray::get (int index) {
    if (index >= size) throw new IndexOutOfBoundsException(String.valueOf(index));
    return items[index];
}

void IntArray::set (int index,int value) {
    if (index >= size) throw new IndexOutOfBoundsException(String.valueOf(index));
    items[index] = value;
}

void IntArray::insert (int index,int value) {
    int[] items = this.items;
    if (size == items.length) items = resize(Math.max(8, (int)(size * 1.75f)));
    if (ordered)
        System.arraycopy(items, index, items, index + 1, size - index);
    else
        items[size] = items[index];
    size++;
    items[index] = value;
}

bool IntArray::contains (int value) {
    int i = size - 1;
    int[] items = this.items;
    while (i >= 0)
        if (items[i--] == value) return true;
    return false;
}

int IntArray::indexOf (int value) {
    int[] items = this.items;
    for (int i = 0, n = size; i < n; i++)
        if (items[i] == value) return i;
    return -1;
}

bool IntArray::removeValue (int value) {
    int[] items = this.items;
    for (int i = 0, n = size; i < n; i++) {
        if (items[i] == value) {
            removeIndex(i);
            return true;
        }
    }
    return false;
}

int IntArray::removeIndex (int index) {
    if (index >= size) throw new IndexOutOfBoundsException(String.valueOf(index));
    int[] items = this.items;
    int value = items[index];
    size--;
    if (ordered)
        System.arraycopy(items, index + 1, items, index, size - index);
    else
        items[index] = items[size];
    return value;
}

int IntArray::pop () {
    return items[--size];
}

int IntArray::peek () {
    return items[size - 1];
}

void IntArray::clear () {
    size = 0;
}

void IntArray::shrink () {
    resize(size);
}

int* IntArray::ensureCapacity (int additionalCapacity) {
    int sizeNeeded = size + additionalCapacity;
    if (sizeNeeded >= items.length) resize(Math.max(8, sizeNeeded));
    return items;
}

int* IntArray::resize (int newSize) {
    int[] newItems = new int[newSize];
    int[] items = this.items;
    System.arraycopy(items, 0, newItems, 0, Math.min(items.length, newItems.length));
    this.items = newItems;
    return newItems;
}

void IntArray::sort () {
    Arrays.sort(items, 0, size);
}

void IntArray::reverse () {
    for (int i = 0, lastIndex = size - 1, n = size / 2; i < n; i++) {
        int ii = lastIndex - i;
        int temp = items[i];
        items[i] = items[ii];
        items[ii] = temp;
    }
}

void IntArray::shuffle () {
    for (int i = size - 1; i >= 0; i--) {
        int ii = MathUtils.random(i);
        int temp = items[i];
        items[i] = items[ii];
        items[ii] = temp;
    }
}

std::string& IntArray::toString () {
    if (size == 0) return "[]";
    int[] items = this.items;
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

