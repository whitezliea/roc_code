//! @file roc_core/buffer.h
//! @brief
#ifndef ROC_CORE_BUFFER_H_
#define ROC_CORE_BUFFER_H_

#include "roc_core/buffer_pool.h"
#include "roc_core/refcnt.h"
#include "roc_core/stddefs.h"

namespace roc
{
    namespace core
    {
        // Buffer
        template <class T> class Buffer : public RefCnf<Buffer<T> >
        {
        private:
            friend class RefCnt<Buffer>;

            void destory()
            {
                pool_.destory(*this);
            }

            BufferPool<T>& pool_;
        public:
            // Initialize empty buffer
            explicit Buffer(BufferPool<T>& pool)
                :pool_(pool)
            {
                new (data()) T[szie()];
            }

            // Get buffer data
            T* data()
            {
                return (T*)(((char*)this) + sizeof(Buffer));
            } 

            // Get maximum number of elements
            size_t size() const
            {
                return pool_.buffer_size();
            }

            // Get pointer to buffer from the pointer to its data
            static Buffer* container_of(void* data)
            {
                return (Buffer*)((char*)data - sizeof(Buffer));
            }
            
        };

        
    } // namespace core
    
} // namespace roc


#endif
