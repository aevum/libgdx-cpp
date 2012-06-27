
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

#include "RemoteSender.hpp"

using namespace gdx;

void RemoteSender::sendUpdate () {
    synchronized (this) {
        if (!connected) return;
    }
    try {
        out.writeInt(ACCEL);
        out.writeFloat(Gdx.input.getAccelerometerX());
        out.writeFloat(Gdx.input.getAccelerometerY());
        out.writeFloat(Gdx.input.getAccelerometerZ());
        out.writeInt(COMPASS);
        out.writeFloat(Gdx.input.getAzimuth());
        out.writeFloat(Gdx.input.getPitch());
        out.writeFloat(Gdx.input.getRoll());
        out.writeInt(SIZE);
        out.writeFloat(Gdx.graphics.getWidth());
        out.writeFloat(Gdx.graphics.getHeight());
    } catch (Throwable t) {
        out = null;
        connected = false;
    }
}

bool RemoteSender::keyDown (int keycode) {
    synchronized (this) {
        if (!connected) return false;
    }

    try {
        out.writeInt(KEY_DOWN);
        out.writeInt(keycode);
    } catch (Throwable t) {
        synchronized (this) {
            connected = false;
        }
    }
    return false;
}

bool RemoteSender::keyUp (int keycode) {
    synchronized (this) {
        if (!connected) return false;
    }

    try {
        out.writeInt(KEY_UP);
        out.writeInt(keycode);
    } catch (Throwable t) {
        synchronized (this) {
            connected = false;
        }
    }
    return false;
}

bool RemoteSender::keyTyped (char character) {
    synchronized (this) {
        if (!connected) return false;
    }

    try {
        out.writeInt(KEY_TYPED);
        out.writeChar(character);
    } catch (Throwable t) {
        synchronized (this) {
            connected = false;
        }
    }
    return false;
}

bool RemoteSender::touchDown (int x,int y,int pointer,int button) {
    synchronized (this) {
        if (!connected) return false;
    }

    try {
        out.writeInt(TOUCH_DOWN);
        out.writeInt(x);
        out.writeInt(y);
        out.writeInt(pointer);
    } catch (Throwable t) {
        synchronized (this) {
            connected = false;
        }
    }
    return false;
}

bool RemoteSender::touchUp (int x,int y,int pointer,int button) {
    synchronized (this) {
        if (!connected) return false;
    }

    try {
        out.writeInt(TOUCH_UP);
        out.writeInt(x);
        out.writeInt(y);
        out.writeInt(pointer);
    } catch (Throwable t) {
        synchronized (this) {
            connected = false;
        }
    }
    return false;
}

bool RemoteSender::touchDragged (int x,int y,int pointer) {
    synchronized (this) {
        if (!connected) return false;
    }

    try {
        out.writeInt(TOUCH_DRAGGED);
        out.writeInt(x);
        out.writeInt(y);
        out.writeInt(pointer);
    } catch (Throwable t) {
        synchronized (this) {
            connected = false;
        }
    }
    return false;
}

bool RemoteSender::touchMoved (int x,int y) {
    return false;
}

bool RemoteSender::scrolled (int amount) {
    return false;
}

bool RemoteSender::isConnected () {
    synchronized (this) {
        return connected;
    }
}

