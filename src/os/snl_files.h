#ifndef SNL_FILES_H
#define SNL_FILES_H

#include <snl_config.h>

#define snl_stdout      STDOUT_FILENO
#define snl_stderr      STDERR_FILENO


typedef int             snl_fd_t;

static snl_inline
ssize_t snl_write_fd(snl_fd_t fd, void *buf, size_t n)
{
	return write(fd, buf, n);
}

static snl_inline
ssize_t snl_read_fd(snl_fd_t fd, void *buf, size_t n)
{
	return read(fd, buf, n);
}

#endif /* SNL_FILES_H */
