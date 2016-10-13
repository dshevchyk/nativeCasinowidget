#include "NativeButtonsGroupQML.h"
#include "NativeButtonImplQML.h"

static int ibuttonsGroupId = 0;

CNativeButtonsGroupQml::CNativeButtonsGroupQml(QQuickItem* parent):
    CQtEventThreadInvoker<QQuickItem>(parent)
  , m_iId(++ibuttonsGroupId)
{
}

int CNativeButtonsGroupQml::GetGroupId() const
{
    return m_iId;
}

CNativeButtonsGroupQml::~CNativeButtonsGroupQml()
{
}

void CNativeButtonsGroupQml::componentComplete()
{
    QQuickItem::componentComplete();
    m_prevPos = absoluteQMLPosition();
    connect(this, SIGNAL(visibleChanged()), this, SLOT(slotOnVisibleChanged()));
    connect(this, SIGNAL(parentChanged()), this, SLOT(slotOnParentChanged()));
    SetupPositionEvents();
}

void CNativeButtonsGroupQml::slotOnParentChanged()
{
    SetupPositionEvents();
}

void CNativeButtonsGroupQml::SetupPositionEvents()
{
    QObject::disconnect(this, SLOT(slotOnXChanged()));
    QObject::disconnect(this, SLOT(slotOnYChanged()));

    if(dynamic_cast<CNativeButtonsGroupQml*>(parentItem()))
    {
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

void CNativeButtonsGroupQml::slotOnVisibleChanged()
{
}
void CNativeButtonsGroupQml::slotOnXChanged()
{
    CNativeButtonImplQml::startMoveTransaction(m_iId);

    double deltaX = absoluteQMLPosition().x() - m_prevPos.x();
    for(auto item: childItems())
    {
        CNativeButtonImplQml* buttonItem = dynamic_cast<CNativeButtonImplQml*>(item);
        if(buttonItem)
        {
            buttonItem->MobeByX(deltaX);
        }
    }
    CNativeButtonImplQml::commitMoveTransaction(m_iId);

    m_prevPos = absoluteQMLPosition();
}

QPointF CNativeButtonsGroupQml::absoluteQMLPosition() {
    QPointF p(0, 0);
    QQuickItem* pItem = this;
    while (pItem != NULL) { // absolute position relative to rootItem
        p += pItem->position();
        pItem = pItem->parentItem();
    }
    return p;
}
void CNativeButtonsGroupQml::slotOnYChanged()
{
    CNativeButtonImplQml::startMoveTransaction(m_iId );
    double deltaY = absoluteQMLPosition().y() - m_prevPos.y();
    for(auto item: childItems())
    {
        CNativeButtonImplQml* buttonItem = dynamic_cast<CNativeButtonImplQml*>(item);
        if(buttonItem)
        {
            buttonItem->MobeByY(deltaY);
        }
    }
    CNativeButtonImplQml::commitMoveTransaction(m_iId);

    m_prevPos = absoluteQMLPosition();
}
