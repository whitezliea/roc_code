//! @file roc_core/backtrace.h
//! @brief Backtrace printing.

#ifndef ROC_CORE_BACKTRACE_H_
#define ROC_CORE_BACKTRACE_H_

namespace roc
{
    namespace core
    {
        //Print backtrace to stderr
        //! @remark
        void print_backtrace();

        //Print backtrace to stderr (emergency mode).
        //! @remark
        void print_emergency_backtrace();

        //Print message to stderr (emergency mode).
        //! @remark
        void print_emergency_message(const char* str);

    } // namespace core
    
} // namespace roc


#endif //ROC_CORE_BACKTRACE_H_