#ifndef __HEACT_RAND_H__ 
#define __HEACT_RAND_H__ 1
#include <stdint.h>

#define SEED_STDLIB
void he_srand();

uint32_t he_rand(void);
inline static uint32_t he_rand_between(uint32_t a, uint32_t b) {
	return he_rand() % (b-a) + a;
}
#endif
