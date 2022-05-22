//! @file roc_core/target_posix/roc_core/endian.h
//! @brief Endian converters

#ifndef ROC_CORE_ENDIAN_H_
#define ROC_CORE_ENDIAN_H_

#include <arpa/inet.h>
#include <inttypes.h>
#include <netinet/in.h>
#include <sys/types.h>

namespace roc
{
    namespace core
    {
        // Network to host (16 bits)
        inline uint16_t ntoh16(uint16_t v)
        {
            return ntohs(v);
        }

        //Network to host (32 bits)
        inline uint32_t ntoh32(uint32_t v)
        {
            return ntohl(v);
        }

        //Host to Network (16 bits)
        inline uint16_t hton16(uint16_t v)
        {
            return htons(v);
        }

        //Host to Network (32 bits)
        inline uint32_t hton32(uint32_t v)
        {
            return htonl(v);
        }
    } // namespace core
    
} // namespace roc

#endif