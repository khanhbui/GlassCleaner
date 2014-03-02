package org.cocos2dx.javascript;

import com.google.android.gms.ads.AdListener;
import com.google.android.gms.ads.AdRequest;
import com.google.android.gms.ads.AdSize;
import com.google.android.gms.ads.AdView;

import android.app.NativeActivity;
import android.graphics.PixelFormat;
import android.graphics.Point;
import android.os.Bundle;
import android.util.Log;
import android.view.ViewGroup.LayoutParams;
import android.widget.LinearLayout;

public class Cocos2dxActivity extends NativeActivity{

	private AdView mAdView;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		
		//For supports translucency
		
		//1.change "attribs" in cocos\2d\platform\android\nativeactivity.cpp
		/*const EGLint attribs[] = {
	            EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
	            EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,  
	            //EGL_BLUE_SIZE, 5,   -->delete 
	            //EGL_GREEN_SIZE, 6,  -->delete 
	            //EGL_RED_SIZE, 5,    -->delete 
	            EGL_BUFFER_SIZE, 32,  //-->new field
	            EGL_DEPTH_SIZE, 16,
	            EGL_STENCIL_SIZE, 8,
	            EGL_NONE
	    };*/
		
		//2.Set the format of window
		//getWindow().setFormat(PixelFormat.TRANSLUCENT);
		
		final Point size = new Point();
        getWindowManager().getDefaultDisplay().getSize(size);

        mAdView = new AdView(this);
        mAdView.setAdSize(AdSize.SMART_BANNER);
        mAdView.setAdUnitId("a1530e0a2793b0f");
        mAdView.setAdListener(new AdListener() {
            private boolean isNotSetY = true;
            @Override
            public void onAdLoaded() {
            	Log.d("00000000000000", "----++ " + size.y + "|" + mAdView.getHeight());
                if (isNotSetY) {
                    //mAdView.setY(size.y - mAdView.getHeight());
                    this.isNotSetY = false;
                }
            }
        });
        AdRequest.Builder adRequestBuilder = new AdRequest.Builder();
        mAdView.loadAd(adRequestBuilder.build());

        LinearLayout layout = new LinearLayout(this);
        layout.setOrientation(LinearLayout.VERTICAL);
        layout.addView(mAdView);
        Log.d("00000000000000", "---- " + layout.getY() + "|" + size.y + "|" + mAdView.getHeight());
        addContentView(layout, new LayoutParams(size.x, size.y));
	}
}
