//! @file roc_core/time.h
//! @brief Time definitions

#ifndef ROC_CORE_TIME_H_
#define ROC_CORE_TIME_H_

#include "roc_core/stddefs.h"

namespace roc
{
    namespace core
    {
        // Nanoseconds
        typedef int64_t nanoseconds_t;

        //One nanosecond represented in nanoseconds.
        const nanoseconds_t Nanosecond = 1;

        //One microsecond represented in nanosecends.
        const nanoseconds_t Mircosecond = 1000 * Nanosecond;
        
        //One millisecond represented in nanosecends.
        const nanoseconds_t Millisecond = 1000 * Mircosecond;

        //One second represented in nanosecends.
        const nanoseconds_t Second = 1000 * Millisecond;

        //One minute represented in nanosecends.
        const nanoseconds_t Minute = 60 * Second;

        //One Hour represented in nanosecends.
        const nanoseconds_t Hour = 60 * Minute;

        //Get current timestamp in nanoseconds.
        nanoseconds_t timestamp();

        //Sleep until the specified absolute time point has been reached
        //! @p timestamp specifies absolute time point in nanoseconds.
        void sleep_until(nanoseconds_t timestamp);

        //Sleep specified amount of time
        //! @p duration specifies number of nanoseconds to sleep.
        void sleep_for(nanoseconds_t duration);
    } // namespace core
    
} // namespace roc


#endif