#ifndef __PERFMON_H__
#define __PERFMON_H__ 1
#include "heact.h"

typedef struct _TimeInterval {
	uint64_t begin;
	uint64_t end;
} TimeInterval;
#define ZERO_TIMEINTERVAL(v) {(v).begin=0;(v).end=0;}

size_t getPeakRSS();
size_t getCurrentRSS();
uint64_t GetTimeMs64();
uint64_t SetTimeLapsed(TimeInterval *);

#endif
