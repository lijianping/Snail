#include <stdio.h>
#include <string.h>
#include <snl_md5.h>

static char *test[] = {
	"",
	"a",
	"abc",
	"message digest",
	"abcdefghijklmnopqrstuvwxyz",
	"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789",
	NULL
};

static char *ret[] = {
	"d41d8cd98f00b204e9800998ecf8427e",
	"0cc175b9c0f1b6a831c399e269772661",
	"900150983cd24fb0d6963f7d28e17f72",
	"f96b697d7cb7938d525a2f31aaf161d0",
	"c3fcd3d76192e4007dfb496cca67e13b",
	"d174ab98d277d9f5a5611c2c9f419d9f",
};

#define MD5_LENGTH    16

static char *pt(unsigned char *md);

void md5_test(const char *src, size_t len, unsigned char digest[16])
{
	snl_md5_ctx_t ctx;

	snl_md5_init(&ctx);
	snl_md5_update(&ctx, (u_char *)src, len);
	snl_md5_final(&ctx, digest);
}

int main(int argc, char *argv[])
{
	int i, err = 0;

	char **p, **r, *t;
	unsigned char md[MD5_LENGTH];

	p = test;
	r = ret;

	i = 1;
	while (*p != NULL) {
		md5_test(*p, strlen(*p), md);
		t = pt(md);

		if (strcmp(t, (char *)*r) != 0) {
			printf("error calculating MD5 on '%s'\n", *p);
			printf("got %s instead of %s\n", t, *r);
			err++;
		} else {
			printf("test %d ok\n", i);
		}
		i++;
		p++;
		r++;
	}

	return err;
}

static char *pt(unsigned char *md)
{
	int i;
	static char buf[80];

	for (i = 0; i < MD5_LENGTH; i++) {
		sprintf(&(buf[i * 2]), "%02x", md[i]);
	}

	return buf;
}
