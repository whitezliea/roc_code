/**
 * @file roc/context.h
 * @brief Roc context.
*/

#ifndef ROC_CONTEXT_H_
#define ROC_CONTEXT_H_

#include "roc/config.h"
#include "roc/platform.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Roc context
 * 
 * @b Thread-safety
 * - can be used concurrently
 * 
 * @see roc_sender, roc_receiver
*/
typedef struct roc_context roc_context;

/**
 * Open a new context.
 * @b Parameters
 * - @p config should point to an initialized config
 * @b Returns
*/
ROC_API roc_context* roc_context_open(const roc_context_config* config);

/**
 * Close the context.
 * @b Parameters 
 * - @p context should point to an opened context
 * @b Returns
 * 
*/
ROC_API roc_context* roc_context_close(roc_context* context);



#ifdef __cplusplus
}/** extern "C" */
#endif

#endif/** ROC_CONTEXT_H_ */

