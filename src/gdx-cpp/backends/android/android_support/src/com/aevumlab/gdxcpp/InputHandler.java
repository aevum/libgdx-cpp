package com.aevumlab.gdxcpp;

import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnKeyListener;
import android.view.View.OnTouchListener;

import com.aevumlab.gdxcpp.ApplicationManager.NativeSurfaceView;

public class InputHandler implements  OnKeyListener, OnTouchListener, SensorEventListener {

	public void setup(NativeSurfaceView view) {
		view.setOnKeyListener(this);
		view.setOnTouchListener(this);
		view.setFocusable(true);
		view.setFocusableInTouchMode(true);
		view.requestFocus();
		view.requestFocusFromTouch();		
	}

	@Override
	public void onAccuracyChanged(Sensor arg0, int arg1) {

	}

	@Override
	public void onSensorChanged(SensorEvent arg0) {
		
	}

	@Override
	public boolean onTouch(View arg0, MotionEvent arg1) {
		ApplicationManager.onTouchEvent(arg1);
		return true;
	}

	@Override
	public boolean onKey(View arg0, int arg1, KeyEvent arg2) {
		ApplicationManager.onKeyEvent(arg2);
		return false;
	}

}
