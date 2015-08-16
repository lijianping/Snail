#ifndef SNL_MD5_H
#define SNL_MD5_H

#include <snl_config.h>

#define SNL_MD5_LEN        16

typedef struct snl_md5_ctx_s
{
    snl_uint32_t state[4];
    snl_uint32_t count[2];
    u_char buffer[64];
} snl_md5_ctx_t;

void snl_md5_init(snl_md5_ctx_t *ctx);
void snl_md5_update(snl_md5_ctx_t *ctx, u_char *input, size_t len);
void snl_md5_final(snl_md5_ctx_t *ctx, u_char digest[SNL_MD5_LEN]);

#endif /* SNL_MD5_H */
