//! @file roc_core/target_posix/roc_core/exit.h
//! @brief Exit function

#ifndef ROC_CORE_EXIT_H_
#define ROC_CORE_EXIT_H_

#include "roc_core/attributes.h"

namespace roc
{
    namespace core
    {
        // Terminate process immediately without calling destructors
        void fast_exit(int code) ROC_ATTR_NORETURN;
    } // namespace core
    
} // namespace roc


#endif