/**
 * @file roc/sender.h
 * @brief Roc sender
*/

#ifndef ROC_SENDER_H_
#define ROC_SENDER_H_

#include "roc/address.h"
#include "roc/config.h"
#include "roc/context.h"
#include "roc/frame.h"
#include "roc/platform.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
 * Roc sender
 * @b Context
 * @b Lifecycle
 * roc_sender_open()-->roc_sender_bind()-->roc_sender_connect()-->roc_sender_write()-->roc_sender_close()
 * @b Ports
 * @b Resampling
 * @b Timing
 * @b Thread-safety
*/
typedef struct roc_sender roc_sender;

/**
 * Open a new sender
 * @b Parameters
 * - @p context
 * - @p config
 * @b Returns 
*/
ROC_API roc_sender* roc_sender_open(roc_context* context,
                                    const roc_sender_config* config);

/**
 * Bind the sender to a local port.
 * @b Parameter
 * - @p sender
 * - @p address
 * @b Returns 
*/
ROC_API roc_sender* roc_sender_bind(roc_sender* sender, roc_address* address);

/**
 * Connect the sender to a remote receiver port.
 * @b Parameter
 * - @p sender
 * - @p type
 * - @p proto
 * - @p address
 * @b Returns
*/
ROC_API int roc_sender_connect(roc_sender* sender,
                               roc_port_type type,
                               roc_protocol proto,
                               const roc_address* address);

/**
 * Encode samples to packets and transmit them to the receiver.
 * @b Parameter
 * - @p sender
 * - @p frame
 * @b Returns
*/
ROC_API int roc_sender_write(roc_sender* sender, const roc_frame* frame);

/**
 * Close the sender.
 * @b Parameter
 * - @p sender
 * @b Returns
*/
ROC_API int roc_sender_close(roc_sender *roc_sender);

#ifdef __cplusplus
}
#endif


#endif