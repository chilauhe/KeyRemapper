#ifndef __ARRAYTREE_H__
#define __ARRAYTREE_H__ 1
#include "heact.h"

typedef struct _ArrayTree {
	uint32_t key;
	Array *v;
	struct _ArrayTree *child;
	struct _ArrayTree *next;
} ArrayTree;

ArrayTree *ArrayTree_new(void);
void ArrayTree_destory(ArrayTree *v);
ArrayTree *ArrayTree_findKey(ArrayTree *v, uint32_t key);
ArrayTree *ArrayTree_SeekEnd(ArrayTree *v);

ArrayTree *ArrayTree_insertOrdered(ArrayTree *iv, ArrayTree *ele);

ArrayTree *ArrayTree_makeByName(ArrayTree *v, Array *a);

Array *ArrayTree_findByName(ArrayTree *v, char *name);
#endif