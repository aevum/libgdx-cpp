
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

#include "IntMap<V>.hpp"

using namespace gdx_cpp::utils;

V& IntMap<V>::put (int key,const V& value) {
    if (key == 0) {
        V oldValue = zeroValue;
        zeroValue = value;
        hasZeroValue = true;
        size++;
        return oldValue;
    }

    // Check for existing keys.
    int index1 = key & mask;
    int key1 = keyTable[index1];
    if (key1 == key) {
        V oldValue = valueTable[index1];
        valueTable[index1] = value;
        return oldValue;
    }

    int index2 = hash2(key);
    int key2 = keyTable[index2];
    if (key2 == key) {
        V oldValue = valueTable[index2];
        valueTable[index2] = value;
        return oldValue;
    }

    int index3 = hash3(key);
    int key3 = keyTable[index3];
    if (key3 == key) {
        V oldValue = valueTable[index3];
        valueTable[index3] = value;
        return oldValue;
    }

    // Check for empty buckets.
    if (key1 == EMPTY) {
        keyTable[index1] = key;
        valueTable[index1] = value;
        if (size++ >= threshold) resize(capacity << 1);
        return null;
    }

    if (key2 == EMPTY) {
        keyTable[index2] = key;
        valueTable[index2] = value;
        if (size++ >= threshold) resize(capacity << 1);
        return null;
    }

    if (key3 == EMPTY) {
        keyTable[index3] = key;
        valueTable[index3] = value;
        if (size++ >= threshold) resize(capacity << 1);
        return null;
    }

    push(key, value, index1, key1, index2, key2, index3, key3);
    return null;
}

void IntMap<V>::putAll (const IntMap<V>& map) {
for (Entry<V> entry : map.entries())
        put(entry.key, entry.value);
}

void IntMap<V>::putResize (int key,const V& value) {
    if (key == 0) {
        zeroValue = value;
        hasZeroValue = true;
        return;
    }

    // Check for empty buckets.
    int index1 = key & mask;
    int key1 = keyTable[index1];
    if (key1 == EMPTY) {
        keyTable[index1] = key;
        valueTable[index1] = value;
        if (size++ >= threshold) resize(capacity << 1);
        return;
    }

    int index2 = hash2(key);
    int key2 = keyTable[index2];
    if (key2 == EMPTY) {
        keyTable[index2] = key;
        valueTable[index2] = value;
        if (size++ >= threshold) resize(capacity << 1);
        return;
    }

    int index3 = hash3(key);
    int key3 = keyTable[index3];
    if (key3 == EMPTY) {
        keyTable[index3] = key;
        valueTable[index3] = value;
        if (size++ >= threshold) resize(capacity << 1);
        return;
    }

    push(key, value, index1, key1, index2, key2, index3, key3);
}

void IntMap<V>::push (int insertKey,const V& insertValue,int index1,int key1,int index2,int key2,int index3,int key3) {
    int[] keyTable = this.keyTable;
    V[] valueTable = this.valueTable;
    int mask = this.mask;

    // Push keys until an empty bucket is found.
    int evictedKey;
    V evictedValue;
    int i = 0, pushIterations = this.pushIterations;
    do {
        // Replace the key and value for one of the hashes.
        switch (MathUtils.random(2)) {
        case 0:
            evictedKey = key1;
            evictedValue = valueTable[index1];
            keyTable[index1] = insertKey;
            valueTable[index1] = insertValue;
            break;
        case 1:
            evictedKey = key2;
            evictedValue = valueTable[index2];
            keyTable[index2] = insertKey;
            valueTable[index2] = insertValue;
            break;
        default:
            evictedKey = key3;
            evictedValue = valueTable[index3];
            keyTable[index3] = insertKey;
            valueTable[index3] = insertValue;
            break;
        }

        // If the evicted key hashes to an empty bucket, put it there and stop.
        index1 = evictedKey & mask;
        key1 = keyTable[index1];
        if (key1 == EMPTY) {
            keyTable[index1] = evictedKey;
            valueTable[index1] = evictedValue;
            if (size++ >= threshold) resize(capacity << 1);
            return;
        }

        index2 = hash2(evictedKey);
        key2 = keyTable[index2];
        if (key2 == EMPTY) {
            keyTable[index2] = evictedKey;
            valueTable[index2] = evictedValue;
            if (size++ >= threshold) resize(capacity << 1);
            return;
        }

        index3 = hash3(evictedKey);
        key3 = keyTable[index3];
        if (key3 == EMPTY) {
            keyTable[index3] = evictedKey;
            valueTable[index3] = evictedValue;
            if (size++ >= threshold) resize(capacity << 1);
            return;
        }

        if (++i == pushIterations) break;

        insertKey = evictedKey;
        insertValue = evictedValue;
    } while (true);

    putStash(evictedKey, evictedValue);
}

