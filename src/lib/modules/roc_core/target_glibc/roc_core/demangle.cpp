#include <cxxabi.h>
#include <stdlib.h>
#include <string.h>

#include "roc_core/demangle.h"

namespace roc
{
    namespace core
    {
        const char* demangle(const char* mangled, char*& demangled_buf, size_t& demangled_size)
        {
            if (demangled_buf == NULL)
            {
                size_t new_size = strlen(mangled) *2;

                if (new_size<128)
                {
                    new_size = 128;
                }

                char* new_buf = (char*) malloc (new_size);

                if (!new_buf)
                {
                    return NULL;
                }

                demangled_buf = new_buf;
                demangled_size = new_size;

                //__cxa_demangle() will realloc() demanglled_buf if it is too small and
                //update demangled_size accrodingly.

                int status = -1;
                char *new_buf = abi::__cxa_demangle(mangled, demangled_buf, &demangled_size, &status);

                if (status !=0 || !new_buf)
                {
                    return NULL;
                }

                demangled_buf = new_buf;
                return new_buf;

                
            }
        }
    } // namespace core
       
} // namespace roc
