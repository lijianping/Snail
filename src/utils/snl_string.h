#ifndef SNL_STRING_H
#define SNL_STRING_H

#include <snl_config.h>
#include <snl_utils.h>

typedef struct
{
	size_t len;
	char *data;
} snl_str_t;

#define snl_string(str)         { sizeof(str) - 1, (u_char *)str }
#define snl_null_string         { 0, NULL }

void snl_string_test();

static snl_inline void *snl_memcpy(void *dst, const void *src, size_t n)
{
	return memcpy(dst, src, n);
}

static snl_inline void *snl_memset(void *s, int c, size_t n)
{
	return memset(s, c, n);
}

static snl_inline void *snl_memzero(void *s, size_t n)
{
	return memset(s, 0, n);
}

static snl_inline char *snl_strcpy(char *dst, const char *src)
{
	return strcpy(dst, src);
}

static snl_inline char *snl_strncpy(char *dst, const char *src, size_t n)
{
	return strncpy(dst, src, n);
}

static snl_inline size_t snl_strlen(const char *s)
{
	return strlen(s);
}

static snl_inline int snl_strcmp(const char *s1, const char *s2)
{
	return strcmp(s1, s2);
}

static snl_inline int snl_strncmp(const char *s1, const char *s2, size_t n)
{
	return strncmp(s1, s2, n);
}

#define snl_strncasecmp(s1, s2, n) \
	strncasecmp((const char *) s1, (const char *) s2, n)

#define snl_strcasecmp(s1, s2) \
	strcasecmp((const char *) s1, (const char *) s2)

#define snl_snprintf       snprintf
#define snl_vsnprintf      vsnprintf

#endif /* SNL_STRING_H */
