
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

#ifndef GDX_CPP_UTILS_SORTEDINTLIST<E>_HPP_
#define GDX_CPP_UTILS_SORTEDINTLIST<E>_HPP_

namespace gdx_cpp {
namespace utils {

class SortedIntList {
public:
    E& insert (int index,const E& value);
    E& get (int index);
    void clear ();
    int size ();
    java.util.Iterator<Node<E>>& iterator ();
    bool hasNext ();
    Node<E>& next ();
    void remove ();
    Iterator& reset ();
    Node<E>& obtain (const Node<E> p, Node<E>& n,const E& value,int index);

protected:
    Node<E>& newObject ();

private:

};

} // namespace gdx_cpp
} // namespace utils

#endif // GDX_CPP_UTILS_SORTEDINTLIST<E>_HPP_
