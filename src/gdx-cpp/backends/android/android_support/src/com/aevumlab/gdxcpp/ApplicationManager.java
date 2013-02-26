package com.aevumlab.gdxcpp;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.HashMap;
import java.util.Stack;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.app.Activity;
import android.content.Context;
import android.content.res.AssetManager;
import android.opengl.GLSurfaceView;
import android.view.Display;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.View;

import com.badlogic.gdx.Files.FileType;
import com.badlogic.gdx.backends.android.AndroidAudio;
import com.badlogic.gdx.backends.android.AndroidFiles;
import com.badlogic.gdx.files.FileHandle;

public class ApplicationManager {
	static HashMap<Integer, Integer> pointerIdToButton = new HashMap<Integer, Integer>();
	static Stack<Integer> pendingIds = new Stack<Integer>();

	static {
		for (int i = 20; i > 0; --i) {
			pendingIds.push(i);
		}
	}
		
	static native void nativeInitSystem();

	static native void nativeInitialize(AssetManager manager, int width, int height);

	static native void nativeCreate();

	static native void nativeUpdate();

	static native void nativePause();

	static native void nativeResume();

	static native void nativeResize(int widht, int height);

	static native void nativeTouchDownEvent(float x, float y, int button);

	static native void nativeTouchUpEvent(float x, float y, int button);

	static native void nativeTouchDragEvent(float x, float y, int button);
	
	static native void nativeKeyEvent(int key, int event);
	
	static native void nativeBackPressed();

	InputHandler handler = new InputHandler();
	Activity activity;
	Runnable onBeforeCreate;
	
	static AndroidFiles files;
	private AndroidAudio audio;

	class NativeSurfaceRenderer implements GLSurfaceView.Renderer {
		boolean created;

		@Override
		public void onDrawFrame(GL10 gl) {
			ApplicationManager.nativeUpdate();
		}

		@Override
		public void onSurfaceChanged(GL10 gl, int width, int height) {
			ApplicationManager.nativeResize(width, height);
			if (!created) {
				if (onBeforeCreate != null) {
					onBeforeCreate.run();
				}
				ApplicationManager.nativeCreate();
				created = true;
			}
		}

		@Override
		public void onSurfaceCreated(GL10 gl, EGLConfig config) {

			Display display = activity.getWindowManager().getDefaultDisplay();
			int width = display.getWidth();
			int height = display.getHeight();

			ApplicationManager.nativeInitialize(null, width, height);
			audio = new AndroidAudio(activity);
			audio.registerAudioEngine(audio);
		}
	}

	class NativeSurfaceView extends GLSurfaceView {

		public NativeSurfaceView(Context context) {
			super(context);
			handler.setup(this);
			setFocusable(true);
			setFocusableInTouchMode(true);
			setRenderer(new NativeSurfaceRenderer());
			setKeepScreenOn(true);
		}

		@Override
		protected void onMeasure(int widthMeasureSpec, int heightMeasureSpec) {
			final int width = View.MeasureSpec.getSize(widthMeasureSpec);
			final int height = View.MeasureSpec.getSize(heightMeasureSpec);

			setMeasuredDimension(width, height);
		}
	}

	public GLSurfaceView createView(Context context) {
		return new NativeSurfaceView(context);
	}

	public void initializeWithSharedLib(String library, AssetManager assetManager) {
		files = new AndroidFiles(assetManager, activity);

		System.loadLibrary(library);
		nativeInitSystem();
	}

	public void initialize(Activity activity, Runnable beforeCreate) {
		this.activity = activity;
		this.onBeforeCreate = beforeCreate;
	}

	public void update() {
	}

	public void pause() {
		nativePause();
		audio.pause();
	}

	public void resume() {
		audio.resume();
		nativeResume();
	}

	public void unload() {
		audio.dispose();
	}
	
	public void backPressed() {
		nativeBackPressed();
	}

	public static void onTouchEvent(MotionEvent evt) {
		final int action = evt.getAction() & MotionEvent.ACTION_MASK;
		int pointerIndex = (evt.getAction() & MotionEvent.ACTION_POINTER_ID_MASK) >> MotionEvent.ACTION_POINTER_ID_SHIFT;
		
		synchronized (pointerIdToButton) {
			switch (action) {
			case MotionEvent.ACTION_DOWN:
			case MotionEvent.ACTION_POINTER_DOWN:{
					int pointerId = evt.getPointerId(pointerIndex);
					pointerIdToButton.put(pointerId, pendingIds.pop());

					nativeTouchDownEvent(evt.getX(pointerIndex), evt.getY(pointerIndex), pointerIdToButton.get(pointerId)); 
				}
				break;
			case MotionEvent.ACTION_POINTER_UP:
			case MotionEvent.ACTION_UP:
				int pointerId = evt.getPointerId(pointerIndex);
				int button = pointerIdToButton.get(pointerId);
				
				nativeTouchUpEvent(evt.getX(pointerIndex), evt.getY(pointerIndex), button);
				
				pendingIds.push(button);
				pointerIdToButton.remove(pointerId);
				break;
			case MotionEvent.ACTION_MOVE:
				for (int i = 0; i < evt.getPointerCount(); i++) {
					nativeTouchDragEvent(evt.getX(i), evt.getY(i), pointerIdToButton.get(evt.getPointerId(i)));
				}
				break;
			}
		}
	}

	static byte[] readFile(String filename, int fileType) {
		FileHandle handle = files.getFileHandle(filename, FileType.values()[fileType]);

		if (handle != null) {
			InputStream is = handle.read();
			ByteArrayOutputStream bos = new ByteArrayOutputStream(); 
			
			try {
				byte[] buffer = new byte[8192];
				int readed = 0;
				while((readed = is.read(buffer)) >= 0) {				
					bos.write(buffer, 0, readed);
				}
				
				
			} catch (IOException e) {
				return null;
			} finally {
				try {
					is.close();
				} catch (IOException e) {
				}
			}
						
			return bos.toByteArray();
		}

		return null;
	}
	
	static boolean fileExists(String filename, int fileType) {
		return files.getFileHandle(filename, FileType.values()[fileType]).exists();
	}
	
	static int writeFile(String filename, byte[] data, boolean append, int fileType) {		
		OutputStream os = files.getFileHandle(filename, FileType.values()[fileType]).write(append);
		
		if (os == null) {
			return 0;
		}
		
		try {
			os.write(data);
			os.flush();
			
			return data.length;
		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			try {
				os.close();
			} catch (IOException e) {
			}
		}
		
		return 0;
	}

	public static void onKeyEvent(KeyEvent arg2) {
		nativeKeyEvent(arg2.getKeyCode(), arg2.getAction());
	}
}
