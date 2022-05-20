//! @file roc_core/demangle.h
//! @brief Symbol demangling

#ifndef ROC_CORE_DEMANGLE_H_
#define ROC_CORE_DEMANGLE_H_

#include "roc_core/stddefs.h"

namespace roc
{
    namespace core
    {
        //! Demangle symbol name
        //! This function is not signal-safe

        const char* demangle(const char* mangled , char* &demangle_buf, size_t& demangle_size);
        
    } // namespace core
    
} // namespace roc


#endif