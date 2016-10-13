#include "NativeViewQML.h"
#include <set>
#include <map>
#include <QThread>
typedef std::set<CNativeViewQML*> CNativeViews;
static CNativeViews setNativeViews;

typedef std::map<QObject*, CNativeViews> StickedViews;
static StickedViews mapStickedViews;

static std::recursive_mutex staticLock;
CNativeViewQML::CNativeViewQML() : m_bIsStickedToParent(false), m_bNeedToStickToParent(false)
{
    staticLock.lock();
    setNativeViews.insert(this);
    staticLock.unlock();
    CAutoRecursiveLock l( &m_lock );
}

CNativeViewQML::~CNativeViewQML()
{
    beforeHide();
}

void CNativeViewQML::beforeShow()
{
    staticLock.lock();
    setNativeViews.insert(this);
    staticLock.unlock();
}

void CNativeViewQML::beforeHide()
{
    CAutoRecursiveLock l( &m_lock );
    RemoveDrawingCacheImage();
    m_pStickToParentCallback.reset();
    m_pUnStickToParentCallback.reset();
    Clean(this);
}

void CNativeViewQML::PrepareAllBeforeAnimation(QObject* obj, CNativeViewQML* excludedView, CallbackSharedPtr pStickToParentCallback)
{

    staticLock.lock();
    for (CNativeViewQML* view : setNativeViews) {
        if(excludedView && excludedView == view)
            continue;
        if (view ) {

            std::pair< QObject*, CNativeViews > pairCurrentStickedViews;
            pairCurrentStickedViews.first = obj;
            if(!view->m_bIsStickedToParent && view->IsVisible()) {

                staticLock.unlock();
                view->StickToParent(pStickToParentCallback);
                staticLock.lock();
                pStickToParentCallback = nullptr;//we need it to be called only once, not for every native view
            }
            else {

                staticLock.unlock();
                view->StickToParent(nullptr);
                staticLock.lock();
            }
            pairCurrentStickedViews.second.insert(view);
            if(mapStickedViews.find(pairCurrentStickedViews.first) != mapStickedViews.end()) {
                auto& container = mapStickedViews.find(pairCurrentStickedViews.first)->second;
                if(container.find(view) == container.end()){
                    mapStickedViews.find(pairCurrentStickedViews.first)->second.insert(view);
                }
            }
            else if (!pairCurrentStickedViews.second.empty()) {
                mapStickedViews.insert(pairCurrentStickedViews);
            }
        }
    }
    staticLock.unlock();
    if(pStickToParentCallback)//if there is no native view, execute callback immediately
        (*pStickToParentCallback)();


}

void CNativeViewQML::OnNativeViewDeleted(CNativeViewQML* obj)
{
    Clean(obj);
}

int CNativeViewQML::GetStickedCount(CNativeViewQML* obj)
{
    int stickedCounter = 0;

    staticLock.lock();
    for(const auto& mapStickedView: mapStickedViews)
    {
        if(mapStickedView.second.find(obj) != mapStickedView.second.end())
        {
            stickedCounter++;
        }
    }
    staticLock.unlock();
    return stickedCounter;
}

bool CNativeViewQML::IsSingleSticked(CNativeViewQML* obj)
{
    return GetStickedCount(obj) <= 1;
}

void CNativeViewQML::ForceUnstick(CNativeViewQML* obj)
{
    if(dynamic_cast<QObject*>(obj))
    {

        staticLock.lock();
        StickedViews::const_iterator itViews = mapStickedViews.find(dynamic_cast<QObject*>(obj));
        if(itViews != mapStickedViews.end())
        {
            for( auto* stickedView: itViews->second)
            {
                if (IsSingleSticked(stickedView))
                {

                    staticLock.unlock();
                    stickedView->UnstickFromParent(nullptr);

                    staticLock.lock();
                }
            }
            mapStickedViews.erase(itViews);
        }
        //if (IsSingleSticked(obj)) {

            staticLock.unlock();
            obj->UnstickFromParent(nullptr);
            staticLock.lock();
        //}
        for(auto& stickedViewPair: mapStickedViews) {
            stickedViewPair.second.erase(obj);
        }
        staticLock.unlock();
    }
}

