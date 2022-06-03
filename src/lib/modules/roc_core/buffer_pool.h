//! @file roc_core/buffer_pool.h
//! @brief Buffer pool

#ifndef ROC_CORE_BUFFER_H_
#define ROC_CORE_BUFFER_H_

#include "roc_core/pool.h"

namespace roc
{
    namespace core
    {
        template <class T>  class Buffer;
        
        // Buffer pool
        template <class T> class BufferPool : public Pool<Buffer<T>>
        {
        private:
            size_t buff_size_;
        public:
            // Initialization
            BufferPool(IAllocator& allocator, size_t buff_size, bool poison)
                : Pool<Buffer<T> >(allocator, sizeof(Buffer<T>) + sizeof(T) * buff_size, poison)
                , buff_size_(buff_size)
                {

                }
            
            // Get buffer size (number of element in buffer).
            size_t buffer_size() const
            {
                return buff_size_;
            }
            
        };
        
        
    } // namespace core
    
} // namespace roc


#endif