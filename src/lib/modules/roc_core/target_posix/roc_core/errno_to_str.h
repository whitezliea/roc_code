//! @file roc_core/target_posix/roc_core/errno_to_str.h
//! @brief Convert errno to string

#ifndef ROC_CORE_ERRNO_TO_STR_H_
#define ROC_CORE_ERRNO_TO_STR_H_

#include "roc_core/noncopyable.h"

namespace roc
{
    namespace core
    {
        //! Convert errno to string
        class errno_to_str : public Noncopyable<>
        {
        private:
            char buffer_[96];
        public:
            //! Construct from errno
            errno_to_str();
            
            //! Construct from custom error code
            explicit errno_to_str(int err);

            const char* c_str() const
            {
                return buffer_;
            }
        };
        
        
    } // namespace core
    
} // namespace roc


#endif