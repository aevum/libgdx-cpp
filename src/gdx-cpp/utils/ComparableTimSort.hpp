
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

#ifndef GDX_CPP_UTILS_COMPARABLETIMSORT_HPP_
#define GDX_CPP_UTILS_COMPARABLETIMSORT_HPP_

namespace gdx {
class ComparableTimSort {
public:
    void doSort (int lo,int hi);

protected:


private:
    static void binarySort (int lo,int hi,int start);
    static int countRunAndMakeAscending (int lo,int hi);
    static void reverseRange (int lo,int hi);
    static int minRunLength (int n);
    void pushRun (int runBase,int runLen);
    void mergeCollapse ();
    void mergeForceCollapse ();
    void mergeAt (int i);
    static int gallopLeft (const Comparable<Object>& key,int base,int len,int hint);
    static int gallopRight (const Comparable<Object>& key,int base,int len,int hint);
    void mergeLo (int base1,int len1,int base2,int len2);
    void mergeHi (int base1,int len1,int base2,int len2);
    Object* ensureCapacity (int minCapacity);
    static void rangeCheck (int arrayLen,int fromIndex,int toIndex);
    int[] runBase;
    int[] runLen;
};

} // namespace gdx

#endif // GDX_CPP_UTILS_COMPARABLETIMSORT_HPP_
