
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

#include "GdxNativesLoader.hpp"

using namespace gdx::utils;

std::string& GdxNativesLoader::crc (const std::string& nativeFile) {
    InputStream input = GdxNativesLoader.class.getResourceAsStream("/" + nativeFile);
    if (input == null) return Version.VERSION; // fallback
    CRC32 crc = new CRC32();
    byte[] buffer = new byte[4096];
    try {
        while (true) {
            int length = input.read(buffer);
            if (length == -1) break;
            crc.update(buffer, 0, length);
        }
    } catch (Exception ex) {
        try {
            input.close();
        } catch (Exception ignored) {
        }
    }
    return Long.toString(crc.getValue());
}

bool GdxNativesLoader::loadLibrary (const std::string& nativeFile32,const std::string& nativeFile64) {
    path = extractLibrary(nativeFile32, nativeFile64);
    if (path != null) {
        System.load(path);
    }

    return path != null;
}

std::string& GdxNativesLoader::extractLibrary (const std::string& native32,const std::string& native64) {
    String nativeFileName = is64Bit ? native64 : native32;
    File nativeFile = new File(nativesDir, nativeFileName);
    try {
        // Extract native from classpath to temp dir.
        InputStream input = GdxNativesLoader.class.getResourceAsStream("/" + nativeFileName);
        if (input == null) return null;
        nativesDir.mkdirs();
        FileOutputStream output = new FileOutputStream(nativeFile);
        byte[] buffer = new byte[4096];
        while (true) {
            int length = input.read(buffer);
            if (length == -1) break;
            output.write(buffer, 0, length);
        }
        input.close();
        output.close();
    } catch (IOException ex) {
    }
    return nativeFile.exists() ? nativeFile.getAbsolutePath() : null;
}

void GdxNativesLoader::load () {
    if (disableNativesLoading) {
        System.out
        .println("So you don't like our native lib loading? Good, you are on your own now. We don't give support from here on out");
        return;
    }
    if (nativesLoaded) return;

    String vm = System.getProperty("java.vm.name");
    if (vm == null || !vm.contains("Dalvik")) {
        if (isWindows) {
            nativesLoaded = loadLibrary("gdx.dll", "gdx-64.dll");
        } else if (isMac) {
            nativesLoaded = loadLibrary("libgdx.dylib", "libgdx.dylib");
        } else if (isLinux) {
            nativesLoaded = loadLibrary("libgdx.so", "libgdx-64.so");
        }
        if (nativesLoaded) return;
    }

    if (!is64Bit || isMac) {
        System.loadLibrary("gdx");
    } else {
        System.loadLibrary("gdx-64");
    }
    nativesLoaded = true;
}

