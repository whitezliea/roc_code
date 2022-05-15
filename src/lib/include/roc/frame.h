/**
 * @file roc/frame.h
 * @brief Audio frame.
*/

#ifndef ROC_FRAME_H_
#define ROC_FRAME_H_

#include "roc/platform.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Audio frame
 * @b Thread-safety
 * - should not be used concurrently 
*/
typedef struct roc_frame
{
    /**
     * Audio samples.
    */
    void* samples;

    /**
     * Sample buffer size.
    */
    size_t samples_size;
}roc_frame;


#ifdef __cplusplus
} /** extern "C" */
#endif

#endif/** ROC_FRAME_H_ */