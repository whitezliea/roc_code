//! @file roc_core/ticker.h
//! @brief Ticker.

#ifndef ROC_CORE_TICKER_H_
#define ROC_CORE_TICKER_H_

#include "roc_core/time.h"
#include "roc_core/panic.h"
#include "roc_core/noncopyable.h"

namespace roc
{
    namespace core
    {
        //Ticker
        class Ticker
        {
        private:
            const double ratio_;
            nanoseconds_t start_;
            bool started_;
        public:
            // Number of ticks
            typedef uint64_t Ticks;

            // Initialize
            //! @p freq defines the number of ticks per second
            explicit Ticker(Ticks freq)
            : ratio_(double(freq)/ Second)
            , start_(0)
            , started_(false)
            {

            }

            //! Start ticker
            void start()
            {
                if (started_)
                {
                    roc_panic("ticker: can't start ticker twice");
                }
                start_ = timestamp();
                started_ = true;
            }

            // Returns number of ticks elapsed since start.
            // If tickers is not started yet, it is started automatically.
            Ticks elapsed()
            {
                if (!started_)
                {
                    start();
                    return 0;
                }
                else
                {
                    return Ticks(double(timestamp() - start_) * ratio_);
                }
            }

            // Wait until the given number of ticks elapses since start.
            // If ticker is not started yet, it is started automatically.
            void wait(Ticks ticks)
            {
                if (!started_)
                {
                    start();
                }
                sleep_until(start_ + nanoseconds_t(ticks / ratio_));
            }

        };
        
    } // namespace core
    
} // namespace roc


#endif