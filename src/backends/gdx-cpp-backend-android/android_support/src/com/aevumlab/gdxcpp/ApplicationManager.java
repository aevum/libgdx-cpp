package com.aevumlab.gdxcpp;

import java.util.HashMap;
import java.util.Stack;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.app.Activity;
import android.content.Context;
import android.content.res.AssetManager;
import android.opengl.GLSurfaceView;
import android.view.Display;
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

	InputHandler handler = new InputHandler();
	Activity activity;
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
		files = new AndroidFiles(assetManager);

		System.loadLibrary(library);
		nativeInitSystem();
	}

	public void initialize(Activity activity) {
		this.activity = activity;
	}

	public void update() {
	}

	public void pause() {
		nativePause();
		audio.pause();
	}

	public void resume() {
		nativeResume();
		audio.resume();
	}

	public void unload() {
		audio.dispose();
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

					nativeTouchDownEvent(evt.getX(), evt.getY(), pointerIdToButton.get(pointerId)); 
				}
				break;
			case MotionEvent.ACTION_POINTER_UP:
			case MotionEvent.ACTION_UP:
				int pointerId = evt.getPointerId(pointerIndex);
				int button = pointerIdToButton.get(pointerId);
				
				nativeTouchUpEvent(evt.getX(), evt.getY(), button);
				
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
			return handle.readBytes();
		}

		return null;
	}
}
