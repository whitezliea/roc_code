//! @file roc_core/scoped_lock.h
//! @brief RAII mutex lock.

#ifndef ROC_CORE_SCOPED_LOCK_H_
#define ROC_CORE_SCOPED_LOCK_H_

#include "roc_core/noncopyable.h"

namespace roc
{
    namespace core
    {
        //! RAII mutex lock
        template <class Mutex> class ScopedLock : Noncopyable<>
        {
            //! Lock
            explicit ScopedLock(const Mutex& mutex): mutex_(mutex)
            {
                mutex_.lock();
            } 

            //! Unlock
            ~ScopedLock()
            {
                mutex_.unlock();
            }

            private:
                const Mutex& mutex_;
        };

    } // namespace core
    
} // namespace roc



#endif