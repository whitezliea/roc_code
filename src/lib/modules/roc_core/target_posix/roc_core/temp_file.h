//! @file roc_core/target_posix/roc_core/temp_file.h
//! @brief Filesystem function

#ifndef ROC_CORE_TEMP_FILE_H_
#define ROC_CORE_TEMP_FILE_H_

#include <limits.h>

#include "roc_core/noncopyable.h"
#include "roc_core/stddefs.h"

namespace roc
{
    namespace core
    {
        // Temporary file
        //A temporary file is created in constructor and removed in destructor.
        class TempFile :public core::Noncopyable<>
        {
        private:
            char dir_[PATH_MAX];
            char file_[PATH_MAX];
        public:
            // Create temporary file
            //! Creates a temporary directory and a file with given @p name inside it.
            //Both will be removed in destructor.
            TempFile(const char *name);

            ~TempFile();

            //! Get file path
            const char* path() const;
        };
        
        
    } // namespace core
    
} // namespace roc



#endif
