package com.playtech.qtshare;


import java.nio.ByteBuffer;
import java.nio.ByteOrder;

import android.app.Activity;
import android.content.Context;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
import android.content.Intent;
import android.os.Build;
import android.view.ViewGroup;
import android.view.MotionEvent;
import android.view.View;
import android.view.inputmethod.EditorInfo;
import android.widget.AbsoluteLayout;
import android.widget.Button;
import android.graphics.*;
import android.util.Log;

import java.util.Map;
import java.util.HashMap;

import java.util.concurrent.FutureTask;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.Callable;

import java.lang.reflect.Constructor;
import java.lang.reflect.Method;
import java.util.concurrent.Semaphore;

@SuppressWarnings("deprecation")
public class NativeButtonController {
    private static Activity activity_ = null;
    private QtHelper qtHelper_ = null;
    private Button view_ = null;
    private int id_ = -1;
    private int groupId_ = -1;

    private AbsoluteLayout.LayoutParams transactionLayoutParams;
    private boolean bTransaction;

    static native void onNativeButtonClicked(final int id);

    private static HashMap<Integer, NativeButtonController> mapControllers_ = new HashMap<Integer, NativeButtonController>();
    
    private void runOnUiThread(final Runnable action) {
        
        if(activity_ != null) {
            try {
                FutureTask<Boolean> futureResult = new FutureTask<Boolean>(new Callable<Boolean>() {
                    @Override
                    public Boolean call() throws Exception {
                        try {
                            Log.i(this.getClass().getName(), "runOnUiThread executing...");
                            action.run();
                        }
                        catch (Exception e) {
                            e.printStackTrace();
                            return false;
                        }
                        return true;
                    }
                });
                activity_.runOnUiThread(futureResult);
                
                Log.i(this.getClass().getName(), "runOnUiThread before wait called");
                boolean returnValue = futureResult.get(2000L, TimeUnit.MILLISECONDS);
                if(returnValue == true)
                {
                    Log.i(this.getClass().getName(), "runOnUiThread success");
                }
                else
                {
                    Log.e(this.getClass().getName(), "runOnUiThread error!");
                }
            }
            catch (Exception e) {
                e.printStackTrace();
                Log.e(this.getClass().getName(), "runOnUiThread exception");
            }
        }
        else
        {
            Log.i(this.getClass().getName(), "runOnUiThread activity is null");
        }
    }

    
    public void create(final Activity activity, final int id) {
        activity_ = activity;
        qtHelper_ = new QtHelper(activity_);
        
        Log.i(this.getClass().getName(), "public void create");
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                id_ = id;
                    mapControllers_.put(new Integer(id), NativeButtonController.this);
                view_ = new Button(activity_);
                view_.setOnClickListener(new View.OnClickListener() {
                     public void onClick(View v) {
                         onNativeButtonClicked(id_);
                     }
                });
                view_.setVisibility(View.INVISIBLE);
                view_.setBackgroundColor(0x6600FF00);
                qtHelper_.getNativeLayout().addView(view_, new ViewGroup.LayoutParams(AbsoluteLayout.LayoutParams.MATCH_PARENT, AbsoluteLayout.LayoutParams.MATCH_PARENT));
            }
        });
    }
    
    public void destroy() {
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                    mapControllers_.remove(id_);
                if(view_ != null){
                    qtHelper_.getNativeLayout().removeView(view_);
                    view_ = null;
                    qtHelper_ = null;
                }
            }
        });
    }
    public void setGeometry(final int x, final int y, final int width, final int height) {

        Log.i(this.getClass().getName(), "public void setGeometry (" + x + " " + y + " " + width + " " + height + " )");
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                if(view_ != null) {
                    qtHelper_.setLayoutParams(view_, new AbsoluteLayout.LayoutParams(width, height, x, y));
                }
            }
        });
    }
    public void setX(final int x) {
        Log.i(this.getClass().getName(), "public void setX (" + x + ")" );
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                if(view_ != null && !bTransaction) {
                    final AbsoluteLayout.LayoutParams viewLayoutParams = qtHelper_.getLayoutParams(view_);
                    qtHelper_.setLayoutParams(view_, new AbsoluteLayout.LayoutParams(viewLayoutParams.width,
                                                                                    viewLayoutParams.height,
                                                                                    x,
                                                                                    viewLayoutParams.y));
                }
            }
        });
    }

    public void moveByY(final int y) {
        Log.i(this.getClass().getName(), "public void moveByY (" + y + ")" );
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                if(view_ != null && !bTransaction) {
                    final AbsoluteLayout.LayoutParams viewLayoutParams = qtHelper_.getLayoutParams(view_);
                    qtHelper_.setLayoutParams(view_, new AbsoluteLayout.LayoutParams(viewLayoutParams.width,
                                                                                    viewLayoutParams.height,
                                                                                    viewLayoutParams.x,
                                                                                    viewLayoutParams.y + y));
                }
                else if(view_ != null) {
                    final AbsoluteLayout.LayoutParams viewLayoutParams = qtHelper_.getLayoutParams(view_);

                    transactionLayoutParams = new AbsoluteLayout.LayoutParams(viewLayoutParams.width,
                                                                                viewLayoutParams.height,
                                                                                viewLayoutParams.x,
                                                                                viewLayoutParams.y + y);
                }
            }
        });
    }
    public void moveByX(final int x) {
        Log.i(this.getClass().getName(), "public void moveByX (" + x + ")" );
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                if(view_ != null && !bTransaction) {
                    final AbsoluteLayout.LayoutParams viewLayoutParams = qtHelper_.getLayoutParams(view_);
                    qtHelper_.setLayoutParams(view_, new AbsoluteLayout.LayoutParams(viewLayoutParams.width,
                                                                                    viewLayoutParams.height,
                                                                                    viewLayoutParams.x + x,
                                                                                    viewLayoutParams.y));
                }
                else if(view_ != null) {
                    final AbsoluteLayout.LayoutParams viewLayoutParams = qtHelper_.getLayoutParams(view_);

                    transactionLayoutParams = new AbsoluteLayout.LayoutParams(viewLayoutParams.width,
                                                                                viewLayoutParams.height,
                                                                                viewLayoutParams.x + x,
                                                                                viewLayoutParams.y);
                }
            }
        });
    }

    public void setY(final int y) {
        Log.i(this.getClass().getName(), "public void setY (" + y + ")" );
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                if(view_ != null && !bTransaction) {
                    final AbsoluteLayout.LayoutParams viewLayoutParams = qtHelper_.getLayoutParams(view_);
                    qtHelper_.setLayoutParams(view_, new AbsoluteLayout.LayoutParams(viewLayoutParams.width,
                                                                                    viewLayoutParams.height,
                                                                                    viewLayoutParams.x,
                                                                                    y));
                }
            }
        });
    }


    public void setWidth(final int width) {

        Log.i(this.getClass().getName(), "public void setWidth (" + width + ")" );
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                if(view_ != null) {
                    final AbsoluteLayout.LayoutParams viewLayoutParams = qtHelper_.getLayoutParams(view_);
                    qtHelper_.setLayoutParams(view_, new AbsoluteLayout.LayoutParams(width,
                                                                                    viewLayoutParams.height,
                                                                                    viewLayoutParams.x,
                                                                                    viewLayoutParams.y));
                }
            }
        });
    }
    public void setHeight(final int height) {

        Log.i(this.getClass().getName(), "public void setHeight (" + height + ")" );
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                if(view_ != null) {
                    final AbsoluteLayout.LayoutParams viewLayoutParams = qtHelper_.getLayoutParams(view_);
                    qtHelper_.setLayoutParams(view_, new AbsoluteLayout.LayoutParams(viewLayoutParams.width,
                                                                                    height,
                                                                                    viewLayoutParams.x,
                                                                                    viewLayoutParams.y));
                }
            }
        });
    }


    public int[] getGeometry() {
        final int[] result = { 0, 0, 0, 0 };
        
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                final AbsoluteLayout.LayoutParams viewLayoutParams = qtHelper_.getLayoutParams(view_);
                result[0] = viewLayoutParams.x;
                result[1] = viewLayoutParams.y;
                result[2] = viewLayoutParams.width;
                result[3] = viewLayoutParams.height;
            }
        });
        
        return result;
    }

    public void setVisibility(final boolean isVisible) {
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                
                if(view_ != null) {
                    
                    Log.e(this.getClass().getName(), "setVisibility " + isVisible);
                    view_.setVisibility(isVisible ? View.VISIBLE : View.INVISIBLE);
                    
                    // It should be here. Otherwise the setVisibility() does not work.
                    qtHelper_.getNativeLayout().requestLayout();
                }
            }
        });
    }
    
    public boolean isVisible() {
        final boolean[] result = { false };
        
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                
                if(view_ != null) {
                    result[0] = (view_.getVisibility() == View.VISIBLE);
                }
            }
        });
        return result[0];
    }
    void setGroupId(final int i)
    {
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                groupId_ = i;
            }
        });
    }

    static public void startMoveTransaction(final int groupId)
    {
            for (Integer key : mapControllers_.keySet()) {
                final NativeButtonController controller = mapControllers_.get(key);
                if(controller.groupId_ == groupId) {
                    controller.runOnUiThread(new Runnable() {
                        @Override
                        public void run() {
                            controller.bTransaction = true;
                            controller.transactionLayoutParams = controller.qtHelper_.getLayoutParams(controller.view_);
                        }
                    });
                }
            }
//        }
    }

    static public void commitMoveTransaction(final int groupId)
    {
        if(!mapControllers_.isEmpty()) {

            Map.Entry<Integer, NativeButtonController> entry = mapControllers_.entrySet().iterator().next();
            final NativeButtonController mainController = entry.getValue();

            mainController.runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    for (Integer key : mapControllers_.keySet()) {
                        final NativeButtonController controller = mapControllers_.get(key);
                        if(controller.groupId_ == groupId) {
                            if(controller.bTransaction == true) {
                                controller.qtHelper_.setLayoutParams(controller.view_, new AbsoluteLayout.LayoutParams(controller.transactionLayoutParams.width,
                                                                                                controller.transactionLayoutParams.height,
                                                                                                controller.transactionLayoutParams.x,
                                                                                                controller.transactionLayoutParams.y));
                                controller.bTransaction = false;
                            }
                        }
                    }
                }
            });
        }
    }
}
