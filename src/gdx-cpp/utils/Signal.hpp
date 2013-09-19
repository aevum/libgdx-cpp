/*
    Copyright 2013 Aevum Softwares aevum @ aevumlab.com

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
    
    @maintainer Victor Vicente de Carvalho victor.carvalho at gmail dot com
*/


#ifndef GDX_SIGNAL_HPP
#define GDX_SIGNAL_HPP

#include <functional>
#include <vector>

namespace gdx {
    
/** Class to use std::function as signal/slot mechaninsm **/
template <typename ... params>
class Signal
{
public:
    typedef std::function< void(params...)> gdx_signal_functor_t;   

    //in a perfect world functors would be comparable and hence a set would be used. Sadly
    //this is not possible, so a good compromise is to return an id to the function added
    //and use it to disconnect if needed
    std::size_t connect(gdx_signal_functor_t functor) {
        functors.push_back(functor);
        return functors.size() - 1;
    }
    
    void disconnect(std::size_t functorId) {
        functors.erase(functors.begin() + functorId);
    }

    Signal& operator()(params... parameters) {
        auto functorsCopy = functors;
        for (const auto& functor: functorsCopy) {
            functor(parameters...);
        }
    }
    
    void clear() {
        functors.clear();
    }

protected:
    std::vector<  gdx_signal_functor_t > functors;
};

}

#endif // GDX_SIGNAL_HPP
