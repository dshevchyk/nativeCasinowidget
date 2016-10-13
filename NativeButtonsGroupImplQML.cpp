#include "NativeButtonsGroupImplQML.h"
#include "NativeButtonQML.h"


#include <jni.h>

#include <QtAndroidExtras/QAndroidJniObject>
#include <QtAndroidExtras/QAndroidJniEnvironment>
#include <QScreen>

static const char* NativeButtonsGroupControllerClassName = "com/playtech/qtshare/NativeButtonController";

CNativeButtonsGroupImplQml::CNativeButtonsGroupImplQml(QQuickItem* parent): CNativeButtonsGroupQml(parent)
{

}


CNativeButtonsGroupImplQml::~CNativeButtonsGroupImplQml()
{
}
