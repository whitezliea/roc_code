/**
 * @file roc/receiver.h
 * @brief Roc receiver.
*/
#ifndef ROC_RECEIVER_H_
#define ROC_RECEIVER_H_

#include "roc/address.h"
#include "roc/config.h"
#include "roc/context.h"
#include "roc/frame.h"
#include "roc/platform.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
 * Roc receiver
 * 
 * @b Context
 * @b Lifecyle
 *  roc_receiver_open()-->roc_receiver_bind()-->roc_receiver_read()-->roc_receiver_close()
 * @b Ports
 * @b Seesions
 * @b Mixing
 * @b Resampling
 * @b Timing
 * @b Thread-safety
*/

typedef struct roc_receiver roc_receiver;

/**
 * Open a new receiver
 * @b Parameters
 * - @p context
 * - @p config
 * @b Returns
*/
ROC_API roc_receiver* roc_receiver_open(roc_context* context,
                                        const roc_receiver_config* config);

/**
 * Bind the receiver to a local port.
 * @b Parameter
 * - @p receiver
 * - @p type
 * - @p proto
 * - @p address
 * @b Returns
*/
ROC_API int roc_receiver_bind(roc_receiver *receiver,
                              roc_port_type type,
                              roc_protocol proto,
                              roc_address* address);
            
/**
 * Read samples from the receiver.
 * @b Parameter
 * - @p receiver
 * - @p frame
 * @b Return
*/
ROC_API int roc_receiver_read(roc_receiver* receiver, roc_frame* frame);

/**
 * Close the receiver
 * @b Parameters
 * - @p receiver
 * @b Returns
*/
ROC_API int roc_receiver_close(roc_receiver* receiverr);

#ifdef __cplusplus
}/** extren "C" */
#endif

#endif /** ROC_RECEIVER_H_ */