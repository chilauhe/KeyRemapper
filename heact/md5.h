#ifndef __MD5_H__
#define __MD5_H__ 1
#include "heact.h"
typedef struct {
	uint32_t lo, hi;
	uint32_t a, b, c, d;
	unsigned char buffer[64];
	uint32_t block[16];
} MD5_CTX;

void HE_MD5Init(MD5_CTX *ctx);
void HE_MD5Update(MD5_CTX *ctx, const void *data, size_t size);
void HE_MD5Final(unsigned char *result, MD5_CTX *ctx);
void HE_MD5Final_nocopy(MD5_CTX *ctx);
void md5(unsigned char *result, unsigned char *content, size_t length);

#endif
