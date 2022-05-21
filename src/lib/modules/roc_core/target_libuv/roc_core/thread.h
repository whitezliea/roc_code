//! @file roc_core/target_libuv/roc_core/thread.h
//! @brief Thread

#ifndef ROC_CORE_THREAD_H_
#define ROC_CORE_THREAD_H_

#include <uv.h>

#include "roc_core/atomic.h"
#include "roc_core/mutex.h"
#include "roc_core/noncopyable.h"

namespace roc
{
     namespace core
     {
         class Thread : public Noncopyable<Thread>
         {

         public:
             //! Check if thread was started and can be joined
             //! ture if start()w was called and join() was not called yet.
             bool joinable() const;

             //! Start thread.
             //! Executes run int new thread.
             bool start();

             //! Join thread.
             //! Block until run() returns nad thread terminates
             void join();
             
         private:
             static void thread_runner_(void* ptr);

             uv_thread_t thread_;

             int started_;
             Atomic joinable_;

             Mutex mutex_;
         protected:
             Thread();
             virtual ~Thread();
            
            //! Method to be executed in thread
             virtual void run() = 0;
         };
        
         
     } // namespace core
     
} // namespace roc


#endif