void IntMap<V>::putStash (int key,const V& value) {
    if (stashSize == stashCapacity) {
        // Too many pushes occurred and the stash is full, increase the table size.
        resize(capacity << 1);
        put(key, value);
        return;
    }
    // Update key in the stash.
    int[] keyTable = this.keyTable;
    for (int i = capacity, n = i + stashSize; i < n; i++) {
        if (keyTable[i] == key) {
            valueTable[i] = value;
            return;
        }
    }
    // Store key in the stash.
    int index = capacity + stashSize;
    keyTable[index] = key;
    valueTable[index] = value;
    stashSize++;
}

V& IntMap<V>::get (int key) {
    if (key == 0) return zeroValue;
    int index = key & mask;
    if (keyTable[index] != key) {
        index = hash2(key);
        if (keyTable[index] != key) {
            index = hash3(key);
            if (keyTable[index] != key) return getStash(key);
        }
    }
    return valueTable[index];
}

V& IntMap<V>::getStash (int key) {
    int[] keyTable = this.keyTable;
    for (int i = capacity, n = i + stashSize; i < n; i++)
        if (keyTable[i] == key) return valueTable[i];
    return null;
}

V& IntMap<V>::remove (int key) {
    if (key == 0) {
        if (!hasZeroValue) return null;
        V oldValue = zeroValue;
        zeroValue = null;
        hasZeroValue = false;
        size--;
        return oldValue;
    }

    int index = key & mask;
    if (keyTable[index] == key) {
        keyTable[index] = EMPTY;
        V oldValue = valueTable[index];
        valueTable[index] = null;
        size--;
        return oldValue;
    }

    index = hash2(key);
    if (keyTable[index] == key) {
        keyTable[index] = EMPTY;
        V oldValue = valueTable[index];
        valueTable[index] = null;
        size--;
        return oldValue;
    }

    index = hash3(key);
    if (keyTable[index] == key) {
        keyTable[index] = EMPTY;
        V oldValue = valueTable[index];
        valueTable[index] = null;
        size--;
        return oldValue;
    }

    return removeStash(key);
}

void IntMap<V>::clear () {
    int[] keyTable = this.keyTable;
    V[] valueTable = this.valueTable;
    for (int i = capacity + stashSize; i-- > 0;) {
        keyTable[i] = EMPTY;
        valueTable[i] = null;
    }
    size = 0;
    stashSize = 0;
    zeroValue = null;
    hasZeroValue = false;
}

bool IntMap<V>::containsValue (const Object& value,bool identity) {
    V[] valueTable = this.valueTable;
    if (value == null) {
        if (hasZeroValue && zeroValue == null) return true;
        int[] keyTable = this.keyTable;
        for (int i = capacity + stashSize; i-- > 0;)
            if (keyTable[i] != EMPTY && valueTable[i] == null) return true;
    } else if (identity) {
        if (value == zeroValue) return true;
        for (int i = capacity + stashSize; i-- > 0;)
            if (valueTable[i] == value) return true;
    } else {
        if (hasZeroValue && value.equals(zeroValue)) return true;
        for (int i = capacity + stashSize; i-- > 0;)
            if (value.equals(valueTable[i])) return true;
    }
    return false;
}

bool IntMap<V>::containsKey (int key) {
    if (key == 0) return hasZeroValue;
    int index = key & mask;
    if (keyTable[index] != key) {
        index = hash2(key);
        if (keyTable[index] != key) {
            index = hash3(key);
            if (keyTable[index] != key) return containsKeyStash(key);
        }
    }
    return true;
}

bool IntMap<V>::containsKeyStash (int key) {
    int[] keyTable = this.keyTable;
    for (int i = capacity, n = i + stashSize; i < n; i++)
        if (keyTable[i] == key) return true;
    return false;
}

void IntMap<V>::ensureCapacity (int additionalCapacity) {
    int sizeNeeded = size + additionalCapacity;
    if (sizeNeeded >= threshold) resize(MathUtils.nextPowerOfTwo((int)(sizeNeeded / loadFactor)));
}

