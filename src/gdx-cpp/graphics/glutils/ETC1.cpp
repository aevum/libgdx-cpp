
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

#include "ETC1.hpp"

#include "gdx-cpp/utils/gzstream.hpp"
#include "gdx-cpp/graphics/Pixmap.hpp"

using namespace gdx;

bool ETC1::hasPKMHeader () {
    return dataOffset == 16;
}

void ETC1::write (const FileHandle& file) {
    DataOutputStream write = null;
    byte[] buffer = new byte[10 * 1024];
    int writtenBytes = 0;
    compressedData.position(0);
    compressedData.limit(compressedData.capacity());
    try {
        write = new DataOutputStream(new GZIPOutputStream(file.write(false)));
        write.writeInt(compressedData.capacity());
        while (writtenBytes != compressedData.capacity()) {
            int bytesToWrite = Math.min(compressedData.remaining(), buffer.length);
            compressedData.get(buffer, 0, bytesToWrite);
            write.write(buffer, 0, bytesToWrite);
            writtenBytes += bytesToWrite;
        }
    } catch (Exception e) {
        throw new GdxRuntimeException("Couldn't write PKM file to '" + file + "'", e);
    }
    finally {
        if (write != null) try {
                write.close();
            } catch (Exception e) {
            }
    }
    compressedData.position(dataOffset);
    compressedData.limit(compressedData.capacity());
}

void ETC1::dispose () {
    BufferUtils.freeMemory(compressedData);
}

std::string& ETC1::toString () {
    if (hasPKMHeader()) {
        return (ETC1.isValidPKM(compressedData, 0) ? "valid" : "invalid") + " pkm [" + ETC1.getWidthPKM(compressedData, 0)
               + "x" + ETC1.getHeightPKM(compressedData, 0) + "], compressed: "
               + (compressedData.capacity() - ETC1.PKM_HEADER_SIZE);
    } else {
        return "raw [" + width + "x" + height + "], compressed: " + (compressedData.capacity() - ETC1.PKM_HEADER_SIZE);
    }
}

int ETC1::getPixelSize (const Pixmap::Format& format) {
    if (format == Pixmap::Format::RGB565) return 2;
    if (format == Pixmap::Format::RGB888) return 3;
    throw new GdxRuntimeException("Can only handle RGB565 or RGB888 images");
}

ETC1Data& ETC1::encodeImage (const Pixmap& pixmap) {
    int pixelSize = getPixelSize(pixmap.getFormat());
    ByteBuffer compressedData = encodeImage(pixmap.getPixels(), 0, pixmap.getWidth(), pixmap.getHeight(), pixelSize);
    return new ETC1Data(pixmap.getWidth(), pixmap.getHeight(), compressedData, 0);
}

ETC1Data& ETC1::encodeImagePKM (const Pixmap& pixmap) {
    int pixelSize = getPixelSize(pixmap.getFormat());
    ByteBuffer compressedData = encodeImagePKM(pixmap.getPixels(), 0, pixmap.getWidth(), pixmap.getHeight(), pixelSize);
    return new ETC1Data(pixmap.getWidth(), pixmap.getHeight(), compressedData, 16);
}

Pixmap& ETC1::decodeImage (const ETC1Data& etc1Data,const Pixmap::Format& format) {
    int dataOffset = 0;
    int width = 0;
    int height = 0;

    if (etc1Data.hasPKMHeader()) {
        dataOffset = 16;
        width = ETC1.getWidthPKM(etc1Data.compressedData, 0);
        height = ETC1.getHeightPKM(etc1Data.compressedData, 0);
    } else {
        dataOffset = 0;
        width = etc1Data.width;
        height = etc1Data.height;
    }

    int pixelSize = getPixelSize(format);
    Pixmap pixmap = new Pixmap(width, height, format);
    decodeImage(etc1Data.compressedData, dataOffset, pixmap.getPixels(), 0, width, height, pixelSize);
    return pixmap;
}


ETC1::ETC1Data::ETC1Data(int width, int height, const char* compressedData, int dataOffset)
    : width(width), height(height), compressedData(compressedData), dataOffset(dataOffset)
{
}

ETC1::ETC1Data::ETC1Data(FileHandle& pkmFile) {
    char* buffer = new char[1024 * 10];
    
    try {        
        gz::igzstream iginput(pkmFile.read());       
        int fileSize;
        
        fileSize << iginput;        
        compressedData = new char[fileSize];
        
        int readBytes = 0;
        while (!iginput.eof()) {
            iginput.read(compressedData[readBytes], )
            compressedData.put(buffer, 0, readBytes);
        }
        compressedData.position(0);
        compressedData.limit(compressedData.capacity());
    } catch (Exception e) {
        throw new GdxRuntimeException("Couldn't load pkm file '" + pkmFile + "'", e);
    } finally {
        if (in != null) try {
                in.close();
            } catch (Exception e) {
            }
    }

    width = getWidthPKM(compressedData, 0);
    height = getHeightPKM(compressedData, 0);
    dataOffset = PKM_HEADER_SIZE;
    compressedData.position(dataOffset);
}
bool ETC1::ETC1Data::hasPKMHeader() {
    return dataOffset == 16;
}
void ETC1::ETC1Data::write(FileHandle file) {
    DataOutputStream write = null;
    byte[] buffer = new byte[10 * 1024];
    int writtenBytes = 0;
    compressedData.position(0);
    compressedData.limit(compressedData.capacity());
    try {
        write = new DataOutputStream(new GZIPOutputStream(file.write(false)));
        write.writeInt(compressedData.capacity());
        while (writtenBytes != compressedData.capacity()) {
            int bytesToWrite = Math.min(compressedData.remaining(), buffer.length);
            compressedData.get(buffer, 0, bytesToWrite);
            write.write(buffer, 0, bytesToWrite);
            writtenBytes += bytesToWrite;
        }
    } catch (Exception e) {
        throw new GdxRuntimeException("Couldn't write PKM file to '" + file + "'", e);
    } finally {
        if (write != null) try {
                write.close();
            } catch (Exception e) {
            }
    }
    compressedData.position(dataOffset);
    compressedData.limit(compressedData.capacity());
}
void ETC1::ETC1Data::dispose() {
    BufferUtils.freeMemory(compressedData);
}
String ETC1::ETC1Data::toString() {
    if (hasPKMHeader()) {
        return (ETC1.isValidPKM(compressedData, 0) ? "valid" : "invalid") + " pkm [" + ETC1.getWidthPKM(compressedData, 0)
               + "x" + ETC1.getHeightPKM(compressedData, 0) + "], compressed: "
               + (compressedData.capacity() - ETC1.PKM_HEADER_SIZE);
    } else {
        return "raw [" + width + "x" + height + "], compressed: " + (compressedData.capacity() - ETC1.PKM_HEADER_SIZE);
    }
}


