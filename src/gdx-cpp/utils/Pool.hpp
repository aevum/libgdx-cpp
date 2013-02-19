/*
 3
 -    Copyright 2011 Aevum Software aevum @ aevumlab.com
 4
 -
 5
 -    Licensed under the Apache License, Version 2.0 (the "License");
 6
 -    you may not use this file except in compliance with the License.
 7
 -    You may obtain a copy of the License at
 8
 -
 9
 -        http://www.apache.org/licenses/LICENSE-2.0
 10
 -
 11
 -    Unless required by applicable law or agreed to in writing, software
 12
 -    distributed under the License is distributed on an "AS IS" BASIS,
 13
 -    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 14
 -    See the License for the specific language governing permissions and
 15
 -    limitations under the License.
 16
 -
 17
 -    @author Victor Vicente de Carvalho victor.carvalho@aevumlab.com
 18
 -    @author Ozires Bortolon de Faria ozires@aevumlab.com
 19
 -*/

#ifndef GDX_CPP_UTILS_POOL_HPP_
#define GDX_CPP_UTILS_POOL_HPP_
#include <vector>
#include <cmath>
#include <limits>
#include <stdexcept>

namespace gdx {
template<class T>
class Pool {
public:
	unsigned int max;

	Pool(int initialCapacity = 16, int _max = std::numeric_limits<int>::max(),
			bool alocate = false) :
			max(max) {
		create(initialCapacity, max, alocate);
	}
	T* obtain() {
		if (freeObjects.size() == 0) {
			return newObject();
		} else {
			T * ret = freeObjects.back();
			freeObjects.pop_back();
			return ret;
		}
	}
	void free(T* const object) {
		if (object == NULL)
			gdx_log_error("gdx", "object cannot be null.");
		if (freeObjects.size() < max) {
			freeObjects.push_back(object);
		} else {
			delete object;
		}
	}
	void freeVector(std::vector<T*>& objects) {
		for (int i = 0; i < objects.size(); i++)
			free(objects[i]);
	}
	void clear() {
		freeObjects.clear();
	}
protected:
private:
	std::vector<T*> freeObjects;
	void create(int initialCapacity, int max, bool alocate) {
		freeObjects.reserve(initialCapacity);
		if (alocate) {
			for (int i = 0; i < initialCapacity; i++) {
				freeObjects.push_back(new T());
			}
		}
	}
	T* newObject() {
		return new T;
	}
};
} // namespace gdx
#endif // GDX_CPP_UTILS_POOL<T>_HPP_
