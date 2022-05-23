//! @file roc_core/target_posix/roc_core/random.h
//! @brief Helpers to work with random number

#ifndef ROC_CORE_RANDOM_H_
#define ROC_CORE_RANDOM_H_

#include "roc_core/stddefs.h"

namespace roc
{
    namespace core
    {
        //Get random integer
        //! @returns random value in range [0: upper).
        unsigned random(unsigned upper);

        //Get random integer
        //! @returns random value in range [from; to].
        unsigned random(unsigned from, unsigned to);
    } // namespace core
    
} // namespace roc


#endif