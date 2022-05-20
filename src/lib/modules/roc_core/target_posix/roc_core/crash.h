//! @file roc_core/targer_posix/roc_core/crash.h
//! @brief Crash handling

#ifndef ROC_CORE_CRASH_H_
#define ROC_CORE_CRASH_H_

#include <signal.h>

#include "roc_core/attributes.h"
#include "roc_core/noncopyable.h"

namespace roc
{
    namespace core
    {
        //! Report a crash and abort application
        void crash(const char* message) ROC_ATTR_NORETURN;

        class CrashHandler : public core::Noncopyable<>
        {
        private:
            void install_(int sig);
            enum {MaxSigs = 8};

            struct sigaction sa_restore_[MaxSigs];
            int sig_restore_[MaxSigs];
            size_t restore_sz_;
        public:
            //! Install singal handlers
            CrashHandler(/* args */);
            
            //! Restore singal handlers
            ~CrashHandler();
        };
        
        
    } // namespace name
    
} // namespace roc


#endif