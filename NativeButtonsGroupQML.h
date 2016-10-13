#ifndef NATIVE_BUTTONS_GROUP_QML_H
#define NATIVE_BUTTONS_GROUP_QML_H

#include <QQuickItem>

#include "EventThreadInvoker.h"
#include <list>

class CNativeButtonQml;
class CNativeButtonsGroupQml : public CQtEventThreadInvoker<QQuickItem>
{
    Q_OBJECT
public:

    int GetGroupId() const;
protected:
    CNativeButtonsGroupQml(QQuickItem* parent = nullptr);
    virtual ~CNativeButtonsGroupQml();

    void SetupPositionEvents();

    void componentComplete();

    QPointF absoluteQMLPosition();
protected:
    const int m_iId;
    QPointF m_prevPos;
signals:
public slots:

    void slotOnVisibleChanged();
    void slotOnXChanged();
    void slotOnYChanged();
    void slotOnParentChanged();
};

#endif // NATIVE_BUTTONS_GROUP_QML_H
