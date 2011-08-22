
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

#ifndef GDX_CPP_MATH_WINDOWEDMEAN_HPP_
#define GDX_CPP_MATH_WINDOWEDMEAN_HPP_
#include <vector>
#include "gdx-cpp/utils/Aliases.hpp"

namespace gdx_cpp {
namespace math {

class WindowedMean {
public:
    WindowedMean (int window_size);
    
    bool hasEnoughData ();
    void clear ();
    void addValue (float value);
    float getMean ();
    float getOldest ();
    float getLatest ();
    float standardDeviation ();

protected:
    std::vector<float> values;
    int added_values;
    int last_value;
    float mean;
    bool dirty;

private:

};

} // namespace gdx_cpp
} // namespace math

#endif // GDX_CPP_MATH_WINDOWEDMEAN_HPP_
