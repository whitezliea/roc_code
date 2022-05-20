#include<string.h>
#include<unistd.h>

#include "roc_core/backtrace.h"

namespace roc
{
    namespace core
    {
        void print_emergency_message(const char* str)
        {
            size_t str_sz = strlen(str);
            while (str_sz > 0)
            {
                ssize_t ret = write(STDERR_FILENO, str, str_sz);
                if (ret <= 0)
                {
                    return ;
                }
                str += (size_t)ret;
                str_sz -= (size_t)ret;
            }
        }
    } // namespace core
    
} // namespace roc
