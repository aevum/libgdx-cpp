package com.aevumlab.gdxcpp;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.app.Activity;
import android.content.Context;
import android.opengl.GLSurfaceView;
import android.view.Display;

public class ApplicationManager {
	static native void nativeInitSystem();

	static native void nativeInitialize(int width, int height);

	static native void nativeCreate();

	static native void nativeUpdate();

	static native void nativePause();

	static native void nativeResume();

	static native void nativeResize(int widht, int height);

	Activity activity;

	class NativeSurfaceRenderer implements GLSurfaceView.Renderer {

		@Override
		public void onDrawFrame(GL10 gl) {
			ApplicationManager.nativeUpdate();
		}

		@Override
		public void onSurfaceChanged(GL10 gl, int width, int height) {
			ApplicationManager.nativeResize(width, height);
			ApplicationManager.nativeCreate();
		}

		@Override
		public void onSurfaceCreated(GL10 gl, EGLConfig config) {

			Display display = activity.getWindowManager().getDefaultDisplay();
			int width = display.getWidth();
			int height = display.getHeight();

			ApplicationManager.nativeInitialize(width, height);
		}
	}

	class NativeSurfaceView extends GLSurfaceView {

		public NativeSurfaceView(Context context) {
			super(context);
			setFocusable(true);
			setFocusableInTouchMode(true);
			setRenderer(new NativeSurfaceRenderer());
		}

		// @Override
		// protected void onMeasure(int widthMeasureSpec, int heightMeasureSpec)
		// {
		// final int width = View.MeasureSpec.getSize(widthMeasureSpec);
		// final int height = View.MeasureSpec.getSize(heightMeasureSpec);
		//
		// setMeasuredDimension( width, height);
		// }
	}

	public GLSurfaceView createView(Context context) {
		return new NativeSurfaceView(context);
	}

	public void initializeWithSharedLib(String library) {
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
	}

	public void resume() {
		nativeResume();
	}

	public void unload() {

	}
}
