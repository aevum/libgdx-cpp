
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

#include "TimSort<T>.hpp"

using namespace gdx::utils;

void TimSort<T>::doSort (const Comparator<T>& c,int lo,int hi) {
    stackSize = 0;
    rangeCheck(a.length, lo, hi);
    int nRemaining = hi - lo;
    if (nRemaining < 2) return; // Arrays of size 0 and 1 are always sorted

    // If array is small, do a "mini-TimSort" with no merges
    if (nRemaining < MIN_MERGE) {
        int initRunLen = countRunAndMakeAscending(a, lo, hi, c);
        binarySort(a, lo, hi, lo + initRunLen, c);
        return;
    }

    this.a = a;
    this.c = c;

    /** March over the array once, left to right, finding natural runs, extending short natural runs to minRun elements, and
     * merging runs to maintain stack invariant. */
    int minRun = minRunLength(nRemaining);
    do {
        // Identify next run
        int runLen = countRunAndMakeAscending(a, lo, hi, c);

        // If run is short, extend to min(minRun, nRemaining)
        if (runLen < minRun) {
            int force = nRemaining <= minRun ? nRemaining : minRun;
            binarySort(a, lo, lo + force, lo + runLen, c);
            runLen = force;
        }

        // Push run onto pending-run stack, and maybe merge
        pushRun(lo, runLen);
        mergeCollapse();

        // Advance to find next run
        lo += runLen;
        nRemaining -= runLen;
    } while (nRemaining != 0);

    // Merge all remaining runs to complete sort
    if (DEBUG) assert lo == hi;
    mergeForceCollapse();
    if (DEBUG) assert stackSize == 1;
}

void TimSort<T>::reverseRange (int lo,int hi) {
    hi--;
    while (lo < hi) {
        Object t = a[lo];
        a[lo++] = a[hi];
        a[hi--] = t;
    }
}

int TimSort<T>::minRunLength (int n) {
    if (DEBUG) assert n >= 0;
    int r = 0; // Becomes 1 if any 1 bits are shifted off
    while (n >= MIN_MERGE) {
        r |= (n & 1);
        n >>= 1;
    }
    return n + r;
}

void TimSort<T>::pushRun (int runBase,int runLen) {
    this.runBase[stackSize] = runBase;
    this.runLen[stackSize] = runLen;
    stackSize++;
}

void TimSort<T>::mergeCollapse () {
    while (stackSize > 1) {
        int n = stackSize - 2;
        if (n > 0 && runLen[n - 1] <= runLen[n] + runLen[n + 1]) {
            if (runLen[n - 1] < runLen[n + 1]) n--;
            mergeAt(n);
        } else if (runLen[n] <= runLen[n + 1]) {
            mergeAt(n);
        } else {
            break; // Invariant is established
        }
    }
}

void TimSort<T>::mergeForceCollapse () {
    while (stackSize > 1) {
        int n = stackSize - 2;
        if (n > 0 && runLen[n - 1] < runLen[n + 1]) n--;
        mergeAt(n);
    }
}

void TimSort<T>::mergeAt (int i) {
    if (DEBUG) assert stackSize >= 2;
    if (DEBUG) assert i >= 0;
    if (DEBUG) assert i == stackSize - 2 || i == stackSize - 3;

    int base1 = runBase[i];
    int len1 = runLen[i];
    int base2 = runBase[i + 1];
    int len2 = runLen[i + 1];
    if (DEBUG) assert len1 > 0 && len2 > 0;
    if (DEBUG) assert base1 + len1 == base2;

    /*
     * Record the length of the combined runs; if i is the 3rd-last run now, also slide over the last run (which isn't involved
     * in this merge). The current run (i+1) goes away in any case.
     */
    runLen[i] = len1 + len2;
    if (i == stackSize - 3) {
        runBase[i + 1] = runBase[i + 2];
        runLen[i + 1] = runLen[i + 2];
    }
    stackSize--;

    /*
     * Find where the first element of run2 goes in run1. Prior elements in run1 can be ignored (because they're already in
     * place).
     */
    int k = gallopRight(a[base2], a, base1, len1, 0, c);
    if (DEBUG) assert k >= 0;
    base1 += k;
    len1 -= k;
    if (len1 == 0) return;

    /*
     * Find where the last element of run1 goes in run2. Subsequent elements in run2 can be ignored (because they're already in
     * place).
     */
    len2 = gallopLeft(a[base1 + len1 - 1], a, base2, len2, len2 - 1, c);
    if (DEBUG) assert len2 >= 0;
    if (len2 == 0) return;

    // Merge remaining runs, using tmp array with min(len1, len2) elements
    if (len1 <= len2)
        mergeLo(base1, len1, base2, len2);
    else
        mergeHi(base1, len1, base2, len2);
}

