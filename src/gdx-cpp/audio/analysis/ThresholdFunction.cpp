
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

using namespace gdx_cpp::audio::analysis;

std::list<Float>& ThresholdFunction::calculate (std::list<Float>& spectralFlux) {
    ArrayList<Float> thresholds = new ArrayList<Float>(spectralFlux.size());

    for (int i = 0; i < spectralFlux.size(); i++) {
        float sum = 0;
        int start = Math.max(0, i - historySize / 2);
        int end = Math.min(spectralFlux.size() - 1, i + historySize / 2);
        for (int j = start; j <= end; j++)
            sum += spectralFlux.get(j);
        sum /= (end - start);
        sum *= multiplier;
        thresholds.add(sum);
    }

    return thresholds;
}

