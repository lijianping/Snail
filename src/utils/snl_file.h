#ifndef SNL_FILE_H
#define SNL_FILE_H

#include <snl_config.h>
#include <snl_utils.h>

struct snl_open_file_s
{
	snl_fd_t fd;
	snl_str_t name;
};

#endif /* SNL_FILE_H */
