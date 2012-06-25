
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

#include "IdentityMap<K, V>.hpp"

using namespace gdx::utils;

V& IdentityMap<K, V>::put (const K& key,const V& value) {
    if (key == null) throw new IllegalArgumentException("key cannot be null.");

    // Check for existing keys.
    int hashCode = System.identityHashCode(key);
    int index1 = hashCode & mask;
    K key1 = keyTable[index1];
    if (key1 == key) {
        V oldValue = valueTable[index1];
        valueTable[index1] = value;
        return oldValue;
    }

    int index2 = hash2(hashCode);
    K key2 = keyTable[index2];
    if (key2 == key) {
        V oldValue = valueTable[index2];
        valueTable[index2] = value;
        return oldValue;
    }

    int index3 = hash3(hashCode);
    K key3 = keyTable[index3];
    if (key3 == key) {
        V oldValue = valueTable[index3];
        valueTable[index3] = value;
        return oldValue;
    }

    // Check for empty buckets.
    if (key1 == null) {
        keyTable[index1] = key;
        valueTable[index1] = value;
        if (size++ >= threshold) resize(capacity << 1);
        return null;
    }

    if (key2 == null) {
        keyTable[index2] = key;
        valueTable[index2] = value;
        if (size++ >= threshold) resize(capacity << 1);
        return null;
    }

    if (key3 == null) {
        keyTable[index3] = key;
        valueTable[index3] = value;
        if (size++ >= threshold) resize(capacity << 1);
        return null;
    }

    push(key, value, index1, key1, index2, key2, index3, key3);
    return null;
}

void IdentityMap<K, V>::putResize (const K& key,const V& value) {
    // Check for empty buckets.
    int hashCode = System.identityHashCode(key);
    int index1 = hashCode & mask;
    K key1 = keyTable[index1];
    if (key1 == null) {
        keyTable[index1] = key;
        valueTable[index1] = value;
        if (size++ >= threshold) resize(capacity << 1);
        return;
    }

    int index2 = hash2(hashCode);
    K key2 = keyTable[index2];
    if (key2 == null) {
        keyTable[index2] = key;
        valueTable[index2] = value;
        if (size++ >= threshold) resize(capacity << 1);
        return;
    }

    int index3 = hash3(hashCode);
    K key3 = keyTable[index3];
    if (key3 == null) {
        keyTable[index3] = key;
        valueTable[index3] = value;
        if (size++ >= threshold) resize(capacity << 1);
        return;
    }

    push(key, value, index1, key1, index2, key2, index3, key3);
}