void CNativeViewQML::Clean(CNativeViewQML* obj)
{
    staticLock.lock();
    setNativeViews.erase(obj);
    staticLock.unlock();
    ForceUnstick(obj);

}

bool CNativeViewQML::UnstickAllFromPopup(CNativeViewQML* view)
{
    if(!view || !view->isPopupElement() || !dynamic_cast<QObject*>(view))
    {
        return false;
    }

    staticLock.lock();
    QObject* objectView = dynamic_cast<QObject*>(view);
    auto iter = mapStickedViews.find(objectView);
    if(iter != mapStickedViews.end())
    {
        for(auto& viewToUnstick: iter->second){
            if(CNativeViewQML::IsSingleSticked(viewToUnstick))
            {
                staticLock.unlock();
                viewToUnstick->UnstickFromParent(nullptr);
                staticLock.lock();
            }
        }
        iter->second.clear();
    }
    staticLock.unlock();
    return true;
}

bool CNativeViewQML::StickToPopupsIfNeeded(CNativeViewQML* view)
{
    bool res = false;

    staticLock.lock();
    for(auto& nativeView: setNativeViews) {
        if(nativeView->isPopupElement() && dynamic_cast<QObject*>(nativeView) && nativeView != view) {
            std::pair< QObject*, CNativeViews > pairCurrentStickedViews;
            pairCurrentStickedViews.first = dynamic_cast<QObject*>(nativeView);
            pairCurrentStickedViews.second.insert(view);

            staticLock.unlock();
            view->StickToParent(nullptr);

            staticLock.lock();
            if(mapStickedViews.find(pairCurrentStickedViews.first) != mapStickedViews.end()) {
                auto& container = mapStickedViews.find(pairCurrentStickedViews.first)->second;
                if(container.find(view) == container.end()){
                    mapStickedViews.find(pairCurrentStickedViews.first)->second.insert(view);
                    res = true;
                }
            }
            else if (!pairCurrentStickedViews.second.empty()) {
                mapStickedViews.insert(pairCurrentStickedViews);
                res = true;
            }
        }
    }

    staticLock.unlock();
    return res;
}

void CNativeViewQML::UnprepareAllAfterAnimation(QObject* obj, CallbackSharedPtr pUnStickToParentCallback)
{


    staticLock.lock();
    StickedViews::const_iterator itViews = mapStickedViews.find(obj);
    if (itViews != mapStickedViews.end()) {
        for (CNativeViewQML* view : itViews->second) {
            bool isSingleStick = IsSingleSticked(view);
            if (isSingleStick) {

                staticLock.unlock();
                view->UnstickFromParent(pUnStickToParentCallback);

                staticLock.lock();
                pUnStickToParentCallback = nullptr;//we need it to be called only once, not for every native view
            }
        }

        mapStickedViews.erase(itViews);
    }

    for(auto& nativeView: setNativeViews) {
        if(GetStickedCount(nativeView) == 0)
        {
            nativeView->UnstickFromParent(nullptr);
        }
    }
    staticLock.unlock();
}


void CNativeViewQML::UpdateDrawingCacheImage()
{
//    RemoveDrawingCacheImage();

//    SNativeViewImpl* pNativeViewImpl = GetNativeViewIml();
//    Q* pImagePlaceholder = GetDrawingCasheImagePlaceholder();
//    if (pNativeViewImpl && pImagePlaceholder) {
//        QPixmapExt* pPixmap = pNativeViewImpl->GetDrawingCache();
//        if (pPixmap) {
//            pPixmap->setDevicePixelRatio(qApp->devicePixelRatio());
//            pImagePlaceholder->setPixmap(*pPixmap);
//            pImagePlaceholder->setVisible(true);

//            delete pPixmap;
//        }
//    }

//    m_bIsStickedToParent = true;
}

void CNativeViewQML::RemoveDrawingCacheImage()
{
//    m_bIsStickedToParent = false;

//    QLabel* pImagePlaceholder = GetDrawingCasheImagePlaceholder();
//    if (pImagePlaceholder) {
//        pImagePlaceholder->setVisible(false);
//    }
}

