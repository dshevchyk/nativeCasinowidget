#include "NativeButtonQML.h"
#include "NativeButtonsGroupImplQML.h"

CNativeButtonQml::CNativeButtonQml(QQuickItem* parent):
    CQtEventThreadInvoker<QQuickItem>(parent)
  , m_pGroup(nullptr)
  , m_dPrevX(-1)
  , m_dPrevY(-1)
{

}


CNativeButtonQml::~CNativeButtonQml()
{
}

void CNativeButtonQml::onSomeButtonClicked(const std::string &sParam)
{

}
QPointF CNativeButtonQml::absoluteQMLPosition() {
    QPointF p(0, 0);
    QQuickItem* pItem = this;
    while (pItem != NULL) { // absolute position relative to rootItem
        p += pItem->position();
        pItem = pItem->parentItem();
    }
    return p;
}

void CNativeButtonQml::componentComplete()
{
    QQuickItem::componentComplete();

    connect(this, SIGNAL(visibleChanged()), this, SLOT(slotOnVisibleChanged()));
    connect(this, SIGNAL(parentChanged()), this, SLOT(slotOnParentChanged()));
    SetupPositionEvents();

    QRectF qmlRect(absoluteQMLPosition(), QSizeF(width(), height()));
    SetGeometry(QRect(qmlRect.x(), qmlRect.y(), qmlRect.width(), qmlRect.height()));
    SetVisibility(QQuickItem::isVisible());
}

void CNativeButtonQml::slotOnParentChanged()
{
    SetupPositionEvents();
}

void CNativeButtonQml::slotOnVisibleChanged()
{
    SetVisibility(QQuickItem::isVisible());
}

void CNativeButtonQml::slotOnWidthChanged()
{
    SetWidth(QQuickItem::width());
}

void CNativeButtonQml::slotOnHeightChanged()
{
    SetHeight(QQuickItem::height());
}

void CNativeButtonQml::slotOnXChanged()
{
//    if(m_pGroup)
//    {
//        double dDelta = absoluteQMLPosition().x() - m_dPrevX;
//        if(std::fabs(dDelta) >= 1.0)
//        {
//           m_pGroup->MoveByX(dDelta);
//        }
//        return;
//    }
    SetX(absoluteQMLPosition().x());
//    m_dPrevX = absoluteQMLPosition().x();
}

void CNativeButtonQml::slotOnYChanged()
{
//    if(m_pGroup)
//    {
//        double dDelta = absoluteQMLPosition().y() - m_dPrevY;
//        if(std::fabs(absoluteQMLPosition().y() - m_dPrevY) >= 1.0)
//        {
//            m_pGroup->MoveByY(dDelta);
//        }
//        return;
//    }
    SetY(absoluteQMLPosition().y());
//    m_dPrevY = absoluteQMLPosition().y();
}

CNativeButtonsGroupImplQml* CNativeButtonQml::GetGroup() const
{
    return m_pGroup;
}

void CNativeButtonQml::SetupPositionEvents()
{
    QObject::disconnect(this, SLOT(slotOnXChanged()));
    QObject::disconnect(this, SLOT(slotOnYChanged()));

    if(dynamic_cast<CNativeButtonsGroupImplQml*>(parentItem()))
    {
        SetGroup(dynamic_cast<CNativeButtonsGroupImplQml*>(parentItem()));
        return;
    }
    QQuickItem* item = this;
    while(item != nullptr)
    {
        connect(item, SIGNAL(xChanged()), this, SLOT(slotOnXChanged()));
        connect(item, SIGNAL(yChanged()), this, SLOT(slotOnYChanged()));
        item = item->parentItem();
    }
}

void CNativeButtonQml::SetGroup(CNativeButtonsGroupImplQml* pGroup)
{
    SetGroupId(-1);
    m_pGroup = pGroup;
    if(m_pGroup)
    {
        m_pGroup = pGroup;
        SetGroupId(m_pGroup->GetGroupId());
    }
    emit signalGroupChanged();
}

