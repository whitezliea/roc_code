//! @file roc_core/target_stdio/roc_core/panic.h
//! @brief Panic function

#ifndef ROC_CORE_PANIC_H_
#define ROC_CORE_PANIC_H_

#include "roc_core/attributes.h"
#include "roc_core/helpers.h"

#ifndef ROC_MODULE
#error "ROC_MODULE not defined"
#endif

//! Panic is condition is ture.
#define roc_panic_if(x)        \
    do {                        \
        if ((x)) {              \
             roc_panic("%s", #x); \
             }                      \
    }while(0)

//! Panic if condition is false
#define roc_panic_if_not(x) roc_panic_if(!(x))

//!Print error message and terminate program gracefully
#define roc_panic(...)  \
    ::roc::core::panic(ROC_STRINGIZE(ROC_MODULE), __FILE__, __LINE__, __VA_ARGS__)

namespace roc
{
    namespace core
    {
        //Print error message and terminate program gracefully
        void panic(const char* module, const char* file, int line, const char* fromat, ...) 
            ROC_ATTR_NORETURN ROC_ATTR_PRINTF(4, 5);
    } // namespace core

} // namespace roc


#endif // ROC_CORE_PANIC_H_