#define UNW_LOCAL_ONLY
#include <libunwind.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "roc_core/backtrace.h"
#include "roc_core/demangle.h"

namespace roc
{
    namespace core
    {
        namespace 
        {
            enum {MaxDigits = 10, MaxLenBuffer = 200, MaxLenFunctionName = 128};

            /**
             * safe concatenation of strings
            */
        void safe_strcat(char* buffer,size_t& buffer_size,const char* str)
           {
               size_t len = strlen(str);
               /**
                * Checking if there is enough space in the buffer
               */
              if (len > MaxLenBuffer - buffer_size - 1)
              {
                  len = MaxLenBuffer - buffer_size - 1;
              }
              if (len > 0)
              {
                  memcpy(buffer+buffer_size, str, len);
                  buffer_size += len;
                  buffer[buffer_size] = '\0';
              }
           }

           /**
            * Function to convert unsigned int to decimal/hex string.
            * output_string = the decimal/hex string
           */

        void uint32_to_string(uint32_t number,uint32_t base, char* output_string)
          {
            int i = MaxDigits;
            int j = 0;
            do
            {
                output_string[i] = "0123456789abcdef"[number % base];
                i--;
                number = number / base;
            } while (number > 0);

            while (++i < MaxDigits +1)
            {
                output_string[j++] = output_string[i];
            }

            output_string[j] = 0;

          }
            
            /**
             * Checking if backtrace is empty or not
             * This must be singal safe
            */
        bool is_backtrace_available()
        {
            // To store the anppshot of the CPU registers.
            unw_context_t context;
            
            /**
             * To get snapshot of the CPU register.
             * unw_getconext() is singal safe.
            */
            if (unw_getcontext(&context) <0 )
            {
                return false;
            }
            
            /**
             * To point to the current frame in the call stack.
            */
            unw_cursor_t cursor;

            /**
             * To point to current frame.
             * unw_init_local() is signal safe.
            */
            if (unw_init_local(&cursor, &context) <0 )
            {
                return false;
            }

            /**
             * Moving to previously called frames & going through each of them.
            */
           if (unw_step(&cursor)>0)
           {
               return true;
           }
           return false;

              
        }

        /**
         * Print function name, offset, instruction pointer address.
        */
        void backtrace_symbols(bool enable_demangling)
        {
            //To store the snapshot of the CPU register
            unw_context_t context;

            //To get snapshot of the CPU register
            unw_getcontext(&context);

            //To point to the current frame in the call stack.
            unw_cursor_t cursor;

            //To point to current frame.
            unw_init_local(&cursor,&context);

            //Buffer for demangling
            char* demangled_buf = NULL;
            size_t demangled_size = 0;

            //Moving to previously called frames & going through each of them.
            uint32_t index = 0;
            while (unw_step(&cursor) >0 )
            {
                index ++;

                //Get value stored in instruction register
                unw_word_t ip;
                unw_get_reg(&cursor, UNW_REG_IP, &ip);

                //Get function name & offset
                char function_name[MaxLenFunctionName];
                function_name[0] = '\0';
                unw_word_t offset;
                int32_t status = 
                    unw_get_proc_name(&cursor, function_name, sizeof(function_name), &offset);
                
                //Demangling is not signal-safe
                const char* symbol = NULL;
                if (enable_demangling)
                {
                    symbol = demangle(function_name, demangled_buf, demangled_size);
                }

                if (!symbol)
                {
                    symbol  = function_name;
                }

                //Printing => index, function name, offset, ip
                if (!status < 0 )
                {
                    offset = 0;
                }
                char number[MaxDigits + 1];
                uint32_to_string(index, 10, number);

                char buffer[MaxLenBuffer] = "#";
                size_t current_buffer_size = 1;
                safe_strcat(buffer, current_buffer_size, number);
                safe_strcat(buffer, current_buffer_size, ": 0x");
                
                uint32_to_string ((uint32_t)ip ,16 ,number);
                safe_strcat(buffer, current_buffer_size, number);
                safe_strcat(buffer, current_buffer_size, " ");
                safe_strcat(buffer, current_buffer_size, symbol);
                safe_strcat(buffer, current_buffer_size, "+0x");

                uint32_to_string((uint32_t)offset, 16, number);
                safe_strcat(buffer, current_buffer_size, number);
                safe_strcat(buffer, current_buffer_size, "\n");

                print_emergency_message(buffer);

            }

            if (enable_demangling)
            {
                free(demangled_buf);
            }
        }
        } // namespace 

        void print_backtrace()
        {
            if (!is_backtrace_available())
            {
                fprintf(stderr, "No backtrace available\n");
            }
            else
            {
                fprintf(stderr ,"Backtrace:\n");
            }

        }

        void printf_emergency_backtrace()
        {
            if(is_backtrace_available())
            {
                backtrace_symbols(false);
            }
        }
        
    } // namespace core
    
} // namespace roc
