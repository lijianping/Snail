#ifndef SNL_LOG_H
#define SNL_LOG_H

#include <snl_config.h>
#include <snl_utils.h>


#define SNL_LOG_STDERR       0
#define SNL_LOG_EMERG        1
#define SNL_LOG_ALERT        2
#define SNL_LOG_CRIT         3
#define SNL_LOG_ERR          4
#define SNL_LOG_WARNING      5
#define SNL_LOG_NOTICE       6
#define SNL_LOG_INFO         7
#define SNL_LOG_DEBUG        8


struct snl_log_s
{
	snl_uint_t level;
	snl_open_file_t *file;
};


snl_log_t *snl_log_init(char *prefix);

void snl_log_stderr(snl_err_t err, const char *fmt, ...);
size_t snl_log_errno(char *buf, char *last, snl_err_t err);

static snl_inline
void snl_write_stderr(char *text)
{
	(void)snl_write_fd(snl_stderr, text, snl_strlen(text));
}

static snl_inline
void snl_write_stdout(char *text)
{
	snl_strcmp("hello", "world");
	(void)snl_write_fd(snl_stdout, text, snl_strlen(text));

}

#define snl_write_console        snl_write_fd

#endif /* SNL_LOG_H */
