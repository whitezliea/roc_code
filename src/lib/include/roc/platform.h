/**
 * @file roc/platform.h
 * @brief Platform-specific definitions
*/

#ifndef ROC_PLATFORM_H_
#define ROC_PLATFORM_H_

#include <stddef.h>

#if defined(__GNUC__)
/** 
 * Compiler attribute for an exported API function.
*/
#define ROC_API __attribute__((visibility("default")))
#else /** !__GNUC___ */
#error "unsupported compiler"
#endif /** __GNUC*/

#endif /** ROC_PLATFORM_H_ */