void IntMap<V>::resize (int newSize) {
    int oldEndIndex = capacity + stashSize;

    capacity = newSize;
    threshold = (int)(newSize * loadFactor);
    mask = newSize - 1;
    hashShift = 31 - Integer.numberOfTrailingZeros(newSize);
    stashCapacity = Math.max(3, (int)Math.ceil(Math.log(newSize)));
    pushIterations = Math.max(Math.min(capacity, 32), (int)Math.sqrt(capacity) / 4);

    int[] oldKeyTable = keyTable;
    V[] oldValueTable = valueTable;

    keyTable = new int[newSize + stashCapacity];
    valueTable = (V[])new Object[newSize + stashCapacity];

    size = hasZeroValue ? 1 : 0;
    stashSize = 0;
    for (int i = 0; i < oldEndIndex; i++) {
        int key = oldKeyTable[i];
        if (key != EMPTY) putResize(key, oldValueTable[i]);
    }
}

int IntMap<V>::hash2 (int h) {
    h *= PRIME2;
    return (h ^ h >>> hashShift) & mask;
}

int IntMap<V>::hash3 (int h) {
    h *= PRIME3;
    return (h ^ h >>> hashShift) & mask;
}

std::string& IntMap<V>::toString () {
    if (size == 0) return "[]";
    StringBuilder buffer = new StringBuilder(32);
    buffer.append('[');
    int[] keyTable = this.keyTable;
    V[] valueTable = this.valueTable;
    int i = keyTable.length;
    while (i-- > 0) {
        int key = keyTable[i];
        if (key == EMPTY) continue;
        buffer.append(key);
        buffer.append('=');
        buffer.append(valueTable[i]);
        break;
    }
    while (i-- > 0) {
        int key = keyTable[i];
        if (key == EMPTY) continue;
        buffer.append(", ");
        buffer.append(key);
        buffer.append('=');
        buffer.append(valueTable[i]);
    }
    buffer.append(']');
    return buffer.toString();
}

Entries<V>& IntMap<V>::entries () {
    if (entries == null)
        entries = new Entries(this);
    else
        entries.reset();
    return entries;
}

Values<V>& IntMap<V>::values () {
    if (values == null)
        values = new Values(this);
    else
        values.reset();
    return values;
}

Keys& IntMap<V>::keys () {
    if (keys == null)
        keys = new Keys(this);
    else
        keys.reset();
    return keys;
}

std::string& IntMap<V>::toString () {
    return key + "=" + value;
}

void IntMap<V>::reset () {
    currentIndex = INDEX_ILLEGAL;
    nextIndex = INDEX_ZERO;
    if (map.hasZeroValue)
        hasNext = true;
    else
        findNextIndex();
}

void IntMap<V>::remove () {
    if (currentIndex == INDEX_ZERO && map.hasZeroValue) {
        map.zeroValue = null;
        map.hasZeroValue = false;
    } else if (currentIndex < 0) {
        throw new IllegalStateException("next must be called before remove.");
    } else if (currentIndex >= map.capacity) {
        map.removeStashIndex(currentIndex);
    } else {
        map.keyTable[currentIndex] = EMPTY;
        map.valueTable[currentIndex] = null;
    }
    currentIndex = INDEX_ILLEGAL;
    map.size--;
}

Entry<V>& IntMap<V>::next () {
    if (!hasNext) throw new NoSuchElementException();
    int[] keyTable = map.keyTable;
    if (nextIndex == INDEX_ZERO) {
        entry.key = 0;
        entry.value = map.zeroValue;
    } else {
        entry.key = keyTable[nextIndex];
        entry.value = map.valueTable[nextIndex];
    }
    currentIndex = nextIndex;
    findNextIndex();
    return entry;
}

bool IntMap<V>::hasNext () {
    return hasNext;
}

Iterator<Entry<V>>& IntMap<V>::iterator () {
    return this;
}

bool IntMap<V>::hasNext () {
    return hasNext;
}

V& IntMap<V>::next () {
    V value;
    if (nextIndex == INDEX_ZERO)
        value = map.zeroValue;
    else
        value = map.valueTable[nextIndex];
    currentIndex = nextIndex;
    findNextIndex();
    return value;
}

Iterator<V>& IntMap<V>::iterator () {
    return this;
}

Array<V>& IntMap<V>::toArray () {
    Array array = new Array(true, map.size);
    while (hasNext)
        array.add(next());
    return array;
}

int IntMap<V>::next () {
    int key = nextIndex == INDEX_ZERO ? 0 : map.keyTable[nextIndex];
    currentIndex = nextIndex;
    findNextIndex();
    return key;
}

IntArray& IntMap<V>::toArray () {
    IntArray array = new IntArray(true, map.size);
    while (hasNext)
        array.add(next());
    return array;
}

