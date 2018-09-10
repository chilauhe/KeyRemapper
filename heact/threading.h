#ifndef __THREADING_H__
#define __THREADING_H__ 1

#ifdef _WIN32
typedef size_t he_tid;
#else
#define HAVE_PTHREAD
#include <pthread.h>
typedef pthread_t he_tid;
#endif

typedef void(*PROC_THREAD)(void *);

typedef struct {
	size_t s;
	struct timeval timeout;
	void(*f)(void *);
} SELECT_INFO;

void he_select_proc(SELECT_INFO *s);
he_tid he_CreateThread(void(*FUNC)(void *), void *PARM);
void he_TerminateThread(he_tid v);

#endif
