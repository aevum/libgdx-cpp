
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
*/

#ifndef GDX_CPP_UTILS_POOLEDLINKEDLIST_HPP_
#define GDX_CPP_UTILS_POOLEDLINKEDLIST_HPP_

#include "Pool.hpp"

namespace gdx {

template <typename T>
class PooledLinkedList {
public:
    PooledLinkedList (int maxPoolSize)
        : size(0), pool(16, maxPoolSize)
    {
    }
    
    struct Item {
        T* payload;
        Item* next;
        Item* prev;
        Item() : payload(NULL), next(NULL), prev(NULL) { }
    };
    
    void add (T* const object) {
        Item* item = pool.obtain();
        item->payload = object;
        item->next = NULL;
        item->prev = NULL;
        
        if (head == NULL) {
            head = item;
            tail = item;
            size++;
            return;
        }
        
        item->prev = tail;
        tail->next = item;
        tail = item;
        size++;

    }
    
    void iter () {
        iterator = head;
    }
    
    T* next () {
        if (iterator == NULL) return NULL;
        
        T* payload = iterator->payload;
        curr = iterator;
        iterator = iterator->next;
        return payload;
    }
    
    void remove () {
        if (curr == NULL) return;
        
        size--;
        pool.free(curr);
        
        Item* c = curr;
        Item* n = curr->next;
        Item* p = curr->prev;
        curr = NULL;
        
        if (size == 0) {
            head = NULL;
            tail = NULL;
            return;
        }
        
        if (c == head) {
            n->prev = NULL;
            head = n;
            return;
        }
        
        if (c == tail) {
            p->next = NULL;
            tail = p;
            return;
        }
        
        p->next = n;
        n->prev = p;
    }
    
    void clear () {
        iter();
        T* v = NULL;
        while ((v = next()) != NULL) {
            remove();
        }
    }

protected:
    Item* newObject ();

private:
    Pool< Item > pool;
    Item* head;
    Item* tail;
    Item* iterator;
    Item* curr;
    int size;
};

} // namespace gdx

#endif // GDX_CPP_UTILS_POOLEDLINKEDLIST<T>_HPP_
