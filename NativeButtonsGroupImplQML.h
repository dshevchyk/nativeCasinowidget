#ifndef NATIVE_BUTTONS_GROUP__IMPL_QML_H
#define NATIVE_BUTTONS_GROUP__IMPL_QML_H

#include <QQuickItem>

#include "NativeButtonsGroupQML.h"
class CNativeButtonsGroupImplQml : public CNativeButtonsGroupQml
{
    Q_OBJECT
protected:
    friend class CNativeButtonQml;
    CNativeButtonsGroupImplQml(QQuickItem* parent = nullptr);
    ~CNativeButtonsGroupImplQml();
signals:
public slots:

};

#endif // NATIVE_BUTTONS_GROUP_QML_H
