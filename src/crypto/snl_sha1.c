#include <snl_sha1.h>

/* The SHA1 circular left shift macro */
#define CIRCULAR_SHIFT(bits, word) \
	(((word) << (bits)) | ((word) >> (32 - (bits))))

static void snl_sha1_pad_message(snl_sha1_ctx_t *ctx);
static void snl_sha1_process_message_block(snl_sha1_ctx_t *ctx);

void snl_sha1_init(snl_sha1_ctx_t *ctx)
{
	ctx->low = 0;
	ctx->high = 0;
	ctx->index = 0;

	ctx->hash[0] = 0x67452301;
	ctx->hash[1] = 0xEFCDAB89;
	ctx->hash[2] = 0x98BADCFE;
	ctx->hash[3] = 0x10325476;
	ctx->hash[4] = 0xC3D2E1F0;

	ctx->computed = 0;
	ctx->corrupted = 0;
}

void snl_sha1_update(snl_sha1_ctx_t *ctx, u_char *input, size_t len)
{
	if (ctx->computed) {
		ctx->corrupted = SHA1_STATE_ERROR;
		return;
	}

	while (len-- && !ctx->corrupted) {
		ctx->block[ctx->index++] = (*input & 0xFF);

		ctx->low += 8;
		if (ctx->low == 0) {
			ctx->high++;
			if (ctx->high == 0) {
				/* Message is too long */
				ctx->corrupted = SHA1_INPUT_TOO_LONG;
			}
		}

		if (ctx->index == 64) {
			snl_sha1_process_message_block(ctx);
		}

		input++;
	}
}

int snl_sha1_final(snl_sha1_ctx_t *ctx, u_char digest[SNL_SHA1_LEN])
{
	snl_int_t i;

	if (ctx->corrupted) {
		return ctx->corrupted;
	}

	if (!ctx->computed) {
		snl_sha1_pad_message(ctx);
		for (i = 0; i < 64; ++i) {
			/* Message may be sensitive, clear it out */
			ctx->block[i] = 0;
		}
		ctx->low = 0;
		ctx->high = 0;
		ctx->computed = 1;
	}

	for (i = 0; i < SNL_SHA1_LEN; ++i) {
		digest[i] = ctx->hash[i >> 2] >> 8 * (3 - (i & 0x03));
	}

	return SHA1_SUCCESS;
}

static void snl_sha1_pad_message(snl_sha1_ctx_t *ctx)
{
	if (ctx->index > 55) {
		ctx->block[ctx->index++] = 0x80;
		while (ctx->index < 64) {
			ctx->block[ctx->index++] = 0;
		}

		snl_sha1_process_message_block(ctx);

		while (ctx->index < 56) {
			ctx->block[ctx->index++] = 0;
		}
	} else {
		ctx->block[ctx->index++] = 0x80;

		while (ctx->index < 56) {
			ctx->block[ctx->index++] = 0;
		}
	}

	ctx->block[56] = ctx->high >> 24;
	ctx->block[57] = ctx->high >> 16;
	ctx->block[58] = ctx->high >> 8;
	ctx->block[59] = ctx->high;

	ctx->block[60] = ctx->low >> 24;
	ctx->block[61] = ctx->low >> 16;
	ctx->block[62] = ctx->low >> 8;
	ctx->block[63] = ctx->low;

	snl_sha1_process_message_block(ctx);
}

static void snl_sha1_process_message_block(snl_sha1_ctx_t *ctx)
{
	const snl_uint32_t K[] = {
		0x5A827999, 0x6ED9EBA1, 0x8F1BBCDC, 0xCA62C1D6
	};

	snl_int_t i;                  /* Loop counter */
	snl_uint32_t temp;            /* Temporary word value */
	snl_uint32_t W[80];           /* Word sequence */
	snl_uint32_t A, B, C, D, E;   /* Word buffers */

	for (i = 0; i < 16; i++) {
		W[i] = ctx->block[i * 4] << 24;
		W[i] |= ctx->block[i * 4 + 1] << 16;
		W[i] |= ctx->block[i * 4 + 2] << 8;
		W[i] |= ctx->block[i * 4 + 3];
	}

	for (i = 16; i < 80; i++) {
		W[i] = CIRCULAR_SHIFT(1, W[i-3] ^ W[i-8] ^ W[i-14] ^ W[i-16]);
	}

	A = ctx->hash[0];
	B = ctx->hash[1];
	C = ctx->hash[2];
	D = ctx->hash[3];
	E = ctx->hash[4];

	for (i = 0; i < 20; i++) {
		temp = CIRCULAR_SHIFT(5, A) + ((B&C) | ((~B)&D)) + E + W[i] + K[0];

		E = D;
		D = C;
		C = CIRCULAR_SHIFT(30, B);
		B = A;
		A = temp;
	}

	for (i = 20; i < 40; i++) {
		temp = CIRCULAR_SHIFT(5, A) + (B ^ C ^ D) + E + W[i] + K[1];
		
		E = D;
		D = C;
		C = CIRCULAR_SHIFT(30, B);
		B = A;
		A = temp;
	}

	for (i = 40; i < 60; i++) {
		temp = CIRCULAR_SHIFT(5, A) + 
			((B&C) | (B&D) | (C&D)) + E + W[i] + K[2];

		E = D;
		D = C;
		C = CIRCULAR_SHIFT(30, B);
		B = A;
		A = temp;
	}

	for (i = 60; i < 80; i++) {
		 temp = CIRCULAR_SHIFT(5,A) + (B ^ C ^ D) + E + W[i] + K[3];
		 
		 E = D;
		 D = C;
		 C = CIRCULAR_SHIFT(30, B);
		 B = A;
		 A = temp;
	}

	ctx->hash[0] += A;
	ctx->hash[1] += B;
	ctx->hash[2] += C;
	ctx->hash[3] += D;
	ctx->hash[4] += E;

	ctx->index = 0;
}
