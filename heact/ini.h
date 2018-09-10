#ifndef __INI_H__
#define __INI_H__ 
#include "heact.h"
#include "array.h"

typedef struct _INI {
	void *h;
	char *filename;
} INI;

typedef char *(*ini_val_func)();
char *ini_readString(INI *ini, char *key);
int ini_readInt(INI *ini, char *key);
int64_t ini_readInt64(INI *ini, char *key);
double ini_readDouble(INI *ini, char *key);

char *ini_setString(INI *ini, char *key, char *val);
char *ini_setInt(INI *ini, char *key, int val);
char *ini_setDouble(INI *ini, char *key, double val);

void ini_unload(INI *ini);
char ini_load(INI *ini, char *filename);
char ini_loadString(INI *ini, char *content);

#endif
