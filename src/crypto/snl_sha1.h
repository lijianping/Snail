#ifndef SNL_SHA1_H
#define SNL_SHA1_H

#include <snl_config.h>

enum
{
	SHA1_SUCCESS = 0,
	SHA1_NULL,            /* NULL pointer parameter */
	SHA1_INPUT_TOO_LONG,  /* Input data too long */
	SHA1_STATE_ERROR      /* Called input after result */
};

#define SNL_SHA1_LEN      20

typedef struct snl_sha1_ctx_s
{
	snl_uint32_t hash[SNL_SHA1_LEN / 4];   /* Message digest */

	snl_uint32_t low;       /* Message length in bits */
	snl_uint32_t high;      /* Message length in bits */

	snl_int16_t index;      /* Index to message block array */
	snl_uint8_t block[64];  /* 512-bit message blocks */

	snl_int_t computed;     /* Is the digest computed? */
	snl_int_t corrupted;    /* Is the message digest corrupted? */
} snl_sha1_ctx_t;

void snl_sha1_init(snl_sha1_ctx_t *ctx);
void snl_sha1_update(snl_sha1_ctx_t *ctx, u_char *input, size_t len);
int snl_sha1_final(snl_sha1_ctx_t *ctx, u_char digest[SNL_SHA1_LEN]);

#endif /* SNL_SHA1_H */
