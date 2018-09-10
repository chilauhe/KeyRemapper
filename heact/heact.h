#ifndef __HEACT_H__
#define __HEACT_H__ 1

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <memory.h>
#include <ctype.h>

#define HAVE_CRC32
#define HAVE_CRC16
#define HAVE_CRC8

#ifdef _MSC_VER
//stop M$ from breaking portable code
#pragma warning(disable:4996)
#endif // _MSC_VER


#ifdef HEACT_EXPORTS
#define HEACT __declspec(dllexport)
#else
#ifdef _WIN32
#include <WINSOCK2.H>
#include <Ws2ipdef.h>
#include <Windows.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#endif
//#define HEACT __declspec(dllimport)
#define HEACT 
#endif

#include "array.h"
#include "dbg.h"
#include "perfmon.h"
#include "ini.h"
#include "base64.h"
#include "base90.h"
#include "crc32.h"
#include "md5.h"
#include "rand.h"
#include "he_socket.h"
#include "threading.h"
//#include "utf8.h"


uint32_t getFileSize(const char *filename);
char *read2memory(const char * filename, char **p);
uint32_t sgets(char *buf, uint32_t n, const char *src);
char *dirname(char *val);

char *url_encode(char const *s, size_t len, size_t *new_length);
size_t url_decode(char *str, size_t len);
char *strtoupper(char *v);

char *WCHAR2C(char *p);
char *strdup(const char *val);
char *strndup(const char *val, size_t n);
/* strcmp dealing with unhandled condition */
int StrcmpEx(const unsigned char *a, const unsigned char *b);

#ifdef _WIN32
#include "win32_serial.h"
#include "win32_serial_list.h"
#endif

#ifndef NULL
#define NULL 0
#endif


#endif
