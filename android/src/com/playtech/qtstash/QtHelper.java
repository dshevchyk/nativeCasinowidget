package com.playtech.qtshare;

import java.lang.reflect.Field;
import java.lang.reflect.InvocationTargetException;

import dalvik.system.DexClassLoader;
import android.app.Activity;
import android.content.Context;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AbsoluteLayout;

@SuppressWarnings("deprecation")
public class QtHelper {
    private final Activity activity_;
    private final ViewGroup nativeLayout_;
    private final DexClassLoader classLoader_;
    
    @SuppressWarnings("rawtypes")
    private Class nativeLayoutParamsClass_ = null;
    private Field nativeLayoutParamsXField_ = null;
    private Field nativeLayoutParamsYField_ = null;
    
    public QtHelper(final Activity activity) {
        activity_ = activity;
        nativeLayout_ = findNativeLayout((ViewGroup)activity_.getWindow().getDecorView().getRootView());
        
        classLoader_ = new DexClassLoader("", activity_.getDir("outdex", Context.MODE_PRIVATE).getAbsolutePath(), null, activity_.getClassLoader());
        
        try {
            nativeLayoutParamsClass_ = classLoader_.loadClass(nativeLayout_.getClass().getName() + "$LayoutParams");
            nativeLayoutParamsXField_ = nativeLayoutParamsClass_.getDeclaredField("x");
            nativeLayoutParamsYField_ = nativeLayoutParamsClass_.getDeclaredField("y");
            nativeLayoutParamsXField_.setAccessible(true);
            nativeLayoutParamsYField_.setAccessible(true);
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        } catch (NoSuchFieldException e) {
            e.printStackTrace();
        }
    }
    
    private ViewGroup findNativeLayout(final ViewGroup parentViewGroup) {
        ViewGroup result = null;
        
        for (int i = 0; i < parentViewGroup.getChildCount() && result == null; ++i) {
            final View childView = parentViewGroup.getChildAt(i);
            if (childView instanceof ViewGroup) {
                ViewGroup childViewGroup = (ViewGroup)childView;
                if (childViewGroup.getClass().getName().compareTo("org.qtproject.qt5.android.QtLayout") == 0) {
                    result = childViewGroup;
                }
                else {
                    result = findNativeLayout(childViewGroup);
                }
            }
        }
        
        return result;
    }
    
    public ViewGroup getNativeLayout() {
        return nativeLayout_;
    }
    
    public void setLayoutParams(final View view, final AbsoluteLayout.LayoutParams layoutParams) {
        try {
            final ViewGroup.LayoutParams nativeLayoutParams = (ViewGroup.LayoutParams)nativeLayoutParamsClass_.getConstructor(ViewGroup.LayoutParams.class).newInstance(new ViewGroup.LayoutParams(0, 0));
            nativeLayoutParamsXField_.set(nativeLayoutParams, (Integer)layoutParams.x);
            nativeLayoutParamsYField_.set(nativeLayoutParams, (Integer)layoutParams.y);
            nativeLayoutParams.width = layoutParams.width;
            nativeLayoutParams.height = layoutParams.height;
            view.setLayoutParams(nativeLayoutParams);
        } catch (IllegalAccessException e) {
            e.printStackTrace();
        } catch (IllegalArgumentException e) {
            e.printStackTrace();
        } catch (InstantiationException e) {
            e.printStackTrace();
        } catch (InvocationTargetException e) {
            e.printStackTrace();
        } catch (NoSuchMethodException e) {
            e.printStackTrace();
        }
    }
    
    public AbsoluteLayout.LayoutParams getLayoutParams(final View view) {
        AbsoluteLayout.LayoutParams result = null;
        
        final ViewGroup.LayoutParams nativeLayoutParams = view.getLayoutParams();
        result = new AbsoluteLayout.LayoutParams(0, 0, 0, 0);
        try {
            result.x = (Integer)nativeLayoutParamsXField_.get(nativeLayoutParams);
            result.y = (Integer)nativeLayoutParamsYField_.get(nativeLayoutParams);
        } catch (IllegalAccessException e) {
            e.printStackTrace();
        } catch (IllegalArgumentException e) {
            e.printStackTrace();
        }
        result.width = nativeLayoutParams.width;
        result.height = nativeLayoutParams.height;
        
        return result;
    }
}