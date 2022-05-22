#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "roc_core/backtrace.h"
#include "roc_core/crash.h"
#include "roc_core/errno_to_str.h"
#include "roc_core/log.h"
#include "roc_core/panic.h"
#include "roc_core/stddefs.h"

namespace roc
{
    namespace core
    {
        namespace 
        {
            volatile sig_atomic_t crash_in_progress = 0;
            const char* signal_string(int sig, siginfo_t* si)
            {
                switch (sig)
                {
                case SIGABRT:
                    return "caught SIGABRT";
                case SIGSEGV:
                    return "caught SIGSEGV";
                case SIGILL:
                    return "caught SIGILL";
            #ifdef SIGBUS
                case SIGBUS:
                    return "caught SIGBUS";
            #endif
            #ifdef SIGSTKFLT:
                case SIGSTKFLT:
                    return "caught SIGSTKFLT";
            #endif
                case SIGFPE:
                    switch (si->si_code)
                    {
                    case FPE_INTDIV:
                        return "caught SIGFPE (integer divide by zero) ";
                    case FPE_INTOVF:
                        return "caught SIGFPE (integer overflow) ";
                    case FPE_FLTDIV:
                        return "caught SIGFPE (floating-point divide by zero) ";
                    case FPE_FLTOVF:
                        return "caught SIGFPE (floating-point overflow) ";
                    case FPE_FLTUND:
                        return "caught SIGFPE (floating-point underflow) ";
                    case FPE_FLTRES:
                        return "caught SIGFPE (floating-point indexact result) ";
                    case FPE_FLTINV:
                        return "caught SIGFPE (floating-point invalid operation) ";
                    case FPE_FLTSUB:
                        return "caught SIGFPE (subscript out of range) ";    
                    default:
                        break;
                    }
                    return "caught SIGFPE";
                default:
                    break;
                
                }
                return "caught unknow singal";
            }

            void singal_handler(int sig, siginfo_t* si, void*)
            {
                if (!crash_in_progress)
                {
                    print_emergency_message("\nERROR: ");
                    print_emergency_message(signal_string(sig, si));
                    print_emergency_message("\n\n");
                    print_emergency_backtrace();
                }

                // this will finally kill us since we use SA_RESETHAND
                raise(sig);
            }
        } // namespace 
        
        void crash(const char* message)
        {
            crash_in_progress = 1;

            fprintf(stderr ,"\nERROR :%s\n\n", message);
            print_backtrace();

            abort();
        }

        CrashHandler::CrashHandler() : restore_sz_(0)
        {
            install_(SIGABRT);
            install_(SIGSEGV);
            install_(SIGILL);
        #ifdef SIGBUS
            install_(SIGBUS);
        #endif
        #ifdef SIGSTKFLT
            install_(SIGSTKFLT);
        #endif
            install_(SIGFPE);
        }

        CrashHandler::~CrashHandler()
        {
            for (size_t n = 0; n < restore_sz_; n++ )
            {
                if (sigaction(sig_restore_[n], &sa_restore_[n], NULL) != 0)
                {
                    roc_log(LogError ,"crash handler: sigaction(): %s", errno_to_str().c_str());
                }
            } 
        }


        void CrashHandler::install_(int sig)
        {
            roc_panic_if(restore_sz_ == MaxSigs);

            struct sigaction sa;
            sa.sa_sigaction = singal_handler;
            sa.sa_flags = int(SA_SIGINFO | SA_RESETHAND);

            if (sigemptyset(&sa.sa_mask) != 0)
            {
                roc_log(LogError, "crash handler: sigemptyset(): %s" ,errno_to_str().c_str());
            }

            if (sigaction(sig, &sa , &sa_restore_[restore_sz_]) != 0)
            {
                roc_log (LogError ,"crash handler: sigaction(): %s", errno_to_str().c_str());
            }

            sig_restore_[restore_sz_] = sig;
            restore_sz_ ++;
        }
    } // namespace core
    
} // namespace roc
