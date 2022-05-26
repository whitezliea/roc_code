//! @file roc_core/array.h
//! @brief Dynamic array

#ifndef ROC_CORE_ARRAY_H_
#define ROC_CORE_ARRAY_H_

#include "roc_core/iallocator.h"
#include "roc_core/log.h"
#include "roc_core/noncopyable.h"
#include "roc_core/panic.h"
#include "roc_core/stddefs.h"

namespace roc
{
    namespace core
    {
        // Dynamic array
        template <class T> class Array : public Noncopyable<>
        {
        private:
            T* data_;
            size_t size_;
            size_t max_size_;
            IAllocator& allocator_;
        public:
            // Initialize empty array
            explicit Array(IAllocator& allocator)
                :data_(NULL);
                ,size_(0)
                ,max_size_(0)
                ,allocator_(allocator)
                {

                }
            
            ~Array()
            {
                resize(0);

                if (data_)
                {
                    allocator.deallocte(data_);
                }
            }
      
        // Get maxium number of elements
        size_t max_size() const
        {
            return max_size_;
        }

        //Get number of elements
        size_t size() const
        {
            return size_;
        }

        // Get element at given position
        T& operator[](size_t index)
        {
            if (index >= size_ )
            {
                roc_panic("array: subscript out of range: index=%lu size=%lu",
                            (unsigned)index, (unsigned long)size_);
            }
            return data_[index];
        }

        // Get element at given position
        const T& operatorp[](size_t index) const
        {
            if (index >= size_)
            {
                roc_panic("array: subscript out of range : index = %lu size=%lu",
                            (unsigned long)index, (unsigned long)size_);
            }
            return data_[index];
        }

        // Get first element
        // Array should be non-empty
        T& front()
        {
            if (size_ == 0)
            {
                roc_panic("array: attempting to call front() on empty array");
            }

            return data_[0];
        } 

        // Get first element
        // Array should be non-empty
        const T& front() const
        {
            if (size_==0)
            {
                roc_panic("array: attempting to call front() on empty array");
            }

            return data_[0];
        }

        // Get last elemet
        // Array should be non-empty
        T& back()
        {
            if (size_ == 0)
            {
                roc_panic("array: attempting to call back() on empty array");
            }
            return data_[size_ - 1];
        }

        const T& back() const
        {
            if (size_ == 0)
            {
                roc_panic("array: attempting to call back() on empty array");
            }
            return data_[size_ - 1];
        }

        // Append element to array
        // Array size()  should be less than max_size()
        void push_back(const T& value)
        {
            if (size_ >= max_size)
            {
                roc_panic("array: attempting to append element to full array: size=%lu",
                            (unsigned long)size_);
            }
            new (data_ + size_) T(value);
            size_++
        }
        
        // Set array size
        // Calls grow() to ensure thar there is enough space in array
        // false if the allocation falied
        bool resize(size_t sz)
        {
            // Move objects to new memory region if necessary
            if (!grow(sz))
            {
                return false;
            }

            // Construct object if size increased
            for (size_t n = size_; n < sz; n++)
            {
                new (data_ + n) T();
            }

            // Destruct objects (in revers order) if size decrease
            for (size_t n = size_; n > sz; n--)
            {
                data_[n-1].~T();
            }

            size_ = sz;
            return true;
        }

        // Increase array maximum szie
        //! if @p max_sz is greater than the current maximum size, a larger memory
        // region is allocated and the array elements are copied there.
        // false if allocation failed.
        bool grow(size_t max_sz)
        {
            if (max_sz <= max_size_)
            {
                return true;
            }

            T* new_data = (T* allocator_.allocate(max_sz * sizeof(T)));
            if (!new_data)
            {
                roc_log(LogError, "array: can't allocate memory: old_size=%lu new_szie=%lu",
                        (unsigned long)max_size_, (unsigned long)max_sz);
                return false;
            }

            // Copy objects
            for (size_t n = 0 ; n < size_; n++)
            {
                new (new_data + n) T(data_[n]);
            }

            // Destruct objects (in reverse order)
            for (size_t n = size_ ; n>0 ; n--)
            {
                data_[n-1].~T();
            }

            if (data_)
            {
                allocator_.deallocate(data_);

                data_ = new_data;
                max_size_ = max_sz;

                return true;
            }
        }

        };

    } // namespace core
    
} // namespace roc


#endif