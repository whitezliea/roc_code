/**
 * @file roc/log.h
 * @brief Logger configuration
*/

#ifndef ROC_LOG_H_
#define ROC_LOG_H_

#include "roc/platform.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Log level
 * @see roc_log_set_level
*/
typedef enum roc_log_level {
    /**
     * No Message
    */
    ROC_LOG_NONE = 0,

    /**
     * Error message
    */
    ROC_LOG_ERROR = 1,

    /**
     * Informational messages
    */
    ROC_LOG_INFO = 2,

    /**
     * Debug messages
    */
    ROC_LOG_DEBUG = 3,

    /**
     * Debug messages (extra verbosity)
    */
    ROC_LOG_TRACE = 4

}roc_log_level;

/**
 * Log handler
 * @b Parameters
 * @p level defines the message level
 * @p component defines the component that product the message
 * @p messgae defines the message text
 * 
 * @see roc_log_set_handler
*/
typedef void (*roc_log_handler)(roc_log_level,
                                const char* component,
                                const char* message);

/**
 * Set maximum log level
 * @b Thread-safety
 * - can be used concurrently
*/
ROC_API void roc_log_set_level(roc_log_level level);

/**
 * Set log handler.
 * @b Thread-safety
 * - can be used concurrently
 * - handler calls are serialized, so the handler itself doesn't need to be thread-safe
*/

#ifdef __cplusplus
} /** extren "C" */
#endif

#endif /** ROC_LOG_H_ */

