#include "roc_core/heap_allocator.h"

namespace roc
{
    namespace core
    {
        HeapAllocator::~HeapAllocator()
        {
            if (num_allocations_ != 0)
            {
                roc_panic("heap allocator: detected leak, num_allocations=%d",
                            (int)num_allocations);
            }
        }

        void* HeapAllocator::allocate(size_t size)
        {
            ++ num_allocations_;
            return new char[size];
        }

        void HeapAllocator::deallocate(void* ptr)
        {
            if (num_allocations_ <= 0)
            {
                roc_panic("heap allocator : unpaired deallocate");
            }

            --num_allocations_;
            delete[](char*) ptr;
        }

        size_t HeapAllocator::num_allocations() const
        {
            return (size_t)num_allocations_;
        }
    } // namespace core
    
} // namespace roc
