
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

#include "ThresholdFunction.hpp"
#include <cmath>
#include <vector>

using namespace gdx_cpp::audio::analysis;

ThresholdFunction::ptr ThresholdFunction::calculate (std::vector< float >& spectralFlux) {
    ThresholdFunction::ptr thresholds(new std::vector< float > (spectralFlux.size()));

    for (int i = 0; i < spectralFlux.size(); i++) {
        float sum = 0;
        int start = std::max(0, i - historySize / 2);
        int size = spectralFlux.size();
        int end = std::min( size - 1, i + historySize / 2);
        for (int j = start; j <= end; j++)
            sum += spectralFlux.at(j);
        sum /= (end - start);
        sum *= multiplier;
        thresholds->push_back(sum);
    }

    return thresholds;
}

