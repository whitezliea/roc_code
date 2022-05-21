//! @file roc_core/target_stdio/roc_core/log.h
//! @brief Logging

#ifndef ROC_CORE_LOG_H_
#define ROC_CORE_LOG_H_

#include "roc_core/attributes.h"
#include "roc_core/mutex.h"
#include "roc_core/noncopyable.h"
#include "roc_core/singleton.h"

#ifndef ROC_MODULE
#error "ROC_MODULE not defined"
#endif

//! Print message to log 
#define roc_log(...)
    
namespace roc
{
    //! Log level
    enum LogLevel {
        LogNone, //Disable all message
        LogError, //Error message
        LogInfo, //Infomational message
        LogDebug, //Debug message
        LogTrace // Debug message (extra verbosity)
    };

    namespace core
    {
        //! Default log level
        const LogLevel DefaultLogLevel = LogError;

        //! Colors mode
        enum ColorsMode {
            ColorsDisabled,  //Do not use colored logs
            ColorsEnabled //Use colored log
        };

        //! Default colors mode
        const ColorsMode DefaultColorsMode = ColorsDisabled;

        //Log handler
        typedef void (*LogHandler)(LogLevel level, const char* module, const char* message);

        //! Logger
        class Logger : public Noncopyable<>
        {
        private:
            friend class Singleton<Logger>;
            Logger();
            Mutex mutex_;
            LogLevel level_;
            LogHandler handler_;
            ColorsMode colors_;
        public:
            //! Get logger instance
            static Logger& instance()
            {
                return Singleton<Logger>::instance(); 
            }

            //! Print message to log.
            void print(const char* module, LogLevel level, const char * format, ...)
                ROC_ATTR_PRINTF(4,5);
            
            //! Get current maxium log level
            LogLevel level();

            //! Set maximum log level
            // Messgae with higher log level will be dropped.
            // Default log level is LogError
            void set_level(LogLevel);

            // Set log handler
            void set_handler(LogHandler hander);

            // Set colors mode
            // Default colors mode is ColorsAuto
            void set_colors(ColorsMode mode);

            
        };
        
        
    } // namespace core
    
} // namespace roc


#endif