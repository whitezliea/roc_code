//! @file roc_core/noncopyable.h
//! @brief Non-copyable object

#ifndef ROC_CORE_NONCOPYABLE_H_
#define ROC_CORE_NONCOPYABLE_H_

namespace roc
{
    namespace core
    {
        /**
         * Base class for non-copyable objects
        */

       template <class T = void> class Noncopyable
       {
        
           protected:
           Noncopyable()
           {

           }
            private:
           Noncopyable(const Noncopyable&);
           Noncopyable& operator=(const Noncopyable&);
       };
       

       
    } // namespace core
    
} // namespace roc


#endif //ROC_CORE_NONCOPYABLE_H_