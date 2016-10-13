#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#ifdef Q_OS_ANDROID

#include <jni.h>

#include <QtAndroidExtras/QAndroidJniObject>
#include <QtAndroidExtras/QAndroidJniEnvironment>
#include "NativeButtonImplQML.h"
#include "NativeButtonsGroupImplQml.h"

extern "C"
{
JNIEXPORT void JNICALL Java_com_playtech_PokerActivity_testNative(JNIEnv *env, jobject thisObject, jstring data)
{
    const char *nativeString = env->GetStringUTFChars(data, 0);

    // use your string

    //(*env).ReleaseStringUTFChars(env, javaString, nativeString);
    qDebug(nativeString);
}
}
#endif

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    qmlRegisterType<CNativeButtonImplQml>("com.playtech", 1, 0, "NativeButton");
    qmlRegisterType<CNativeButtonsGroupImplQml>("com.playtech", 1, 0, "NativeButtonsGroup");
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
