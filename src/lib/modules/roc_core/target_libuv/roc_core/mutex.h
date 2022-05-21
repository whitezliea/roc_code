//! @file roc_core/target_libuv/roc_core/mutex.h
//! @brief Mutex.

#ifndef ROC_CORE_MUTEX_H_
#define ROC_CORE_MUTEX_H_

#include <uv.h>

#include "roc_core/noncopyable.h"
#include "roc_core/panic.h"
#include "roc_core/scoped_lock.h"

namespace roc
{
    namespace core
    {
        class Cond;
        
        //! Mutex
        class Mutex : public Noncopyable<>
        {
        private:
            friend class Cond;

            mutable uv_mutex_t mutex_;
        public:

        //! RAII lock.
            typedef ScopedLock<Mutex> Lock;
            Mutex()
            {
                if (int err = uv_mutex_init(&mutex_))
                {
                    roc_panic("mutex: uv_mutex_init(): [%s] %s", uv_err_name(err), uv_strerror(err));
                }
            }

            ~Mutex()
            {
                uv_mutex_destroy(&mutex_);
            }

            //! Lock mutex
            void lock() const
            {
                uv_mutex_lock(&mutex_);
            }

            //! Unlock mutex
            void unlock() const
            {
                uv_mutex_unlock(&mutex_);
            }
        };
        

    } // namespace core
    
} // namespace roc



#endif
