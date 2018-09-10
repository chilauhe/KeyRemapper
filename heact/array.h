#ifndef __ARRAY_H__
#define __ARRAY_H__
//#ifdef __cplusplus
//extern "C"{
//#endif//__cplusplus
#define ARRAY_NAME_HASH 1

typedef enum { ARRAY_OBJECT=0, ARRAY_LONGLONG, ARRAY_LONG, ARRAY_SHORT, ARRAY_CHAR,
			   ARRAY_DOUBLE, ARRAY_FLOAT, ARRAY_STRING, ARRAY_ARRAY, ARRAY_IMM_INT
} Array_T;
typedef enum {ARRAY_UNICODE, ARRAY_ANSI} Array_String_T;
#define SIZE_CHAR 1
#define SIZE_SHORT 2
#define SIZE_LONG 4
#define SIZE_FLOAT 4
#define SIZE_LONGLONG 8
#define SIZE_DOUBLE 8

typedef struct _Array {
	size_t i;//index of the element
	size_t len;
	unsigned char *name;
	void *v;//value object of the array
	struct _Array *next;
	unsigned int t;//type of the array object
#ifdef ARRAY_NAME_HASH
				   /*make the struct aligined to 32 bit*/
	unsigned int len_name;
	unsigned int hash_name;
	unsigned int hash_v;
#endif
} Array;

#include "heact.h"

#ifndef HEACT
#define HEACT
#endif

#define ARRAY_STRING_SHRINK 1
#define ARRAY_STRING_HEXINT (1<<1)
#define ARRAY_STRING_FPSCI (1<<2)
#define ARRAY_STRING_NOQUOTE (1<<3)
#define ARRAY_STRING_NOSUB (1<<4)
#define ARRAY_STRING_NOESCAPE (1<<5)
#define ARRAY_STRING_OBJPROC (1<<6)



Array *Array_new(void);
void Array_delete(Array *v);
size_t Array_size(Array *head);
void Array_remove(Array *v, Array *lslibing);
HEACT void Array_removeElementByName(Array **head, const char *name);
HEACT void Array_removeElementById(Array **head, size_t id);

HEACT Array *Array_setValue(Array *subject, void *v, Array_T t, size_t len);
Array *Array_setElementById(Array *head, size_t id, const char *name, void *v, Array_T t, size_t len);
size_t Array_getValueToString(Array *ele, char *buf, size_t max_len, unsigned int flags);
char *Array_StringEscape(char *org_str, char *escaped_str, size_t max_len, size_t *escaped_len);
//size_t Array_getValueJSONArray(Array *th, char *buf, size_t max_len);
//size_t Array_getValueStringArray(Array *th, char *buf, size_t max_len);

Array *Array_Stringify(Array *th, unsigned int flags);

HEACT Array *Array_getElementByName(Array *head, const char *name);
HEACT Array *Array_getElementByNameCust(Array *head, const char *name, int(*cmp)(const char *a, const char *b));
Array *Array_getElementByValueCust(Array *head, const void *needle, int (*cmp)(const void *a,const void *b, const char type));
Array *Array_getElementByStringValue(Array *head, char *val);
//HEACT Array *Array_getElementById(Array *head, size_t id);
//HEACT Array *Array_seek(Array *head, size_t count, char where);
HEACT Array *Array_create(Array *head, char *name, void *v, Array_T t, size_t len);

HEACT Array *Array_column(Array *i, char *v, char *k);
HEACT Array *Array_keys(Array *head);
HEACT void Array_Print(Array *head, size_t tab);
#define Array_print(head) Array_Print(head, 0)

size_t Array_foreach(Array *head, int (*callback)(const Array *));
size_t Array_foreachOpt(Array *head, void *opt, int (*callback)(Array *, void *opt));
size_t Array_implode(Array *th, const char *divider, char *buf, size_t max_len);
size_t Array_getValueListString(Array *th, char *buf, size_t max_len, const char *divider[5], unsigned int flags, size_t(*)(Array *, char *, size_t));
size_t Array_getKeyValueListString(Array *th, char *buf, size_t max_len, const char *divider[6], unsigned int flags, size_t(*)(Array *, char *, size_t));

Array *Array_getElementByNameOOP(Array *head, const char *name);
char *Array_getElementStringValByNameOOP(Array *head, const char *name);

Array *Array_append(Array *head, Array *ele);
Array *Array_slice(Array *head, size_t n);

inline static Array *Array_getElementById(Array *head, size_t id) {
	for (;head && head->i < id; head = head->next);
	if (head && id == head->i) {
		return head;
	}
	return NULL;
}

Array *Array_seek(Array *head, size_t count, char where);

inline static Array *Array_reindex(Array *head, size_t start) {
	Array *h=head;
	for (; head; head=head->next) {
		head->i = start++;
	}
	return h;
}

inline static Array *Array_clone(Array *head, Array *ptr) {
	if (ptr)
		return Array_create(head, (char *)ptr->name, ptr->v, (Array_T)ptr->t, ptr->len);
	else
		return head;
}

inline static char *Array_getElementStringValByName(Array *head, char *name) {
	Array *str = Array_getElementByName(head, name);
	if(str && str->t == ARRAY_STRING)
		return (char *)str->v;
	return NULL;
}

inline static size_t Array_getValueListStringQ(Array *th, char *buf, size_t max_len, const char *divider[5], unsigned int flags){
	return Array_getValueListString(th, buf, max_len, divider, flags,NULL);
}
inline static size_t Array_getKeyValueListStringQ(Array *th, char *buf, size_t max_len, const char *divider[6], unsigned int flags) {
	return Array_getKeyValueListString(th, buf, max_len, divider, flags, NULL);
}
inline static size_t Array_getValueJSONArray(Array *th, char *buf, size_t max_len) {
	const char *div[] = { "{","," ,"}" ,":","\"","\""};
	return Array_getKeyValueListStringQ(th, buf, max_len, div,0);
}

inline static size_t Array_getValueStringArray(Array *th, char *buf, size_t max_len) {
	const char *div[] = { "[","=" ,"]" ,"'","'"};
	return Array_getValueListStringQ(th, buf, max_len, div,0);
}

inline static Array *Array_createString(Array *th, char *name, char *val) {
	return Array_create(th, name, val, ARRAY_STRING, 0);
}

inline static Array *Array_createStringById(Array *th, size_t id, char *name, char *val) {
	return Array_setElementById(th, id, name, val, ARRAY_STRING, 0);
}

inline static Array *Array_createSubArray(Array *th, char *name, Array *v) {
	if (name) {
		Array *entry=Array_getElementByName(th, name);
		if (entry) {
			return Array_append(entry, v);
		}
	}
	return Array_create(th, name, v, ARRAY_ARRAY, 0);
}

inline static Array *Array_insertNoCheck(Array *subject, void *v, Array_T t, size_t len) {
	Array *e = Array_seek(subject, 0, SEEK_END);
	return Array_create(e, NULL, v, t, len);
}

inline size_t Array_serializeSize(Array *head) {
	size_t len=0, v_len=0;
	while (head) {
		if (head->t == ARRAY_STRING) {
			v_len += head->len + 1;
		}
		else if (head->t == ARRAY_ARRAY) {
			v_len += Array_serializeSize((Array *)head->v);
		}
		else if (head->t != ARRAY_OBJECT || (head->t == ARRAY_OBJECT && head->len > 0)) {
			v_len += head->len;
		}
		v_len += head->len_name + 1;
		len++;
		head = head->next;
	}
	return len;
}

//#ifdef __cplusplus
//}
//#endif//__cplusplus

#endif