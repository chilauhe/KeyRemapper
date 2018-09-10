#ifndef __BASE64_H__
#define __BASE64_H__ 1

#include "heact.h"
char *base64_encode(const unsigned char *, size_t);
char *base64_decode(const unsigned char *str,char *result);

#endif
