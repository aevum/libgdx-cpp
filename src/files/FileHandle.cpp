
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

#include "FileHandle.hpp"

using namespace gdx_cpp::files;

std::string& FileHandle::path () {
    return file.getPath();
}

std::string& FileHandle::name () {
    return file.getName();
}

std::string& FileHandle::extension () {
    String name = file.getName();
    int dotIndex = name.lastIndexOf('.');
    if (dotIndex == -1) return "";
    return name.substring(dotIndex + 1);
}

std::string& FileHandle::nameWithoutExtension () {
    String name = file.getName();
    int dotIndex = name.lastIndexOf('.');
    if (dotIndex == -1) return name;
    return name.substring(0, dotIndex);
}

gdx_cpp::Files::FileType& FileHandle::type () {
    return type;
}

File& FileHandle::file () {
    if (type == FileType.External) return new File(Gdx.files.getExternalStoragePath(), file.getPath());
    return file;
}

InputStream& FileHandle::read () {
    if (type == FileType.Classpath || (type == FileType.Internal && !file.exists())) {
        InputStream input = FileHandle.class.getResourceAsStream("/" + file.getPath().replace('\\', '/'));
        if (input == null) throw new GdxRuntimeException("File not found: " + file + " (" + type + ")");
        return input;
    }
    try {
        return new FileInputStream(file());
    } catch (FileNotFoundException ex) {
        if (file().isDirectory())
            throw new GdxRuntimeException("Cannot open a stream to a directory: " + file + " (" + type + ")", ex);
        throw new GdxRuntimeException("Error reading file: " + file + " (" + type + ")", ex);
    }
}

std::string& FileHandle::readString () {
    return readString(null);
}

std::string& FileHandle::readString (const std::string& charset) {
    StringBuilder output = new StringBuilder(512);
    InputStreamReader reader = null;
    try {
        if (charset == null)
            reader = new InputStreamReader(read());
        else
            reader = new InputStreamReader(read(), charset);
        char[] buffer = new char[256];
        while (true) {
            int length = reader.read(buffer);
            if (length == -1) break;
            output.append(buffer, 0, length);
        }
    } catch (IOException ex) {
        throw new GdxRuntimeException("Error reading layout file: " + this, ex);
    }
    finally {
        try {
            if (reader != null) reader.close();
        } catch (IOException ignored) {
        }
    }
    return output.toString();
}

char* FileHandle::readBytes () {
    int length = (int)length();
    if (length == 0) length = 512;
    byte[] buffer = new byte[length];
    int position = 0;
    InputStream input = read();
    try {
        while (true) {
            int count = input.read(buffer, position, buffer.length - position);
            if (count == -1) break;
            position += count;
            if (position == buffer.length) {
                // Grow buffer.
                byte[] newBuffer = new byte[buffer.length * 2];
                System.arraycopy(buffer, 0, newBuffer, 0, position);
                buffer = newBuffer;
            }
        }
    } catch (IOException ex) {
        throw new GdxRuntimeException("Error reading file: " + this, ex);
    }
    finally {
        try {
            if (input != null) input.close();
        } catch (IOException ignored) {
        }
    }
    if (position < buffer.length) {
        // Shrink buffer.
        byte[] newBuffer = new byte[position];
        System.arraycopy(buffer, 0, newBuffer, 0, position);
        buffer = newBuffer;
    }
    return buffer;
}

OutputStream& FileHandle::write (bool append) {
    if (type == FileType.Classpath) throw new GdxRuntimeException("Cannot write to a classpath file: " + file);
    if (type == FileType.Internal) throw new GdxRuntimeException("Cannot write to an internal file: " + file);
    try {
        return new FileOutputStream(file(), append);
    } catch (FileNotFoundException ex) {
        if (file().isDirectory())
            throw new GdxRuntimeException("Cannot open a stream to a directory: " + file + " (" + type + ")", ex);
        throw new GdxRuntimeException("Error writing file: " + file + " (" + type + ")", ex);
    }
}

FileHandle* FileHandle::list () {
    if (type == FileType.Classpath) throw new GdxRuntimeException("Cannot list a classpath directory: " + file);
    String[] relativePaths = file().list();
    if (relativePaths == null) return new FileHandle[0];
    FileHandle[] handles = new FileHandle[relativePaths.length];
    for (int i = 0, n = relativePaths.length; i < n; i++)
        handles[i] = child(relativePaths[i]);
    return handles;
}

