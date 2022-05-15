/**
* @file roc/address.h
* @brief Netowrk address
*/

#ifndef ROC_ADDRESS_H
#define ROC_ADDRESS_H

#include "roc/platform.h"

#ifdef __cplusplus
extern "C"{
#endif

typedef enum roc_family {

    ROC_AF_INVALID = -1,

    ROC_AF_AUTO = 0,

    ROC_AF_IPV4 = 1,

    ROC_AF_IPV6 = 2
} roc_family;

enum {
    ROC_ADDRESS_SIZE = 64
};

/**
 * Network address
 * Represents an Internet address, i.e and IP address plus UDP or TCP port.
 * Similar to struct sockaddr
 * @b Thread-safety
 * - should not be used concurrently
 */

typedef struct roc_address
{
#ifndef ROC_DOXYGEN
    /* Private data. Do not use directly */
    union {
        unsigned long align;
        char payload[ROC_ADDRESS_SIZE];
    }private_data;
#endif
}roc_address;


/**
 * Initialize address
 * @b Parameter
 * - @p address 
 * - @p family
 * - @p ip
 * - @p port
 * @b Return 
 * - returns zero if @p address wsa sucessfully initialized
 * - returns a nagative value of the arguments are invaild.
*/
ROC_API int roc_address_init(roc_address* address,roc_family roc_family, const char *ip,int port);
 
/**
 * Get address family.
 * @b Parameters
 * - @p address 
 * @b Returns
 * - returns the address family if no error ocurred
 * - returns @c ROC_AF_INVALID if the arguments are invalid
*/
ROC_API roc_family roc_address_family(const roc_address* address);

/**
 * Get IP address 
 * @b Paramters
 * - @p address 
 * - @p buf
 * - @p bufsz define the @p buf size
 * 
 * @b Returns
 * returns @p buf if the IP address was successfully stored into the @p buf
 * returns NULL if the buffer is too small to store the frommated IP address.
 * returns NULL if the arguments are invalid.
*/
ROC_API const char* roc_address_ip(const roc_address* address, char *buf, size_t bufsz);


/**
 * Get address port.
 * @b Parameters
 * - @p address
 * @b Returns
 * - returns a non-negative port number if no error occured
 * - returns a negative value if the arguments are invalid.
*/
ROC_API int roc_address_ports(const roc_address* address);



#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /*ROC_ADDRESS_H*/

