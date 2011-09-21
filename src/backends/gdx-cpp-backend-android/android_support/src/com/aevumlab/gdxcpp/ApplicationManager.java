package com.aevumlab.gdxcpp;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import com.badlogic.gdx.backends.android.AndroidAudio;

import android.app.Activity;
import android.content.Context;
import android.content.res.AssetManager;
import android.opengl.GLSurfaceView;
import android.view.Display;
import android.view.MotionEvent;
import android.view.View;

public class ApplicationManager {
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
	private AssetManager assets;
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

			ApplicationManager.nativeInitialize(assets, width, height);
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
		this.assets = assetManager;
		System.loadLibrary(library);
		nativeInitSystem();
	}

	public void initialize(Activity activity) {
		this.activity = activity;
		System.loadLibrary("gdx-cpp");
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
		switch(evt.getAction()) {
		case MotionEvent.ACTION_DOWN:
			nativeTouchDownEvent(evt.getX(), evt.getY(), evt.getAction() & MotionEvent.ACTION_POINTER_ID_MASK >> MotionEvent.ACTION_POINTER_ID_SHIFT);
			break;
		case MotionEvent.ACTION_UP:
			nativeTouchUpEvent(evt.getX(), evt.getY(), evt.getAction() & MotionEvent.ACTION_POINTER_ID_MASK >> MotionEvent.ACTION_POINTER_ID_SHIFT);
			break;
		case MotionEvent.ACTION_MOVE:
			nativeTouchDragEvent(evt.getX(), evt.getY(), evt.getAction() & MotionEvent.ACTION_POINTER_ID_MASK >> MotionEvent.ACTION_POINTER_ID_SHIFT);
			break;
		}		
	}
}