void TimSort<T>::mergeLo (int base1,int len1,int base2,int len2) {
    if (DEBUG) assert len1 > 0 && len2 > 0 && base1 + len1 == base2;

    // Copy first run into temp array
    T[] a = this.a; // For performance
    T[] tmp = ensureCapacity(len1);
    System.arraycopy(a, base1, tmp, 0, len1);

    int cursor1 = 0; // Indexes into tmp array
    int cursor2 = base2; // Indexes int a
    int dest = base1; // Indexes int a

    // Move first element of second run and deal with degenerate cases
    a[dest++] = a[cursor2++];
    if (--len2 == 0) {
        System.arraycopy(tmp, cursor1, a, dest, len1);
        return;
    }
    if (len1 == 1) {
        System.arraycopy(a, cursor2, a, dest, len2);
        a[dest + len2] = tmp[cursor1]; // Last elt of run 1 to end of merge
        return;
    }

    Comparator<? super T> c = this.c; // Use local variable for performance
    int minGallop = this.minGallop; // "    " "     " "
outer:
    while (true) {
        int count1 = 0; // Number of times in a row that first run won
        int count2 = 0; // Number of times in a row that second run won

        /*
         * Do the straightforward thing until (if ever) one run starts winning consistently.
         */
        do {
            if (DEBUG) assert len1 > 1 && len2 > 0;
            if (c.compare(a[cursor2], tmp[cursor1]) < 0) {
                a[dest++] = a[cursor2++];
                count2++;
                count1 = 0;
                if (--len2 == 0) break outer;
            } else {
                a[dest++] = tmp[cursor1++];
                count1++;
                count2 = 0;
                if (--len1 == 1) break outer;
            }
        } while ((count1 | count2) < minGallop);

        /*
         * One run is winning so consistently that galloping may be a huge win. So try that, and continue galloping until (if
         * ever) neither run appears to be winning consistently anymore.
         */
        do {
            if (DEBUG) assert len1 > 1 && len2 > 0;
            count1 = gallopRight(a[cursor2], tmp, cursor1, len1, 0, c);
            if (count1 != 0) {
                System.arraycopy(tmp, cursor1, a, dest, count1);
                dest += count1;
                cursor1 += count1;
                len1 -= count1;
                if (len1 <= 1) // len1 == 1 || len1 == 0
                    break outer;
            }
            a[dest++] = a[cursor2++];
            if (--len2 == 0) break outer;

            count2 = gallopLeft(tmp[cursor1], a, cursor2, len2, 0, c);
            if (count2 != 0) {
                System.arraycopy(a, cursor2, a, dest, count2);
                dest += count2;
                cursor2 += count2;
                len2 -= count2;
                if (len2 == 0) break outer;
            }
            a[dest++] = tmp[cursor1++];
            if (--len1 == 1) break outer;
            minGallop--;
        } while (count1 >= MIN_GALLOP | count2 >= MIN_GALLOP);
        if (minGallop < 0) minGallop = 0;
        minGallop += 2; // Penalize for leaving gallop mode
    } // End of "outer" loop
    this.minGallop = minGallop < 1 ? 1 : minGallop; // Write back to field

    if (len1 == 1) {
        if (DEBUG) assert len2 > 0;
        System.arraycopy(a, cursor2, a, dest, len2);
        a[dest + len2] = tmp[cursor1]; // Last elt of run 1 to end of merge
    } else if (len1 == 0) {
        throw new IllegalArgumentException("Comparison method violates its general contract!");
    } else {
        if (DEBUG) assert len2 == 0;
        if (DEBUG) assert len1 > 1;
        System.arraycopy(tmp, cursor1, a, dest, len1);
    }
}

