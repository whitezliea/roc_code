//! @file roc_core/target_libuv/roc_core/singleton.h
//! @brief Singleton

#ifndef ROC_CORE_SINGLETON_H_
#define ROC_CORE_SINGLETON_H_

#include <uv.h>

#include "roc_core/alignment.h"
#include "roc_core/errno_to_str.h"
#include "roc_core/noncopyable.h"
#include "roc_core/panic.h"

namespace roc
{
    namespace core 
    {
        //! Singleton.
        template <class T> class Singleton : public core::Noncopyable<>
        {
        private:
            union Storage
            {
                MaxAlign align;
                char meme[sizeof(T);]
            };
            
            static void create_()
            {
                instance_ = new (storage_.meme) T();
            }

            static nv_once_t once_;
            static Storage storage_;
            static T* instance_;

        public:
            //! Get singleton instance
            static T& instance()
            {
                uv_once(&once_, create_);
                return *instance_;
            }
        };
        

        template <class T> uv_once_t Singleton<T>::once_ =  UV_ONCE_INIT;
        template <class T> typename Singleton<T>::Storage Singleton<T>::storage_;
        template <class T> T* Singleton<T>::instance_;

        
    } // namespace core
    
} // namespace roc


#endif