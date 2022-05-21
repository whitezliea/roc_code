//! @file roc_core/target_libuv/roc_core/cond.h
//! @brief Condition variable

#include <uv.h>

#include "roc_core/mutex.h"
#include "roc_core/panic.h"
#include "roc_core/noncopyable.h"

namespace roc
{
    namespace core
    {
        class Cond : public Noncopyable<>
        {
        private:
            mutable uv_cond_t cond_;
            uv_mutex_t& mutex_;
        public:
            //! Initialize
            Cond(const Mutex& mutex) : mutex_(mutex.mutex_)
            { 
                if (int err = uv_cond_init(&cond_))
                {
                    roc_panic("cond: uv_cond_init(): [%s] %s", uv_err_name(err),
                            uv_strerror(err));
                }

            }

            ~Cond()
            {
                uv_cond_destroy(&cond_);
            }

            //! Wait
            void wait() const{
                uv_cond_wait(&cond_, &mutex_);
            }

            //! Wake up all pending waits
            void broadcast() const{
                uv_cond_broadcast(&cond_);
            }
        };

    } // namespace core
    
} // namespace roc
