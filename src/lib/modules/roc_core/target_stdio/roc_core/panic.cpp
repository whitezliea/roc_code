#include<stdarg.h>
#include<stdio.h>

#include "roc_core/crash.h"
#include "roc_core/panic.h"

namespace roc
{
    namespace core
    {
        void panic(const char* module,const char* file, int line, const char* format, ...)
        {
            fprintf (stderr , "\n%s:%d :error: roc_panic()\n", file, line);
            char message[128] = {};
            size_t message_sz = sizeof(message) - 1;

            int off = snprintf(message, message_sz, "%s: ", module);

            if (off>0)
            {
                message_sz -= (size_t)off;
            }

            va_list args;
            va_start(args, format);
            vsnprintf(message + off, message_sz ,format, args);
            va_end(args);

            crash(message);
            
        }
    } // namespace core
    
} // namespace roc


