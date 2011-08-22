
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

#include "SerializationException.hpp"

using namespace gdx_cpp::utils;

bool SerializationException::causedBy (const Class& type) {
    return causedBy(this, type);
}

bool SerializationException::causedBy (const Throwable& ex,const Class& type) {
    Throwable cause = ex.getCause();
    if (cause == null || cause == ex) return false;
    if (type.isAssignableFrom(cause.getClass())) return true;
    return causedBy(cause, type);
}

std::string& SerializationException::getMessage () {
    if (trace == null) return super.getMessage();
    StringBuffer buffer = new StringBuffer(512);
    buffer.append(super.getMessage());
    if (buffer.length() > 0) buffer.append('\n');
    buffer.append("Serialization trace:");
    buffer.append(trace);
    return buffer.toString();
}

void SerializationException::addTrace (const std::string& info) {
    if (info == null) throw new IllegalArgumentException("info cannot be null.");
    if (trace == null) trace = new StringBuffer(512);
    trace.append('\n');
    trace.append(info);
}

