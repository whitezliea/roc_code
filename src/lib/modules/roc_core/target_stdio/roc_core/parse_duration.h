//! @file roc_core/target_stdio/roc_core/parse_duration
//! @brief Parse duration

#ifndef ROC_CORE_PARSE_DURATION_H_
#define ROC_CORE_PARSE_DURATION_H_

#include "roc_core/time.h"

namespace roc
{
    namespace core
    {
        // Parse duration from string
        // This input string should be in one of the following forms:
        // - "<number>ns"
        // - "<number>us"
        // - "<number>ms"
        // - "<number>s"
        // - "<number>m"
        // - "<number>h"
        //! @return

        // false if string can't be
        bool parse_duration(const char* string, nanoseconds_t& result);
    } // namespace core
    
} // namespace roc


#endif