#include<pthread.h>
#include<stdlib.h>

#include "roc_core/errno_to_str.h"
#include "roc_core/mutex.h"
#include "roc_core/panic.h"
#include "roc_core/random.h"
#include "roc_core/time.h"


namespace roc
{
    namespace core
    {
        namespace 
        {
            pthread_once_t rand_once = PTHREAD_ONCE_INIT;

            unsigned short rand_seed[3] = {};
            
            void random_init()
            {
                nanoseconds_t seed_48 = timestamp();
                rand_seed[0] = (seed_48 & 0xffff);
                rand_seed[1] = ((seed_48 >> 16) & 0xffff);
                rand_seed[2] = ((seed_48 >> 32) & 0xffff);
            }

        } // namespace 
        
        unsigned random(unsigned upper)
        {
            roc_panic_if_not(upper > 0);
            return random(0, upper-1);
        }

        // Based on arc4random_uniform() from OpenBSD
        unsigned random(unsigned from, unsigned to)
        {
            if (int err = pthread_once(&rand_once, random_init))
            {
                roc_panic ("pthread_once: %s", errno_to_str(err).c_str());
            }

            roc_panic_if_not (from <= to);

            uint32_t upper = uint32_t(to - from + 1);
            uint32_t min = -upper % upper;
            uint32_t val = 0 ;

            for (;;)
            {
                if ((val = (uint32_t)nrand48(rand_seed)) >= min)
                {
                    break;
                }
            }

            unsigned ret = from + (unsigned)(val % upper);

            roc_panic_if_not(ret >= from);
            roc_panic_if_not(ret <= to);

            return ret;
        }
    } // namespace core
    
} // namespace roc
