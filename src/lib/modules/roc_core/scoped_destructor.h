//! @file roc_core/scoped_destructor.h
//! @brief Scoped destructor.

#include  "roc_core/noncopyable.h"

namespace roc
{
    namespace core
    {
        // Destorys the object via custom deleter.
        template < class T, void (*Func)(T)> class ScopedDestructor : public Noncopyable<>
        {
        private:
            T obj_;
        public:
            // Initialize
            explicit ScopedDestructor(T obj)
            : obj_(obj)
            {

            }
            ~ScopedDestructor()
            {
                Func(obj_);
            }
        };
        

        
    } // namespace core
    
} // namespace roc
