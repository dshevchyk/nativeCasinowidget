package com.playtech;

import com.playtech.qtshare.QtHelper;

import android.webkit.WebSettings;
import android.webkit.WebSettings.PluginState;

import android.content.Context;
import android.os.Bundle;
import android.os.AsyncTask;
import android.os.Handler;
import android.util.Log;
import android.content.res.Configuration;

import org.qtproject.qt5.android.bindings.QtActivity;
import android.content.pm.ActivityInfo;
import android.content.pm.PackageManager;

import java.util.concurrent.TimeUnit;

import android.app.Activity;
import android.content.Intent;
import android.graphics.Rect;
import android.graphics.PixelFormat;
import android.os.Bundle;
import android.os.Build;
import android.os.Handler;
import android.os.PowerManager;

import android.webkit.WebView;
import android.webkit.WebViewClient;

import android.util.DisplayMetrics;
import android.view.Gravity;
import android.view.View;
import android.view.ViewGroup;
import android.view.ViewTreeObserver;
import android.view.Window;
import android.view.WindowManager;
import android.view.MotionEvent;
import android.view.KeyEvent;
import android.view.ViewGroup;

import android.widget.FrameLayout;
import android.widget.TextView;
import android.widget.AbsoluteLayout;


public class PokerActivity extends QtActivity
{

    private WebView mWebView;
    private QtHelper mHelper;
    static native void testNative(String logMessage);
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        Log.i(getClass().getName(), "onResume()");
        super.onCreate(savedInstanceState);
        mHelper = new QtHelper(this);
        mWebView = new WebView(this);

        mWebView.setWebViewClient(new WebViewClient() {
            public boolean shouldOverrideUrlLoading(WebView view, String url) {
                view.loadUrl(url);
                return true;
            }
        });

    final WebSettings webSettings = mWebView.getSettings();
    webSettings.setJavaScriptEnabled(true);
    webSettings.setJavaScriptCanOpenWindowsAutomatically(true);
    webSettings.setDomStorageEnabled(true);
    webSettings.setPluginState(PluginState.ON);
    webSettings.setUseWideViewPort(true);
    webSettings.setSupportMultipleWindows(true);
    mWebView.setVerticalScrollBarEnabled(false);
    mWebView.setHorizontalScrollBarEnabled(false);
        mWebView.loadUrl("http://game-ua-mobile-poker-qa9.playtechmobile.com/casinoclient.html?game=ashbob&inPoker&real=1&hub=0&username=PT830012BOT29&temptoken=mW4HtBOQFrjtwuJNTPlgEFAA8NCgIPDI&debuginvp");


        mHelper.getNativeLayout().addView(mWebView, new ViewGroup.LayoutParams(AbsoluteLayout.LayoutParams.MATCH_PARENT, AbsoluteLayout.LayoutParams.MATCH_PARENT));
//        final AbsoluteLayout.LayoutParams viewLayoutParams = mHelper.getLayoutParams(mWebView);
//        mHelper.setLayoutParams(mWebView, new AbsoluteLayout.LayoutParams(500,
//                                                                        500,
//                                                                        500,
//                                                                        500));

//        View v = new View(this);
//        v.setBackgroundColor(0xFF00FF00);
//        mHelper.getNativeLayout().addView(v, new ViewGroup.LayoutParams(AbsoluteLayout.LayoutParams.MATCH_PARENT, AbsoluteLayout.LayoutParams.MATCH_PARENT));

    }


    @Override
    public void onResume()
    {
        Log.i(getClass().getName(), "onResume()");
        super.onResume();

    }
    
    @Override
    public void onPause()
    {
        Log.i(getClass().getName(), "onPause()");
        super.onPause();
    }
    
    @Override
    public void onStop()
    {
        Log.i(getClass().getName(), "onStop()");
        super.onStop();
    }

    @Override
    public boolean dispatchTouchEvent(MotionEvent event) {
        return super.dispatchTouchEvent(event);
    }

    @Override
    public void onStart()
    {
        Log.i(getClass().getName(), "onStart()");
        super.onStart();
    }

    @Override
    protected void onDestroy()
    {
        Log.i(getClass().getName(), "onDestroy()");
        super.onDestroy();
    }

    // 2.0 and above
    @Override
    public void onBackPressed() {

        Log.i(getClass().getName(), "onBackPressed()");
    }

    // Before 2.0
    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event) {

        Log.i(getClass().getName(), "onKeyDown()");
        testNative("onKeyDown from Java");
        if (keyCode == KeyEvent.KEYCODE_BACK) {
            return true;
        }
        return super.onKeyDown(keyCode, event);
    }


}
