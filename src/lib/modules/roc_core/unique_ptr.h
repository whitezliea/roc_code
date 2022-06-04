//! @file roc_core/unique_ptr.h
//! @brief Unique ownership pointer

#ifndef ROC_CORE_UNIQUE_PTR_H_
#define ROC_CORE_UNIQUE_PTR_H_

#include "roc_core/iallocator.h"
#include "roc_core/noncopyable.h"
#include "roc_core/panic.h"
#include "roc_core/stddefs.h"

namespace roc
{
    namespace core
    {
        // Unique ownership pointer
        //! @tparam T defines pointer type. It may be const
        //! @tparam Destory is used to destory the object
        template<class T, class Destoryer = IAllocator> class UniquePtr : public Noncopyable<>
        {
        private:
            void destory_()
            {
                if (ptr_)
                {
                    roc_panic_if ( destory_== NULL);
                    destory_->destory(*ptr_);
                }
            }

            T* ptr_;
            Destoryer* destoryer_;
        public:
            // Initialized null pointer
            UniquePtr()
            : ptr_(NULL)
            ,destoryer_()
            {

            }

            // Initialize from a raw pointer
            UniquePtr(T* ptr, Destoryer& destoryer)
            : ptr_(ptr)
            , destoryer_(& destoryer)
            {

            }

            // Destory object;
            ~UniquePtr()
            {
                destory_();
            }

            // Reset pointer to a null
            void reset()
            {
                destory_();
                ptr_ = NULL;
                destoryer_ = NULL;
            }

            // Reset pointer to a new value
            void reset(T* new_ptr, Destoryer& new_destory)
            {
                if ( new_ptr != ptr)
                {
                    destory_();
                    ptr_ = new_ptr;
                    destoryer_ = new_destory;
                }
            }

            //! Get underlying pointer and pass ownership to the caller.
            T* release() 
            {
                T* ret = ptr_;
                if (ret == NULL)
                {
                    roc_panic("uniqueptr: attempting to release a null pointer");
                }
                ptr_ = NULL;
                destroyer_ = NULL;
                return ret;
            }

            //! Get underlying pointer.
            T* get() const 
            {
                return ptr_;
            }

            //! Get underlying pointer.
            T* operator->() const 
            {
                return ptr_;
            }

            //! Get underlying reference.
            T& operator*() const 
            {
                if (ptr_ == NULL) 
                {
                    roc_panic("unique ptr: attempting to dereference a null pointer");
                }
                return *ptr_;
            }

            //! Convert to bool.
            operator const struct unspecified_bool*() const 
            {
                return (unspecified_bool*)ptr_;
            }

        };
        

        
    } // namespace core
    
} // namespace roc


#endif