#include "NativeButtonImplQML.h"


#include <QtAndroidExtras/QAndroidJniObject>
#include <QtAndroidExtras/QAndroidJniEnvironment>
#include <QScreen>

extern "C"
{
JNIEXPORT void JNICALL Java_com_playtech_qtshare_NativeButtonController_onNativeButtonClicked(JNIEnv *env, jobject thisObject, jint id)
{

    int a =1;
    int b =a;
    a=b;
    qDebug("click processing");
}
}

static const char* CasinoGamesWidgetControllerClassName = "com/playtech/qtshare/NativeButtonController";

static int iCounter = 0;
float GetPixelsRatio()
{
    return (qApp && qApp->primaryScreen() && qApp->primaryScreen()->devicePixelRatio() == 0) ? 1 : qApp->primaryScreen()->devicePixelRatio();
}
CNativeButtonImplQml::CNativeButtonImplQml(QQuickItem* parent):
    CNativeButtonQml(parent)
  , javaController(std::unique_ptr<QAndroidJniObject>(new QAndroidJniObject(CasinoGamesWidgetControllerClassName)))
  , m_iId(++iCounter)
{
    QAndroidJniObject activity = QAndroidJniObject::callStaticObjectMethod("org/qtproject/qt5/android/QtNative", "activity", "()Landroid/app/Activity;");   //activity is valid
    javaController->callMethod<void>("create", "(Landroid/app/Activity;I)V", activity.object<jobject>(), m_iId);
}

CNativeButtonImplQml::~CNativeButtonImplQml()
{
    javaController->callMethod<void>("destroy", "()V");

}

void CNativeButtonImplQml::SetWidth(double dWidth)
{
    float pixelRatio = GetPixelsRatio();
    javaController->callMethod<void>("setWidth", "(I)V",
                                     (int) (dWidth* pixelRatio));
}

void CNativeButtonImplQml::SetHeight(double dHeight)
{
    float pixelRatio = GetPixelsRatio();
    javaController->callMethod<void>("setHeight", "(I)V",
                                                  (int) (dHeight* pixelRatio));

}

void CNativeButtonImplQml::SetX(double dX)
{
    float pixelRatio = GetPixelsRatio();
    javaController->callMethod<void>("setX", "(I)V",
                                                  (int) (dX* pixelRatio));
}
void CNativeButtonImplQml::SetY(double dY)
{
    float pixelRatio = GetPixelsRatio();
    javaController->callMethod<void>("setY", "(I)V",
                                                  (int) (dY* pixelRatio));
}
void CNativeButtonImplQml::SetVisibility(bool isVisible)
{
    javaController->callMethod<void>("setVisibility", "(Z)V", static_cast<jboolean>(isVisible));
}


void CNativeButtonImplQml::SetGroupId(int iId)
{
    javaController->callMethod<void>("setGroupId", "(I)V", static_cast<jint>(iId));
}

void CNativeButtonImplQml::SetGeometry(const QRect &geometry)
{
    float pixelRatio = GetPixelsRatio();
    javaController->callMethod<void>("setGeometry", "(IIII)V",
                                                  (int) (geometry.x()* pixelRatio),
                                                  (int) (geometry.y() * pixelRatio),
                                                  (int) (geometry.width() * pixelRatio),
                                                  (int) (geometry.height() * pixelRatio));

}

void CNativeButtonImplQml::startMoveTransaction(int iId)
{
    QAndroidJniObject::callStaticMethod<void>(CasinoGamesWidgetControllerClassName, "startMoveTransaction", "(I)V", static_cast<jint>(iId));
}

void CNativeButtonImplQml::commitMoveTransaction(int iId)
{
    QAndroidJniObject::callStaticMethod<void>(CasinoGamesWidgetControllerClassName, "commitMoveTransaction", "(I)V", static_cast<jint>(iId));
}

void CNativeButtonImplQml::MobeByY(double dDeltaY)
{
    float pixelRatio = GetPixelsRatio();
    javaController->callMethod<void>("moveByY", "(I)V",
                                                  (int) (dDeltaY* pixelRatio));

}

void CNativeButtonImplQml::MobeByX(double dDeltaX)
{
    float pixelRatio = GetPixelsRatio();
    javaController->callMethod<void>("moveByX", "(I)V",
                                                  (int) (dDeltaX* pixelRatio));

}
