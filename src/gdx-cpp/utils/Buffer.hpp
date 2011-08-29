/*
    Copyright 2011 <copyright holder> <email>

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/


#ifndef GDX_CPP_UTILS_BUFFER_HPP
#define GDX_CPP_UTILS_BUFFER_HPP

#include "Aliases.hpp"
#include <stdexcept>

namespace gdx_cpp {

namespace utils {

struct buffer_base {
public:
    typedef ref_ptr_maker<char>::type char_ptr;
    buffer_base(char_ptr bf, int capacity, int position, int mark, int limit)
            : bf(bf)
            , capacity(capacity)
            , position(position)
            , mark(mark)
            , limit(limit)
    {
    }

    char_ptr bf;
    int capacity;
    int position;
    int mark;
    int limit;
};

template <typename T>
struct buffer : protected buffer_base {
    buffer(int mark, int pos, int lim , int capacity)
    : buffer_base(buffer_base::char_ptr(new char[capacity]), capacity, position, mark, lim)
    {
        setLimit(lim);
        setPosition(pos);
        if (mark >= 0) {
            if (mark > pos) {
                std::stringstream ss;
                ss << " mark > position: (" << mark << " > " << pos + ")";
                throw std::runtime_error(ss.str());
            }
        }
    }

    int getCapacity() {
        return capacity;
    }

    int getPosition() {
        return position;
    }

    template <typename Other>
    buffer<Other> convert() {
        return buffer<Other>((buffer_base&) *this);
    }

    void put(const T& value) {
        ((T*)bf.get())[nextPutIndex()] = value;
    }

    T& get() {
        return ((T*)bf.get())[nextGetIndex()];
    }

    T& get(const int position) const {
        return ((T*)bf.get())[checkIndex(position)];
    }

    T& operator[](int position) {
        return ((T*)bf.get())[checkIndex(position)];
    }

    buffer<T>& setPosition(int newPosition) {
        if ((newPosition > limit) || (newPosition < 0))
            throw std::runtime_error("");
        position = newPosition;
        if (mark > position) clearMark();
        return *this;
    }

    int getLimit() {
        return limit;
    }

    buffer<T>& setLimit(int newLimit)
    {
        if ((newLimit > capacity) || (newLimit < 0))
            throw std::runtime_error("");
        limit = newLimit;
        if (position > limit) position = limit;
        if (mark > position) clearMark();
        return *this;
    }

    buffer<T>& reset() {
        int m = mark;
        if (m < 0)
            throw std::runtime_error();
        position = m;
        return *this;
    }

    buffer<T>& newMark() {
        mark = position;
        return *this;
    }

    buffer<T>& clear() {
        position = 0;
        limit = capacity;
        clearMark();
        return *this;
    }

    buffer<T>& flip() {
        limit = position;
        position = 0;
        clearMark();
        return this;
    }

    buffer<T>& rewind() {
        position = 0;
        clearMark();
        return *this;
    }

    int remaining() {
        return limit - position;
    }

    bool hasRemaining() {
        return position < limit;
    }


    buffer(const buffer_base& other)
            : buffer_base(other)
    {
    }

protected:
    int nextGetIndex() {
        if (position >= limit)
            throw std::runtime_error("buffer underflow");
        return position++;
    }

    int nextGetIndex(int nb) {
        if (limit - position < nb)
            throw std::runtime_error("buffer underflow");
        int p = position;
        position += nb;
        return p;
    }

    int nextPutIndex() {
        if (position >= limit)
            throw std::runtime_error("buffer overflow");
        return position++;
    }

    int nextPutIndex(int nb) {
        if (limit - position < nb)
            throw std::runtime_error("buffer overflow");
        int p = position;
        position += nb;
        return p;
    }

    int checkIndex(int i) {
        if ((i < 0) || (i >= limit))
            throw std::runtime_error("invalid index");
        return i;
    }

    int checkIndex(int i, int nb) {
        if ((i < 0) || (nb > limit - i))
            throw std::runtime_error();
        return i;
    }

    void discardMark() {
        mark = -1;
    }

    static void checkBounds(int off, int len, int size) {
        if ((off | len | (off + len) | (size - (off + len))) < 0)
            throw std::runtime_error();
    }

    int markValue() {
        return mark;
    }

    void clearMark() {
        mark = -1;
    }
};

template <typename T>
struct default_buffer : public buffer<T> {
    default_buffer(int capacity) :
            buffer<T>(-1, 0, capacity, capacity)
    {
    }
};

typedef default_buffer<char> byte_buffer;
typedef default_buffer<short> short_buffer;
typedef default_buffer<float> float_buffer;
typedef default_buffer<int> int_buffer;

}
}

#endif // GDX_CPP_UTILS_BUFFER_HPP