FileHandle* FileHandle::list (const std::string& suffix) {
    if (type == FileType.Classpath) throw new GdxRuntimeException("Cannot list a classpath directory: " + file);
    String[] relativePaths = file().list();
    if (relativePaths == null) return new FileHandle[0];
    FileHandle[] handles = new FileHandle[relativePaths.length];
    int count = 0;
    for (int i = 0, n = relativePaths.length; i < n; i++) {
        String path = relativePaths[i];
        if (!path.endsWith(suffix)) continue;
        handles[count] = child(path);
        count++;
    }
    if (count < relativePaths.length) {
        FileHandle[] newHandles = new FileHandle[count];
        System.arraycopy(handles, 0, newHandles, 0, count);
        handles = newHandles;
    }
    return handles;
}

bool FileHandle::isDirectory () {
    if (type == FileType.Classpath) return false;
    return file().isDirectory();

}

FileHandle& FileHandle::child (const std::string& name) {
    if (file.getPath().length() == 0) return new FileHandle(new File(name), type);
    return new FileHandle(new File(file, name), type);
}

FileHandle& FileHandle::parent () {
    File parent = file.getParentFile();
    if (parent == null) {
        if (type == FileType.Absolute)
            parent = new File("/");
        else
            parent = new File("");
    }
    return new FileHandle(parent, type);
}

void FileHandle::mkdirs () {
    if (type == FileType.Classpath) throw new GdxRuntimeException("Cannot mkdirs with a classpath file: " + file);
    if (type == FileType.Internal) throw new GdxRuntimeException("Cannot mkdirs with an internal file: " + file);
    file().mkdirs();
}

bool FileHandle::exists () {
    switch (type) {
    case Internal:
        if (file.exists()) return true;
        // Fall through.
    case Classpath:
        return FileHandle.class.getResourceAsStream("/" + file.getPath().replace('\\', '/')) != null;
    }
    return file().exists();
}

bool FileHandle::delete () {
    if (type == FileType.Classpath) throw new GdxRuntimeException("Cannot delete a classpath file: " + file);
    if (type == FileType.Internal) throw new GdxRuntimeException("Cannot delete an internal file: " + file);
    return file().delete();
}

bool FileHandle::deleteDirectory () {
    if (type == FileType.Classpath) throw new GdxRuntimeException("Cannot delete a classpath file: " + file);
    if (type == FileType.Internal) throw new GdxRuntimeException("Cannot delete an internal file: " + file);
    return deleteDirectory(file());
}

void FileHandle::copyTo (const FileHandle& dest) {
    InputStream input = null;
    OutputStream output = null;
    try {
        input = read();
        output = dest.write(false);
        byte[] buffer = new byte[4096];
        while (true) {
            int length = input.read(buffer);
            if (length == -1) break;
            output.write(buffer, 0, length);
        }
    } catch (Exception ex) {
        throw new GdxRuntimeException("Error copying source file: " + file + " (" + type + ")\n" //
                                      + "To destination: " + dest.file + " (" + dest.type + ")", ex);
    }
    finally {
        try {
            if (input != null) input.close();
        } catch (Exception ignored) {
        }
        try {
            if (output != null) output.close();
        } catch (Exception ignored) {
        }
    }
}

void FileHandle::moveTo (const FileHandle& dest) {
    if (type == FileType.Classpath) throw new GdxRuntimeException("Cannot move a classpath file: " + file);
    if (type == FileType.Internal) throw new GdxRuntimeException("Cannot move an internal file: " + file);
    copyTo(dest);
    delete();
}

long FileHandle::length () {
    if (type == FileType.Classpath || (type == FileType.Internal && !file.exists())) {
        InputStream input = read();
        try {
            return input.available();
        } catch (Exception ignored) {
        } finally {
            try {
                input.close();
            } catch (IOException ignored) {
            }
        }
        return 0;
    }
    return file().length();
}

std::string& FileHandle::toString () {
    return file.getPath();
}

bool FileHandle::deleteDirectory (const File& file) {
    if (file.exists()) {
        File[] files = file.listFiles();
        if (files != null) {
            for (int i = 0, n = files.length; i < n; i++) {
                if (files[i].isDirectory())
                    deleteDirectory(files[i]);
                else
                    files[i].delete();
            }
        }
    }
    return file.delete();
}

