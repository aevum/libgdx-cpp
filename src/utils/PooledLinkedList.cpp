
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

#include "PooledLinkedList<T>.hpp"

using namespace gdx_cpp::utils;

Item<T>& PooledLinkedList<T>::newObject () {
    return new Item<T>();
}

void PooledLinkedList<T>::add (const T& object) {
    Item<T> item = pool.obtain();
    item.payload = object;
    item.next = null;
    item.prev = null;

    if (head == null) {
        head = item;
        tail = item;
        size++;
        return;
    }

    item.prev = tail;
    tail.next = item;
    tail = item;
    size++;
}

void PooledLinkedList<T>::iter () {
    iter = head;
}

T& PooledLinkedList<T>::next () {
    if (iter == null) return null;

    T payload = iter.payload;
    curr = iter;
    iter = iter.next;
    return payload;
}

void PooledLinkedList<T>::remove () {
    if (curr == null) return;

    size--;
    pool.free(curr);

    Item<T> c = curr;
    Item<T> n = curr.next;
    Item<T> p = curr.prev;
    curr = null;

    if (size == 0) {
        head = null;
        tail = null;
        return;
    }

    if (c == head) {
        n.prev = null;
        head = n;
        return;
    }

    if (c == tail) {
        p.next = null;
        tail = p;
        return;
    }

    p.next = n;
    n.prev = p;
}

void PooledLinkedList<T>::main () {
// PooledLinkedList<Integer> list = new PooledLinkedList<Integer>(10);
//
// list.add(1);
// list.add(2);
// list.add(3);
// list.add(4);
// list.iter();
// list.next();
// list.next();
// list.remove();
// list.next();
// list.next();
// list.remove();
//
// list.iter();
// Integer v = null;
// while ((v = list.next()) != null)
// System.out.println(v);
//
// list.iter();
// list.next();
// list.next();
// list.remove();
//
// list.iter();
// list.next();
// list.remove();
// }

    void PooledLinkedList<T>::clear () {
        iter();
        T v = null;
        while ((v = next()) != null)
            remove();

    }

