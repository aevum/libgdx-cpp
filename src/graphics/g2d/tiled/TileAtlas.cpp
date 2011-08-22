
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

#include "TileAtlas.hpp"

using namespace gdx_cpp::graphics::g2d::tiled;

gdx_cpp::graphics::g2d::TextureRegion& TileAtlas::getRegion (int id) {
    return regionsMap.get(id);
}

void TileAtlas::dispose () {
for (Texture texture : textures) {
        texture.dispose();
    }
    textures.clear();
}

std::string& TileAtlas::removeExtension (const std::string& s) {
    int extensionIndex = s.lastIndexOf(".");
    if (extensionIndex == -1) {
        return s;
    }

    return s.substring(0, extensionIndex);
}

std::string& TileAtlas::removePath (const std::string& s) {
    String temp;

    int index = s.lastIndexOf('\\');
    if (index != -1) {
        temp = s.substring(index + 1);
    } else {
        temp = s;
    }

    index = temp.lastIndexOf('/');
    if (index != -1) {
        return s.substring(index + 1);
    } else {
        return s;
    }
}

gdx_cpp::files::FileHandle& TileAtlas::getRelativeFileHandle (const gdx_cpp::files::FileHandle& path,const std::string& relativePath) {
    if (relativePath.trim().length() == 0) {
        return path;
    }

    FileHandle child = path;

    StringTokenizer tokenizer = new StringTokenizer(relativePath, "\\/");
    while (tokenizer.hasMoreTokens()) {
        String token = tokenizer.nextToken();
        if (token.equals("..")) {
            child = child.parent();
        } else {
            child = child.child(token);
        }
    }

    return child;
}

