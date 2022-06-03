//! @file roc_core/shared_ptr.h
//! @brief Shared ownership intrusive pointer

#ifndef ROC_CORE_SHARED_PTR_H_
#define ROC_CORE_SHARED_PTR_H_

#include "roc_core/ownership.h"
#include "roc_core/panic.h"
#include "roc_core/stddefs.h"

namespace roc
{
    namespace core
    {
        // Shared ownership intrusive pointer
        //! @tparam T defines pointee type. It may be const
        //! @tparam Ownership defines methods to increase and decrease the reference counter
        // embedded into object. If RefCntOwnership is used, T should inherit RefCnf
        template <class T, template <class TT> class Ownership = RefCntOwnership> class SharedPtr
        {
        private:
            void acquire_()
            {
                if (ptr_ != NULL)
                {
                    Ownership<T>::acquire(*ptr_);
                }
            }

            void release_()

            T* ptr_;
        public:
            SharedPtr(/* args */);
            ~SharedPtr();
        };
        
    } // namespace core
    
} // namespace roc


#endif