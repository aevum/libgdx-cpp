package com.aevumlab.gdxcpp.tests;

import android.app.Activity;
import android.content.pm.ActivityInfo;
import android.content.res.AssetManager;
import android.os.Bundle;
import android.view.Window;
import android.view.WindowManager;

import com.aevumlab.gdxcpp.ApplicationManager;

public class LibGdxCppTestActivity extends Activity {
    ApplicationManager manager;
    AssetManager assetManager;
    
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        
        assetManager = getAssets();
        
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);
        getWindow().clearFlags(WindowManager.LayoutParams.FLAG_FORCE_NOT_FULLSCREEN);
        
        setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);
        manager = new ApplicationManager();
                
        manager.initialize(this);
        
        System.loadLibrary("gdx-cpp-box2d");
        System.loadLibrary("gdx-cpp-box2d-layer");
        
        manager.initializeWithSharedLib("SpritePerformanceTest");
        setContentView(manager.createView(this));
    }
    
    @Override
    protected void onDestroy() {
    	manager.unload();
    	super.onDestroy();
    }
}