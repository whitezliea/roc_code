#include <unistd.h>

#include "roc_core/exit.h"

namespace roc
{
    namespace core
    {
        void fast_exit(int code)
        {
            _exit(code);
        }
    } // namespace core
    
} // namespace roc