void IdentityMap<K, V>::push (const K& insertKey,const V& insertValue,int index1,const K& key1,int index2,const K& key2,int index3,const K& key3) {
    K[] keyTable = this.keyTable;
    V[] valueTable = this.valueTable;
    int mask = this.mask;

    // Push keys until an empty bucket is found.
    K evictedKey;
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
        int hashCode = System.identityHashCode(evictedKey);
        index1 = hashCode & mask;
        key1 = keyTable[index1];
        if (key1 == null) {
            keyTable[index1] = evictedKey;
            valueTable[index1] = evictedValue;
            if (size++ >= threshold) resize(capacity << 1);
            return;
        }

        index2 = hash2(hashCode);
        key2 = keyTable[index2];
        if (key2 == null) {
            keyTable[index2] = evictedKey;
            valueTable[index2] = evictedValue;
            if (size++ >= threshold) resize(capacity << 1);
            return;
        }

        index3 = hash3(hashCode);
        key3 = keyTable[index3];
        if (key3 == null) {
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

void IdentityMap<K, V>::putStash (const K& key,const V& value) {
    if (stashSize == stashCapacity) {
        // Too many pushes occurred and the stash is full, increase the table size.
        resize(capacity << 1);
        put(key, value);
        return;
    }
    // Update key in the stash.
    K[] keyTable = this.keyTable;
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

V& IdentityMap<K, V>::get (const K& key) {
    int hashCode = System.identityHashCode(key);
    int index = hashCode & mask;
    if (!key.equals(keyTable[index])) {
        index = hash2(hashCode);
        if (!key.equals(keyTable[index])) {
            index = hash3(hashCode);
            if (!key.equals(keyTable[index])) return getStash(key);
        }
    }
    return valueTable[index];
}

V& IdentityMap<K, V>::getStash (const K& key) {
    K[] keyTable = this.keyTable;
    for (int i = capacity, n = i + stashSize; i < n; i++)
        if (keyTable[i] == key) return valueTable[i];
    return null;
}

V& IdentityMap<K, V>::remove (const K& key) {
    int hashCode = System.identityHashCode(key);
    int index = hashCode & mask;
    if (keyTable[index] == key) {
        keyTable[index] = null;
        V oldValue = valueTable[index];
        valueTable[index] = null;
        size--;
        return oldValue;
    }

    index = hash2(hashCode);
    if (keyTable[index] == key) {
        keyTable[index] = null;
        V oldValue = valueTable[index];
        valueTable[index] = null;
        size--;
        return oldValue;
    }

    index = hash3(hashCode);
    if (keyTable[index] == key) {
        keyTable[index] = null;
        V oldValue = valueTable[index];
        valueTable[index] = null;
        size--;
        return oldValue;
    }

    return removeStash(key);
}

void IdentityMap<K, V>::clear () {
    K[] keyTable = this.keyTable;
    V[] valueTable = this.valueTable;
    for (int i = capacity + stashSize; i-- > 0;) {
        keyTable[i] = null;
        valueTable[i] = null;
    }
    size = 0;
    stashSize = 0;
}

bool IdentityMap<K, V>::containsValue (const Object& value,bool identity) {
    V[] valueTable = this.valueTable;
    if (value == null) {
        K[] keyTable = this.keyTable;
        for (int i = capacity + stashSize; i-- > 0;)
            if (keyTable[i] != null && valueTable[i] == null) return true;
    } else if (identity) {
        for (int i = capacity + stashSize; i-- > 0;)
            if (valueTable[i] == value) return true;
    } else {
        for (int i = capacity + stashSize; i-- > 0;)
            if (value.equals(valueTable[i])) return true;
    }
    return false;
}

bool IdentityMap<K, V>::containsKey (const K& key) {
    int hashCode = System.identityHashCode(key);
    int index = hashCode & mask;
    if (!key.equals(keyTable[index])) {
        index = hash2(hashCode);
        if (!key.equals(keyTable[index])) {
            index = hash3(hashCode);
            if (!key.equals(keyTable[index])) return containsKeyStash(key);
        }
    }
    return true;
}

bool IdentityMap<K, V>::containsKeyStash (const K& key) {
    K[] keyTable = this.keyTable;
    for (int i = capacity, n = i + stashSize; i < n; i++)
        if (keyTable[i] == key) return true;
    return false;
}

void IdentityMap<K, V>::ensureCapacity (int additionalCapacity) {
    int sizeNeeded = size + additionalCapacity;
    if (sizeNeeded >= threshold) resize(MathUtils.nextPowerOfTwo((int)(sizeNeeded / loadFactor)));
}

void IdentityMap<K, V>::resize (int newSize) {
    int oldEndIndex = capacity + stashSize;

    capacity = newSize;
    threshold = (int)(newSize * loadFactor);
    mask = newSize - 1;
    hashShift = 31 - Integer.numberOfTrailingZeros(newSize);
    stashCapacity = Math.max(3, (int)Math.ceil(Math.log(newSize)));
    pushIterations = Math.max(Math.min(capacity, 32), (int)Math.sqrt(capacity) / 4);

    K[] oldKeyTable = keyTable;
    V[] oldValueTable = valueTable;

    keyTable = (K[])new Object[newSize + stashCapacity];
    valueTable = (V[])new Object[newSize + stashCapacity];

    size = 0;
    stashSize = 0;
    for (int i = 0; i < oldEndIndex; i++) {
        K key = oldKeyTable[i];
        if (key != null) putResize(key, oldValueTable[i]);
    }
}

int IdentityMap<K, V>::hash2 (long h) {
    h *= PRIME2;
    return (int)((h ^ h >>> hashShift) & mask);
}

int IdentityMap<K, V>::hash3 (long h) {
    h *= PRIME3;
    return (int)((h ^ h >>> hashShift) & mask);
}

std::string& IdentityMap<K, V>::toString () {
    if (size == 0) return "[]";
    StringBuilder buffer = new StringBuilder(32);
    buffer.append('[');
    K[] keyTable = this.keyTable;
    V[] valueTable = this.valueTable;
    int i = keyTable.length;
    while (i-- > 0) {
        K key = keyTable[i];
        if (key == null) continue;
        buffer.append(key);
        buffer.append('=');
        buffer.append(valueTable[i]);
        break;
    }
    while (i-- > 0) {
        K key = keyTable[i];
        if (key == null) continue;
        buffer.append(", ");
        buffer.append(key);
        buffer.append('=');
        buffer.append(valueTable[i]);
    }
    buffer.append(']');
    return buffer.toString();
}

Values<V>& IdentityMap<K, V>::values () {
    if (values == null)
        values = new Values(this);
    else
        values.reset();
    return values;
}

Keys<K>& IdentityMap<K, V>::keys () {
    if (keys == null)
        keys = new Keys(this);
    else
        keys.reset();
    return keys;
}

std::string& IdentityMap<K, V>::toString () {
    return key + "=" + value;
}

void IdentityMap<K, V>::reset () {
    currentIndex = -1;
    nextIndex = -1;
    findNextIndex();
}

void IdentityMap<K, V>::remove () {
    if (currentIndex < 0) throw new IllegalStateException("next must be called before remove.");
    if (currentIndex >= map.capacity) {
        map.removeStashIndex(currentIndex);
    } else {
        map.keyTable[currentIndex] = null;
        map.valueTable[currentIndex] = null;
    }
    currentIndex = -1;
    map.size--;
}

bool IdentityMap<K, V>::hasNext () {
    return hasNext;
}

bool IdentityMap<K, V>::hasNext () {
    return hasNext;
}

V& IdentityMap<K, V>::next () {
    V value = map.valueTable[nextIndex];
    currentIndex = nextIndex;
    findNextIndex();
    return value;
}

Iterator<V>& IdentityMap<K, V>::iterator () {
    return this;
}

Array<V>& IdentityMap<K, V>::toArray () {
    Array array = new Array(true, map.size);
    while (hasNext)
        array.add(next());
    return array;
}

bool IdentityMap<K, V>::hasNext () {
    return hasNext;
}

K& IdentityMap<K, V>::next () {
    K key = map.keyTable[nextIndex];
    currentIndex = nextIndex;
    findNextIndex();
    return key;
}

Iterator<K>& IdentityMap<K, V>::iterator () {
    return this;
}

Array<K>& IdentityMap<K, V>::toArray () {
    Array array = new Array(true, map.size);
    while (hasNext)
        array.add(next());
    return array;
}

