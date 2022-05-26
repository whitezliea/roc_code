//! @file roc_core/iallocator.h
//! @brief Memory allocator interface

#ifndef ROC_CORE_IALLOCATOR_H_
#define ROC_CORE_IALLOCATOR_H_

#include "roc_core/attributes.h"
#include "roc_core/panic.h"
#include "roc_core/stddefs.h"

namespace roc
{
    namespace core
    {
        //Memory allocator interface
        class IAllocator
        {
        public:

            virtual ~IAllocator();
            // Allocate memory
            //! pointer to a maximum aligened uninitialized memory at least of @p size
            //! bytes or NULL if memory can't be allocated
            virtual void* allocate(size_t size) = 0;

            // Deallocate previously allocated memory
            virtual void deallocate(void* ) = 0;

            //! Destory object and deallocate its memory/
            template<class T> void destory(T& object)
            {
                object.~T();
                deallocate(&object);
            }

        };
        
    } // namespace core
    
} // namespace roc

// Placement new ofr core::IAllocator
// nothrow forces complier to check for NULL return value before calling ctor.
inline void* operator new(size_t size,
                        roc::core::IAllocator& allocator) ROC_ATTR_NOTHROW
                        {
                            return allocator.allocate(size);
                        }

// Placement new[] for core::IAllocator
// Nothrow forces compiler to check for NULL return value before calling ctor.
inline void* operator new[](size_t size,
                            roc::core::IAllocator & allocator) ROC_ATTR_NOTHROW
                            {
                                return allocator.allocate(size);
                            }

// Placement delete for core::IAllocator
// Compiler calls this if ctor throws in a placement new expression.
template <class T>
inline void operator delete(void* ptr, roc::core::IAllocator& allocator) ROC_ATTR_NOTHROW
{
    allocator.deallocate(ptr);
}

// Placement delete[] for core::IAllocator
// Compiler calls this if ctor throws in a placement new[] expression
template <class T>
inline void operator delete[](void* ptr,
                            roc::core::IAllocator& allocator) ROC_ATTR_NOTHROW
{
    allocator.deallocate(ptr);
}

#endif