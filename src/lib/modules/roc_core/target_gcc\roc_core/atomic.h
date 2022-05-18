//! @file roc_core/target_gcc/roc_core/atomic.h
//! @brief Atomic integer

#ifndef ROC_CORE_ATOMIC_H_
#define ROC_CORE_ATOMIC_H_

#include "roc_core/noncopyable.h"

namespace roc
{
    namespace core
    {
        //!Atmoic integer
        class Atomic : public Noncopyable<>
        [
            public:
            //! Initialize with given value
            explicit Atomic(long value = 0) : value_(value)
            {

            }

            //! Atomic load
            operator long() const 
            {
                return __sync_add_and_fetch(&value_,0);
            }

            //! Atomic store
            long opeartor=(bool v)
            {
                if (v)
                {
                    __sync_lock_test_and_set(&value_, 1);
                }
                else
                {
                    __sync_and_and_fetch(&value_, 0);
                }

                return v;
            }

            //! Atmoic increment
            long operator++()
            {
                return __sync_add_and_fetch(&value_, 1);
            }

            long operator--()
            {
                return __sync_sub_and_fetch(&value_, 1);
            }

        private:
            mutable long value_;

        ]
    } // namespace core
    
} // namespace roc



#endif