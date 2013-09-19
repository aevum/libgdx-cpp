
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

#include "WindowedMean.hpp"
#include <cmath>

using namespace gdx;

WindowedMean::WindowedMean (int window_size)
{
    added_values = 0;
    last_value = 0;
    mean = 0;
    dirty = true;
    values.resize(window_size);
}

bool WindowedMean::hasEnoughData () {
    return added_values >= values.size();
}

void WindowedMean::clear () {
    added_values = 0;
    last_value = 0;
    for (auto & elem : values)
        elem = 0;
    dirty = true;
}

void WindowedMean::addValue (float value) {
    added_values++;
    values[last_value++] = value;
    if (last_value > (values.size() - 1)) last_value = 0;
    dirty = true;
}

float WindowedMean::getMean () {
    if (hasEnoughData()) {
        if (dirty == true) {
            float mean = 0;
            for (auto & elem : values)
                mean += elem;

            this->mean = mean / values.size();
            dirty = false;
        }
        return this->mean;
    } else
        return 0;
}

float WindowedMean::getOldest () {
    return last_value == (values.size() - 1) ? values[0] : values[last_value + 1];
}

float WindowedMean::getLatest () {
    return values[(int(last_value) - 1 == -1) ? values.size() - 1 : last_value - 1];
}

float WindowedMean::standardDeviation () {
    if (!hasEnoughData()) return 0;

    float mean = getMean();
    float sum = 0;
    for (auto & elem : values) {
        sum += (elem - mean) * (elem - mean);
    }

    return (float) std::sqrt(sum / values.size());
}

