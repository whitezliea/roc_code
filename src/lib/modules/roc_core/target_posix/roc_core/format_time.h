//! @file roc_core/target_posix/roc_core/fromat_time.h
//! @brief Retri
#ifndef ROC_CORE_FORMAT_TIME_H_
#define ROC_CORE_FORMAT_TIME_H_

#include "roc_core/stddefs.h"

namespace roc
{
    namespace core
    {
        // Retrieve and format current time
        // The time is printed in the fromat "13:10:05.123"
        // False if an error occured our buffer is too small
        // This function should not log anything because it is used in the loger implementation
        bool format_time(char *buf, size_t bufsz);
    } // namespace core
    
} // namespace roc


#endif