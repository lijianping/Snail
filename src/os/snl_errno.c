#include <snl_config.h>
#include <snl_utils.h>

size_t snl_strerror_r(int errnum, char *buf, size_t buflen)
{
	size_t len;

	if (buflen == 0) {
		return 0;
	}

	buf[0] = '\0';

	strerror_r(errnum, buf, buflen);

	for (len = 0; len < buflen; ++len) {
		if (buf[len] == '\0') {
			break;
		}
	}

	return len;
}
