package com.cocos.ads.helper;

import org.cocos2dx.lib.Cocos2dxActivity;

import android.view.Gravity;
import android.view.ViewGroup;
import android.widget.FrameLayout;
import android.widget.FrameLayout.LayoutParams;

import com.chance.ads.*;

public class CocosAdsHelper {
	private static Cocos2dxActivity sCocos2dxActivity = null;
	private static AdView sBanner = null;

	public static void showBanner(final String placementID, final String position) {
		sCocos2dxActivity = (Cocos2dxActivity) Cocos2dxActivity.getContext();
		sCocos2dxActivity.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				if(sBanner == null){
					sBanner = new AdView(sCocos2dxActivity, placementID);
				}else{
					ViewGroup parent = (ViewGroup) sBanner.getParent();
					if(parent != null){
						parent.removeView(sBanner);
					}
				}

				FrameLayout.LayoutParams params = new FrameLayout.LayoutParams(LayoutParams.WRAP_CONTENT, LayoutParams.WRAP_CONTENT);

        if (position.equals("LEFT_TOP")) {
          params.gravity = Gravity.LEFT | Gravity.TOP;
        } else if (position.equals("CENTER_TOP")) {
          params.gravity = Gravity.CENTER_HORIZONTAL | Gravity.TOP;
        } else if (position.equals("RIGHT_TOP")) {
          params.gravity = Gravity.RIGHT | Gravity.TOP;
        } else if (position.equals("LEFT_BOTTOM")) {
          params.gravity = Gravity.LEFT | Gravity.BOTTOM;
        } else if (position.equals("CENTER_BOTTOM")) {
          params.gravity = Gravity.CENTER_HORIZONTAL | Gravity.BOTTOM;
        } else if (position.equals("RIGHT_BOTTOM")) {
          params.gravity = Gravity.RIGHT | Gravity.BOTTOM;
        }

				sCocos2dxActivity.addContentView(sBanner, params);
				sBanner.loadAd(new AdRequest());
			}
		});
	}

	public static void hideBanner() {
		sCocos2dxActivity = (Cocos2dxActivity) Cocos2dxActivity.getContext();
		sCocos2dxActivity.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				if(sBanner == null){
					return;
				}else{
					ViewGroup parent = (ViewGroup) sBanner.getParent();
					if(parent != null){
						parent.removeView(sBanner);
					}
					sBanner.destroy();
					sBanner = null;
				}
			}
		});
	}
}
