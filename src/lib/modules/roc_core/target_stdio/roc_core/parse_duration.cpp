#include "roc_core/parse_duration.h"
#include "roc_core/log.h"
#include "roc_core/stddefs.h"
#include "roc_core/stddefs.h"

namespace roc
{
    namespace core
    {
        namespace 
        {
            const char* find_suffix(const char* str, size_t str_len, const char* suffix)
            {
                const size_t suffix_len = strlen(suffix);
                if (str_len < suffix_len)
                {
                    return NULL;
                }
                if (strcmp(str + str_len - suffix_len, suffix) != 0 )
                {
                    return NULL;
                }
                return str + str_len - suffix_len;
            }
        } // namespace 
        
        bool parse_duration(const char* str, nanoseconds_t& result)
        {
            if (str == NULL)
            {
                roc_log(LogError, "parse duration: string is null");
                return false;
            }

            nanoseconds_t multiplier = 0;

            const size_t str_len = strlen(str);
            const char* suffix;

            if ((suffix = find_suffix(str, str_len, "ns")))
            {
                multiplier = Nanosecond;
            }
            else if ((suffix = find_suffix(str, str_len, "us")))
            {
                multiplier = Mircosecond;
            }
            else if ((suffix = find_suffix(str, str_len, "ms")))
            {
                multiplier = Millisecond;
            }
            else if ((suffix = find_suffix(str, str_len, "s")))
            {
                multiplier = Second;
            }
            else if ((suffix = find_suffix(str, str_len, "m")))
            {
                multiplier = Minute;
            }
            else if ((suffix = find_suffix(str, str_len, "h")))
            {
                multiplier = Hour;
            }
            else 
            {
                roc_log(Logger, "parse duration: no known suffix (ns, us, ms, s, m, h)");
                return false;
            }

            if (str == suffix)
            {
                roc_log(
                    LogError,
                    "parse duration: invalid format, missing number, expected <number><suffix>"
                );
                return false;
            }

            if (!isdigit(*str) && *str != '-')
            {
                roc_log(
                    LogError,
                    "parse duration: invalid fromat, can't parse number, expected"
                    "<number><suffix>"
                );
                return false;
            }

            char* number_end = NULL;
            long number = strtol(str, &number_end, 10);
            
            if (number == LONG_MAX || number == LONG_MIN || !number_end || number_end != suffix)
            {
                roc_log(
                    LogError,
                    "parse duration: invalid format, can't parse number, expected "
                    "<number><suffix>"
                );
                return false;
            }

            result = nanoseconds_t(number) * multiplier;
            return true;
        }
    } // namespace core
    
} // namespace roc
