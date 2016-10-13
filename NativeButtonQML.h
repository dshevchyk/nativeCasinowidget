#ifndef CASINOGAMESWIDGETQML_H
#define CASINOGAMESWIDGETQML_H

#include <QQuickItem>

#include "EventThreadInvoker.h"

class CNativeButtonsGroupImplQml;
class CNativeButtonQml : public CQtEventThreadInvoker<QQuickItem>
{
    Q_OBJECT
protected:
    friend class CNativeButtonsGroupQml;
    CNativeButtonQml(QQuickItem* parent);
    virtual ~CNativeButtonQml();

    Q_PROPERTY(CNativeButtonsGroupImplQml* group   READ GetGroup      WRITE SetGroup     NOTIFY signalGroupChanged)

    virtual void onSomeButtonClicked(const std::string &sParam);

    virtual void componentComplete() override;
    virtual void SetGeometry(const QRect &geometry) = 0;
    virtual void SetWidth(double dWidth) = 0;
    virtual void SetHeight(double dHeight) = 0;
    virtual void SetX(double dX) = 0;
    virtual void SetY(double dX) = 0;
    virtual void SetGroupId(int iId) = 0;
    virtual void SetVisibility(bool isVisible) = 0;
    QPointF absoluteQMLPosition();

    CNativeButtonsGroupImplQml* GetGroup() const;
    void SetGroup(CNativeButtonsGroupImplQml* pGroup);
    void SetupPositionEvents();


signals:
    void nativeClicked();
    void signalGroupChanged();

public slots:
    void slotOnVisibleChanged();
    void slotOnWidthChanged();
    void slotOnHeightChanged();
    void slotOnXChanged();
    void slotOnYChanged();
    void slotOnParentChanged();
private:
    CNativeButtonsGroupImplQml* m_pGroup;

    double m_dPrevX;
    double m_dPrevY;
};

#endif // CASINOGAMESWIDGETQML_H
