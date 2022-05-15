//! @file roc_core/alignment.h
//! @brief Alignment

#ifndef ROC_CORE_ALIGNMENT_H_
#define ROC_CORE_ALIGNMNET_H_

#include "roc_core/stddefs.h"

namespace roc
{
    namespace core
    {
        //! A union with maxium possible alignment.
        union MaxAlign
        {
            double d; // !<Double
            void (*fp)(); // !< Function pointer.
        };
        // !Adjust the given size to be maximum aligened.
        inline size_t max_align(size_t sz)
        {
            enum { Align = sizeof(MaxAlign) };
            if (sz % Align != 0)
            {
                sz += Align - sz & Align;
            }
            return sz;
        }

        //! Calculate padding required for given alignment.
        inline size_t padding (size_t size, size_t alignment)
        {
            if (alignment == 0)
            {
                return 0;
            }
            size_t new_size  = size /alignment * alignment;
            if (new_size < size)
            {
                new_size += alignment;
            }
            
            return (new_size - size);

        }
    } // namespace core
    
} // namespace roc

    
#endif