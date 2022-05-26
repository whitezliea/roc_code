//! @file roc_core/ownership.h
//! @brief Ownership policies

#ifndef ROC_CORE_OWNERSHIP_H_
#define ROC_CORE_OWNERSHIP_H_

namespace roc
{
    namespace core
    {
        template<class T,template <class TT> class Ownership> class SharedPtr;

        // Reference countable object ownership
        template <class T> struct RefCntOwnership{
            // Pointer type countable object ownership.
            // Container should return smart pointer instead of raw pointer since
            // it can call decref() on returned object later
            typedef SharedPtr<T, core::RefCntOwnership> Pointer;

            // Acquire ownership
            static void acquire(T& object)
            {
                //The incref function simply increments the reference count by one
                object.incref();
            }

            static void release(T& object)
            {
                /**
                 * The decref function not only decrements the reference count by one, 
                 * but also needs to determine whether the reference is 0 after the decrement by one.
                 *  If it is 0, the object needs to be released: call the release function of the object.
                */
                object.decref();
            }
        };

        //No onwership
        template <class T> struct NoOwnership
        {
            // Pointer type returned from intrusive containers
            // It's safe to return raw poniter since container will never free objects.
            typedef T* Pointer;

            // Acquire ownership
            static void acquire(T&)
            {

            }

            //Release onwership
            static void release(T&)
            {

            }
        };
    } // namespace core
    
} // namespace roc


#endif