void TimSort<T>::mergeHi (int base1,int len1,int base2,int len2) {
    if (DEBUG) assert len1 > 0 && len2 > 0 && base1 + len1 == base2;

    // Copy second run into temp array
    T[] a = this.a; // For performance
    T[] tmp = ensureCapacity(len2);
    System.arraycopy(a, base2, tmp, 0, len2);

    int cursor1 = base1 + len1 - 1; // Indexes into a
    int cursor2 = len2 - 1; // Indexes into tmp array
    int dest = base2 + len2 - 1; // Indexes into a

    // Move last element of first run and deal with degenerate cases
    a[dest--] = a[cursor1--];
    if (--len1 == 0) {
        System.arraycopy(tmp, 0, a, dest - (len2 - 1), len2);
        return;
    }
    if (len2 == 1) {
        dest -= len1;
        cursor1 -= len1;
        System.arraycopy(a, cursor1 + 1, a, dest + 1, len1);
        a[dest] = tmp[cursor2];
        return;
    }

    Comparator<? super T> c = this.c; // Use local variable for performance
    int minGallop = this.minGallop; // "    " "     " "
outer:
    while (true) {
        int count1 = 0; // Number of times in a row that first run won
        int count2 = 0; // Number of times in a row that second run won

        /*
         * Do the straightforward thing until (if ever) one run appears to win consistently.
         */
        do {
            if (DEBUG) assert len1 > 0 && len2 > 1;
            if (c.compare(tmp[cursor2], a[cursor1]) < 0) {
                a[dest--] = a[cursor1--];
                count1++;
                count2 = 0;
                if (--len1 == 0) break outer;
            } else {
                a[dest--] = tmp[cursor2--];
                count2++;
                count1 = 0;
                if (--len2 == 1) break outer;
            }
        } while ((count1 | count2) < minGallop);

        /*
         * One run is winning so consistently that galloping may be a huge win. So try that, and continue galloping until (if
         * ever) neither run appears to be winning consistently anymore.
         */
        do {
            if (DEBUG) assert len1 > 0 && len2 > 1;
            count1 = len1 - gallopRight(tmp[cursor2], a, base1, len1, len1 - 1, c);
            if (count1 != 0) {
                dest -= count1;
                cursor1 -= count1;
                len1 -= count1;
                System.arraycopy(a, cursor1 + 1, a, dest + 1, count1);
                if (len1 == 0) break outer;
            }
            a[dest--] = tmp[cursor2--];
            if (--len2 == 1) break outer;

            count2 = len2 - gallopLeft(a[cursor1], tmp, 0, len2, len2 - 1, c);
            if (count2 != 0) {
                dest -= count2;
                cursor2 -= count2;
                len2 -= count2;
                System.arraycopy(tmp, cursor2 + 1, a, dest + 1, count2);
                if (len2 <= 1) // len2 == 1 || len2 == 0
                    break outer;
            }
            a[dest--] = a[cursor1--];
            if (--len1 == 0) break outer;
            minGallop--;
        } while (count1 >= MIN_GALLOP | count2 >= MIN_GALLOP);
        if (minGallop < 0) minGallop = 0;
        minGallop += 2; // Penalize for leaving gallop mode
    } // End of "outer" loop
    this.minGallop = minGallop < 1 ? 1 : minGallop; // Write back to field

    if (len2 == 1) {
        if (DEBUG) assert len1 > 0;
        dest -= len1;
        cursor1 -= len1;
        System.arraycopy(a, cursor1 + 1, a, dest + 1, len1);
        a[dest] = tmp[cursor2]; // Move first elt of run2 to front of merge
    } else if (len2 == 0) {
        throw new IllegalArgumentException("Comparison method violates its general contract!");
    } else {
        if (DEBUG) assert len1 == 0;
        if (DEBUG) assert len2 > 0;
        System.arraycopy(tmp, 0, a, dest - (len2 - 1), len2);
    }
}

T* TimSort<T>::ensureCapacity (int minCapacity) {
    if (tmp.length < minCapacity) {
        // Compute smallest power of 2 > minCapacity
        int newSize = minCapacity;
        newSize |= newSize >> 1;
        newSize |= newSize >> 2;
        newSize |= newSize >> 4;
        newSize |= newSize >> 8;
        newSize |= newSize >> 16;
        newSize++;

        if (newSize < 0) // Not bloody likely!
            newSize = minCapacity;
        else
            newSize = Math.min(newSize, a.length >>> 1);

        T[] newArray = (T[])new Object[newSize];
        tmp = newArray;
    }
    return tmp;
}

void TimSort<T>::rangeCheck (int arrayLen,int fromIndex,int toIndex) {
    if (fromIndex > toIndex) throw new IllegalArgumentException("fromIndex(" + fromIndex + ") > toIndex(" + toIndex + ")");
    if (fromIndex < 0) throw new ArrayIndexOutOfBoundsException(fromIndex);
    if (toIndex > arrayLen) throw new ArrayIndexOutOfBoundsException(toIndex);
}

