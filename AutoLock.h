#ifndef __POKER_AUTOLOCK_HEADER__25_01_2014__11_33__
#define __POKER_AUTOLOCK_HEADER__25_01_2014__11_33__

#include <mutex>

class CAutoLock {
public:
    CAutoLock(std::mutex *m)
        :m_Mutex(m)
    {
        m_Mutex->lock();
    }
    ~CAutoLock()
    {
        m_Mutex->unlock();
    }

    std::mutex *m_Mutex;
};

class CAutoRecursiveLock {
public:
    CAutoRecursiveLock(std::recursive_mutex *m)
        :m_Mutex(m)
    {
        m_Mutex->lock();
    }
    ~CAutoRecursiveLock()
    {
        m_Mutex->unlock();
    }

    std::recursive_mutex *m_Mutex;
};



#endif /* __POKER_AUTOLOCK_HEADER__25_01_2014__11_33__ */
