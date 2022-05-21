//! @file roc_core/target_posix/roc_core/colors.h
//! @brief Colorrization functions

#ifndef ROC_CORE_COLORS_H_
#define ROC_CORE_COLORS_H_

#include "roc_core/log.h"
#include "roc_core/stddefs.h"

namespace roc
{
    namespace core
    {
        //Check if current stderr is connected to a tty
        bool colors_available();

        //Fill colored str into buf according to the dog level.
        bool format_colored(LogLevel, const char* str, char* buf, size_t bufsz); 
    } // namespace core
    
} // namespace roc

#endif