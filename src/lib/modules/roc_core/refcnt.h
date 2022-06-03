//! @file roc_core/refcnt.h
//! @brief  Base class for reference countable objects.

#ifndef ROC_CORE_REFCNT_H_
#define ROC_CORE_REFCNT_H_

#include "roc_core/atomic.h"
#include "roc_core/noncopyable.h"
#include "roc_core/panic.h"

namespace roc
{
    namespace core
    {
        // Base class for reference countable objects.
        //! @tparam T defines the derived class, which should provide free() method
        template<class T> class RefCnf : public Noncopyable<RefCnf<T> >
        {
        private :
            mutable Atomic counter_;
        
        public:
            RefCnf() 
                : counter_(0)
            {

            }

            ~RefCnf()
            {
                if (counter_ != 0)
                {
                    roc_panic("refcnt: reference counter is non-zero in destructor, counter=%d",
                                (int)counter_);
                }
            }

            // Get reference counter
            long getref() const
            {
                return counter_;
            }

            // Increment reference counter
            void incerf() const
            {
                if ( counter_ < 0)
                {
                    roc_panic("refcnt: attempting to call incref() on freed object");
                }
                ++counter_;
            }

            // Decrement reference counter
            // Calls free() if reference counter becomes zero.
            void decref() const
            {
                if (counter_ <= 0)
                {
                    roc_panic("refcnt: attmpting to call decref() on destoryed object");
                }

                if (--counter_ == 0)
                {
                    static_cast<T*>(const_cast<RefCnf*>(this))->destory();
                }
            }
            
        };
    } // namespace core
    
} // namespace roc


#endif