//! @file roc_core/pool.h
//! @brief Pool

#ifndef ROC_CORE_POOL_H_
#define ROC_CORE_POOL_H_

#include "roc_core/alignment.h"
#include "roc_core/iallocator.h"
#include "roc_core/log.h"
#include "roc_core/mutex.h"
#include "roc_core/noncopyable.h"
#include "roc_core/panic.h"
#include "roc_core/stddefs.h"
#include "roc_core/list.h"

namespace roc
{
    namespace core
    {
        /**
         * Pool
         * ! @tparam T defines object type
         * Allocates chunks from given allocator containing a fixed number of fixed
         * sized objects. Maintains a list of free objects
         * The memory is always maximum aligend. Thread-safe.
        */
       template <class T> class Pool : public Noncopyable<>
       {
           /**
            * Initialization
           */
          Pool(IAllocator& allocator, size_t object_size, bool poison)
            :allocator_(allocator)
            ,
       };
    } // namespace core
    
} // namespace roc


#endif