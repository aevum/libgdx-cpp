/*******************************************************************************
 * Copyright 2011 See AUTHORS file.
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ******************************************************************************/
package com.badlogic.gdx.backends.android;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import android.app.Activity;
import android.content.Context;
import android.content.res.AssetFileDescriptor;
import android.media.AudioManager;
import android.media.MediaPlayer;
import android.media.SoundPool;

import com.badlogic.gdx.Audio;
import com.badlogic.gdx.Files.FileType;
import com.badlogic.gdx.audio.AudioDevice;
import com.badlogic.gdx.audio.AudioRecorder;
import com.badlogic.gdx.audio.Music;
import com.badlogic.gdx.audio.Sound;
import com.badlogic.gdx.utils.GdxRuntimeException;

/**
 * An implementation of the {@link Audio} interface for Android.
 * 
 * @author mzechner
 * @author scooterman
 */
public final class AndroidAudio {
	private SoundPool soundPool;
	private final AudioManager manager;
	protected final List<AndroidMusic> musics = new ArrayList<AndroidMusic>();
	protected final List<Boolean> wasPlaying = new ArrayList<Boolean>();
	
	native void registerAudioEngine(AndroidAudio self);
	
	public AndroidAudio (Activity context) {
		soundPool = new SoundPool(16, AudioManager.STREAM_MUSIC, 100);
		manager = (AudioManager)context.getSystemService(Context.AUDIO_SERVICE);
		context.setVolumeControlStream(AudioManager.STREAM_MUSIC);
		
		registerAudioEngine(this);
	}

	public void pause () {
		synchronized(musics) {
			wasPlaying.clear();
			for (AndroidMusic music : musics) {
				if (music.isPlaying()) {
					music.pause();
					wasPlaying.add(true);
				} else
					wasPlaying.add(false);
			}
		}
	}

	public void resume () {
		synchronized(musics) {
			for (int i = 0; i < musics.size(); i++) {
				if (wasPlaying.get(i)) musics.get(i).play();
			}
		}
	}

	/**
	 * {@inheritDoc}
	 */
	public AudioDevice newAudioDevice (int samplingRate, boolean isMono) {
		return new AndroidAudioDevice(samplingRate, isMono);
	}

	/**
	 * {@inheritDoc}
	 */
	public Music newMusic (String path, int fileType) {
		AndroidFileHandle file = new AndroidFileHandle(null, path, FileType.values()[fileType]);

		MediaPlayer mediaPlayer = new MediaPlayer();

		if (file.type() == FileType.Internal) {
			try {
				AssetFileDescriptor descriptor = file.assets.openFd(file.path());
				mediaPlayer.setDataSource(descriptor.getFileDescriptor(), descriptor.getStartOffset(), descriptor.getLength());
				descriptor.close();
				mediaPlayer.prepare();
				AndroidMusic music = new AndroidMusic(this, mediaPlayer);
				synchronized(musics) {
					musics.add(music);
				}
				return music;
			} catch (Exception ex) {
				throw new GdxRuntimeException("Error loading audio file: " + file
					+ "\nNote: Internal audio files must be placed in the assets directory.", ex);
			}
		} else {
			try {
				mediaPlayer.setDataSource(file.path());
				mediaPlayer.prepare();
				AndroidMusic music = new AndroidMusic(this, mediaPlayer);
				musics.add(music);
				return music;
			} catch (Exception ex) {
				throw new GdxRuntimeException("Error loading audio file: " + file, ex);
			}
		}

	}

	/**
	 * {@inheritDoc}
	 */
	public Sound newSound (String path, int fileType) {
		AndroidFileHandle file = new AndroidFileHandle(null, path, FileType.values()[fileType]);
		if (file.type() == FileType.Internal) {
			try {
				AssetFileDescriptor descriptor = file.assets.openFd(file.path());
				AndroidSound sound = new AndroidSound(soundPool, manager, soundPool.load(descriptor, 1));
				descriptor.close();
				return sound;
			} catch (IOException ex) {
				throw new GdxRuntimeException("Error loading audio file: " + file
					+ "\nNote: Internal audio files must be placed in the assets directory.", ex);
			}
		} else {
			try {
				return new AndroidSound(soundPool, manager, soundPool.load(file.path(), 1));
			} catch (Exception ex) {
				throw new GdxRuntimeException("Error loading audio file: " + file, ex);
			}
		}
	}

	/**
	 * {@inheritDoc}
	 */
	public AudioRecorder newAudioRecoder (int samplingRate, boolean isMono) {
		return new AndroidAudioRecorder(samplingRate, isMono);
	}

	/**
	 * Kills the soundpool and all other resources
	 */
	public void dispose () {
		synchronized(musics) {
			// gah i hate myself.... music.dispose() removes the music from the list...
			ArrayList<AndroidMusic> musicsCopy = new ArrayList<AndroidMusic>(musics);
			for (AndroidMusic music : musicsCopy) {
				music.dispose();
			}		
		}
		soundPool.release();
	}
}
