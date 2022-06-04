//! @file roc_core/heap_allocator.h
//! @brief Heap allocator implementation

#ifndef ROC_CORE_HEAP_ALLOCATOR_H_
#define ROC_CORE_HEAP_ALLOCATOR_H_

#include "roc_core/atomic.h"
#include "roc_core/iallocator.h"
#include "roc_core/noncopyable.h"

namespace roc
{
    namespace core
    {
        // Heap allocator implementaion
        // Uses global opeartor new[] and operator delete[]
        // The memory is always maximum aligend. Thread-safe
        class HeapAllocator : public IAllocator, public NonCopyable<>
        {
        private:
            Atomic num_allocations_;
        public:
            ~HeapAllocator();

            // Allocate memory
            virtual void* allocate(size_t size);

            // Deallocate previously allocated memory
            virtual void deallocate(void*);

            // Get number of allocated blocks
            size_t num_allocations() const;
        };
        
        

    } // namespace core
    
} // namespace roc



#endif
