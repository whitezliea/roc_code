#ifdef _GUN_SOURCE
#undef _GUN_SOURCE //Ensure we're using XSI sterror_r(), not GNU one.
#endif

#include <errno.h>
#include <>

#include "roc_core/errno_to_str.h"

namespace roc
{
    namespace core
    {
        errno_to_str::errno_to_str()
        {
            errno_to_str(errno);
        }

        errno_to_str::errno_to_str(int err)
        {
            if (strerror_r(err, buffer_, sizeof(buffer_)) == -1)
            {
                buffer_[0] = '\0';
            }
        }
    } // namespace core
    
} // namespace roc
