/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package com.kd.GlassCleaner;

import org.cocos2dx.lib.Cocos2dxActivity;

import android.graphics.Point;
import android.os.Bundle;

public class GlassCleaner extends Cocos2dxActivity{
	
	// private AdView mAdView;

	protected void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);
		
		final Point size = new Point();
        getWindowManager().getDefaultDisplay().getSize(size);

        /*
        mAdView = new AdView(this);
        mAdView.setAdSize(AdSize.SMART_BANNER);
        mAdView.setAdUnitId("a1530e0a2793b0f");
        mAdView.setAdListener(new AdListener() {
            private boolean isNotSetY = true;
            @Override
            public void onAdLoaded() {
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
        */
	}
	
    static {
        System.loadLibrary("cocos2djs");
    }
}
