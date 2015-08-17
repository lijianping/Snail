#include <snl_config.h>
#include <snl_utils.h>

#define SNL_MAX_ERROR_STR_LEN     2048

static snl_log_t         snl_log;
static snl_open_file_t   snl_log_file;
snl_uint_t               snl_use_stderr = 1;

static snl_str_t err_levels[] = {
	snl_null_string,
	snl_string("emerg"),
	snl_string("alert"),
	snl_string("crit"),
	snl_string("error"),
	snl_string("warn"),
	snl_string("notice"),
	snl_string("info"),
	snl_string("debug")
};


snl_log_t *snl_log_init(char *prefix)
{
	char *p, *name;
	size_t plen, nlen;

	snl_log.file = &snl_log_file;
	snl_log.level = SNL_LOG_NOTICE;

	name = SNL_ERROR_LOG_PATH;

	nlen = snl_strlen(name);

	if (nlen == 0) {
		snl_log_file.fd = snl_stderr;
		return &snl_log;
	}

	if (name[0] != '/') {
		if (prefix) {
			plen = snl_strlen(prefix);
		} else {
#ifdef SNL_PREFIX
			prefix = SNL_PREFIX;
			plen = snl_strlen(prefix);
#else
			plen = 0;
#endif
		}
	}

	return &snl_log;
}

void snl_log_stderr(snl_err_t err, const char *fmt, ...)
{
	char errstr[SNL_MAX_ERROR_STR_LEN];
	size_t len, max;
	va_list args;

	max = SNL_MAX_ERROR_STR_LEN - 1;
	len = 0;

	len += snl_snprintf(errstr + len, max - len, "snail: ");

	va_start(args, fmt);
	len += snl_vsnprintf(errstr + len, max - len, fmt, args);
	va_end(args);

	if (err) {
		len += snl_log_errno(errstr + len, errstr + max, err);
	}

	if (len >= max) {
		len = max;
	}

	errstr[len++] = LF;

	(void) snl_write_console(snl_stderr, errstr, len);
}

size_t snl_log_errno(char *buf, char *last, snl_err_t err)
{
	size_t len;

	if (buf > last - 50) {
		buf = last - 50;
		*buf++ = '.';
		*buf++ = '.';
		*buf++ = '.';
	}

	len = snl_snprintf(buf, last - buf, " (%d: ", err);

	len += snl_strerror_r(err, buf + len, last - buf - len);

	if (buf + len < last) {
		*buf++ = ')';
		len++;
	}

	return len;
}
