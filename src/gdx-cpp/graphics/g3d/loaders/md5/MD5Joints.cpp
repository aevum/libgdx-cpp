
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

#include "MD5Joints.hpp"

using namespace gdx::g3d::md5;

void MD5Joints::read (const DataInputStream& in) throws IOException {
    int numNames = in.readInt();
    names = new String[numNames];
    for (int i = 0; i < numNames; i++) {
        names[i] = in.readUTF();
    }
    numJoints = in.readInt();
    joints = new float[numJoints * stride];
    for (int i = 0; i < numJoints * stride; i++) {
        joints[i] = in.readFloat();
    }
}

void MD5Joints::write (const DataOutputStream& out) throws IOException {
    out.writeInt(names.length);
    for (int i = 0; i < names.length; i++) {
        out.writeUTF(names[i]);
    }
    out.writeInt(numJoints);
    for (int i = 0; i < numJoints * stride; i++) {
        out.writeFloat(joints[i]);
    }
}

