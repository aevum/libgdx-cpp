
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

#include "SortedIntList<E>.hpp"

using namespace gdx_cpp::utils;

E& SortedIntList<E>::insert (int index,const E& value) {
    if (first != null) {
        Node<E> c = first;
        // iterate to the right until we can't move any further because the next number is bigger than index
        while (c.n != null && c.n.index <= index) {
            c = c.n;
        }
        // add one to the right
        if (index > c.index) {
            c.n = nodePool.obtain(c, c.n, value, index);
            if (c.n.n != null) {
                c.n.n.p = c.n;
            }
            size++;
        }
        // the new element is smaller than every other element
        else if (index < c.index) {
            Node<E> newFirst = nodePool.obtain(null, first, value, index);
            first.p = newFirst;
            first = newFirst;
            size++;
        }
        // that element already exists so swap the value
        else {
            c.value = value;
        }
    } else {
        first = nodePool.obtain(null, null, value, index);
        size++;
    }
    return null;
}

E& SortedIntList<E>::get (int index) {
    E match = null;
    if (first != null) {
        Node<E> c = first;
        while (c.n != null && c.index < index) {
            c = c.n;
        }
        if (c.index == index) {
            match = c.value;
        }
    }
    return match;
}

void SortedIntList<E>::clear () {
    for (; first != null; first = first.n) {
        nodePool.free(first);
    }
    size = 0;
}

int SortedIntList<E>::size () {
    return size;
}

java.util.Iterator<Node<E>>& SortedIntList<E>::iterator () {
    if (iterator == null) {
        iterator = new Iterator();
    }
    return iterator.reset();
}

bool SortedIntList<E>::hasNext () {
    return position != null;
}

Node<E>& SortedIntList<E>::next () {
    previousPosition = position;
    position = position.n;
    return previousPosition;
}

void SortedIntList<E>::remove () {
    // the contract specifies to remove the last returned element, if nothing was returned yet assumably do nothing
    if (previousPosition != null) {
        // if we are at the second element set it as the first element
        if (previousPosition == first) {
            first = position;
        }
        // else remove last returned element by changing the chain
        else {
            previousPosition.p.n = position;
            if (position != null) {
                position.p = previousPosition.p;
            }
        }
        size--;
    }
}

Iterator& SortedIntList<E>::reset () {
    position = first;
    previousPosition = null;
    return this;
}

Node<E>& SortedIntList<E>::newObject () {
    return new Node<E>();
}

Node<E>& SortedIntList<E>::obtain (const Node<E> p, Node<E>& n,const E& value,int index) {
    Node<E> newNode = super.obtain();
    newNode.p = p;
    newNode.n = n;
    newNode.value = value;
    newNode.index = index;
    return newNode;
}

