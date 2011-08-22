
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

#include "Pool<T>.hpp"

using namespace gdx_cpp::utils;

T& Pool<T>::newObject ();

/** Returns an object from this pool. The object may be new (from {@link #newObject()}

T& Pool<T>::obtain () {
	return freeObjects.size == 0 ? newObject() : freeObjects.pop();
}

void Pool<T>::free (const T& object) {
	if (object == null) throw new IllegalArgumentException("object cannot be null.");
	if (freeObjects.size < max) freeObjects.add(object);
}

void Pool<T>::free (const Array<T>& objects) {
	for (int i = 0, n = Math.min(objects.size, max - freeObjects.size); i < n; i++)
		freeObjects.add(objects.get(i));
}

void Pool<T>::clear () {
	freeObjects.clear();
}

