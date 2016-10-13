#ifndef CEVENTTHREADINVOKER_H
#define CEVENTTHREADINVOKER_H

#include <QEvent>
#include <QCoreApplication>
#include <QObject>
#include <QThread>
#include <functional>
#include <QApplication>


template <class BaseObject>
class CQtEventThreadInvoker : public BaseObject
{
public:
    typedef std::function<void(void)> ThreadCallback;

private:
    class CQtThreadCallbackEvent: public QEvent
    {
    public:
        explicit CQtThreadCallbackEvent(const ThreadCallback &callback)
            : QEvent(QEvent::None), m_callback(callback)
        {

        }

        void Call()
        {
            if (m_callback) {
                m_callback();
            }
            m_callback = [](){};
        }

    private:
        ThreadCallback m_callback;
    };

public:
    explicit CQtEventThreadInvoker(BaseObject *pParent = nullptr)
        : BaseObject(pParent)
    {
        BaseObject::moveToThread( QApplication::instance()->thread() );
    }

    virtual ~CQtEventThreadInvoker()
    {

    }

    void Invoke(const ThreadCallback &threadCallback)
    {
        QCoreApplication::postEvent(this, new CQtThreadCallbackEvent(threadCallback));
    }

    bool event(QEvent *pEvent) override
    {
        bool bResult = false;

        if (dynamic_cast<CQtThreadCallbackEvent*>(pEvent)) {
            (static_cast<CQtThreadCallbackEvent*>(pEvent))->Call();
            bResult = true;
        }

        if (!bResult) {
            bResult = BaseObject::event(pEvent);
        }

        return bResult;
    }
};

#endif // CEVENTTHREADINVOKER_H
