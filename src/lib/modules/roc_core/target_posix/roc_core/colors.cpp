#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "roc_core/colors.h"

//! ANSI Color Code
#define COLOR_NONE ""
#define COLOR_START "\033["
#define COLOR_END "m"
#define COLOR_RESET COLOR_ START "0" COLOR_END
#define COLOR_SEPARTOR ";"
#define COLOR_BOLD "1"
#define COLOR_RED "31"
#define COLOR_BLUE "34"

namespace roc
{
    namespace core
    {
        namespace
        {
            char const* colors_to_levels(LogLevel level)
            {
                char const* color = COLOR_NONE;
                switch (level)
                {
                case LogNone: // No color for Loglevel None
                    break;
                
                case LogError: // Bold Red for Loglevel Error
                    color = COLOR_START COLOR_BOLD COLOR_SEPARTOR COLOR_RED COLOR_END;
                    break;
                
                case LogInfo: //Bold Blue for Loglevel Info
                    color = COLOR_START COLOR_BOLD COLOR_SEPARTOR COLOR_BLUE COLOR_END;
                    break;
                
                case LogDebug: //No color for Loglevel Debug
                    break;

                case LogTrace: //No color for Loglevel Trace
                }

                return color;
            }
        } // namespace
        
        bool colors_available()
        {
            char *term = getenv("TERM");
            return isatty(STDERR_FILENO) && term && strncmp("dumb", term, 4) != 0;
        }

        bool format_colored(LogLevel level, const char* str, char* buf, size_t bufsz)
        {
            roc_panic_if_not(str);
            roc_panic_if_not(buf);

            int printed =
                snprintf(buf, bufsz, "%s%s%s", colors_to_levels(level), str, COLOR_RESET);
            return printed > 0 && (size_t)printed <bufsz;
        }

    } // namespace core
    
} // namespace roc
