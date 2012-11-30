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

import android.content.Context;
import android.content.res.AssetManager;
import android.os.Environment;

import com.badlogic.gdx.Files;
import com.badlogic.gdx.files.FileHandle;

/**
 * @author mzechner
 * @author Nathan Sweet
 */
public class AndroidFiles implements Files {
	protected final String sdcard = Environment.getExternalStorageDirectory().getAbsolutePath() + "/";
	protected final AssetManager assets;
	protected final Context context;

	public AndroidFiles (AssetManager assets, Context context) {
		this.assets = assets;
		this.context = context;
	}

	@Override public FileHandle getFileHandle (String path, FileType type) {
		return new AndroidFileHandle(type == FileType.Internal ? assets : null, path, type, type == FileType.Private  ? context : null);
	}

	@Override public FileHandle classpath (String path) {
		return new AndroidFileHandle(null, path, FileType.Classpath, null);
	}

	@Override public FileHandle internal (String path) {
		return new AndroidFileHandle(assets, path, FileType.Internal, null);
	}

	@Override public FileHandle external (String path) {
		return new AndroidFileHandle(null, path, FileType.External, null);
	}

	@Override public FileHandle absolute (String path) {
		return new AndroidFileHandle(null, path, FileType.Absolute, null);
	}
	
	@Override public FileHandle private_internal (String path) {
		return new AndroidFileHandle(null, path, FileType.Private, context);
	}

	@Override public String getExternalStoragePath () {
		return sdcard;
	}

	@Override public boolean isExternalStorageAvailable () {
		return Environment.getExternalStorageState().equals(Environment.MEDIA_MOUNTED);
	}
}
