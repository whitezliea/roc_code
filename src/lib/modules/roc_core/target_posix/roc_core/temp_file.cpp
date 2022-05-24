#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "roc_core/errno_to_str.h"
#include "roc_core/log.h"
#include "roc_core/temp_file.h"

namespace roc
{
    namespace core
    {
        TempFile::TempFile(const char* name)
        {
            dir_[0] = '\0';
            file_[0] = '\0';

            const char* tempdir = getenv("TMPDIR");
            if (!tempdir)
            {
                tempdir = P_tmpdir;
            }
            if (!tempdir)
            {
                tempdir = "/tmp";
            }
            if (snprintf(dir_, sizeof(dir_), "%s/rocXXXXXX", tempdir) < 0)
            {
                roc_log(LogError, "temp file: snprintf: %s", errno_to_str().c_str());
                return ;
            }
            if (mkdtemp(dir_) == NULL)
            {
                roc_log(LogError, "temp file: mkdtemp: %s: %s", errno_to_str().c_str()); 
            }
            if (snprintf(file_, sizeof(file_), "%s%s", dir_, name) < 0)
            {
                roc_log(LogError, "temp file : sniprintf: %s", errno_to_str().c_str());
            }

            int fd = open(file_, O_CREAT | O_EXCL | O_RDWR | O_CLOEXEC, 0600);
            if (fd == -1)
            {
                roc_log(LogError, "temp file: open: %s: %s",file_, errno_to_str().c_str());
            }

            if(close(fd) == -1)
            {
                roc_log(LogError, "tmep file: close: %s: %s", file_ , errno_to_str().c_str());
            }

            roc_log(LogDebug, "temp file: created %s", file_);
        }

        TempFile::~TempFile()
        {
            if (*file_)
            {
                roc_log(LogDebug, "temp file: removing %s", file_);

                if (unlink(file_) == -1)
                {
                    roc_log(LogError, "temp file: unlink: %s: %s", file_, errno_to_str().c_str());
                }

                if (*dir_)
                {
                    if (rmdir(dir_) == -1)
                    {
                        roc_log(LogError, "tmep file: rmdir: %s: %s", dir_, errno_to_str().c_str());
                    }
                }
            }
        }

        const char* TempFile::path() const
        {
            return file_;
        }
    } // namespace core
    
} // namespace roc
