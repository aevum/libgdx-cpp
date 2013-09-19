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
  -    @author Ozires Bortolon de Faria ozires@aevumlab.com
 */

#ifndef GDX_CPP_UTILS_POOL_HPP_
#define GDX_CPP_UTILS_POOL_HPP_
#include <vector>
#include <cmath>
#include <limits>
#include <stdexcept>

namespace gdx
{
template<class T>
class Pool
{
public:
    unsigned int max;

    Pool ( int initialCapacity = 16, int _max = std::numeric_limits<int>::max(),
           bool alocate = false ) :
        max ( _max ) {
        create ( initialCapacity, max, alocate );
    }
    T* obtain() {
        if ( freeObjects.size() == 0 ) {
            return newObject();
        } else {
            T * ret = freeObjects.back();
            freeObjects.pop_back();
            return ret;
        }
    }
    void free ( T* const object ) {
        if ( object == nullptr ) {
            gdx_log_error ( "gdx", "object cannot be null." );
        }
        if ( freeObjects.size() < max ) {
            freeObjects.push_back ( object );
        } else {
            delete object;
        }
    }
    void freeVector ( std::vector<T*>& objects ) {
        for ( int i = 0; i < objects.size(); i++ ) {
            free ( objects[i] );
        }
    }
    void clear() {
        freeObjects.clear();
    }
protected:
private:
    std::vector<T*> freeObjects;
    void create ( int initialCapacity, int max, bool alocate ) {
        freeObjects.reserve ( initialCapacity );
        if ( alocate ) {
            for ( int i = 0; i < initialCapacity; i++ ) {
                freeObjects.push_back ( new T() );
            }
        }
    }
    T* newObject() {
        return new T;
    }
};
} // namespace gdx
#endif // GDX_CPP_UTILS_POOL<T>_HPP_
