#ifndef CCASINOGAMESWIDGETIMPLQML_H
#define CCASINOGAMESWIDGETIMPLQML_H

#include "NativeButtonQML.h"
#include "NativeViewQML.h"
#include "CasinoGamesWidgetDelegateQML.h"


class QAndroidJniObject;
class CNativeButtonImplQml:
        public CNativeButtonQml
{
    Q_OBJECT
public:
    friend class CNativeButtonsGroupQml;
    CNativeButtonImplQml(QQuickItem* parent = nullptr);
    virtual ~CNativeButtonImplQml();

protected:

    static void startMoveTransaction(int iId);
    static void commitMoveTransaction(int iId);

    void SetWidth(double dWidth) override;
    void SetHeight(double dHeight) override;
    void SetX(double dX) override;
    void SetY(double dX) override;
    void SetGroupId(int iId) override;
    void SetVisibility(bool isVisible) override;
    void SetGeometry(const QRect &geometry) override;

    void MobeByY(double dDeltaY);
    void MobeByX(double dDeltaX);

protected:
    const int m_iId;
#ifdef Q_OS_ANDROID
    std::unique_ptr<QAndroidJniObject> javaController;
#endif
};

#endif // CCASINOGAMESWIDGETIMPLQML_H
