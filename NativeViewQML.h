#ifndef NATIVEVIEWQML_H
#define NATIVEVIEWQML_H

#include <QSGNode>


#include <mutex>
#include <memory>
#include "AutoLock.h"
class CNativeViewQML
{
public:

    typedef std::function<void(void)> CallbackType;
    typedef std::shared_ptr<CallbackType> CallbackSharedPtr;
    typedef std::weak_ptr<CallbackType> CallbackWeakPtr;
    static void PrepareAllBeforeAnimation(QObject* obj, CNativeViewQML* excludedView = nullptr, CallbackSharedPtr pStickToParentCallback = nullptr);
    static void UnprepareAllAfterAnimation(QObject* obj, CallbackSharedPtr pUnStickToParentCallback = nullptr);
    static bool StickToPopupsIfNeeded(CNativeViewQML* view);

    bool UnstickAllFromPopup(CNativeViewQML* view);
    static void OnNativeViewDeleted(CNativeViewQML* obj);
    static void Clean(CNativeViewQML* obj);
    static void ForceUnstick(CNativeViewQML* obj);
    static int GetStickedCount(CNativeViewQML* obj);
    static bool IsSingleSticked(CNativeViewQML* obj);
    virtual void beforeShow();
    virtual void beforeHide();

    virtual bool isPopupElement() { return false; }
    CNativeViewQML();
    virtual ~CNativeViewQML();
protected:

    virtual void StickToParent(CNativeViewQML::CallbackSharedPtr  pStickToParentCallback = nullptr)
    {

        CAutoRecursiveLock l( &m_lock );
        m_pStickToParentCallback = CNativeViewQML::CallbackWeakPtr (pStickToParentCallback);
    }
    virtual void UnstickFromParent(CNativeViewQML::CallbackSharedPtr  pUnStickToParentCallback = nullptr)
    {
        CAutoRecursiveLock l( &m_lock );
        m_pUnStickToParentCallback = CNativeViewQML::CallbackWeakPtr (pUnStickToParentCallback);
    }
    virtual QSGNode* GetDrawingCasheImage() {return NULL;}

    void UpdateDrawingCacheImage();
    void RemoveDrawingCacheImage();
    virtual bool IsVisible() { return false; }
protected:
    CallbackWeakPtr m_pStickToParentCallback;
    CallbackWeakPtr m_pUnStickToParentCallback;
    bool m_bIsStickedToParent;
    bool m_bNeedToStickToParent;
    std::recursive_mutex m_lock;
};
#endif // NATIVEVIEWQML_H
