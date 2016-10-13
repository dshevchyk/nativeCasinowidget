package com.playtech;

import android.content.Context;
//import android.support.multidex.MultiDex;

public class PokerApplication extends org.qtproject.qt5.android.bindings.QtApplication
{
    @Override
    protected void attachBaseContext(Context base)
    {
        super.attachBaseContext(base);
//        MultiDex.install(this);
    }
}
