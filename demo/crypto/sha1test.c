#include <stdio.h>
#include <string.h>
#include <snl_sha1.h>

static char *test[] = {
	"abc",
	"abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq",
	NULL
};

static char *ret[] = {
	"a9993e364706816aba3e25717850c26c9cd0d89d",
	"84983e441c3bd26ebaae4aa1f95129e5e54670f1",
};

static char *pt(unsigned char *md);

void sha1_test(const char *src, size_t len,
		unsigned char digest[SNL_SHA1_LEN])
{
	snl_sha1_ctx_t ctx;

	snl_sha1_init(&ctx);
	snl_sha1_update(&ctx, (u_char *)src, len);
	snl_sha1_final(&ctx, digest);
}

int main(int argc, char *argv[])
{
	int i, err = 0;

	char **p, **r, *t;
	unsigned char md[SNL_SHA1_LEN];

	p = test;
	r = ret;

	i = 1;
	while (*p != NULL) {
		sha1_test(*p, strlen(*p), md);
		t = pt(md);

		if (strcmp(t, (char *)*r) != 0) {
			printf("error calculating SHA1 on '%s'\n", *p);
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

	for (i = 0; i < SNL_SHA1_LEN; i++) {
		sprintf(&(buf[i * 2]), "%02x", md[i]);
	}

	return buf;
}
