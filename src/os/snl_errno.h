#ifndef SNL_ERRNO_H
#define SNL_ERRNO_H

#include <snl_config.h>

typedef int                      snl_err_t;

#define snl_errno                errno
#define snl_set_errno(err)       errno = err

size_t snl_strerror_r(int errnum, char *buf, size_t buflen);

#endif /* SNL_ERRNO_H */
