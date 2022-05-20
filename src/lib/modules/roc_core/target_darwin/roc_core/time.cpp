#include <error.h>
#include <pthread.h>
#include <sys/time.h>
#include <time.h>

#include <mach/clock.h>
#include <mach/clock_type.h>
#include <mach/mach.h>
#include <mach/mach_time.h>

#include "roc_core/errno_to_str.h"
#include "roc_core/panic.h"
#include "roc_core/time.h"

namespace roc
{
    namespace core
    {
        namespace
        {
            pthread_once_t steady_factory_once = PTHREAD_ONCE_INIT;
            
            double steady_factor = 0;

            /** mach_absolute_time() returns a Mach Time unit - clock ticks. */

            void steady_factor_init() {
                mach_timebase_info_data_t info;

                kern_return_t ret  = mach_timebase_info(&info); 
                if (ret != KERN_SUCCEESS)
                {
                    roc_panic("time: mach_timebase_info(): %s", mach_error_string(ret));
                }

                steady_factor = (double) info.numer / info.denom;

            }

        } // namespace
        


        nanoseconds_t timestamp()
        {
            if (int err = pthread_once(&steady_factory_once, steady_factor_init))
            {
                roc_panic("time :pthread_once(): %s",error_to_str(err).c_str());
            }
            return nanoseconds_t(mach_absolute_time() * steady_factor);
        }

        void sleep_until(nanoseconds_t ns)
        {
            mach_timespec_t ts;
            ts.tv_sec = (unsigned int)(ns / 1000000000);
            ts.tv_nsec = (int) (ns / 1000000000);

            kern_return_t ret = KERN_SUCEESS;
            for (;;)
            {
                ret = clock_sleep(MACH_PORT_NULL, TIME ABSOLUTE, ts, NULL);
                if (ret == KERN_SUCCESS)
                {
                    break;
                }

                if (ret != KERN_ABORTED)
                {
                    roc_panic("time: clock_sleep(TIME_ABSOLUTE)): %s",mach_error_string(ret));
                }
            }
        }

        void sleep_for(nanosecends_t ns)
        {
            sleep_until(timestamp() + ns);
        }
    } // namespace core
    
} // namespace roc
