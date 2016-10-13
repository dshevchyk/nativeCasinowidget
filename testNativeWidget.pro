TEMPLATE = app

CONFIG += c++11

QT += gui widgets network quick xml multimedia androidextras

HEADERS += \
    EventThreadInvoker.h \
    NativeViewQML.h \
    CasinoGamesWidgetDelegateQML.h \
    AutoLock.h \
    NativeButtonQML.h \
    NativeButtonImplQML.h \
    NativeButtonsGroupQML.h \
    NativeButtonsGroupImplQML.h

SOURCES += main.cpp \
    NativeViewQML.cpp \
    CasinoGamesWidgetDelegateQML.cpp \
    NativeButtonQML.cpp \
    NativeButtonImplQML.cpp \
    NativeButtonsGroupQML.cpp \
    NativeButtonsGroupImplQML.cpp \

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =
ios {

    INCLUDEPATH += /usr/local/ssl/include
        LIBS += -L/Library/OpenSSL-for-iPhone/lib  -lcrypto -lssl
}

android {
    INCLUDEPATH += /usr/local/ssl/include
    LIBS += -L/usr/local/ssl/lib/android -lcrypto -lssl

    LIBS += -L/usr/local/ndk/sources/crystax/libs/armeabi -lcrystax
    ANDROID_EXTRA_LIBS += /usr/local/ndk/sources/crystax/libs/armeabi/libcrystax.so
}

# Default rules for deployment.
include(deployment.pri)

DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat \
    android/src/com/playtech/* \
    android/src/com/playtech/qtstash/*

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

